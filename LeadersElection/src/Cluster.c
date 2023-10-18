



/**
 * fichier:Cluster.c
 * auteur: Rambal Julien
 * description : Tout ce qui est necessaire pour clusteuriser le graph ainsi que les structures sous jacentes 
 **/



#include "Cluster.h"





struct myPoint** initCentroid (  struct myPoint ** points , size_t taille , size_t dim ,size_t nb_cluster  ){

	double** centroids = (double**)malloc(nb_cluster*sizeof(double*));
	/*for(int i=0;i<nb_cluster;i++){
		centroids[i]=(double*)malloc(dim*sizeof(double));
		for( int j =0 ; j < dim ; j++){
			centroids[i][j]=0;
		}
	}*/

	double* tab_mean = compute_mean ( points ,  taille ,  dim);
	double* tab_stdDevi = compute_stdDeviation ( points ,  taille ,  dim );
	double* stdDevi_i = NULL;

	int max_std = nb_cluster/2 ; 

	for(int std =0 ; std <= max_std  ;std++){
		
		stdDevi_i = *multMatrixScalar(&tab_stdDevi ,std ,1,dim);

		centroids[max_std + std ]=*addMatrix(&tab_mean , &stdDevi_i, 1 , dim );
		if(std>0){
			centroids[max_std - std ]=*substractMatrix(&tab_mean , &stdDevi_i, 1 , dim );
		}
}

free(tab_stdDevi);
free(tab_mean);

	
return collectionPoint(centroids,nb_cluster,dim) ;


}

struct myPoint** initCentroid2 (  struct myPoint ** points , size_t taille , size_t dim ,size_t nb_cluster  ){

	double** centroids = (double**)malloc(nb_cluster*sizeof(double*));
	/*for(int i=0;i<nb_cluster;i++){
		centroids[i]=(double*)malloc(dim*sizeof(double));
		for( int j =0 ; j < dim ; j++){
			centroids[i][j]=0;
		}
	}*/

	double* tab_mean = compute_mean ( points ,  taille ,  dim);
	double* tab_stdDevi = compute_stdDeviation ( points ,  taille ,  dim );
	double* stdDevi_i = (double*)malloc(dim*sizeof(double));

	if(debug_cluster)print_tab_double(tab_mean, dim);
	double p = (double)1.0/(double)(nb_cluster+1);
	double deb = 0;

	for(int std =0 ; std < nb_cluster  ;std++){
		deb+=p;
		for(int i =0 ; i < dim ;i++){
			
			stdDevi_i[i]= gsl_cdf_gaussian_Qinv(deb, tab_stdDevi[i]);
			//printf("%f stdDevi %f %f\n",stdDevi_i[i],deb, tab_stdDevi[i]);
		}

		if(debug_cluster)print_tab_double(stdDevi_i, dim);
		centroids[std ]=*addMatrix(&tab_mean , &stdDevi_i, 1 , dim );

}

free(tab_stdDevi);
free(tab_mean);

	
return collectionPoint(centroids,nb_cluster,dim) ;


}



double d_distance(const Pointer a, const Pointer b)
{
	struct myPoint* da = ((struct myPoint*)a);
	struct myPoint* db = ((struct myPoint *)b);
	assert(da->taille == db->taille);
	/*printf("Edist %f \n",EDist(da->arr,db->arr,da->taille));
	printPoint(da);
	printPoint(db);*/
	return EDist(da->arr,db->arr,da->taille);
}

void d_centroid(const Pointer * objs, const int * clusters, size_t num_objs, int cluster, Pointer centroid)
{
	int i;
	int num_cluster = 0;
	struct myPoint **arr_points = (struct myPoint**)objs;
	struct myPoint *points_centroid = (struct myPoint*)centroid;
	size_t dim = arr_points[0]->taille ; 
	struct myPoint *  dcentroid = (struct myPoint *) centroid; 
	//printf("Cluster \n");
	//print_tab_int(clusters,cluster);
	//printf("Deb \n");
	//printPoint(dcentroid);
	double * sum = (double*)malloc(dim *sizeof(double*));
	for(int i =0 ; i < dim  ; i++ ){
		sum[i]=0;
	}

	if (num_objs <= 0) return;

	for (i = 0; i < num_objs; i++)
	{
		/* Only process objects of interest */
		if (clusters[i] != cluster)
			{continue;}
		//printf("I %d \n",i);
		for ( int j =0 ; j < dim ;j++){
		sum[j] += arr_points[i]->arr[j];
		}
		num_cluster++;
	}
	//printf("cluster %d num_cluster %d \n",cluster,num_cluster);
	if (num_cluster)
	{
		for ( int j =0 ; j < dim ;j++){
		sum[j] /= num_cluster;
		}
		dcentroid->arr = sum;
	}
	//printf("End \n");
	//printPoint(dcentroid);
	//printf("\n \n");
	return;
}




