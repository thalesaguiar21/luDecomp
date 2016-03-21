#include <iostream>
#include <iomanip>
#include <locale>
#include <math.h>
#include "luDecomp.h"


using std::cout;
using std::cin;
using std::endl;

float ** makeMatrix(int row, int col){
	cout << "\nCriando uma nova matriz...\n";
	float **newMatrix = new float*[row];
	for(int i = 0; i < row; i++){
		newMatrix[i] = new float[col];
	}
	return newMatrix;
}

void initMatrix(int row, int col, float **matrix, float option){
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

void destroyMatrix(int row, float **matrix){
	cout << "\nDestruindo a matriz...\n";
	for(int i = 0; i < row; i++)
		delete []matrix[i];
	delete matrix;
}

void printMatrix(int row, int col, float **matrix){
	if(row < 0 || col < 0){
		cout << "\nAs dimensões da matriz devem ser positivas...\n";
		return;
	}
	cout << "\nA matrix é...\n";
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			cout << std::setw(12) << matrix[i][j];
		}
		cout << "\n";
	}
}

void printMatrix(int row, int col, float *matrix){
	if(row < 0 || col < 0){
		cout << "\nAs dimensões da matriz devem ser positivas...\n";
		return;
	}
	cout << "\nA matriz dos termos independentes é...\n";
	if(row == 0 && col > 0){
		for(int j = 0; j < col; j++){
			cout << std::setw(12) << matrix[j] << endl;
		}
	}
	else if(row > 0 && col == 0){
		for(int j = 0; j < col; j++){
			cout << std::setw(12) << matrix[j];
		}
	}
	else{
		cout << "\nA matriz não é do tipo linha ou coluna...\n";
	}
}

float * fatLU(int row, int col, float **matrix, float *constTerms){
	luDecomp(row, col, matrix, constTerms);
	float *result = PRsubstitution(row, col, matrix, constTerms);
	return result;
}

void luDecomp(int row, int col, float **matrix, float *constTerms){
	cout <<  "\nDecompondo a matriz em fatores LU...\n";
	for(int i = 0; i+1 < row; i++){
		partPivo(row, col, matrix, i);
		for(int j = i; j+1<col; j++){
			float factor = (matrix[j+1][i] / matrix[i][i]);
			for(int k=j; k<col; k++)
				matrix[j+1][k] -= factor * matrix[i][k];
			matrix[j+1][i] = factor;
		}
	}
}

void partPivo(int row, int col, float **matrix, int pivoCol){
	cout << "\nExecutando o pivotamento parcial na coluna " << pivoCol + 1 <<endl;
	float pivo = matrix[pivoCol][pivoCol];
	for(int i = pivoCol+1; i < row; i++){
		if(abs(matrix[i][pivoCol]) > abs(pivo)){
			pivo = matrix[i][pivoCol];
			for(int j = 0; j < col; j++){
				float aux = matrix[pivoCol][j];
				matrix[pivoCol][j] = matrix[i][j];
				matrix[i][j] = aux;
			}
		}
	}
}

float abs(float number){
	if(number < 0)
		return -number;
	else
		return number;
}

float * PRsubstitution(int row, int col, float **matrix, float *constTerms){
	float *result = new float[row];

	cout << "\nExecutando a substituição progressiva...\n";
	for(int i = 1; i < row; i++){
		float sum = constTerms[i];
		for(int j = 0; j < i-1; j++)
			sum -= matrix[i][j] * constTerms[j];
		constTerms[i] = sum;
	}

	cout << "\nExecutando a substituição regrssiva...\n";
	result[row-1] = (float)(constTerms[col-1]/matrix[row-1][col-1]);
	for(int i = row-1; i >= 0; i--){
		float sum = 0;
		for(int j = i+1; j < col; j++)
			sum += matrix[i][j] * result[j];
		result[i] = (constTerms[i] - sum) / matrix[i][i];
	}

	return result;
}

void choleskyDecomp(int row,int col, float **matrix, float *constTerms){
	float *dMatrix = new float[row];

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
			cout << "A matriz é positiva definida...\n";
			dMatrix[i] = sqrt(matrix[i][i]);
			matrix[i][i] = 1;
		}
		for(int j=i; j<col; j++){
			matrix[i][j] = 0;
		}
	}

	delete []dMatrix;
}

bool isSymetric(int row, int col, float **matrix){
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

void copyVector( int row, float *x, float *y){
	for( int i(0) ; i<row ; i++ ){
		y[i] = x[i];
	}
	return;
}

double norma(int row, float *x){
	double acumulate(0);
	for(int i(0) ; i<row ; i++){
		acumulate += x[i]*x[i];
	}
	return sqrt(acumulate);
}

double gausSeidel(int row,int col, float **matrix, float *x, float* b, double erro){
	double err=99999;
	float *xAnterior = new float[col];
	float *xs = new float[col];
	copyVector(col, x, xs);
	while( err>erro ){
		copyVector(col, x, (float*)xAnterior);
		for( int i(0) ; i<row ; i++ ){
			float value(b[i]);
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
		float test[col];
		for( int j(0); j<col ; j++ ){
			test[j] = x[j]-xAnterior[j];
			//std::cout << "test[" << j << "] = " << x[j] << " - " << xAnterior[j] << " = " << test[j] << std::endl;
		}
		err = norma(col, test);
		//std::cout << "ERRO = " << err << std::endl;
	}
	copyVector(col, (float*)xAnterior, x);
	delete [] xAnterior;
	delete [] xs;
	return err;
}