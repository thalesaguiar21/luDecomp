#include <iostream>
#include "luDecomp.h"
#define COL 3
#define ROW 3

int main(){
	float **myMatrix = makeMatrix(ROW, COL);
	float *myConstTerms = new float[ROW];
	float *result = new float[ROW];
	
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
	myConstTerms[2] = 71.4;

	std::cout << "A:\n";
	printMatrix(ROW, COL, myMatrix);
	std::cout << "b:\n";
	printMatrix(0, COL, myConstTerms);
	result = fatLU(ROW, COL, myMatrix, myConstTerms);

	printMatrix(0, COL, result);


	destroyMatrix(ROW, myMatrix);
	std::cout << "\nDestruindo o resto das coisas...\n";
	delete []myConstTerms;
	delete []result;
	return 0;
}