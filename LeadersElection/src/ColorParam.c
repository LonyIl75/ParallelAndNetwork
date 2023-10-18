
/**
 * fichier:ColorParam.c
 * auteur: Rambal Julien
 * description : Tout ce qui est necessaire pour faire une coloration de Graph 
 **/




#include "ColorParam.h"




void init_gamma(int** adj_matrix, int** gamma,int* tab_tailleGamma,  int* init_coloring , size_t taille_initColor) {
    int node_cnt = taille_initColor;
    int color_cnt = tab_tailleGamma[0];
    int node_idx;
    int color;
    int node_idx2;
    int conflict_count;
    for (node_idx = 0; node_idx < node_cnt; node_idx++) {
        for (color = 0; color < color_cnt; color++) {
            conflict_count = 0;
            for (node_idx2 = 0; node_idx2 < node_cnt; node_idx2++) {
                if ((node_idx != node_idx2) && adj_matrix[node_idx][node_idx2] && color == init_coloring[node_idx2]) {
                    conflict_count += 1;
                }
            }
            gamma[node_idx][color] = conflict_count;
        }
    }
}

int count_conflicts(int** adj_matrix,size_t taille_adj, int* init_coloring) {
    int conflict_cnt = 0;
    int idx;
    int j;
    for (idx = 0; idx < taille_adj; idx++) {
        for (j = 0; j < idx; j++) {
            if (adj_matrix[idx][j] && init_coloring[idx] == init_coloring[j]) {
                conflict_cnt += 1;
            }
        }
    }
    return conflict_cnt;
}
int sizeofSmallestCliqueDf(){return 3; }
double count_conflicts_degree_based(int** adj_matrix,size_t taille , int* init_coloring, int * nb_edges) {
    int conflict_cnt = 0;
    int * conflicting_nodes = (int*) malloc( taille * sizeof(int));
    for (int i =0 ; i< taille ;i++) conflicting_nodes[i]=0;
    int l;
    int i;
    //printf("taille %d \n",taille);

    for (int idx = 0; idx < taille ; idx++) {
        for (int j = idx+1; j < taille ; j++) {
            
            if ((adj_matrix[idx][j] ||adj_matrix[j][idx])  && init_coloring[idx] == init_coloring[j]) { //TODO PB i==j conflict 
                //if(idx==117)
                 if(DEBUG_COLOR)printf("II %d  JJ %d \n",idx,j);
                conflict_cnt += 1;
                conflicting_nodes[idx] += 1;
                conflicting_nodes[j] += 1;
            }
            //if(idx==117)printf("PAS CONFLICT i%d j %d conf %d  (c :%d vs %d )\n ", idx ,j,(adj_matrix[idx][j]+adj_matrix[j][idx]),init_coloring[idx] ,init_coloring[j]  );
        }
    }
    //print_tab_int(init_coloring,taille);
    double h1 = 0;
    double tmp =0;
    for (int i =0 ; i < taille; i++)h1+=(nb_edges[i] >0 ? ((double)conflicting_nodes[i]/(double)nb_edges[i]):0);
    /*{
        tmp =  (nb_edges[i] >0 ? ((double)conflicting_nodes[i]/(double)nb_edges[i]):0);
        printf("tmp %f i %d edges %d \n ",tmp,i+1,nb_edges[i]);
        h1+=(nb_edges[i] >0 ? ((double)conflicting_nodes[i]/(double)nb_edges[i]):0);
    }*/
    //printf("H1 %f \n",h1);
    h1/=taille;
    //printf(" conflict_cnt %d vs h1 %f \n", conflict_cnt,h1);
    //sum([double(l) / double(len(nodes[i])) for i, l in enumerate(conflicting_nodes)]) / node_cnt;
    return conflict_cnt - h1;
}
struct ColorationResult * base_colorResult(size_t taille ){
	struct ColorationResult * CR = (struct ColorationResult *)malloc(sizeof(struct ColorationResult )*1);
	CR->coloring =emptyColoring(taille ) ;
	CR->taille=taille;
    CR->color_cnt = -1;
    CR->conflict = taille;
}

struct ColorationResult * cst_colorResult(int* _coloration , int colorCnt,size_t taille , int nbConflict ){
	struct ColorationResult * CR =  base_colorResult( taille );
	if(debug_colorG)printf("CR %d vs %d %d \n ",CR->color_cnt,colorCnt, CR->color_cnt>colorCnt );
	if(CR->color_cnt<0 || CR->color_cnt>colorCnt ){
	for(int i =0 ; i <taille ; i++){
		CR->coloring[i]=_coloration[i];
	}
    CR->color_cnt =  colorCnt;
    CR->conflict = nbConflict;
}
if(debug_colorG){
printf("colorResult Cst ");
print_tab_int(_coloration,taille);
printf("\n\n");
}
return CR;

}
/*
void init_colorResult(struct ColorationResult ** res , int* _coloration , int colorCnt,size_t taille ){
	struct ColorationResult * CR =  base_colorResult( taille );
	if(CR->color_cnt!=-1 && CR->color_cnt>colorCnt ){
	for(int i =0 ; i <taille ; i++){
		CR->coloring[i]=_coloration[i];
	}
    CR->color_cnt =  colorCnt;
}
printf("colorResult Cst ");
print_tab_int(_coloration,taille);
printf("\n\n");
return CR;

}*/

 
const char colorResultDelim(){return '?';}

