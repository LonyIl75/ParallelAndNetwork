

/**
 * fichier:ColorParam.h
 * auteur: Rambal Julien
 * description : Tout ce qui est necessaire pour une coloration de graph
 * 
 **/


#ifndef ColorParam_h
#define ColorParam_h


#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
//#include".h"
#include "ParserJ.h"
#include "algebre.h"
#include "tableau.h"



#define DEFAULT_A  10
#define DEFAULT_ALPHA  0.6
#define DEFAULT_P_MAX 1000
#define DEFAULT_STOP_K  3 
#define DEFAULT_DO_OPT  1
#define MAX_ITERATIONS  10000000
#define DEFAULT_TIMEOUT 600  // in secondes

#define DEBUG_COLOR 0 
#define debug_colorG 0


int sizeofSmallestCliqueDf();



struct ColorationParam {

    struct GraphData * graphD;
    int color_cnt;
    int timeout;
    int A;
    float alpha;
    int p_max;
    bool do_opt;
    int stop_k;
    int* coloring ;
    int* fixed;
};

struct ColorationResult{
    int* coloring ;
    int color_cnt;
    size_t taille ; 
    int conflict ; 

};

void freeColorParam(struct ColorationParam  * cur);
void   process_graph2(struct ColorationResult ** res,struct ColorationParam* colorParam);
int* emptyFixed(size_t taille );

void init_gamma(int** adj_matrix, int** gamma,int* tab_tailleGamma,  int* init_coloring , size_t taille_initColor) ;
int count_conflicts(int** adj_matrix,size_t taille_adj, int* init_coloring) ;
int sizeofSmallestCliqueDf();
double count_conflicts_degree_based(int** adj_matrix,size_t taille , int* init_coloring, int * nb_edges) ;


void  process_graph(struct ColorationResult ** res, struct ColorationParam* colorParam);
//struct GraphData * _graphD, int color_cnt, int timeout, int A, float alpha, int p_max, bool do_opt, int stop_k, int** _coloring ,int* fixed );

//int sec_process_graph(struct GraphData * _graphD, int color_cnt, int timeout, int A, float alpha, int p_max, bool do_opt, int stop_k, int** _coloring ,int* fixed );
struct ColorationParam * base_ColorationParam (struct GraphData * _graphD  );

int* emptyColoring(size_t taille );

struct ColorationParam  * cstdef_ColorationParam(struct GraphData * _graphD);
struct ColorationParam  * cst_ColorationParam(struct GraphData * _graphD, int _colorCnt,const int* _coloring,const int* _fixed );
struct ColorationParam  * cst_ColorationParam2(struct GraphData * _graphD, int _colorCnt, int* _coloring, int* _fixed );

void set_setupColorationParam(struct ColorationParam  * cur , struct ColorationParam  * colorSetup );
const char* reponseColorDelim2();

int checkColorationParam(struct ColorationParam* params);

void color_graph(struct ColorationResult ** res ,struct ColorationParam * params);

//pipeline 
void  mergeColoration( int* accumulator_coloring , int* coloration_cluster , int* trad_cluster,size_t taille_cluster  );


char* setupColorParamToStr(struct ColorationParam *_color);
char* colorParamToStr(struct ColorationParam *_color);

struct ColorationParam* strToColorSetup(char** strToken ,char ** save_ptr);
const char reponseColorDelim();

const  char colorParamDelim();
struct ColorationParam* strToColorParam(char* str );

int* fixed2 (struct GraphData* graph ,  int* trad_cluster );
void  updateBestColor( struct ColorationParam * acc, struct ColorationResult * CR , int* trad_cluster  );

struct ColorationResult * base_colorResult(size_t taille );

struct ColorationResult * cst_colorResult(int* _coloration , int colorCnt,size_t taille , int conflict );

int* andTab(int* tab1 , int *tab2, size_t taille);

int* fixed (int** adj , size_t taille ,  int* cluster1D );

int* andTab(int* tab1 , int *tab2, size_t taille);


const char colorResultDelim();

char*  CRToStr(struct ColorationResult * CR);


#endif