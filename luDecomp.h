#ifndef LUDECOMP_H
#define LUDECOMP_H

/*	Alocates space for a new matrix of order row x col.*/
float ** makeMatrix(int row, int col);


/*Initialize the given matrix.
  Option = 0 -> null matrix.
  Option = 1 -> identity matrix.
  Other case -> input a matrix line by line.*/
void initMatrix(int row, int col, float **matrix, float option = 0);


/* Free the space of the given matrix */
void destroyMatrix(int row, float **matrix);


/* Prints the given matrix line by line. */
void printMatrix(int row, int col, float **matrix);


void printMatrix(int row, int col, float *matrix);


/* Return the absolute value of a float. */
float abs(float number);


/* Makes a partial pivoting on the given matrix at the given col(pivoCol).*/
void partPivo(int row, int col, float **matrix, int pivoCol);


/* Makes a regressive substitution considering **matrix and *constTerms.
   Note that the snumber of lines of *constTerms must be the same of **matrix*/
float * regressiveSub(int row, int col, float **matrix, float *constTerms);

void choleskyDecomp(int row,int col, float **matrix);


/* Make a LU decomposition on the **matrix and *constTermas.
   The L matrix is stored under the main diagonal of **matrix.*/
void luDecomp(int row, int col, float **matrix, float *constTerms);

float * fatLU(int row, int col, float **matrix, float *constTerms);


/* Return true if the matrix is symetric, and false otherwise.*/
bool isSymetric(int row, int col, float **matrix);

/**/
double gausSeidel(int row,int col, float **matrix, float *x, float* b, double erro);

/* Make a copy of vector x on vector y (theys must have the same size).*/
void copyVector( int row, float *x, float *y);

/* Calculate the norm of vector x.*/
double norma(int row, float *x);


#endif