


/**
 * fichier: Parser.c
 * auteur: Rambal Julien (ft BazJo)
 * description : Fichier definissant toutes les composantes essentielles à un GraphData
**/



#include"ParserJ.h"







///////////////////////////////DEBUT JOHNATHAN //////////////////////////////

struct GraphData * Parsera(const char* _path , const char* filename ) {

    FILE *fichierGraph;


    struct GraphData * graph =  (struct GraphData*)malloc(1*sizeof(struct GraphData));//structure qui sera renvoyée
    int flag = 1;
    char line[PARSERJ_MAXS] = {0};//ligne de 0
    char  * path =(char*)malloc(strlen(_path)+1); //AJOUT  JULIEN
    strcpy(path,_path); //AJOUT  JULIEN 
    int vertice1,vertice2,nbVertices,nbEdges;
    int *matrix = NULL;//on initualise le tableau qui simule une matrice en 2 dim grâce a getMat
    int matrixSize = 0;
    path= fusionstr ( path ,filename ,fileSeparator("LINUX") ); //AJOUT  JULIEN

    fichierGraph = fopen(path,"r"); // mieux -> //fichierGraph =open_fichier(path,"r"); 
    if(DEBUG_PARSER)printf("-Debut du parseur \n");

    int*tabNbEdges;

    //Si le fichier n'existe pas
    if(fichierGraph == NULL) {
        printf("\nErreur sur le fichier d'entrée\n\n");
        exit(1);
    }

    
    while(!feof(fichierGraph)) {
        
        
        if(DEBUG_PARSER)printf("-Entrée dans le fichier\n");
        
        //On récupère la ligne
        while (fgets(line,PARSERJ_MAXS,fichierGraph) != NULL) {
            char *p = line;//la ligne
            char * tmp; // la variable qui recevra le strtol()
            size_t len = strlen(line);//taille de la ligne
            

            while(len>0 && (line[len-1] == '\n' || line[len-1] == '\r')){
                line[--len] = 0;

            }

            while(isspace(*p)) p++;

            if(*p == 'c'){//si la ligne est un commentaire 
                //printf("commentaire repéré\n");
                continue;

            // si la ligne est la definition de problème
            }else if(*p == 'p'){
                //printf("parametre repéré\n");
                
                tmp = strtok(line, " ");
                while(tmp != NULL) {
                    if(flag == 3) {//au 3ème espace c'est le nombre de sommets du graph
                        nbVertices = (int)strtol(tmp, &tmp, 10);
                        matrixSize = nbVertices*nbVertices;
                        matrix = malloc((matrixSize+1)*sizeof(int));//on initialise un tablea de taille nbNoeuds*nbNoeuds pour simuler la matrice
                        
                        //AJOUT  JULIEN
                        tabNbEdges = malloc(nbVertices*sizeof(int));//on initialise un tablea de taille nbNoeuds*nbNoeuds pour simuler la matrice
                        for(int i =0; i < nbVertices ;i++)tabNbEdges[i]=0;
                        //FIN AJOUT   JULIEN

                        //on initialise tous les elements de la matrice a 0
                        for(int a;a<matrixSize;a++){ 
                            matrix[a]=0;
                        }
                    }
                    if(flag == 4) {//au 4ème espace c'est le nombre d'arrêtes
                            nbEdges = (int)strtol(tmp, &tmp, 10);
                    }

                    tmp = strtok(NULL, " ");
                    flag++;//un espace de plus a été franchi on augmente flag
                }
                

            // si c'est une ligne definissant une arrête
            }else if(*p == 'e'){ 
                
                tmp = strtok(line, " ");
                flag=1;
                vertice1=0;
                vertice2=0;


                while(tmp != NULL) {
                    if(flag == 2){//on récupère le sommet 1 de l'arrête
                        vertice1=(unsigned int)strtol(tmp,&tmp,10);
                    }else if(flag == 3){//on récupère le sommet 2 de l'arrête
                        vertice2=(unsigned int)strtol(tmp,&tmp,10);
                    }
                    tmp = strtok(NULL, " ");
                    flag++;
                }
                //AJOUT  JULIEN
                 tabNbEdges[vertice1-1]++;
                tabNbEdges[vertice2-1]++;
                //FIN AJOUT   JULIEN

                
                //on remplis la matrice d'adjacence de façon symétrique 
                setSymMatValue(matrix,nbVertices, vertice1,vertice2);   

            }else{

                printf("Ligne ignorée\n");
                
            }            
        }      
    }
   