struct myPoint ** centree(struct myPoint ** points , size_t taille ){
	int* clusters=(int*)malloc(taille*sizeof(int));
	for(int i  = 0 ; i < taille;i++)clusters[i]=defaultCluster();
	struct myPoint * centroid = Point(taille); 
	double** tmp = NULL;
	d_centroid((const Pointer *)  points,  clusters, taille, defaultCluster(), (Pointer) centroid);
	for(int i  = 0 ; i < taille;i++){
		tmp=substractMatrix( &points[i]->arr , &centroid->arr, 1, centroid->taille );
		//free(points[i]->arr);
		points[i]->arr= *tmp;

	}

}
void minDist ( struct myPoint** points ,  struct myPoint** points2  , size_t taille ,size_t taille2 )
{
	struct myPoint* ptr_Pt = NULL;
	double min , curDist ;
	int index_min ;
	int dim = points[0]->taille; 
	assert(points[0]->taille==points2[0]->taille);
	double * min_tab = (double*)malloc(sizeof(double)*taille2);

	curDist=0;
	for(int i =0 ; i < taille ; i++){
		ptr_Pt=points[i];
		min=10000000000000;
		index_min =0;
		for(int i  = 0 ; i < taille;i++)min_tab[i]=0;
		for(int j =0; j< taille2;j++){
		
				min_tab[j] = EDist( ptr_Pt->arr ,points2[j]->arr , dim);
				
				if(min> min_tab[j] ){
					min=min_tab[j];
					index_min=j;
				}
			
		}
		if(DEBUG_CL){
		print_tab_double(min_tab,taille);
		printf("index_min %d val_min %f \n",index_min,min);
		printf("\n\n");
	}

	}
	free(min_tab);

}

 int*  maxDegreeCluster(int*idCluster,int * tabEdges,size_t taille , size_t taille2){
	int *  tab_maxDegree = (int*)malloc(taille*sizeof(int ));
	for(int i =0 ; i<taille ; i ++){
		tab_maxDegree[i]=0;
	}
	for(int j =0 ; j < taille2 ;j++){
		if(tab_maxDegree[idCluster[j]]< tabEdges[j]){
			tab_maxDegree[idCluster[j]]=tabEdges[j];
		}
	}
	if(debug_cluster){
		printf("maxDegree");
		print_tab_int(tab_maxDegree,taille);
	}
	return tab_maxDegree;

}

int eigenDecomp(struct GraphData * _graphD, double** eigen_vectors , double** eigen_values ){

	
	int graph_size =  _graphD->nodesQuantity;

	//PARAM & CONVERSION : 
	double** incidence2 = convertToDoubleSq( _graphD->matrix , graph_size);
	double** edges2 = convertToDouble( &_graphD->tabNbEdges , 1,graph_size);

	//LAPLACIENNE
	double** matrix_degree2 = toDiagonal(*edges2 ,graph_size );
	double ** subst_matrix2 = substractMatrixSq(matrix_degree2,incidence2,graph_size );
    diagPowerSq(matrix_degree2,-0.5,graph_size);

    //LAPLACIENNE NORMALISE
    double ** DL = multMatrixSq(matrix_degree2 ,subst_matrix2,graph_size) ;
    double ** DLD = multMatrixSq(DL ,matrix_degree2,graph_size) ;

    //PARAM & CONVERSION BIS
    double * subst_matrix1=convertToUniDirSq (DLD,graph_size);
   

 	//EIGEN DECOMP
    return rs ( graph_size, subst_matrix1, *eigen_values , 1, *eigen_vectors );


	
}






