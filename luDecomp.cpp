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
	cout << "\nDestruindo a matriz...\n";
	for(int i = 0; i < row; i++)
		delete []matrix[i];
	delete matrix;
}

void printMatrix(int row, int col, double **matrix){
	if(row < 0 || col < 0){
		cout << "\nAs dimensões da matriz devem ser positivas...\n";
		return;
	}
	cout << "\nA matrix é...\n";
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			cout << std::setw(18) << matrix[i][j];
		}
		cout << "\n";
	}
}

void printMatrix(int row, int col, double *matrix){
	if(row < 0 || col < 0){
		cout << "\nAs dimensões da matriz devem ser positivas...\n";
		return;
	}
	cout << "\nA matriz dos termos independentes é...\n";
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

double * fatLU(int row, int col, double **matrix, double *constTerms){
	luDecompPivo(row, col, matrix, constTerms);
	double *result = PRsubstitution(row, col, matrix, constTerms);
	return result;
}

void luDecomp(int row, int col, double **matrix, double *constTerms){
	cout <<  "\nDecompondo a matriz em fatores LU...\n";
	for(int i = 0; i+1 < row; i++){
		for(int j = i; j+1 < col; j++){
			double factor = (matrix[j+1][i] / matrix[i][i]);
			for(int k= j; k < col; k++)
				matrix[j+1][k] -= factor * matrix[i][k];
			matrix[j+1][i] = -factor;
		}
	}
}

void luDecompPivo(int row, int col, double **matrix, double *constTerms){
	cout <<  "\nDecompondo a matriz em fatores LU...\n";
	for(int i = 0; i+1 < row; i++){
		partPivo(row, col, matrix, i);
		for(int j = i; j+1 < col; j++){
			double factor = (matrix[j+1][i] / matrix[i][i]);
			for(int k= j; k < col; k++)
				matrix[j+1][k] -= factor * matrix[i][k];
			matrix[j+1][i] = factor;
		}
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

double * PRsubstitution(int row, int col, double **matrix, double *constTerms){
	double *result = new double[row];

	cout << "\nExecutando a substituição progressiva...\n";
	for(int i = 1; i < row; i++){
		double sum = constTerms[i];
		for(int j = 0; j < i-1; j++)
			sum -= matrix[i][j] * constTerms[j];
		constTerms[i] = sum;
	}

	cout << "\nExecutando a substituição regrssiva...\n";
	result[row-1] = (double)(constTerms[col-1]/matrix[row-1][col-1]);
	for(int i = row-1; i >= 0; i--){
		double sum = 0;
		for(int j = i+1; j < col; j++)
			sum += matrix[i][j] * result[j];
		result[i] = (constTerms[i] - sum) / matrix[i][i];
	}

	return result;
}

void choleskyDecomp(int row,int col, double **matrix, double *constTerms){
	double **dMatrix = makeMatrix(row, col);

	if(!isSymetric(row, col, matrix))
		return;

	luDecomp(row, col, matrix, constTerms);

	printMatrix(row, col, matrix);

	cout << "\nVerificando se a matriz é positiva definida...\n";
	for(int i=0; i<row; i++){
		if(matrix[i][i] < 0){
			cout << "\nA matriz não é positiva definida...\n";
			delete []dMatrix;
			return;
		}
		else{
			dMatrix[i][i] = 1/sqrt(matrix[i][i]);
			matrix[i][i] = 1;
		}
		for(int j=0; j<col; j++){
			if(i != j){
				dMatrix[i][j] = 0;
				if(i > j)
					matrix[i][j] = 0;
			}			
		}
	}

	destroyMatrix(row, dMatrix);
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