char*  CRToStr(struct ColorationResult * CR){

	if(debug_colorG)printf("CRToStr t %d c %d  ",CR->taille ,CR->color_cnt);
	char* result = NULL; 
	char delim = colorResultDelim() ;
	if(debug_colorG)print_tab_int(CR->coloring,CR->taille );

/*	
	char* strTaille = intToChar(CR->taille) ;
	result= (char*)malloc(strlen(strTaille)+1);
	strcpy(result,strTaille);
	printf("strTaille result %s\n\n \n \n",result);
*/

	char* strColorCount = intToChar(CR->color_cnt);
    //result=fusionstr (result ,strColorCount  ,  delim  );
    result= (char*)malloc(strlen(strColorCount)+1);
    //if(DEBUG_COLOR)
    strcpy(result,strColorCount);
    if(debug_colorG)printf("strColorCount result %s\n\n \n \n",result);


    char* strColorConflict = intToChar(CR->conflict);
	result=fusionstr (result ,strColorConflict  ,  delim  );
	if(debug_colorG)printf("strColorTab result %s\n\n \n \n",strColorConflict);

	char* strColorTab = intTabToString (CR->coloring,CR->taille , tabDelim(),CR->color_cnt,0)  ;
	//result= (char*)malloc(strlen(strColorTab)+1);
	result=fusionstr (result ,strColorTab  ,  delim  );;
	//if(DEBUG_COLOR)
	if(debug_colorG)printf("strColorTab result %s\n\n \n \n",result);


    free(strColorTab);
    free(strColorCount);
    //free(strTaille);


    return result ;

}