struct ClusteringParam * base_ClusteringParam (struct GraphData * _graphD){
       struct ClusteringParam* clParam = (struct ClusteringParam*)malloc(1*sizeof(struct ClusteringParam));
        clParam->graphD=_graphD;
       
        return clParam;
}

struct ClusteringParam * cstdef_ClusteringParam(struct GraphData * _graphD){
    struct ClusteringParam* clParam = base_ClusteringParam ( _graphD);
    clParam->nb_cluster=DEFAULT_NB_CLUSTER;
    clParam->max_iteration=DEFAULT_MAX_ITER;
    clParam->strategie=1;
    return clParam;
}

struct ClusteringParam * cst_ClusteringParam(struct GraphData * _graphD,int _nbCluster,int _maxIteration){
    struct ClusteringParam* clParam = cstdef_ClusteringParam( _graphD);
    clParam->nb_cluster=_nbCluster;
    clParam->max_iteration=_maxIteration;
     return clParam;
}






kmeans_config*  base_KmeansParam (struct myPoint** PopV  , size_t taille_pop ){
       kmeans_config* Kconfig = (kmeans_config*)malloc(1*sizeof(kmeans_config));
       Kconfig->num_objs = taille_pop+1; //sz + NULL

       Kconfig->objs = (Pointer*) malloc(Kconfig->num_objs* sizeof(Pointer));


       for(int i =0 ; i < taille_pop ;i++)Kconfig->objs[i] =(Pointer)PopV[i];
	   Kconfig->objs[taille_pop] = NULL;

		
		Kconfig->clusters = (int*) malloc(Kconfig->num_objs*sizeof(int));
		for(int i =0 ; i < Kconfig->num_objs ;i++)Kconfig->clusters[i] =0;

        return Kconfig;
}



kmeans_config* cstdef_ConfigKmeans(struct myPoint** PopV  , size_t taille_pop   ){  	
	kmeans_config* Kconfig = base_KmeansParam (  PopV, taille_pop );

	Kconfig->k = DEFAULT_NB_CLUSTER ;
	Kconfig->max_iterations = DEFAULT_MAX_ITER;
	Kconfig->distance_method = d_distance;
	Kconfig->centroid_method = d_centroid;

	Kconfig->centers = (Pointer*) malloc(Kconfig->k*sizeof(Pointer));

	Kconfig->centers = (Pointer*) initCentroid2 (  PopV, Kconfig->num_objs-1 ,Kconfig->k  ,PopV[0]->taille );

	return Kconfig;

}

kmeans_config* cst_ConfigKmeans(struct myPoint** PopV  , size_t taille_pop   , size_t dim , int select ){ // la dim de la pop peut être plus grande que la dim specifier , la dim specifier permets de ne considérer  que les dim premiere dim
  	
	kmeans_config* Kconfig = base_KmeansParam (  PopV, taille_pop );

	Kconfig->k = DEFAULT_NB_CLUSTER ;
	Kconfig->max_iterations = DEFAULT_MAX_ITER;
	Kconfig->distance_method = d_distance;
	Kconfig->centroid_method = d_centroid;

	Kconfig->centers = (Pointer*) malloc(Kconfig->k*sizeof(Pointer));


	if(select==1)Kconfig->centers = (Pointer*) initCentroid2 (  PopV, Kconfig->num_objs-1 ,Kconfig->k  ,dim );

	return Kconfig;

}


int checkClusteringParam(struct ClusteringParam* params){
	return 1;
}

