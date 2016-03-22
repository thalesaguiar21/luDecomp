#include <iostream>
#include "luDecomp.h"
#define COL 3
#define ROW 3

int main(){
	double **myMatrix = makeMatrix(ROW, COL);
	double *myConstTerms = new double[ROW];
	double *result = new double[ROW];
	
	/*myMatrix[0][0] = 3;
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

	myMatrix[0][0] = 10;
	myMatrix[0][1] = 20;
	myMatrix[0][2] = 30;
	myMatrix[1][0] = 20;
	myMatrix[1][1] = 45;
	myMatrix[1][2] = 80;
	myMatrix[2][0] = 30;
	myMatrix[2][1] = 80;
	myMatrix[2][2] = 171;

	myConstTerms[0] = 0;
	myConstTerms[1] = 15;
	myConstTerms[2] = 61;

	printMatrix(ROW, COL, myMatrix);
	printMatrix(0, COL, myConstTerms);
	//result = fatLU(ROW, COL, myMatrix, myConstTerms);
	//printMatrix(0, COL, result);
	result = choleskyDecomp(ROW, COL, myMatrix, myConstTerms);
	printMatrix(0, COL, result);


	destroyMatrix(ROW, myMatrix);
	std::cout << "\nDestruindo o resto das coisas...\n";
	delete []myConstTerms;
	delete []result;
	return 0;
}