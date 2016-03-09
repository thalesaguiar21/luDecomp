#include <iostream>
#include "luDecomp.h"
#define ROW 3
#define COL 3

using std::cout;
using std::cin;
using std::endl;


int main(){
	float **myMatrix = makeMatrix(ROW, COL);
	initMatrix(ROW, COL, myMatrix, 10);
	printMatrix(ROW, COL, myMatrix);
	partPivo(ROW, COL, myMatrix, 0);
	printMatrix(ROW, COL, myMatrix);
	destroyMatrix(ROW, myMatrix);
	return 0;
}