int* makeClusters(struct ClusteringParam* params ){

	struct GraphData * _graphD = params->graphD;
	int graphSize =  _graphD->nodesQuantity;
	int nbCluster= params->nb_cluster;

	//PARAM
	double * eigen_vectors = (double*) malloc( pow(graphSize,2) *sizeof(double));
    for(int i = 0; i<pow(graphSize,2); i++)eigen_vectors[i]=0;
    double * eigen_values = (double*) malloc( graphSize *sizeof(double));
 	for(int i = 0; i<graphSize; i++)eigen_values[i]=0;

 	//EIGEN DECOMP
 	int err_rs = eigenDecomp(_graphD, &eigen_vectors , &eigen_values );

 	//CONVERSION  
 	double** S = toDiagonal(eigen_values ,graphSize );  

    double** V = convertToBiDirSq ( eigen_vectors ,graphSize );

    int* taille_tab= taille_bisInt (&graphSize , graphSize );
    //printTabtab_double( V , graphSize,  taille_tab);
    double** NV = normalizingBunchOfVector( V ,graphSize ,taille_tab  );
    //printf("vs \n\n ");
    //printTabtab_double( NV , graphSize,  taille_tab);	

	struct myPoint** PS = collectionPointCpy(S,graphSize ,nbCluster);

    struct myPoint** PNV = collectionPointCpy(NV,graphSize ,nbCluster);

    //INIT CONFIG 
    kmeans_config* Kconfig = cst_ConfigKmeans( PNV  , graphSize  , nbCluster , params->strategie ); // la dim de la pop peut être plus grande que la dim specifier , la dim specifier permets de ne considérer  que les dim premiere dim
  	
  	//KMEANS
   kmeans_result Kresult = kmeans(Kconfig); //TODO pas ptr a voir 

    return  Kconfig->clusters;
 		return NULL;



 }


 struct ClusterMeta *  base_ClusterMeta(){


 	struct ClusterMeta * cluster = (struct ClusterMeta *)malloc(1*sizeof(struct ClusterMeta ));

 	cluster->nb_cluster=0;

 	cluster->cluster1D=NULL;

 	cluster->bestColoring = NULL;

 	cluster->cluster2DTaille=(int**)malloc(2*sizeof(int*));//car on dois le passer en paramètre car deux return impossible => init le ptr pour pouvoir écrire dessus

    cluster->cluster2DTaille[0]=NULL;
    cluster->cluster2DTaille[1]=NULL;

//les fonctions suivantes realloqueront pour arriver à un tab de taille nb_cluster * cluster2DTaille[0][i] 
    cluster->cluster2DdjMat=NULL;

    cluster->cluster2DTrad=NULL;

    return cluster;


 }


void initClusterMeta (struct ClusteringParam* params , struct ClusterMeta * cluster ){

	struct GraphData * graphD = params->graphD;
	int graphSize =  graphD->nodesQuantity;
	int nbCluster= params->nb_cluster;

	cluster->bestColoring= (struct ColorationResult **)malloc(sizeof(struct ColorationResult *)* graphSize);
    //for(int i = 0 ; i < _graphD->nodesQuantity ;i++)clParam->bestColorCount[i]=base_colorResult(_graphD->nodesQuantity );
        

   	cluster->cluster1D = makeClusters( params);



if(DEBUG_CL){
    printf("Cluster du graph : \n ");
    print_tab_int ( cluster->cluster1D  , graphSize );
}

    cluster->nb_cluster= nbCluster;
    cluster->cluster2DdjMat= (int***) malloc(  nbCluster *sizeof(int**));
    cluster->cluster2DTrad =(int**) malloc(  nbCluster *sizeof(int*));                           
    classCluster ( &cluster->cluster2DTrad  , cluster->cluster1D ,graphSize,nbCluster, &cluster->cluster2DTaille );


    printTabtab_int( cluster->cluster2DTrad ,nbCluster, cluster->cluster2DTaille[0]);

      printTabtab_int( cluster->cluster2DTrad ,nbCluster, cluster->cluster2DTaille[1]);


    

    //printTabtab_int2(  graphD->matrix ,graphSize);

                    
     adjClusterGraph(  graphD ,   cluster );

if(debug_cluster){
    printf("adjCluster & Trad : \n ");
    for(int i=0 ;i < nbCluster ;i++) {
        if(DEBUG_CL)printTabtab_int2(cluster->cluster2DdjMat[i],cluster->cluster2DTaille[0][i]);
        print_tab_int(cluster->cluster2DTrad[i],cluster->cluster2DTaille[0][i]);
        }
    }



    }

const char idClusterDelim(){return ':';}

char* idClusterDelim2(){
	char* delim = (char*)malloc(2);
	delim[0]=idClusterDelim();
	delim[1]='\0';
	return delim ;
}


