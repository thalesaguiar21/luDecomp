#include <iostream>
#include <iomanip>
#include <locale>
#include <math.h>
#include "luDecomp.h"


using std::cout;
using std::cin;
using std::endl;

double ** makeMatrix(int row, int col){
	cout << "\nCriando uma nova matriz...\n";
	double **newMatrix = new double*[row];
	for(int i = 0; i < row; i++){
		newMatrix[i] = new double[col];
	}
	return newMatrix;
}

void initMatrix(int row, int col, double **matrix, double option){
	cout << "\nInicializando a matrix...\n";
	if(option == 1){
		for(int i = 0; i < row; i++){
			for(int j = 0; j < col; j++){
				if(i != j)
					matrix[i][j] = 0.0;
				else
					matrix[i][j] = 1.0;
			}
		}
	}
	else if(option == 0){
		for(int i = 0; i < row; i++){
			for(int j = 0; j < col; j++){
				matrix[i][j] = 0.0;
			}
		}
	}
	else{
		cout << "Digite os valores da matrix por linha...\n";
		for(int i = 0; i < row; i++){
			for(int j = 0; j < col; j++){
				cin >> matrix[i][j];
			}
		}
	}
}

void destroyMatrix(int row, double **matrix){
	for(int i = 0; i < row; i++)
		delete []matrix[i];
	delete matrix;
	cout << "\nA matriz foi destruida...\n";
}

void printMatrix(int row, int col, double **matrix){
	cout << endl;
	if(row < 0 || col < 0){
		cout << "\nAs dimensões da matriz devem ser positivas...\n";
		return;
	}
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			cout << std::setw(18) << matrix[i][j];
		}
		cout << "\n";
	}
}

void printMatrix(int row, int col, double *matrix){
	cout << endl;
	if(row < 0 || col < 0){
		cout << "\nAs dimensões da matriz devem ser positivas...\n";
		return;
	}
	if(row == 0 && col > 0){
		for(int j = 0; j < col; j++){
			cout << std::setw(18) << matrix[j] << endl;
		}
	}
	else if(row > 0 && col == 0){
		for(int j = 0; j < col; j++){
			cout << std::setw(18) << matrix[j];
		}
	}
	else{
		cout << "\nA matriz não é do tipo linha ou coluna...\n";
	}
}

double ** transposeMatrix(int row, int col, double **matrix){
	if(row < 0 || col < 0)	return NULL;

	double **tMatrix = makeMatrix(col, row);
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			tMatrix[i][j] = matrix[j][i];
		}
	}

	return tMatrix;
}

void fatLU(int row, int col, double **matrix, double *constTerms){
	luDecomp(row, col, matrix, constTerms, true);
	cout << "\nVerificando se o sistema é determinado...\n";
	for(int i = 0; i < col; i++){
		if(matrix[i][i] == 0){
			cout << "\nO sistema não é determinado...\n";
			return;
		}
	}
	progresSub(row, col, matrix, constTerms);
	double *result = regresSub(row, col, matrix, constTerms);
	cout << "\nA solução do sistema é:\n";
	printMatrix(0, col, result);
	delete []result;
}

void luDecomp(int row, int col, double **matrix, double *constTerms, bool doPivoting){
	cout <<  "\nDecompondo a matriz em fatores LU...\n";
	for(int k = 0; k < row-1; k++){
		if(doPivoting = true)	partPivo(row, col, matrix, k);
		for(int i = k+1; i < col; i++){
			double factor = -(matrix[i][k] / matrix[k][k]);
			for(int j = k+1; j < col; j++){
				matrix[i][j] += factor * matrix[k][j];
			}
			matrix[i][k] = factor;
		}
		printMatrix(row, col, matrix);
	}
}

void partPivo(int row, int col, double **matrix, int pivoCol){
	cout << "\nExecutando o pivotamento parcial na coluna " << pivoCol + 1 <<endl;
	double pivo = matrix[pivoCol][pivoCol];
	for(int i = pivoCol+1; i < row; i++){
		if(abs(matrix[i][pivoCol]) > abs(pivo)){
			cout << "\nTrocando a linha " << i << " por " << pivoCol <<endl;
			pivo = matrix[i][pivoCol];
			for(int j = 0; j < col; j++){
				double aux = matrix[pivoCol][j];
				matrix[pivoCol][j] = matrix[i][j];
				matrix[i][j] = aux;
			}
		}
	}
}

