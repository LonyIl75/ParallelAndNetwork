

/**
 * fichier: Stub.c
 * auteur: Rambal Julien
 * description : Stub divers non inclu dans le code deja epprouver
 **/




#include"Stub.h"

int **  allocation_matrix( int  sz_row , int sz_col ){

   int **  matrix = (int**) malloc(sizeof(int*)*sz_row);
    for(int i =0;i< sz_row ;i++ ){
            matrix[i]=(int*) malloc(sizeof(int)*sz_col);
    }
    return matrix ;
}

void init_bitmatrix(  int ** matrix ,int  sz_row , int sz_col ){

    for(int i =0;i< sz_row ;i++ ){
          //printf("i %d \n",i);
        for(int j=0 ; j< sz_col;j++){
           // printf("j %d \n",j);
        if(i==0 || j==0 )matrix[i][j]=1;
        else if(i!=j)matrix[i][j]=(i+j)%2; //1/2 case a 1 comme un damier/echequier sauf  diag 
        else if(i==j)matrix[i][j]=0;

    }
    }
}

void init_bitmatrix2(  int ** matrix ,int  sz_row , int sz_col ){ 

    for(int i =0;i< sz_row ;i++ ){
          //printf("i %d \n",i);
        for(int j=0 ; j< sz_col;j++){
           // printf("j %d \n",j);
        if(i!=j)matrix[i][j]=(i+j)%2; //1/2 case a 1 comme un damier/echequier sauf  diag 
        else if(i==j)matrix[i][j]=0;

    }
    }
}

void print_matrix (int **matrix , int  sz_row , int sz_col ){
     for(int i =0;i<sz_row ;i++ ){
        printf("[|");
        for(int j=0 ; j<sz_col ;j++){
        printf(" %d|",matrix[i][j]);

    }
    printf("]\n");
    }

}