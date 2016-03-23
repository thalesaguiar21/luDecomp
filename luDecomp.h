#ifndef LUDECOMP_H
#define LUDECOMP_H

/*	Alocates space for a new matrix of order row x col.*/
double ** makeMatrix(int row, int col);


/*Initialize the given matrix.
  Option = 0 -> null matrix.
  Option = 1 -> identity matrix.
  Other case -> input a matrix line by line.*/
void initMatrix(int row, int col, double **matrix, double option = 0);


/* Free the space of the given matrix */
void destroyMatrix(int row, double **matrix);


/* Prints the given matrix line by line. */
void printMatrix(int row, int col, double **matrix);


/* Prints a a vector */
void printMatrix(int row, int col, double *matrix);


/* Return a transposed matrix of the given **matrix */
double ** transposeMatrix(int row, int col, double **matrix);


/* Return the absolute value of a double. */
double abs(double number);


/* Makes a partial pivoting on the given matrix at the given col(pivoCol).*/
void partPivo(int row, int col, double **matrix, int pivoCol);


void choleskyDecomp(int row, int col, double **matrix, double *constTerms);

double ** matrixProd(double **matriz1, int row1, int col1, double **matriz2, int row2, int col2);

double * matrixProd(double **matriz1, int row1, int col1, double *matriz2, int row2);


/* Return true if the matrix is symetric, and false otherwise.*/
bool isSymetric(int row, int col, double **matrix);


/* Make a LU decomposition on the **matrix and *constTermas.
   The L matrix is stored under the main diagonal of **matrix.*/
void luDecomp(int row, int col, double **matrix, double *constTerms);


/* Make a LU decomposition with partial pivoting on the **matrix and *constTermas.
   The L matrix is stored under the main diagonal of **matrix.*/
void luDecompPivo(int row, int col, double **matrix, double *constTerms);


/* Execute a progressive substitution with the **matrix and the *constTerms
   Note that *constTerms and **matrix must have the same number of lines. */
void progresSub(int row, int col, double **matrix, double *constTerms);


/* Execute a regressive substitution with the **matrix and the *constTerms
   Note that *constTerms and **matrix must have the same number of lines.
   Returns the result of the system */
double * regresSub(int row, int col, double **matrix, double *constTerms);


/* Make a LU decomposition on the **matrix and *constTerms. This function
   will test the system. */
void fatLU(int row, int col, double **matrix, double *constTerms);


/**/
double gausSeidel(int row,int col, double **matrix, double *x, double* b, double erro);


/* Make a copy of vector x on vector y (theys must have the same size).*/
void copyVector( int row, double *x, double *y);


/* Calculate the norm of vector x.*/
double norma(int row, double *x);


#endif