double abs(double number){
	if(number < 0)
		return -number;
	else
		return number;
}

void progresSub(int row, int col, double **matrix, double *constTerms){
	cout << "\nExecutando a substituição progressiva...\n";
	for(int i = 0; i < row; i++){
		double sum = constTerms[i];
		for(int j = 0; j < i; j++)
			sum -= matrix[i][j] * constTerms[j];
		constTerms[i] = sum;
	}
}

double * regresSub(int row, int col, double **matrix, double *constTerms){
	double *result = new double[row];
	cout << "\nExecutando a substituição regrssiva...\n";
	result[row-1] = (double)(constTerms[col-1]/matrix[row-1][col-1]);
	for(int i = row-1; i > -1; i--){
		double sum = 0;
		for(int j = i+1; j < col; j++)
			sum += matrix[i][j] * result[j];
		result[i] = (constTerms[i] - sum) / matrix[i][i];
	}

	return result;
}

void choleskyDecomp(int row, int col, double **matrix, double *constTerms){
	double **dMatrix = makeMatrix(row, col);
	double *result = new double(row);
	if(!isSymetric(row, col, matrix))
		return;
	luDecomp(row, col, matrix, constTerms);


	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			if(i == j){
				if(matrix[i][j] < 0){
					cout << "\nA matriz não é positiva definida...\n";
					return;
				}
				else if(matrix[i][j] == 0){
					cout << "\nO sistema não é determinado...\n";
					return;
				}
				else
					matrix[i][j] = 1;
			}
			else if(i < j){
				matrix[i][j] = 0;
			}
		}
	}

	progresSub(row, col, matrix, constTerms);

	double **algumaCoisa = transposeMatrix(row, col, matrix);

	result = regresSub(row, col, algumaCoisa, constTerms);

	printMatrix(0, col, result);

	destroyMatrix(row, dMatrix);
	delete []result;
}

bool isSymetric(int row, int col, double **matrix){
	cout << "\nVerificando a simetria da matriz...\n";
	if(row != col){
		cout << "\nA matriz não é simétrica...\n";
		return false;
	} 
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			if(i != j){
				if(matrix[i][j] != matrix[j][i]){
					cout << "\nA matriz não é simétrica...\n";
					return false;
				}
			}
		}
	}
	cout << "\nA matriz é simétrica...\n";
	return true;
}

void copyVector( int row, double *x, double *y){
	for( int i(0) ; i<row ; i++ ){
		y[i] = x[i];
	}
	return;
}

double norma(int row, double *x){
	double acumulate(0);
	for(int i(0) ; i<row ; i++){
		acumulate += x[i]*x[i];
	}
	return sqrt(acumulate);
}

double gausSeidel(int row,int col, double **matrix, double *x, double* b, double erro){
	double err=99999;
	double *xAnterior = new double[col];
	double *xs = new double[col];
	copyVector(col, x, xs);
	while( err>erro ){
		copyVector(col, x, (double*)xAnterior);
		for( int i(0) ; i<row ; i++ ){
			double value(b[i]);
			for( int j(0) ; j<i ; j++ ){
				value -= matrix[i][j]*xs[j];
			}
			for( int j(i+1) ; j<col ; j++ ){
				value -= matrix[i][j]*x[j];
			}
			xs[i] = value/matrix[i][i];
			//std::cout << "X[" << i << "] = " << x[i] << std::endl;
		}
		copyVector(col, xs, x);
		double test[col];
		for( int j(0); j<col ; j++ ){
			test[j] = x[j]-xAnterior[j];
			//std::cout << "test[" << j << "] = " << x[j] << " - " << xAnterior[j] << " = " << test[j] << std::endl;
		}
		err = norma(col, test);
		//std::cout << "ERRO = " << err << std::endl;
	}
	copyVector(col, (double*)xAnterior, x);
	delete [] xAnterior;
	delete [] xs;
	return err;
}