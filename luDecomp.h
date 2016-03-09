#ifndef LUDECOMP_H
#define LUDECOMP_H

float ** makeMatrix(int row, int col);

/*
Option = 0 -> null matrix
Option = 1 -> identity matrix
Other case -> input a matrix line by line
*/
void initMatrix(int row, int col, float **matrix, float option = 0);

void destroyMatrix(int row, float **matrix);

void printMatrix(int row, int col, float **matrix);

float abs(float number);

void partPivo(int row, int col, float **matrix, int pivoCol);

//regressiveSub()

//progressiveSub()

//void luDecomp(int row, int col, float **matrix);



#endif