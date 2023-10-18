/**
 * fichier: algebre.h
 * auteur: Rambal Julien
 * description : Fonction d'algebre et de statistique élémentaire 
**/



#include "algebre.h"


//DEBUT JONATHAN 
int getMatValue(int *mat,int side, int i, int j){
    return mat[((i-1)*side + j)-1];
}

void setSymMatValue(int *mat,int side, int i, int j){
    mat[((i-1)*side + j)-1]=1;
    mat[((j-1)*side + i)-1]=1;
}
//JONATHAN FIN 

double** convertToDouble ( int** arr , size_t nb_r , size_t nb_c ){
	double ** conv_arr = (double**)malloc(nb_r*sizeof(double*));
	for(int i = 0 ; i< nb_r ; i++){
		conv_arr[i]=(double*)malloc(nb_c*sizeof(double));
		for(int j =0 ; j < nb_c ; j++){
		conv_arr[i][j] = (double)arr[i][j];
	}
		//free(arr[i]);
	}
	//free(arr); 
	return conv_arr; 
}

double * convertToUniDir ( double ** arr , size_t nb_r, size_t nb_c ){
	double* conv_arr = (double *)malloc(nb_r*nb_c*sizeof( arr[0][0]));
	for(int i = 0 ; i< nb_r ; i++){
		for(int j =0 ; j <  nb_c ; j++){
		conv_arr[i*nb_c+j] = arr[i][j];
	}
		//free(arr[i]);
	}
	//free(arr);
	return conv_arr; 
}
double * convertToUniDirSq ( double** arr , size_t square_taille){
	return convertToUniDir(arr, square_taille,square_taille);
}

double ** convertToBiDir ( double * arr , size_t nb_r, size_t nb_c ){
	double ** conv_arr = (double**)malloc(nb_r*sizeof(double*));
	for(int i = 0 ; i< nb_r ; i++){
		conv_arr[i]=(double*)malloc(nb_c*sizeof(double));//arr[0]));
		for(int j =0 ; j <  nb_c ; j++){
		conv_arr[i][j] = arr[i*nb_c+j];

	}
	}
	free(arr);
	return conv_arr; 
}

double ** convertToBiDirSq ( void * arr , size_t square_taille ){
	return convertToBiDir ( arr , square_taille, square_taille );

}


double** convertToDoubleSq ( int** arr , size_t square_taille){
	return convertToDouble(arr,square_taille,square_taille);

}

double* convertToDouble2Sq ( int** arr , size_t square_taille){
	double** tmp = convertToDouble(arr,square_taille,square_taille) ;
	double *res = (double*)convertToUniDir ( tmp , square_taille,square_taille);
	return res ;  


}

double** substractMatrix(double** mat1 , double** mat2, size_t nb_r , size_t nb_c ){ // TODO a templater je me rappelle plus comment faire voir tp multimedia i guess L3 
	double ** res_arr = (double**)malloc(nb_r*sizeof(double*));
	for(int i = 0 ; i< nb_r ; i++){
		res_arr[i]=(double*)malloc(nb_c*sizeof(double));
		for(int j =0 ; j < nb_c ; j++){
			res_arr[i][j]= mat1[i][j]-mat2[i][j];
		}
	}
	return res_arr;

}
double** substractMatrixSq(double** mat1 , double** mat2, size_t square_taille ){ 
	return substractMatrix(mat1,mat2,square_taille,square_taille);
}


double** addMatrix(double** mat1 , double** mat2, size_t nb_r , size_t nb_c ){ // TODO a templater je me rappelle plus comment faire voir tp multimedia i guess L3 
	double ** res_arr = (double**)malloc(nb_r*sizeof(double*));
	for(int i = 0 ; i< nb_r ; i++){
		res_arr[i]=(double*)malloc(nb_c*sizeof(double));
		for(int j =0 ; j < nb_c ; j++){
			res_arr[i][j]= mat1[i][j]+mat2[i][j];
		}
	}
	return res_arr;

}
double** addMatrixSq(double** mat1 , double** mat2, size_t square_taille ){ 
	return addMatrix(mat1,mat2,square_taille,square_taille);
}



double** toDiagonal(double* arr , size_t taille ){
	double ** res_arr = (double**)malloc(taille*sizeof(double*));
	for(int i = 0 ; i< taille ; i++){
		res_arr[i]=(double*)malloc(taille*sizeof(double));
		for(int j =0 ; j < taille ; j++){
			if(i==j){res_arr[i][j]=arr[i];}
			else {res_arr[i][j]=0;}
}
}
//free(arr);
return res_arr;
}

double squaredEDist( double * pt1 , double *pt2 , size_t taille){
	double sum =0;
	for(int i =0 ; i < taille ; i++){
		sum+=pow((pt1[i]-pt2[i]),2);
	}
	assert(sum >= 0 );
	return sum ; 
}

double EDist( double * pt1 , double * pt2 , size_t taille ){ 
	return pow(squaredEDist(pt1,pt2,taille) , 0.5);
}

double pnorm(double* x, int n, double p) {
	double result=0;
	int i;
	for (int i=0;i<n;i++) {

		result += pow(fabs(x[i]),p);
	}
	if(debug_algebre)printf("pnorm result %f  \n ",result );
	return pow(result, (double) 1/p);
}

double squaredFrobeniusNorm( double** mat , size_t nb_r , size_t nb_c){
	double sum =0;
	for(int i =0 ; i< nb_r ;i++){
		printf("%f nomr \n ",pnorm(mat[i], nb_c, 2) );
		sum+=pnorm(mat[i], nb_c, 2);
	}
	return sum;
}

