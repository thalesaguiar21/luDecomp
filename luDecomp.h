#ifndef LUDECOMP_H
#define LUDECOMP_H

/*
	Alocates space for a new matrix of order rowxcol.
*/
float ** makeMatrix(int row, int col);


/*
	Initialize the given matrix.
	Option = 0 -> null matrix.
	Option = 1 -> identity matrix.
	Other case -> input a matrix line by line.
*/
void initMatrix(int row, int col, float **matrix, float option = 0);


/*
	Free the space of the given matrix;
*/
void destroyMatrix(int row, float **matrix);


/*
	Prints the given matrix line by line.
*/
void printMatrix(int row, int col, float **matrix);


void printMatrix(int row, int col, float *matrix);

/*
	Return the absolute value of a float.
*/
float abs(float number);


/*
	Makes a partial pivoting on the given matrix at the given col(pivoCol).
*/
void partPivo(int row, int col, float **matrix, int pivoCol);

//regressiveSub()

//progressiveSub()

void luDecomp(int row, int col, float **matrix, float *constantTerms);

/*
	Return true if the matrix is symetric, and false otherwise.
*/
bool isSymetric(int row, int col, float **matrix);



#endif