char* idClusterTabTab (int** tabTab, size_t taille2 , size_t taille , const char * concatEndDelim , int idmax ,int select, int idCluster ){ //pour Adj par ex

		char* tabTabStr=intTabTabToString (  tabTab ,  taille2 ,  taille , concatEndDelim , 1 , 0  );//idmax == nb_cluster
		return fusionNbStr(tabTabStr ,idCluster ,idClusterDelim());
	
}



char* idClusterTab  ( int* tab , size_t  squareTaille , int color_cnt ,const char  concatEndDelim  ,int idCluster   ,int select ){//idmax == nb_cluster //select==1 pour coloration 


		char* tabStr= intTabToString(  tab  , squareTaille , concatEndDelim, color_cnt-1 , 0  );//idmax == nb_cluster
		return fusionNbStr(tabStr ,idCluster ,idClusterDelim() );
	
}


char* idClusterStr  ( char* str ,int idCluster   ){//idmax == nb_cluster //select==1 pour coloration 

		return fusionNbStr( str ,idCluster ,idClusterDelim() );
	
}




int* nbPerCluster ( int* cluster , size_t taille , int nb_cluster ){ // renvoie le nombre de elements dans chaque cluster 
	int* tab_res =(int*) malloc( nb_cluster *sizeof(int));
	for(int i=0 ; i < taille ;i++){
		tab_res[cluster[i]]++;
	}
	return tab_res;
}



// renvoie nb_cluster tableau de noeuds , ex le tableau 0 = idnoeuds dans cluster 0 
void  classCluster ( int*** tab_res2 , int* cluster ,size_t taille, int nb_cluster, int*** tab_tailleAndIndex ){  //cluster[id_item]= id_cluster; => il y a  taille item
	//int** tab_res =(int**) malloc( nb_cluster *sizeof(int*));

	int** tab_res =*tab_res2;
	int init_taille=1;
	if(1||debug_cluster){printf("nb cluster %d \n",nb_cluster );}
	for(int i = 0 ; i < nb_cluster ;i++)tab_res[i]=(int*)malloc(init_taille*sizeof(int));
	
	//*tab_tailleAndIndex =realloc(tab_tailleAndIndex ,  nb_cluster );
	int ** ptr_tailleAndIndex = *tab_tailleAndIndex;
	if(ptr_tailleAndIndex[0]!=NULL)free(ptr_tailleAndIndex[0]);
	if(ptr_tailleAndIndex[1]!=NULL)free(ptr_tailleAndIndex[1]);

	ptr_tailleAndIndex[0] =(int*) malloc( nb_cluster *sizeof(int*));
	ptr_tailleAndIndex[1] =(int*) malloc(nb_cluster *sizeof(int*));
		

	for(int i = 0 ; i < nb_cluster ;i++) {
		ptr_tailleAndIndex[0][i]=0;
		ptr_tailleAndIndex[1][i]=init_taille;
	}

	int* ptr_taille ,*ptr_index ;
	ptr_index = ptr_tailleAndIndex[0];
	ptr_taille = ptr_tailleAndIndex[1];
	int*tmp=NULL;
	int k = 0; 

	for(int i=0 ; i < taille ;i++){
		k=cluster[i];
		//ptr_index = (ptr_tailleAndIndex[0]+k);
		//ptr_taille = (ptr_tailleAndIndex[1]+k); 

		if(ptr_index[k] == ptr_taille[k] ) {
			ptr_taille[k]= ptr_taille[k]*2;
			//printf("ol %d %d %p OOOOO \n\n",k,ptr_taille[k],tab_res[k]);
			tmp= (int*)malloc(sizeof(int)*ptr_taille[k]);
			for(int o = 0 ; o < ptr_index[k] ;o++)tmp[o]=tab_res[k][o];
			free(tab_res[k]);
			tab_res[k]=tmp;
			//tab_res[k] = realloc( tab_res[k] ,  ptr_taille[k]);
			//printf("ol %d  %p  OOOOO \n\n",i,tab_res[k]);
		}
		
		tab_res[k][ptr_index[k]]=i ;
		//printf("i : %d cluster :%d index %d val :%d  \n ",i , k,ptr_index[k],tab_res[k][ptr_index[k]]);
		ptr_index[k]++;//*ptr_index++;
	}


	//printf("ol\n");
		//print_tab_int(ptr_tailleAndIndex[1],nb_cluster);
	//print_tab_int(ptr_tailleAndIndex[0],nb_cluster);
	//printTabtab_int(  tab_res ,nb_cluster, ptr_tailleAndIndex[0]);

	//printf("ol\n");
	//return tab_res;

}




