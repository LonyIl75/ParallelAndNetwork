

 
/**
 * fichier:Point.c
 * auteur: Rambal Julien
 * description : Implemente un point ou un nuage de point sans fonction supplémentaire 
 **/


#include"Point.h"


struct myPoint* Point(size_t taille ){
	struct myPoint* pt = malloc(1*sizeof(struct myPoint ));
	pt->taille=taille;
	pt->arr=(double*)malloc(taille*sizeof(double));
	for(int i = 0 ; i < pt->taille;i++)pt->arr[i]=0;
	return pt;

}

void printPoint(struct myPoint * pt){
	printf("taille point : %ld \n",pt->taille);
	print_tab_double (pt->arr , pt->taille);

}

void printTabPoint(struct myPoint ** pts , size_t taille ){
	for(int i = 0; i<taille;i++){
		printPoint(pts[i]);

	}

}
struct myPoint* arrToPointCpy(double * arr , size_t taille){
	struct myPoint* pt = malloc(1*sizeof(struct myPoint ));
	pt->arr=(double*)malloc(taille*sizeof(double));
	for(pt->taille = 0 ; pt->taille < taille;pt->taille++)pt->arr[pt->taille]=arr[pt->taille];
	return pt;
}


struct myPoint* arrToPoint(double * arr , size_t taille){
	struct myPoint* pt = malloc(1*sizeof(struct myPoint ));
	pt->taille=taille;
	pt->arr=arr;
	return pt;

}




struct myPoint ** initCollectionPoint(size_t taille , size_t dim){
	struct myPoint** res = (struct myPoint**) malloc(taille*sizeof(struct myPoint*)); //Faire le calcul ici et assigner le resultat à res 
        for(int i = 0; i<taille; i++){
        	res[i] = Point(dim );
            for(int j = 0; j<dim; j++){
                res[i]->arr[j]=0;
            }
        }
        return res ; 
}

/*

double** affinityMatrix ( )//TODO ajoute fonction de distance squared par defaut euclidean squared
{



}*/

struct myPoint ** collectionPointCpy(double** points , size_t taille , size_t dim){
	struct myPoint** res = (struct myPoint**) malloc(taille*sizeof(struct myPoint*)); //Faire le calcul ici et assigner le resultat à res 
        for(int i = 0; i<taille; i++){
        	res[i] = arrToPointCpy(points[i],dim );
            
        }
        return res ; 
}


struct myPoint ** collectionPoint(double** points , size_t taille , size_t dim){
	struct myPoint** res = (struct myPoint**) malloc(taille*sizeof(struct myPoint*)); //Faire le calcul ici et assigner le resultat à res 
        for(int i = 0; i<taille; i++){
        	res[i] = arrToPoint(points[i],dim );
            
        }
        return res ; 
}