     graph->nodesQuantity=nbVertices;
    graph->edgesQuantity=nbEdges;
    // AJOUT JULIEN :
    graph->tabNbEdges= tabNbEdges;
    graph->taille_r = taille_bisInt (&graph->nodesQuantity,graph->nodesQuantity);
    //print_tab_int (matrix,graph->nodesQuantity*graph->nodesQuantity );
    graph->matrix=toTabTabInt(matrix, graph->nodesQuantity,graph->taille_r ) ;
    //printTabtab_int(  graph->matrix , graph->nodesQuantity , graph->edgesQuantity );
    // FIN AJOUT 




    /*graph.nodesQuantity=nbVertices;
    graph.edgesQuantity=nbEdges;
    graph.matrix=matrix;*/
  
    return graph;
}





///////////////////////////////FIN JOHNATHAN //////////////////////////////





///////////////////////////////DEBUT JULIEN //////////////////////////////



int servWeight(){return 1; }




void freeGraph(struct GraphData * _graph){
    freeTabTab((void**)_graph->matrix,_graph->nodesQuantity);
    freeToNull((void**)&_graph->edgesQuantity);

}




struct GraphData * init_graphData ( const char * path , const char* filename ){


     if(DEBUG_PARSER)printf("path : %s filename : %s \n",path,filename);
	
    struct GraphData * graph =NULL;// cst_graphFromFile(path,filename);
    graph= Parsera(path,filename);


   //printTabtab_int(graph->matrix , graph->nodesQuantity,graph->taille_r );
}
/*

struct GraphData {
    int ** matrix;
    int nodesQuantity; //NB_NODE
    int  edgesQuantity; 
    int * taille_r;
    int * tabNbEdges;
};
*/

struct GraphData * cst_baseGraphData ( int nodesQuantity ){
     struct GraphData* graph =  (struct GraphData*)malloc(1*sizeof(struct GraphData));
     graph->nodesQuantity=nodesQuantity;
     return graph;
    }


struct GraphData * cpy_graphData ( struct GraphData * graph){
    struct GraphData* graphcpy= cst_baseGraphData (graph->nodesQuantity );
    graphcpy->edgesQuantity=graph->edgesQuantity;
    graphcpy->taille_r= cpy_tab_int (graph->taille_r,graphcpy->nodesQuantity);
    graphcpy->matrix= cpy_tabTab_int (graph->matrix, graphcpy->taille_r , graphcpy->nodesQuantity);
    graphcpy->tabNbEdges= cpy_tab_int (graph->tabNbEdges,graphcpy->nodesQuantity);

    return graphcpy;

}


struct GraphData * graphDataFromAdj ( int ** adjMatrix ,size_t taille_square){
    struct GraphData* graph= cst_baseGraphData (taille_square );

    graph->tabNbEdges= cst_nbEdgesAdj ( adjMatrix ,  taille_square );
   
    graph->edgesQuantity=-1;//inutile TODO a calculer si besoin 

    graph->taille_r= taille_bisInt (&graph->nodesQuantity,graph->nodesQuantity);
    graph->matrix=adjMatrix;

    return graph;

}

struct GraphData * graphDataCpyFromAdj ( int ** adjMatrix ,size_t taille_square){
    struct GraphData* graph= cst_baseGraphData (taille_square );

    graph->tabNbEdges= cst_nbEdgesAdj ( adjMatrix ,  taille_square );
   
    graph->edgesQuantity=-1;//inutile TODO a calculer si besoin 

    graph->taille_r= taille_bisInt (&graph->nodesQuantity,graph->nodesQuantity);
    graph->matrix=cpy_tabTab_int (adjMatrix,graph->taille_r ,taille_square);

    return graph;

}


struct GraphData* includeServGraphData(struct GraphData * graph){
    //printf("joijgoiedoiz\n\n");

     // [shift_case = graph->nodesQuantity ] [graph->edgesQuantity ]
            int * tab_tmp = (int*)malloc(sizeof(int)*2);
            int shift =1;
            graph->taille_r =(int*)realloc(graph->taille_r ,sizeof(int)*graph->nodesQuantity+shift);
            tabInt_decalH2 (graph->taille_r , graph->nodesQuantity , shift );

            graph->taille_r[0]= graph->nodesQuantity;
    //print_tab_int ( graph->taille_r  , graph->nodesQuantity +shift);

   
  //print_tab_int ( graph->tabNbEdges  , graph->nodesQuantity );

     graph->tabNbEdges =(int*)realloc(graph->tabNbEdges ,sizeof(int)*graph->nodesQuantity+shift);
   tabInt_decalH2 (graph->tabNbEdges , graph->nodesQuantity , shift );
   graph->tabNbEdges[0]=graph->nodesQuantity ;
   //print_tab_int ( graph->tabNbEdges  , graph->nodesQuantity +shift);
   

    tabSquare(tab_tmp,2,shift);