void  adjCluster( int** adj , size_t taille1 ,  int nb_cluster  ,int**tab_tailleAndIndex , int** trad_cluster , int*** resultat ){ // matrice d'adjacence de chaque cluster ,trad_cluster contient les id originel des points du cluster dans la matrice d'adj du graph originel


/*
	int** tab_tailleAndIndex=(int**)malloc(2*sizeof(int*));

 	tab_tailleAndIndex[0]=NULL;
 	tab_tailleAndIndex[1]=NULL;
classCluster ( cluster , taille1,nb_cluster,&tab_tailleAndIndex ) ; 

	int** res_tab = classCluster ( cluster , taille1,nb_cluster,&tab_tailleAndIndex ) ; 
	*/
	int** res_tab =trad_cluster;
	for(int i=0; i< nb_cluster ;i++ ){
	resultat[i]=(int**) malloc(  tab_tailleAndIndex[0][i]  *sizeof(int*));


	for (int j =0; j <  tab_tailleAndIndex[0][i]   ;j++) {
		resultat[i][j]=(int*)malloc(tab_tailleAndIndex[0][i]*sizeof(int));
		resultat[i][j][j]=0;//diag 
		for( int z = 0 ; z < tab_tailleAndIndex[0][i] ;z++){
			if(j!=z)resultat[i][j][z]=-1;
		}
	}
	/*printf("I %d %d\n",i,tab_tailleAndIndex[0][i]);
	printTabtab_int2(resultat[i],tab_tailleAndIndex[0][i]);
	printf("\n \n");*/
}
  


	int * ptr_taille = tab_tailleAndIndex[0];

	int* ptr_index = tab_tailleAndIndex[1];// on va re utiliser le tableau de taille raw ( taille allouer ) comme index et le tableau d'index deviendra le tableau de taille 
	for(int i =0 ; i <  nb_cluster ;i++){
		 ptr_index[i]=0; 
	}


	//print_tab_int(ptr_taille,nb_cluster);



	for(int i =0; i <  nb_cluster   ; i++){ //normalement deja trier but anyway sanity check 

		qsort( res_tab[i] ,ptr_taille[i] , sizeof(int), intComparator ); 

	}


	/*printf("Res  \n");
	printTabtab_int(res_tab,nb_cluster,tab_tailleAndIndex[0]);
	printf("\n \n");*/

	int pos ,stop_cond,k,z ;
	pos=stop_cond=k=z=0;

	//adj res_tab en double subscript 
	for(int i =0 ; i < taille1 ;i++){
		stop_cond=0;
		for( k = 0 ; k < nb_cluster ; k++){
			//printf("éfe %d %d",res_tab[k][ptr_index[k]],i);
			if(res_tab[k][ptr_index[k]]==i ) {
				stop_cond=1;
				break;
			}
		}
		if(stop_cond){


			for( z =ptr_index[k] +1 ; z< ptr_taille[k] ;z++ ){
				/*printf("result %d\n",resultat[0][1][0]);
				printf("result2 %d\n",resultat[0][0][1]);
				printf("%d icic k %d z %d ptr_index %d taille %d\n",res_tab[k][z],k,z,ptr_index[k],ptr_taille[k]);*/
				resultat[k][ptr_index[k]][z]=adj[i][res_tab[k][z]];
				resultat[k][z][ptr_index[k]]=adj[res_tab[k][z]][i];
			}	
			ptr_index[k]++;
		
		

		}
	}


	//
		
		
	//return resultat ;
	 

}

void  adjClusterGraph( struct GraphData *graph ,struct ClusterMeta * cluster ){//int* cluster,int nb_cluster, ,int**tab_tailleAndIndex, int** trad_cluster ){ // matrice d'adjacence de chaque cluster ,trad_cluster contient les id originel des points du cluster dans la matrice d'adj du graph originel

	 adjCluster(  graph->matrix ,graph->nodesQuantity , cluster->nb_cluster , cluster->cluster2DTaille,cluster->cluster2DTrad,cluster->cluster2DdjMat ); 

}




