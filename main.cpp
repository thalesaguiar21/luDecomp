#include <iostream>
#include "luDecomp.h"
#define COL 3
#define ROW 3

int main(){
	float **myMatrix = makeMatrix(ROW, COL);
	float *myConstTerms = new float[ROW];
	float *result = new float[ROW];
	/*
	myMatrix[0][0] = 6;
	myMatrix[0][1] = 15;
	myMatrix[0][2] = 55;
	myMatrix[1][0] = 15;
	myMatrix[1][1] = 55;
	myMatrix[1][2] = 225;
	myMatrix[2][0] = 55;
	myMatrix[2][1] = 225;
	myMatrix[2][2] = 979;

	myConstTerms[0] = 7.85;
	myConstTerms[1] = -19.3;
	myConstTerms[2] = 71.4;*/


	myMatrix[0][0] = 8;
	myMatrix[0][1] = 2;
	myMatrix[0][2] = 2;
	myMatrix[1][0] = 2;
	myMatrix[1][1] = 8;
	myMatrix[1][2] = 2;
	myMatrix[2][0] = 2;
	myMatrix[2][1] = 2;
	myMatrix[2][2] = 8;


	myConstTerms[0] = 20;
	myConstTerms[1] = 26;
	myConstTerms[2] = 38;

	std::cout << "A:\n";
	printMatrix(ROW, COL,myMatrix);
	std::cout << "b:\n";
	printMatrix(0, COL, myConstTerms);
	//choleskyDecomp(ROW, COL, myMatrix);
	//rintMatrix(ROW, COL, myMatrix);

	gausSeidel(ROW, COL, myMatrix, result, myConstTerms, 0.001);
	std::cout << "x:\n";
	printMatrix(0, COL, result);

	destroyMatrix(ROW, myMatrix);
	delete []myConstTerms;
	return 0;
}