double FrobeniusNorm( double** mat , size_t nb_r , size_t nb_c){

	return sqrt(squaredFrobeniusNorm(  mat ,  nb_r ,  nb_c));
}


double** diagPowerCpy (double** mat , double power , size_t nb_r ,size_t nb_c  ){

	 double** res = (double**)malloc(nb_r *sizeof(double*));

	for(int i = 0 ; i < nb_r ; i++){
		res[i]=(double*)malloc(nb_c*sizeof(double));
		for(int j = 0 ; j < nb_c ; j++){
		if(i==j){if(mat[i][i])res[i][j]=pow(mat[i][i],power);}
		else{
			res[i][j]=0;
		}
	}
}
	return mat ; 

}

double** diagPowerCpySq (double** mat , double power , size_t square_taille ){
	return diagPowerCpy ( mat ,  power , square_taille, square_taille );
}


void diagPower(double** mat , double power , size_t nb_r ,size_t nb_c  ){
	for(int i = 0 ; i < nb_r ; i++){
		if(mat[i][i])mat[i][i]=pow(mat[i][i],power);


		}

}

void diagPowerSq (double** mat , double power , size_t square_taille ){
	
	return diagPower ( mat ,  power , square_taille, square_taille );
}


double** multMatrix(double**  m1 ,double** m2,size_t taille ,size_t dim) { // calcul du produit matriciel m1.m2
        //Pour acceder a un element de la premiere matrice (*this)(i,j) et de la deuxième m2(k,l)

        double** res = (double**)malloc(taille *sizeof(double*));
         
        for(int i = 0; i<taille; i++){
        	res[i]=(double*)malloc(dim*sizeof(double));
            for(int j = 0; j<dim; j++){
            	res[i][j]=0;
                for(int a = 0; a<dim; a++){
                    res[i][j] += m1[i][a] * m2[a][j];
                }
            }
        } 
        return res;
    }

double** multMatrixSq(double**  m1 ,double** m2 ,size_t square_taille  ) { // calcul du produit matriciel m1.m2
    	return multMatrix(m1 ,m2 ,  square_taille, square_taille );
   }

    double** multMatrixScalar(double**  m1 ,double scalar ,size_t taille ,size_t dim ) { // calcul du produit matriciel m1.m2
        //Pour acceder a un element de la premiere matrice (*this)(i,j) et de la deuxième m2(k,l)
        double** res = (double**)malloc(taille *sizeof(double*));
         
        for(int i = 0; i<taille; i++){
        	res[i]=(double*)malloc(dim*sizeof(double));

            for(int j = 0; j<dim; j++){
                    res[i][j] = m1[i][j] * scalar;
            }
        } 
        return res;
    }

double** multMatrixScalarSq(double**  m1 ,double scalar ,size_t square_taille  ) { // calcul du produit matriciel m1.m2
    	return multMatrixScalar(m1 ,scalar ,  square_taille, square_taille );
    }

double* normalizingVector(double* v , size_t taille ){
	double* vm = (double*)malloc(taille*sizeof(double));
	double sum =0;
	for(int i =0 ; i<taille ; i++){
		sum+=pow(v[i],2);
	}
	double a = sqrt(sum);
		for(int i =0 ; i<taille ; i++){
		vm[i]=v[i]/a;
	}
	return vm;

}

double** normalizingBunchOfVector(double** vs , size_t taille , int* tab_taille  ){
	double** res = (double**)malloc(sizeof(double*)*taille);

	for(int i =0 ; i<taille ; i++){
		res[i]= normalizingVector(vs[i] , tab_taille[i] );
	}
	return res;

}
int closestPower2( int val ){
    return (int)(val==0?-1:pow(2,log(val)) );
}


double * compute_mean ( struct myPoint ** points ,size_t taille , size_t dim){
	double* tab_mean = (double*)malloc( sizeof(double)* dim);
	for(int i =0 ; i < dim ; i++)tab_mean[i]=0;
	struct myPoint* ptr_Pt = points[0];
	for(int i =0 ; i < taille ; i++){
		ptr_Pt = points[i];
		assert(dim==ptr_Pt->taille);
		for(int j=0 ; j < dim ; j++){
			tab_mean[j]+=(ptr_Pt->arr[j]/(double)taille);
		}
	}
	//print_tab_double (tab_mean , dim);
	return tab_mean ; 
}
double *  compute_variance (struct myPoint ** points , size_t taille , size_t dim ){
	double* tab_variance = (double*)malloc( sizeof(double)* dim);
	for(int i =0 ; i < dim ; i++)tab_variance[i]=0;
	struct myPoint* ptr_Pt = points[0];
	double* tab_mean = compute_mean ( points ,taille ,  dim);
	for(int i =0 ; i < taille ; i++){
		ptr_Pt = points[i];
		assert(dim==ptr_Pt->taille);
		for(int j=0 ; j < dim ; j++){
			tab_variance[j]+=(pow( ptr_Pt->arr[j] - tab_mean[j],2)/(double)taille);
		}
	}
	free(tab_mean);
	return tab_variance;

}
double *  compute_stdDeviation (struct myPoint ** points , size_t taille , size_t dim ){
	double* tab_stdDevi = (double*)malloc( sizeof(double)* dim);
	for(int i =0 ; i < dim ; i++)tab_stdDevi[i]=0;
	struct myPoint* ptr_Pt = points[0];
	double* tab_var = compute_variance ( points ,taille ,  dim);
	for(int j =0 ; j < dim ; j++){
		tab_stdDevi[j]= sqrt(tab_var[j]);
	}
	free(tab_var);
	return tab_stdDevi;
}


