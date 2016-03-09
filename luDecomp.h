#ifndef LUDECOMP_H
#define LUDECOMP_H

float ** makeMatrix(int row, int col);

void initMatrix(int row, int col, float **matrix, float option = 0);

void destroyMatrix(int row, float **matrix);

void printMatrix(int row, int col, float **matrix);

void partPivo(int row, int col, float **matrix, int pivoCol);

//regressiveSub()

//progressiveSub()

void luDecomp(int row, int col, float **matrix);



#endif