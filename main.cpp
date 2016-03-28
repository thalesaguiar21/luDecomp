#include <iostream>
#include "luDecomp.h"
#define COL 3
#define ROW 3

int main(){
	double **myMatrix = makeMatrix(ROW, COL);
	double *myConstTerms = new double[ROW];
	double *result = new double[ROW];
	
	
	/*//Esse daqui é pra fatoração LU
	myMatrix[0][0] = 3;
	myMatrix[0][1] = -0.1;
	myMatrix[0][2] = -0.2;
	myMatrix[1][0] = 0.1;
	myMatrix[1][1] = 7;
	myMatrix[1][2] = -0.3;
	myMatrix[2][0] = 0.3;
	myMatrix[2][1] = -0.2;
	myMatrix[2][2] = 10;

	myConstTerms[0] = 7.85;
	myConstTerms[1] = -19.3;
	myConstTerms[2] = 71.4;*/

	myMatrix[0][0] = 2;
	myMatrix[0][1] = 3;
	myMatrix[0][2] = -1;
	myMatrix[1][0] = 4;
	myMatrix[1][1] = 1;
	myMatrix[1][2] = 1;
	myMatrix[2][0] = -2;
	myMatrix[2][1] = 1;
	myMatrix[2][2] = 1;

	myConstTerms[0] = 4;
	myConstTerms[1] = 6;
	myConstTerms[2] = 0;

	printMatrix(ROW, COL, myMatrix);
	printMatrix(0, COL, myConstTerms);

	fatLU(ROW, COL, myMatrix, myConstTerms);
	//choleskyDecomp(ROW, COL, myMatrix, myConstTerms);


	destroyMatrix(ROW, myMatrix);
	delete []myConstTerms;
	delete []result;
	return 0;
}