void   process_graph2(struct ColorationResult ** res,struct ColorationParam* colorParam){


    char* name;
  	struct GraphData * _graphD = colorParam->graphD;
  	   if(debug_colorG){printf("\n\n\n");
  	printTabtab_int2( colorParam->graphD->matrix , colorParam->graphD->nodesQuantity);
           printf("Press Any Key to Continue\n");  
           getchar(); }
  	int color_cnt = colorParam->color_cnt;
  	int timeout = colorParam->timeout ;
  	int A = colorParam->A;
  	float alpha = colorParam->alpha;
  	int p_max=colorParam->p_max;
  	bool do_opt = colorParam->do_opt;
  	int stop_k =colorParam->stop_k;
  	int* _coloring = colorParam->coloring;
  	int* fixed = colorParam->fixed;

    // parse(filename, name, node_cnt, edge_cnt, nodes);
    int * nb_edges =_graphD->tabNbEdges; // _nn->metas->nb_edges;
    int node_cnt =   _graphD->nodesQuantity; //_nn->metas->taille;
    int maxDegree4=maxOfTabInt (nb_edges, node_cnt );
    color_cnt = (color_cnt > 0 ? color_cnt :(maxDegree4<=0?1:maxDegree4));//normalement c'est deja fait degree max 

    /*if(min_color > color_cnt ){
        printf("color_cnt > min_color \n");
        color_cnt=min_color;
    }*/
    printf(" color count: %d, A: %d, alpha: %f, Pmax: %d, timeout: %d max_color : %d  vs %d ColoringTab :", color_cnt, A, alpha, p_max, timeout,color_cnt ,maxOfTabInt (nb_edges, node_cnt ));
    print_tab_int( _coloring,node_cnt );
    printf("fixed : ");
    print_tab_int( fixed ,node_cnt );
    printf("\n\n\n");
    int **  adj_matrix =  _graphD->matrix;//_nn->metas->uids;
    // faire switcht case pour select function : if elseif et strcmp param_fonctioneval 
    //evaluation_fu = count_conflicts_degree_based
    //printTabtab_int3(adj_matrix, node_cnt);
    bool job_done =  false;
    
    int ** gamma = (int **)malloc(node_cnt *  sizeof(int *));
    size_t taille_gamma = node_cnt ; 
    for (int i = 0; i < taille_gamma; i++)  {
        gamma[i] = (int *)malloc(color_cnt* sizeof(int));
        for (int j = 0; j < color_cnt; j++) {
                 gamma[i][j] = 0;
             }
            }


    int ** tabu_list = (int **)malloc(node_cnt * sizeof(int *));
    size_t taille_tabu_list = node_cnt ; 
         for (int i = 0; i < taille_tabu_list; i++) {
             tabu_list[i] = (int *)malloc(color_cnt * sizeof(int));
             for (int j = 0; j < color_cnt; j++) {
                 tabu_list[i][j] = 0;
             }
         }

    int * taille_bis = (int*) malloc ( taille_gamma * sizeof(int) ); //int* taille_bisInt (int* valeur , size_t taille )
    for (int i =0 ; i < node_cnt;i++)taille_bis[i]= color_cnt;

 


    int * coloring = (int*)malloc(sizeof(int) * node_cnt);
    size_t taille_coloring = node_cnt ; 
    for (int i = 0; i < node_cnt; i++) {
            coloring[i] = 0;
        }
    double  min_conflicts = 1000000 ;

    
    int iter_counter = 1;
    int last_p_change = iter_counter;
    int tl_extension = 0;
     
    time_t start_time = time(NULL);

    double old_conflict_cnt =-1.0 ;

    double cur_conflict_cnt = -1.0 ; 

    int *  best_coloring = (int*)malloc( sizeof(int)* node_cnt);
    for (int i = 0; i < node_cnt; i++)  best_coloring[i]=-1;

    int *  last_coloring = (int*)malloc( sizeof(int)* node_cnt);
    for (int i = 0; i < node_cnt; i++)  last_coloring[i]=-1;


    double  best_delta  = min_conflicts ;
    int best_node = -1;
    int best_color = -1;



    int tl = 0 ;

    double cur_delta = -1;

    int color_tabu = -1;
    for (int i = 0; i < node_cnt; i++)  best_coloring[i]=-1;
          

    while (! job_done) 
    {

        for (int i = 0; i < node_cnt; i++)  last_coloring[i]=best_coloring[i];

         for (int i = 0; i < node_cnt; i++) {
             for (int j = 0; j < color_cnt; j++) {
                 if(fixed!=NULL && fixed[i]==1){tabu_list[i][j]=-1;}
                 else{tabu_list[i][j] = 0;}
             }
         }

        printf("\n\n\n");
        for (int i = 0; i < node_cnt; i++) {
            if(fixed!=NULL && fixed[i] && _coloring!=NULL && (_coloring)[i]>=0 ){

            coloring[i] = (_coloring)[i];} // && fixed!=NULL && fixed[i] 
            else{coloring[i] = rand() % color_cnt;}
            printf("%d / ",coloring[i]);
        }
        printf("\n\n\n");
         

        init_gamma(adj_matrix, gamma,taille_bis ,  coloring , node_cnt );
        iter_counter = 1;
        last_p_change = iter_counter;
        tl_extension = 0;
     
        start_time = time(NULL);

        old_conflict_cnt =-1 ;

        min_conflicts = 1000000 ;

        while (true )
        {
            //printf("kkofe\n");
            /*if (iter_counter % 1000000 == 0) {
                printf("  iteration %ld  \n ",iter_counter);
            }*/
             //printf("kkofe\n");
        //print_tab_int (  coloring  , node_cnt  );
   	
           cur_conflict_cnt = count_conflicts_degree_based(adj_matrix, node_cnt , coloring, nb_edges);
            
           /*printf("cur_conflict %f \n ", cur_conflict_cnt);
           print_tab_int(coloring , node_cnt);
           printf("Press Any Key to Continue\n");  
           getchar(); */
           if (old_conflict_cnt == cur_conflict_cnt ){
            if (last_p_change + p_max <= iter_counter){
                    last_p_change = iter_counter;
                    tl_extension += 1;
                }
            
            //if (tl_extension == 1 || tl_extension % 20 == 0)printf("Pmax reached, increase to %d \n ", tl_extension);
            }else{

                last_p_change = iter_counter;
                tl_extension = 0;
                // if (cur_conflict_cnt < 5) printf("conflict count", cur_conflict_cnt);
                 }
                 
                old_conflict_cnt = cur_conflict_cnt;
            
            if (cur_conflict_cnt < min_conflicts){
                //printf("update \n");
                min_conflicts = cur_conflict_cnt;
                //best_coloring = coloring.copy()
                for (int i =0 ; i < node_cnt ;i++)best_coloring[i]= coloring[i]; 
                //if (cur_conflict_cnt < 10) printf("%d conflicts at iteration %d after %d s",min_conflicts, iter_counter, time(NULL) - start_time);
                if (cur_conflict_cnt == 0 && color_cnt <= sizeofSmallestCliqueDf())
                    {
                        if(debug_colorG)printf("done \n \n");
                        job_done = true;
                        if(debug_colorG)printf("GRAPH COLOR RR :");print_tab_int(coloring , node_cnt);
                        *res = cst_colorResult(coloring , color_cnt ,node_cnt ,cur_conflict_cnt) ;
                        return;
                        //for(int i =0 ; i < node_cnt;i++)(*_coloring)[i]=coloring[i]; //si random resoud pb
                        //return cst_colorResult(coloring , color_cnt ,node_cnt ) ;//, iter_counter; // return coloring ? 
                    }
                    else if (cur_conflict_cnt == 0)
                    {
                        //printf("break\n");
                        break;
                    }
            
            }
            best_delta = 1000000 ; 

            for (int n = 0; n < node_cnt; n++) {
                if (fixed==NULL || fixed[n]==0){
                for (int c = 0; c < color_cnt; c++) {
                    if (c != coloring[n]) {
                        int delta = gamma[n][c] - gamma[n][coloring[n]];
                        //printf("delta %d best_delta %d \n",delta,best_delta);
                        if (delta < best_delta) {
                            //printf("bestdelta %d \n",delta);
                            if (tabu_list[n][c]!= -1 && (tabu_list[n][c] < iter_counter || delta + cur_conflict_cnt < min_conflicts)) {
                                best_node = n;
                                best_color = c;
                                best_delta = delta;
                            }
                        }
                    }
                }
            }
        }
            //printf("best_node %d best_color %d \n ", best_node , best_color );
            tl =  (int)(alpha * cur_conflict_cnt  + 0.5 )  + ( rand() %A +1 ) + tl_extension; //round(alpha * cur_conflict_cnt) + ( rand() %A +1 ) + tl_extension;
            color_tabu = coloring[best_node];
            tabu_list[best_node][color_tabu] = tl + iter_counter;
            coloring[best_node] = best_color;

            for  (int i =0 ; i < taille_gamma ; i++ ) {
                if (adj_matrix[i][best_node]){
                    gamma[i][color_tabu] -= 1;
                     gamma[i][best_color] += 1;
                }


            }
            iter_counter++;

            if (iter_counter == MAX_ITERATIONS) {
                int moi =  count_conflicts(adj_matrix, taille_gamma, best_coloring) ;
                /*int moi2 = count_conflicts(adj_matrix, taille_gamma, coloring) ;
                double moi_bis = count_conflicts_degree_based(adj_matrix, node_cnt , best_coloring, nb_edges); 
                double moi2_bis = count_conflicts_degree_based(adj_matrix, node_cnt , coloring, nb_edges); */
                
                if(debug_colorG)printf("Max iteration count reached (%d == %d ), aborting search for k=%d conflict %d  \n", MAX_ITERATIONS,iter_counter, color_cnt, moi);//,moi_bis,moi2,moi2_bis );
                //print_tab_int (  best_coloring  , node_cnt  );
                for(int i =0 ; i < node_cnt;i++){coloring[i]=(last_coloring[0]>=0?last_coloring[i]:best_coloring[i]);
                }
                 if(debug_colorG)printf("GRAPH COLOR RR :");print_tab_int(coloring , node_cnt);
                *res=cst_colorResult(coloring , color_cnt+1 ,node_cnt  ,cur_conflict_cnt) ;
                return;
                //return cst_colorResult(coloring , color_cnt+1 ,node_cnt  ) ; // iter_counter;
            }

            if (timeout != 0 && (( time(NULL) - start_time) > timeout)) {
               time_t mytime =(time(NULL) - start_time);
                struct tm * time_str = gmtime(&mytime);
                int moi =  count_conflicts(adj_matrix, taille_gamma, best_coloring) ;
                if(debug_colorG)printf("Timeout reached ( %d sec <  %d sec ), aborting search for k=%d conflict %d  \n",timeout, 60*time_str->tm_min+ time_str->tm_sec, color_cnt, moi);//,moi_bis,moi2,moi2_bis );

               
                //print_tab_int (  best_coloring  , node_cnt  );
                 for(int i =0 ; i < node_cnt;i++){coloring[i]=(last_coloring[0]>=0?last_coloring[i]:best_coloring[i]);
                	}
                *res=cst_colorResult(coloring , color_cnt+1 ,node_cnt ,cur_conflict_cnt) ;
                return;
                	//return cst_colorResult(coloring , color_cnt+1 ,node_cnt ) ; // iter_counter;
            }
            

            //job_done = true; break;
        }
            time_t mytime =(time(NULL) - start_time);
            struct tm * time_str = gmtime(&mytime);
            if(debug_colorG)printf("Found solution within %d min %d sec \n ",time_str->tm_min, time_str->tm_sec) ;
            int moi =  count_conflicts(adj_matrix, taille_gamma, best_coloring) ;
            if(debug_colorG)printf("CONFLICT SOL %d ",moi);
            if(debug_colorG)printf("COLOR %d\n",color_cnt);
            //if(debug_colorG)print_tab_int (  best_coloring  , node_cnt  );
      
            if (!do_opt || color_cnt <= stop_k) {

                //for(int i =0 ; i < node_cnt;i++)(*_coloring)[i]=best_coloring[i];
                 if(debug_colorG)printf("GRAPH COLOR RR :");print_tab_int(best_coloring , node_cnt);
                  *res =cst_colorResult(best_coloring , color_cnt  ,node_cnt ,cur_conflict_cnt) ;
                  return;
                  //return cst_colorResult(best_coloring , color_cnt  ,node_cnt  ) ;  //, iter_counter
            }
            color_cnt --;
            
    }
           //for(int i =0 ; i < node_cnt;i++)(*_coloring)[i]=best_coloring[i];
            
            if(debug_colorG)printf("GRAPH COLOR RR :");print_tab_int(best_coloring , node_cnt);
           *res =cst_colorResult(best_coloring , color_cnt  ,node_cnt  ,cur_conflict_cnt) ;
           return;
           //return cst_colorResult(best_coloring , color_cnt  ,node_cnt  ) ;
}




