

/**
 * fichier:Cluster.h
 * auteur: Rambal Julien
 * description : Tout ce qui est necessaire pour clusteuriser le graph avec les structures sous jacentes qui vont avec  
 **/




#ifndef Cluster_h
#define Cluster_h


#include "eispack.h"
#include "kmeans.h"
//#include "qnorm.c"
#include "ParserJ.h"

#include"my-util.h"
#include "tableau.h"
#include "algebre.h"
#include "ColorParam.h"
#include <gsl/gsl_sf_bessel.h>
#include <gsl/gsl_cdf.h>
#include<string.h>
#include <stdlib.h> 
#include <math.h>

#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>


#define DEBUG_CL 0 
#define debug_cluster 0 

#define DEFAULT_NB_CLUSTER 3 
#define DEFAULT_MAX_ITER 100 
#define defaultCluster() 0  




struct myPoint** initCentroid (  struct myPoint ** points , size_t taille , size_t dim ,size_t nb_cluster  );
struct myPoint** initCentroid2 (  struct myPoint ** points , size_t taille , size_t dim ,size_t nb_cluster  );



double d_distance(const Pointer a, const Pointer b);

void d_centroid(const Pointer * objs, const int * clusters, size_t num_objs, int cluster, Pointer centroid);


struct myPoint ** centree(struct myPoint ** points , size_t taille );
void minDist ( struct myPoint** points ,  struct myPoint** points2  , size_t taille ,size_t taille2 );
int*  maxDegreeCluster(int*idCluster,int * tabEdges,size_t taille , size_t taille2);
int eigenDecomp(struct GraphData * _graphD, double** eigen_vectors , double** eigen_values );

struct ClusteringParam {

    struct GraphData * graphD;
    int nb_cluster;
    int max_iteration;
    int strategie;
};
char* idClusterDelim2();
struct ClusteringParam * base_ClusteringParam (struct GraphData * _graphD);
struct ClusteringParam * cstdef_ClusteringParam(struct GraphData * _graphD);
struct ClusteringParam * cst_ClusteringParam(struct GraphData * _graphD,int _nbCluster,int _maxIteration);
char* idClusterTab  ( int* tab , size_t  squareTaille , int color_cnt ,const char  concatEndDelim  ,int idCluster   ,int select );
kmeans_config*  base_KmeansParam (struct myPoint** PopV  , size_t taille_pop );
kmeans_config* cstdef_ConfigKmeans(struct myPoint** PopV  , size_t taille_pop   );
kmeans_config* cst_ConfigKmeans(struct myPoint** PopV  , size_t taille_pop   , size_t dim , int select );

int checkClusteringParam(struct ClusteringParam* params);
int* makeClusters(struct ClusteringParam* params );

char* idClusterStr  ( char* str ,int idCluster   );

 struct ClusterMeta{

 	int nb_cluster;
    int* cluster1D;
 	int**cluster2DTaille;
 	int** cluster2DTrad;
 	int*** cluster2DdjMat;
    struct ColorationResult ** bestColoring ; 
 };

struct ClusterMeta *  base_ClusterMeta();
void initClusterMeta (struct ClusteringParam* params , struct ClusterMeta * cluster );


char* idClusterTabTab (int** tabTab, size_t taille2 , size_t taille , const char * concatEndDelim , int idmax ,int select, int idCluster );
char* idClusterAdjMat (int** adjMat , size_t squareTaille  ,const char * concatEndDelim ,  int idCluster , int select );

const char idClusterDelim();

//const char * clusterMatAdjDelim();



int* nbPerCluster ( int* cluster , size_t taille , int nb_cluster );
int closestPower2( int val );

void classCluster (int*** tab ,  int* cluster ,size_t taille, int nb_cluster, int*** tab_tailleAndIndex );
int intComparator ( const void * first, const void * second );
int isIn ( int* tab , int val , size_t taille  );

void adjCluster( int** adj , size_t taille1 ,  int nb_cluster  ,int**tab_tailleAndIndex , int** trad_cluster , int*** resultat );
void adjClusterGraph( struct GraphData *graph , struct ClusterMeta * cluster );



#endif /*mat_h */
