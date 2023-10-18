
/**
 * fichier: Parser.h
 * auteur: Rambal Julien
 * description : Fichier definissant toutes les composantes essentielles à un GraphData
**/





#ifndef PARSERJ_H
#define PARSERJ_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <ctype.h>
#include "algebre.h"

#include <stdbool.h>
#include <math.h>
#include "my_file.h"


#include <errno.h>
#include "tableau.h"
#include "my-util.h"


#define PARSERJ_MAXS 10000

#define DEBUG_PARSER 0


struct GraphData {
    int ** matrix;
    int nodesQuantity; //NB_NODE
    int  edgesQuantity; 
    int * taille_r;
    int * tabNbEdges;
};





int servWeight();

///////////////////////////////DEBUT JOHNATHAN //////////////////////////////


void freeGraph(struct GraphData * _graph);

struct GraphData * Parsera(const char* _path , const char* filename ) ;



///////////////////////////////FIN JOHNATHAN //////////////////////////////





///////////////////////////////DEBUT JULIEN //////////////////////////////

struct GraphData * init_graphData ( const char * path , const char* filename );

struct GraphData * cst_baseGraphData ( int nodesQuantity );
struct GraphData * cpy_graphData ( struct GraphData * graph);

struct GraphData * graphDataFromAdj ( int ** adjMatrix ,size_t taille_square);
struct GraphData * graphDataCpyFromAdj ( int ** adjMatrix ,size_t taille_square);

struct GraphData* includeServGraphData(struct GraphData * graph);



const char graphParamDelim();

//const char*  graphParamDelims();

char* graphToStr( struct GraphData *  graph);

 struct GraphData * strToGraph(char* str);

///////////////////////////////FIN JULIEN //////////////////////////////


#endif