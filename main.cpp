#include <iostream>
#include "luDecomp.h"
#define COL 3
#define ROW 3
int main(){
	float **myMatrix = makeMatrix(ROW, COL);
	float *myConstTerms = new float[ROW];

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
	myConstTerms[2] = 71.4;

	printMatrix(ROW, COL,myMatrix);
	choleskyDecomp(ROW, COL, myMatrix);
	printMatrix(ROW, COL, myMatrix);

	//printMatrix(0, COL, result);

	destroyMatrix(ROW, myMatrix);
	delete []myConstTerms;
	return 0;
}