/*
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
};*/
/*
struct ColorationResult *   sec_process_graph(struct ColorationParam* colorParam ){
    if(colorParam->coloring==NULL){
                printf("coloring_tab == NULL\n");
                return -1;
    }
    if(colorParam->fixed!=NULL){
        for(int i =0 ; i< colorParam->graphD->nodesQuantity ;i++ ){
            if(colorParam->fixed[i]!=1 ){
            if( colorParam->fixed[i]!=0){
                printf("bad fixed\n");
                return -1;
        }else if( colorParam->coloring[i]< 0 ){//|| _coloring[i] > color_cnt ){ //depasse color_cnt discutable par exemple freeze certaine couleur et minimiser autre possible
                printf("bad coloring\n");
                return -1;
        }
    }
}


    }

    return process_graph(_graphD, color_cnt,  timeout,  A,  alpha,  p_max,  do_opt,  stop_k,  _coloring , fixed );
}
*/

//TODO faire un constructor de GraphData car on n'enverra que le tableau d'adj et le nombre de noeud aux clients donc il faut calculer le reste  pour l'utiliser dans colorationParam
//TODO faire une fonction defaultColorCnt qui est une fonction du nb de noeud 

int* emptyFixed(size_t taille ){
	int* tab = (int*)malloc(sizeof(int)*taille);
	for(int i =0; i <taille ;i++)tab[i]=0;
	return tab ;
}

struct ColorationParam * base_ColorationParam (struct GraphData * _graphD  ){
       struct ColorationParam * clParam = (struct ColorationParam *)malloc(1*sizeof(struct ColorationParam ));
        clParam->graphD=_graphD;
        clParam->color_cnt=maxOfTabInt (clParam->graphD->tabNbEdges , clParam->graphD->nodesQuantity );

        return clParam;
}

int* emptyColoring(size_t taille ){
    int * coloring = (int*)malloc(taille*sizeof(int));
    for(int i=0 ; i < taille;i++ )coloring[i]=-1;
    return coloring ;
}

struct ColorationParam  * cstdef_ColorationParam(struct GraphData * _graphD){
    struct ColorationParam * clParam = base_ColorationParam ( _graphD);

    clParam->coloring = emptyColoring(clParam->graphD->nodesQuantity);

    clParam->timeout=DEFAULT_TIMEOUT;
    clParam->A=DEFAULT_A;
    clParam->alpha=DEFAULT_ALPHA;
    clParam->p_max=DEFAULT_P_MAX;
    clParam->do_opt=DEFAULT_DO_OPT ;
    clParam->stop_k=DEFAULT_STOP_K;
    clParam->fixed = emptyFixed(clParam->graphD->nodesQuantity);
    return clParam;
}

struct ColorationParam  * cst_ColorationParam(struct GraphData * _graphD, int _colorCnt,const int* _coloring,const int* _fixed ){ //copy _coloring et _fixed
    struct ColorationParam * clParam = cstdef_ColorationParam( _graphD);

    clParam->color_cnt=_colorCnt;
    for(int i=0 ; i <clParam->graphD->nodesQuantity ;i++ )clParam->coloring[i]=_coloring[i];

    clParam->fixed = (int*)malloc(clParam->graphD->nodesQuantity*sizeof(int));
    for(int i=0 ; i <clParam->graphD->nodesQuantity ;i++ )clParam->fixed[i]=_fixed[i];
     

    return clParam;
}

struct ColorationParam  * cst_ColorationParam2(struct GraphData * _graphD, int _colorCnt, int* _coloring, int* _fixed ){ //pas copy _coloring et fixed
    struct ColorationParam * clParam = base_ColorationParam ( _graphD);

    clParam->color_cnt=_colorCnt;
    clParam->timeout=DEFAULT_TIMEOUT;
    clParam->A=DEFAULT_A;
    clParam->alpha=DEFAULT_ALPHA;
    clParam->p_max=DEFAULT_P_MAX;
    clParam->do_opt=DEFAULT_DO_OPT ;
    clParam->stop_k=DEFAULT_STOP_K;
    clParam->coloring =_coloring;
    clParam->fixed =  _fixed;

    return clParam;
}


void freeColorParam(struct ColorationParam  * cur){

    freeGraph(cur->graphD);
    freeToNull((void**)&cur->coloring) ;
    freeToNull((void**)&cur->fixed);
}


void set_setupColorationParam(struct ColorationParam  * cur , struct ColorationParam  * colorSetup ){

    cur->timeout=colorSetup->timeout;
    cur->A=colorSetup->A;
    cur->alpha=colorSetup->alpha;
    cur->p_max=colorSetup->p_max;
    cur->do_opt=colorSetup->do_opt ;
    cur->stop_k=colorSetup->stop_k;

}




