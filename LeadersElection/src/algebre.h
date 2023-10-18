#ifndef algebre_h
#define algebre_h


#include <stdio.h> 
#include <stdlib.h>
#include<string.h>
#include <errno.h>
#include "tableau.h"
#include"my-util.h"
#include"Point.h"
#include <assert.h>


#define debug_algebre 0 

int getMatValue(int *mat,int side, int i, int j);

void setSymMatValue(int *mat,int side, int i, int j);
double** convertToDouble ( int** arr , size_t nb_r , size_t nb_c );
double** convertToDoubleSq ( int** arr , size_t square_taille);
double* convertToDouble2Sq ( int** arr , size_t square_taille);

double * convertToUniDir ( double ** arr , size_t nb_r, size_t nb_c );
double * convertToUniDirSq ( double** arr , size_t square_taille);

double ** convertToBiDir ( double * arr , size_t nb_r, size_t nb_c );
double ** convertToBiDirSq ( void * arr , size_t square_taille );

double** toDiagonal(double* arr , size_t taille );



double** substractMatrix(double** mat1 , double** mat2, size_t nb_r , size_t nb_c );
double** substractMatrixSq(double** mat1 , double** mat2, size_t square_taille );

double** addMatrix(double** mat1 , double** mat2, size_t nb_r , size_t nb_c );
double** addMatrixSq(double** mat1 , double** mat2, size_t square_taille );

double** multMatrix(double**  m1 ,double** m2,size_t taille ,size_t dim);
double** multMatrixSq(double**  m1 ,double** m2 ,size_t square_taille  );
 double** multMatrixScalar(double**  m1 ,double scalar ,size_t taille ,size_t dim ) ;
double** multMatrixScalarSq(double**  m1 ,double scalar ,size_t square_taille  );
double* normalizingVector(double* v , size_t taille );
double** normalizingBunchOfVector(double** vs , size_t taille , int* tab_taille  );
double** diagPowerCpy (double** mat , double power , size_t nb_r ,size_t nb_c  );
double** diagPowerCpySq (double** mat , double power , size_t square_taille );

void diagPower(double** mat , double power , size_t nb_r ,size_t nb_c  );
void diagPowerSq (double** mat , double power , size_t square_taille );

double squaredEDist( double * pt1 , double *pt2 , size_t taille);
double EDist( double * pt1 , double * pt2 , size_t taille );

double pnorm(double* x, int n, double p);
double squaredFrobeniusNorm( double** mat , size_t nb_r , size_t nb_c);

double FrobeniusNorm( double** mat , size_t nb_r , size_t nb_c);
int closestPower2( int val );

//STAT
double * compute_mean ( struct myPoint ** points ,size_t taille , size_t dim);
double *  compute_variance (struct myPoint ** points , size_t taille , size_t dim );
double *  compute_stdDeviation (struct myPoint ** points , size_t taille , size_t dim );

#endif