    //but : allouer les shift premiere ligne et les shift premiere colonne  à servWeight
    tabtabInt_AppendVal (&graph->matrix  ,  &graph->nodesQuantity ,graph->taille_r , tab_tmp , servWeight() );

   for(int i =0;i < graph->nodesQuantity +shift ; i++)graph->tabNbEdges[i]+=shift;
    //printf("\n\n");
	//printTabtab_int(graph->matrix , graph->nodesQuantity,graph->taille_r );

    //printf("\n\n");
    return graph ;
}





const char graphParamDelim(){return '%';}
/*
const char*  graphParamDelims(){
    char* delims = (char*)malloc(2);
    delims[0]= graphParamDelim();
    delims[1]=endDelimDf();
    return delims;}
*/


char* graphToStr( struct GraphData *  graph){

    char* nodesQuantity = intToChar(graph->nodesQuantity);
    char* result = (char*)malloc(strlen(nodesQuantity)+1);
    char delim = graphParamDelim(); 
    strcpy(result,nodesQuantity);

    if(DEBUG_PARSER)printf("\n\n NodeQuantity  %s\n\n ",result);

    char* matrix = intTabTabToString2 ( graph->matrix , graph->nodesQuantity , graph->taille_r , tabTabDelims() , 1 ,0  );
   

    result=fusionstr (result ,matrix  ,  delim  );

    if(DEBUG_PARSER)printf("result + adjMatrix  %s\n\n ",result);


    char* taille_r = intTabToString ( graph->taille_r ,  graph->nodesQuantity , tabDelim() ,graph->nodesQuantity ,0 );
    result=fusionstr (result ,taille_r  ,  delim  );

    if(DEBUG_PARSER)printf("result + taille_r  %s\n\n  ",result);




    char* edgesQuantity = intToChar(graph->edgesQuantity);
    result=fusionstr (result ,edgesQuantity ,  delim  );

    if(DEBUG_PARSER)printf("result + edgesQuantity  %s\n\n ",result);



    char* tabNbEdges = intTabToString ( graph->tabNbEdges ,  graph->nodesQuantity , tabDelim() ,graph->nodesQuantity ,0 );
    result=fusionstr (result ,tabNbEdges  , delim  );

    if(DEBUG_PARSER)printf("result+tabNbEdges %s\n\n",result);



    free(edgesQuantity);
    free(tabNbEdges);
    free(matrix);
    free(taille_r);
    free(nodesQuantity);

    return result ;

}



 struct GraphData * strToGraph(char* str){


    if(DEBUG_PARSER)printf("DEB %s \n",str);
    struct GraphData * graph ;
    char delim= graphParamDelim();
    char* save_ptr;

    char* strToken = strtok_r ( str, &delim ,&save_ptr);

    int nodesQuantity = strToInt (strToken);
    if(DEBUG_PARSER)printf("NodesQ %d \n", nodesQuantity);

    graph =  cst_baseGraphData (nodesQuantity  );

    strToken= strtok_r (NULL , &delim ,&save_ptr);

    if(DEBUG_PARSER)printf("TAB %s \n\n",strToken);

    //printf("%s delims \n\n",tabTabDelims());

    graph->matrix =  strToTabTab( strToken,tabTabDelims());


    //char* intTabTabToString ( int** tabTab , size_t taille2 , int taille , const char * concatEndDelim , int idmax ,int select  ){ //idmax == nb_cluster
    
    if(DEBUG_PARSER){
        printf("MatAdj ");
        printTabtab_int2(graph->matrix,nodesQuantity);
    }

    strToken= strtok_r (NULL , &delim ,&save_ptr);

    graph->taille_r = strToTab(strToken ,tabDelim());

    strToken= strtok_r (NULL , &delim ,&save_ptr);

    graph->edgesQuantity = strToInt (strToken);

    strToken= strtok_r (NULL , &delim ,&save_ptr);

    graph->tabNbEdges = strToTab(strToken ,tabDelim());


    return graph;
 
}


///////////////////////////////FIN JULIEN //////////////////////////////
/*
int main(int argc, char *argv[]) {


    if (argc != 3 ) { 
        printf("utilisation : %s  path filename   \n", argv[0]); //voir si color_cnt pas max degree 
        exit(1);
    }

    struct GraphData * graphD = Parsera(argv[1],argv[2]);
    struct GraphData * graphCpy =  graphDataCpyFromAdj ( graphD->matrix ,graphD->nodesQuantity);
    char* str =graphToStr(graphCpy);
    //printf("\n STR %s \n ",str);

    struct GraphData * graphRet =  strToGraph( str); 


    char* str2 =graphToStr(graphRet);

    //printf("\n STR %s \n ",str2);


    return 0;
    }*/
