#ifndef LUDECOMP_H
#define LUDECOMP_H

/* Execute the Gauss-Seidel algorithm under the matrix... */
double gausSeidel(int row,int col, double **matrix, double *x, double* b, double erro);

/* Execute the Cholesky decomposition in the matrix, wih the constant terms (constTerms).
   This function checks if the matrix is symetric and positive defined. If one of these
   tests fail, the function will stop.*/
void choleskyDecomp(int row, int col, double **matrix, double *constTerms);

/* Make a LU decomposition on the matrix and constTerms. This function
   will test if the system has a single unique solution, otherwise the function will stop. */
void fatLU(int row, int col, double **matrix, double *constTerms);

/*	Alocates space for a new matrix of order row x col.*/
double ** makeMatrix(int row, int col);

/*Initialize the given matrix.
  Option = 0 -> null matrix.
  Option = 1 -> identity matrix.
  Other case -> input a matrix line by line.*/
void initMatrix(int row, int col, double **matrix, double option = 0);

/* Free the memory allocated for the matrix */
void destroyMatrix(int row, double **matrix);

/* Prints the matrix line by line. */
void printMatrix(int row, int col, double **matrix);

/* Prints a vector */
void printMatrix(int row, int col, double *matrix);

/* Returns a transposed matrix of the matrix */
double ** transposeMatrix(int row, int col, double **matrix);

/* Return the absolute value of a double. */
double abs(double number);

/* Makes a partial pivoting on the given matrix at the given col(pivoCol).*/
void partPivo(int row, int col, double **matrix, int pivoCol);

/* Return true if the matrix is symetric, and false otherwise.*/
bool isSymetric(int row, int col, double **matrix);

/* Make a LU decomposition on the **matrix and *constTermas.
   The L matrix is stored under the main diagonal of **matrix.*/
void luDecomp(int row, int col, double **matrix, double *constTerms, bool doPivoting = false);

/* Execute a progressive substitution with the **matrix and the *constTerms
   Note that *constTerms and **matrix must have the same number of lines. */
void progresSub(int row, int col, double **matrix, double *constTerms);

/* Execute a regressive substitution with the **matrix and the *constTerms
   Note that *constTerms and **matrix must have the same number of lines.
   Returns the result of the system */
double * regresSub(int row, int col, double **matrix, double *constTerms);

/* Make a copy of vector x on vector y (theys must have the same size).*/
void copyVector( int row, double *x, double *y);

/* Calculate the norm of vector x.*/
double norma(int row, double *x);




#endif