int checkColorationParam(struct ColorationParam* params){
    return 1;
}

void  color_graph(struct ColorationResult ** res , struct ColorationParam * params){

    //int* res = (int*)malloc(sizeof(int));
    //*res=process_graph(params->graphD, params->color_cnt,  params->timeout,  params->A,  params->alpha,  params->p_max,  params->do_opt,  params->stop_k,  &params->coloring , params->fixed );
    //return res;
    process_graph2( res ,params );
 
}



//pipeline 
void  mergeColoration( int* accumulator_coloring , int* coloration_cluster , int* trad_cluster,size_t taille_cluster  ){ // cluster[i]=>idAdj_i issu de classCluster
	int k =0;
	for(int i =0 ; i <taille_cluster ;i++){
		k= trad_cluster[i];
		accumulator_coloring[k]=coloration_cluster[i];
	}
}


void  updateBestColor( struct ColorationParam * acc, struct ColorationResult * CR , int* trad_cluster  ){ // cluster[i]=>idAdj_i issu de classCluster
	int k =0;
	for(int i =0 ; i <CR->taille ;i++){ //CR->taille = taille du cluster
		k= trad_cluster[i];
		acc->coloring[k]=CR->coloring[i]; 
		if(acc->fixed[k]==0)acc->fixed[k]=1;
	}
    if(debug_colorG){
	printf("ACC FIXED : ");
	print_tab_int(acc->fixed,acc->graphD->nodesQuantity);
	printf("ACC COLORING : ");
	print_tab_int(acc->coloring,acc->graphD->nodesQuantity);
}
}

int* andTab(int* tab1 , int *tab2, size_t taille){
    if(DEBUG_COLOR){
	printf("AndTab tab1 :");
	print_tab_int(tab1,taille);
	printf("\n AndTab tab2 :");
	print_tab_int(tab2,taille);
	printf("\n");
}

	int* resultat = (int*)malloc(taille*sizeof(int));
	for(int i=0; i < taille; i++){
		resultat[i]=(tab1[i]&tab2[i]);//tout le monde est fixer par defaut optimiste 
	}
	if(debug_colorG){
    printf("AndTab (Final) :");
	print_tab_int(resultat,taille);
	printf("\n");
}
	return resultat ;
}


int* fixed (int** adj , size_t taille ,  int* cluster1D ){ //renvoie le tableau de noeuds fixé : les noeuds qui joignent 2 clusters


	int* resultat = (int*)malloc(taille*sizeof(int));
	for(int i=0; i < taille; i++){
		resultat[i]=1;//tout le monde est fixer par defaut optimiste 
	}


	for(int i =0 ; i < taille ; i++){
		for(int j =i; j<taille ; j++){
			if(resultat[i]==1 &&adj[i][j]>0 )//| adj[i][j]>0 //si ils sont adj
			{
				
				if( cluster1D[i]!=cluster1D[j])//si ils appartiennent à deux cluster diff 
				{
					//printf("cluster_i \n");
					if(DEBUG_COLOR)printf("i %d j %d  adj %d\n ", i , j , adj[i][j]);
					resultat[i]=resultat[j]=0; //alors ils ne sont pas fixe 

				}
			} 
		}
	}
	return resultat ; 

}
int* fixed2 (struct GraphData* graph ,  int* trad_cluster ){
	return  fixed (graph->matrix , graph->nodesQuantity ,   trad_cluster );

}



char* setupColorParamToStr(struct ColorationParam *_color){
    char* color_cnt = intToChar(_color->color_cnt);
    char* result = (char*)malloc(strlen(color_cnt)+1);

    char delim= colorParamDelim();

    strcpy(result,color_cnt);

 
    char* timeout=intToChar(_color->timeout);
    result=fusionstr (result ,timeout  ,delim );

    char* alpha=floatToChar(_color->alpha);
    result=fusionstr (result ,alpha ,delim);


    char* A=floatToChar(_color->A);
    result=fusionstr (result ,A ,delim );


    char* p_max=intToChar(_color->p_max);
    result=fusionstr (result ,p_max  ,delim );

     char* do_opt=intToChar(_color->do_opt);
    result=fusionstr (result ,do_opt  ,delim);

     char* stop_k=intToChar(_color->stop_k);
    result=fusionstr (result ,stop_k  ,delim );


    free(stop_k);
    free(p_max);
    free(do_opt);
    free(alpha);
    free(timeout );
    free(color_cnt);

    return result;

}
char* colorParamToStr(struct ColorationParam *_color){

    
 
    
    char* graph = graphToStr(_color->graphD) ; 
    char* result = (char*)malloc( strlen(graph)+1);
    strcpy(result,graph);
    if(DEBUG_COLOR)printf("result+graph %s \n",result);
    char delim= colorParamDelim();

    char* setup = setupColorParamToStr(_color);


    result=fusionstr (result , setup , delim);
    if(DEBUG_COLOR)printf("result+setup %s \n",result);

    if(_color->coloring)print_tab_int(_color->coloring ,  _color->graphD->nodesQuantity);
    char* coloring = intTabToString ( _color->coloring ,  _color->graphD->nodesQuantity , tabDelim() , (_color->color_cnt>9?_color->color_cnt:-1) ,0 );
    result=fusionstr (result ,coloring  , delim);
    if(DEBUG_COLOR)printf("result+coloring %s \n",result);

    char* fixed = intTabToString ( _color->fixed ,  _color->graphD->nodesQuantity , tabDelim() ,_color->graphD->nodesQuantity ,0 );
    result=fusionstr (result ,fixed  , delim );
    if(DEBUG_COLOR)printf("result+fixed %s \n",result);


    free(setup);
    free(graph);
    free(fixed);
    free(coloring );

    return result;



}

//TODO MARCHE PAS : VOIR  #K89
struct ColorationParam* strToColorSetup(char** strToken ,char ** save_ptr ){
    struct ColorationParam * clParam = (struct ColorationParam *)malloc(1*sizeof(struct ColorationParam ));

