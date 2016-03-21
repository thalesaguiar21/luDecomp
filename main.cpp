#include <iostream>
#include "luDecomp.h"
#define COL 3
#define ROW 3

int main(){
	double **myMatrix = makeMatrix(ROW, COL);
	double *myConstTerms = new double[ROW];
	double *result = new double[ROW];
	
	myMatrix[0][0] = 4;
	myMatrix[0][1] = 1;
	myMatrix[0][2] = -1;
	myMatrix[1][0] = 2;
	myMatrix[1][1] = 6;
	myMatrix[1][2] = -3;
	myMatrix[2][0] = -1;
	myMatrix[2][1] = -2;
	myMatrix[2][2] = 6;

	myConstTerms[0] = 4;
	myConstTerms[1] = 5;
	myConstTerms[2] = 3;

	printMatrix(ROW, COL, myMatrix);
	printMatrix(0, COL, myConstTerms);
	result = fatLU(ROW, COL, myMatrix, myConstTerms);
	printMatrix(0, COL, result);
	//choleskyDecomp(ROW, COL, myMatrix, myConstTerms);


	destroyMatrix(ROW, myMatrix);
	std::cout << "\nDestruindo o resto das coisas...\n";
	delete []myConstTerms;
	delete []result;
	return 0;
}