#include <iostream>
#include "luDecomp.h"
#define COL 3
#define ROW 3
int main(){
	float **myMatrix = makeMatrix(ROW, COL);
	float *myConstTerms = new float[ROW];

	myMatrix[0][0] = 1;
	myMatrix[0][1] = 2;
	myMatrix[0][2] = 3;
	myMatrix[1][0] = 4;
	myMatrix[1][1] = 5;
	myMatrix[1][2] = 6;
	myMatrix[2][0] = 7;
	myMatrix[2][1] = 8;
	myMatrix[2][2] = 9;

	myConstTerms[0] = 1;
	myConstTerms[1] = 2;
	myConstTerms[2] = 3;

	printMatrix(ROW, COL,myMatrix);
	printMatrix(0, COL, myConstTerms);

	return 0;
}