     if(debug_colorG)printf("TR %s \n",*strToken);


     char delim= colorParamDelim();
     //char* save_ptr;
    
    (*strToken) = strtok_r ( NULL ,  &delim ,save_ptr);
    
    clParam->color_cnt =  strToInt_p (  *strToken );
    if(debug_colorG)printf("color_cnt %d\n", clParam->color_cnt );

     (*strToken)= strtok_r (NULL ,  &delim ,save_ptr);

    clParam->timeout  =  strToInt_p (  *strToken );
    if(debug_colorG)printf("timeout %d\n", clParam->timeout );


    (*strToken)= strtok_r (NULL ,  &delim ,save_ptr);

    clParam->alpha  =  strToFloat (  *strToken );
    if(debug_colorG)printf("alpha %f\n", clParam->alpha );


   (*strToken)= strtok_r (NULL ,  &delim ,save_ptr);

    clParam->A  =  strToFloat (  *strToken );
    if(debug_colorG)printf("A %f\n", clParam->A );

    (*strToken)= strtok_r (NULL ,  &delim ,save_ptr);

    clParam->p_max  =  strToInt_p  (  *strToken );
    if(debug_colorG)printf("p_max %d\n", clParam->p_max );

    (*strToken)= strtok_r (NULL ,  &delim ,save_ptr);

    clParam->do_opt  =  strToInt_p  (  *strToken );
    if(debug_colorG)printf("do_opt %d\n", clParam->do_opt );


   (*strToken)= strtok_r (NULL ,  &delim ,save_ptr);

    clParam->stop_k  =  strToInt_p  (  *strToken );
    if(debug_colorG)printf("stop_k %d\n", clParam->stop_k );

    return clParam;



}
const char reponseColorDelim(){return '!';}

const char* reponseColorDelim2(){
    char* delim = (char*)malloc(2);
    delim[0]=reponseColorDelim();
    delim[1]='\0';
    return delim;}


const  char colorParamDelim(){return '#';}


struct ColorationParam* strToColorParam(char* strcpye ){

	char* str = (char*)malloc(strlen(strcpye)+1);
	strcpy(str,strcpye);
    struct ColorationParam* clParam;
     char delim= colorParamDelim();
     char* save_ptr;
    if(DEBUG_COLOR)printf("DEB strColorParam %s \n",str);
    char* strToken = strtok_r ( str, &delim ,&save_ptr );

    if(DEBUG_COLOR)printf("strToken1 %s \n",strToken );

    struct GraphData * graph =  strToGraph(  strToken );

    char* graphStr= graphToStr( graph);

    if(DEBUG_COLOR)printf("GRAPH %s \n",graphStr);


    clParam = base_ColorationParam (graph);

     strToken = strtok_r ( NULL ,  &delim ,&save_ptr);
    clParam->color_cnt =  strToInt_p (  strToken );
    if(debug_colorG)printf("color_cnt %d\n", clParam->color_cnt );

    strToken= strtok_r (NULL ,  &delim ,&save_ptr);

    clParam->timeout  =  strToInt_p (  strToken );
    if(debug_colorG)printf("timeout %d\n", clParam->timeout );


    strToken= strtok_r (NULL ,  &delim ,&save_ptr);

    clParam->alpha  =  strToFloat (  strToken );
    if(debug_colorG)printf("alpha %f\n", clParam->alpha );


    strToken= strtok_r (NULL ,  &delim ,&save_ptr);

    clParam->A  =  strToFloat (  strToken );
    if(debug_colorG)printf("A %f\n", clParam->A );

    strToken= strtok_r (NULL ,  &delim ,&save_ptr);

    clParam->p_max  =  strToInt_p  (  strToken );
    if(debug_colorG)printf("p_max %d\n", clParam->p_max );

    strToken= strtok_r (NULL ,  &delim ,&save_ptr);

    clParam->do_opt  =  strToInt_p  (  strToken );
    if(debug_colorG)printf("do_opt %d\n", clParam->do_opt );


    strToken= strtok_r (NULL ,  &delim ,&save_ptr);

    clParam->stop_k  =  strToInt_p  (  strToken );
    if(debug_colorG)printf("stop_k %d\n", clParam->stop_k );



   /* strToken= strtok_r (NULL , &delim   ,&save_ptr );
     printf("strToken2 %s \n",strToken );*/

    //struct ColorationParam * colorSetup = strToColorSetup(strToken,&save_ptr); //#K89

    //set_setupColorationParam(colorParam , colorSetup );

    strToken= strtok_r (NULL , &delim ,&save_ptr );
    if(DEBUG_COLOR)printf("strToken3 %s \n",strToken );

    //int* coloringK = strToTab(strToken ,tabDelim());

    clParam->coloring = strToTab(strToken ,tabDelim()); //(coloringK?coloringK :emptyColoring(graph->nodesQuantity));

     if(DEBUG_COLOR){
     	printf("TABAR %s",strcpye);
     	print_tab_int(clParam->coloring , graph->nodesQuantity);
     }
    strToken= strtok_r (NULL , &delim  ,&save_ptr );
    if(DEBUG_COLOR)printf("strToken5 %s \n",strToken );

    clParam->fixed = strToTab(strToken ,tabDelim());


    return clParam;
 



}


/*
int main(int argc, char *argv[]) {


    if (argc != 3 ) { 
        printf("utilisation : %s  path filename   \n", argv[0]); //voir si color_cnt pas max degree 
        exit(1);
    }

    struct GraphData * graphD = Parsera(argv[1],argv[2]);
    struct ColorationParam * color =  cstdef_ColorationParam(graphD);
    color->color_cnt=5;
    char* str= colorParamToStr(color);
    printf("str %s \n\n ",str);

    struct ColorationParam * color2=strToColorParam(str);

    char* str2= colorParamToStr(color2);

     printf("str2 %s \n\n ",str2);







    return 0;
    }*/

