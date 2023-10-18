/**
 * fichier:Point.c
 * auteur: Rambal Julien
 * description : Implemente un point ou un nuage de point sans fonction supplémentaire 
 **/


#ifndef Point_h
#define Point_h

#include <stdio.h> 
#include <stdlib.h>
#include<string.h>
#include <errno.h>
#include "tableau.h"
#include"my-util.h"


#define  myArray myPoint // forgive me 

struct myArray {
	double* arr ; //void* chaine de (arr,taille) quand arr=null alors le most inner array etait le precdent 
	size_t taille ;

};



struct myPoint* Point(size_t taille );

void printPoint(struct myPoint * pt);

void printTabPoint(struct myPoint ** pts , size_t taille );
struct myPoint* arrToPointCpy(double * arr , size_t taille);


struct myPoint* arrToPoint(double * arr , size_t taille);


struct myPoint ** initCollectionPoint(size_t taille , size_t dim);

/*

double** affinityMatrix ( )//TODO ajoute fonction de distance squared par defaut euclidean squared
{



}*/

struct myPoint ** collectionPointCpy(double** points , size_t taille , size_t dim);


struct myPoint ** collectionPoint(double** points , size_t taille , size_t dim);

#endif