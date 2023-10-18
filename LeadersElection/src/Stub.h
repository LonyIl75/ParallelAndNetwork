/**
 * fichier: Stub.h
 * auteur: Rambal Julien
 * description : (Stub ) Fichier  pour remplacer certaine partie de code 
 **/

#ifndef STUB_H
#define STUB_H
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

int **  allocation_matrix( int  sz_row , int sz_col );

void init_bitmatrix(  int ** matrix ,int  sz_row , int sz_col );

void init_bitmatrix2(  int ** matrix ,int  sz_row , int sz_col );

void print_matrix (int **matrix , int  sz_row , int sz_col );

#endif