/*

void   process_graph(struct ColorationResult ** res,struct ColorationParam* colorParam){


    char* name;
    struct GraphData * _graphD = colorParam->graphD;
    int color_cnt = colorParam->color_cnt;
    int timeout = colorParam->timeout ;
    int A = colorParam->A;
    float alpha = colorParam->alpha;
    int p_max=colorParam->p_max;
    bool do_opt = colorParam->do_opt;
    int stop_k =colorParam->stop_k;
    int* _coloring = colorParam->coloring;
    int* fixed = colorParam->fixed;

    // parse(filename, name, node_cnt, edge_cnt, nodes);
    int * nb_edges =_graphD->tabNbEdges; // _nn->metas->nb_edges;
    int node_cnt =   _graphD->nodesQuantity; //_nn->metas->taille;
    int maxDegree4=maxOfTabInt (nb_edges, node_cnt );
    color_cnt = (color_cnt > 0 ? color_cnt :(maxDegree4<=0?1:maxDegree4));//normalement c'est deja fait degree max 

    //if(min_color > color_cnt ){
    //    printf("color_cnt > min_color \n");
    //    color_cnt=min_color;
    //}
    printf(" color count: %d, A: %d, alpha: %f, Pmax: %d, timeout: %d max_color : %d  vs %d ColoringTab :", color_cnt, A, alpha, p_max, timeout,color_cnt ,maxOfTabInt (nb_edges, node_cnt ));
    print_tab_int( _coloring,node_cnt );
    printf("fixed : ");
    print_tab_int( fixed ,node_cnt );
    printf("\n\n\n");
    int **  adj_matrix =  _graphD->matrix;//_nn->metas->uids;
    // faire switcht case pour select function : if elseif et strcmp param_fonctioneval 
    //evaluation_fu = count_conflicts_degree_based
    //printTabtab_int3(adj_matrix, node_cnt);
    bool job_done =  false;
    
    int ** gamma = (int **)malloc(node_cnt *  sizeof(int *));
    size_t taille_gamma = node_cnt ; 
    for (int i = 0; i < taille_gamma; i++)  {
        gamma[i] = (int *)malloc(color_cnt* sizeof(int));
        for (int j = 0; j < color_cnt; j++) {
                 gamma[i][j] = 0;
             }
            }


    int ** tabu_list = (int **)malloc(node_cnt * sizeof(int *));
    size_t taille_tabu_list = node_cnt ; 
         for (int i = 0; i < taille_tabu_list; i++) {
             tabu_list[i] = (int *)malloc(color_cnt * sizeof(int));
             for (int j = 0; j < color_cnt; j++) {
                 tabu_list[i][j] = 0;
             }
         }

    int * taille_bis = (int*) malloc ( taille_gamma * sizeof(int) ); //int* taille_bisInt (int* valeur , size_t taille )
    for (int i =0 ; i < node_cnt;i++)taille_bis[i]= color_cnt;

 


    int * coloring = (int*)malloc(sizeof(int) * node_cnt);
    size_t taille_coloring = node_cnt ; 
    for (int i = 0; i < node_cnt; i++) {
            coloring[i] = 0;
        }
    double  min_conflicts = 1000000 ;

    
    int iter_counter = 1;
    int last_p_change = iter_counter;
    int tl_extension = 0;
     
    time_t start_time = time(NULL);

    double old_conflict_cnt =-1.0 ;

    double cur_conflict_cnt = -1.0 ; 

    int *  best_coloring = (int*)malloc( sizeof(int)* node_cnt);
    for (int i = 0; i < node_cnt; i++)  best_coloring[i]=-1;

    int *  last_coloring = (int*)malloc( sizeof(int)* node_cnt);
    for (int i = 0; i < node_cnt; i++)  last_coloring[i]=-1;


    double  best_delta  = min_conflicts ;
    int best_node = -1;
    int best_color = -1;



    int tl = 0 ;

    double cur_delta = -1;

    int color_tabu = -1;
    for (int i = 0; i < node_cnt; i++)  best_coloring[i]=-1;
          

    while (! job_done) 
    {

        for (int i = 0; i < node_cnt; i++)  last_coloring[i]=best_coloring[i];

         for (int i = 0; i < node_cnt; i++) {
             for (int j = 0; j < color_cnt; j++) {
                 if(fixed!=NULL && fixed[i]==1){tabu_list[i][j]=-1;}
                 else{tabu_list[i][j] = 0;}
             }
         }

        printf("\n\n\n");
        for (int i = 0; i < node_cnt; i++) {
            if(fixed!=NULL && fixed[i] && _coloring!=NULL && (_coloring)[i]>=0 ){

            coloring[i] = (_coloring)[i];} // && fixed!=NULL && fixed[i] 
            else{coloring[i] = rand() % color_cnt;}
            printf("%d / ",coloring[i]);
        }
        printf("\n\n\n");
         

        init_gamma(adj_matrix, gamma,taille_bis ,  coloring , node_cnt );
        iter_counter = 1;
        last_p_change = iter_counter;
        tl_extension = 0;
     
        start_time = time(NULL);

        old_conflict_cnt =-1 ;

        min_conflicts = 1000000 ;

        while (true )
        {
            //printf("kkofe\n");
            //if (iter_counter % 1000000 == 0) {
            //    printf("  iteration %ld  \n ",iter_counter);
            //}
             //printf("kkofe\n");
        //print_tab_int (  coloring  , node_cnt  );
   
           cur_conflict_cnt = count_conflicts_degree_based(adj_matrix, node_cnt , coloring, nb_edges);
     
           if (old_conflict_cnt == cur_conflict_cnt ){
            if (last_p_change + p_max <= iter_counter){
                    last_p_change = iter_counter;
                    tl_extension += 1;
                }
            
            //if (tl_extension == 1 || tl_extension % 20 == 0)printf("Pmax reached, increase to %d \n ", tl_extension);
            }else{

                last_p_change = iter_counter;
                tl_extension = 0;
                // if (cur_conflict_cnt < 5) printf("conflict count", cur_conflict_cnt);
                 }
                 
                old_conflict_cnt = cur_conflict_cnt;
            
            if (cur_conflict_cnt < min_conflicts){
                //printf("update \n");
                min_conflicts = cur_conflict_cnt;
                //best_coloring = coloring.copy()
                for (int i =0 ; i < node_cnt ;i++)best_coloring[i]= coloring[i]; 
                //if (cur_conflict_cnt < 10) printf("%d conflicts at iteration %d after %d s",min_conflicts, iter_counter, time(NULL) - start_time);
                if (cur_conflict_cnt == 0 && color_cnt <= sizeofSmallestCliqueDf())
                    {
                        if(debug_colorG)printf("done \n \n");
                        job_done = true;
                        printf("GRAPH COLOR RR :");print_tab_int(coloring , node_cnt);
                        *res = cst_colorResult(coloring , color_cnt ,node_cnt ,cur_conflict_cnt) ;
                        return;
                        //for(int i =0 ; i < node_cnt;i++)(*_coloring)[i]=coloring[i]; //si random resoud pb
                        //return cst_colorResult(coloring , color_cnt ,node_cnt ) ;//, iter_counter; // return coloring ? 
                    }
                    else if (cur_conflict_cnt == 0)
                    {
                        //printf("break\n");
                        break;
                    }
            
            }
            best_delta = 1000000 ; 

            for (int n = 0; n < node_cnt; n++) {
                if (fixed==NULL || fixed[n]==0){
                for (int c = 0; c < color_cnt; c++) {
                    if (c != coloring[n]) {
                        int delta = gamma[n][c] - gamma[n][coloring[n]];
                        //printf("delta %d best_delta %d \n",delta,best_delta);
                        if (delta < best_delta) {
                            //printf("bestdelta %d \n",delta);
                            if (tabu_list[n][c]!= -1 && (tabu_list[n][c] < iter_counter || delta + cur_conflict_cnt < min_conflicts)) {
                                best_node = n;
                                best_color = c;
                                best_delta = delta;
                            }
                        }
                    }
                }
            }
        }
            //printf("best_node %d best_color %d \n ", best_node , best_color );
            tl =  (int)(alpha * cur_conflict_cnt  + 0.5 )  + ( rand() %A +1 ) + tl_extension; //round(alpha * cur_conflict_cnt) + ( rand() %A +1 ) + tl_extension;
            color_tabu = coloring[best_node];
            tabu_list[best_node][color_tabu] = tl + iter_counter;
            coloring[best_node] = best_color;

            for  (int i =0 ; i < taille_gamma ; i++ ) {
                if (adj_matrix[i][best_node]){
                    gamma[i][color_tabu] -= 1;
                     gamma[i][best_color] += 1;
                }


            }
            iter_counter++;

            if (iter_counter == MAX_ITERATIONS) {
                int moi =  count_conflicts(adj_matrix, taille_gamma, best_coloring) ;
                //int moi2 = count_conflicts(adj_matrix, taille_gamma, coloring) ;
                //double moi_bis = count_conflicts_degree_based(adj_matrix, node_cnt , best_coloring, nb_edges); 
                //double moi2_bis = count_conflicts_degree_based(adj_matrix, node_cnt , coloring, nb_edges); 
                
                if(debug_colorG)printf("Max iteration count reached (%d == %d ), aborting search for k=%d conflict %d  \n", MAX_ITERATIONS,iter_counter, color_cnt, moi);//,moi_bis,moi2,moi2_bis );
                //print_tab_int (  best_coloring  , node_cnt  );
                for(int i =0 ; i < node_cnt;i++){coloring[i]=(last_coloring[0]>=0?last_coloring[i]:best_coloring[i]);
                }
                 printf("GRAPH COLOR RR :");print_tab_int(coloring , node_cnt);
                *res=cst_colorResult(coloring , color_cnt+1 ,node_cnt  ,cur_conflict_cnt) ;
                return;
                //return cst_colorResult(coloring , color_cnt+1 ,node_cnt  ) ; // iter_counter;
            }

            if (timeout != 0 && (( time(NULL) - start_time) > timeout)) {
               time_t mytime =(time(NULL) - start_time);
                struct tm * time_str = gmtime(&mytime);
                int moi =  count_conflicts(adj_matrix, taille_gamma, best_coloring) ;
                if(debug_colorG)printf("Timeout reached ( %d sec <  %d sec ), aborting search for k=%d conflict %d  \n",timeout, 60*time_str->tm_min+ time_str->tm_sec, color_cnt, moi);//,moi_bis,moi2,moi2_bis );

               
                //print_tab_int (  best_coloring  , node_cnt  );
                 for(int i =0 ; i < node_cnt;i++){coloring[i]=(last_coloring[0]>=0?last_coloring[i]:best_coloring[i]);
                    }
                *res=cst_colorResult(coloring , color_cnt+1 ,node_cnt ,cur_conflict_cnt) ;
                return;
                    //return cst_colorResult(coloring , color_cnt+1 ,node_cnt ) ; // iter_counter;
            }
            

            //job_done = true; break;
        }
            time_t mytime =(time(NULL) - start_time);
            struct tm * time_str = gmtime(&mytime);
            if(debug_colorG)printf("Found solution within %d min %d sec \n ",time_str->tm_min, time_str->tm_sec) ;
            int moi =  count_conflicts(adj_matrix, taille_gamma, best_coloring) ;
            if(debug_colorG)printf("CONFLICT SOL %d ",moi);
            if(debug_colorG)printf("COLOR %d\n",color_cnt);
            //if(debug_colorG)print_tab_int (  best_coloring  , node_cnt  );
      
            if (!do_opt || color_cnt <= stop_k) {

                //for(int i =0 ; i < node_cnt;i++)(*_coloring)[i]=best_coloring[i];
                 printf("GRAPH COLOR RR :");print_tab_int(best_coloring , node_cnt);
                  *res =cst_colorResult(best_coloring , color_cnt  ,node_cnt ,cur_conflict_cnt) ;
                  return;
                  //return cst_colorResult(best_coloring , color_cnt  ,node_cnt  ) ;  //, iter_counter
            }
            color_cnt --;
            
    }
           //for(int i =0 ; i < node_cnt;i++)(*_coloring)[i]=best_coloring[i];
            
            printf("GRAPH COLOR RR :");print_tab_int(best_coloring , node_cnt);
           *res =cst_colorResult(best_coloring , color_cnt  ,node_cnt  ,cur_conflict_cnt) ;
           return;
           //return cst_colorResult(best_coloring , color_cnt  ,node_cnt  ) ;
}
*/