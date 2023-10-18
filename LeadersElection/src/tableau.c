


/**
 * fichier: tableau.c
 * auteur: Rambal Julien
 * description : Fonctions utiles pour manipuler les tableaux : print , creer , serializer etc 
 **/


#include "tableau.h"

int* cst_nbEdges ( int ** adjMatrix , int nb_node ,int nb_limit){
     if(DEBUG_TABLEAU)printf("11\n");
    int * nb_edges = (int*) malloc(sizeof(int)*nb_node);
    for (int i =0; i <nb_node ;i++){
        nb_edges[i]=0;
    }
    for(int i = 0;i<nb_node ;i++){
        for(int j =0 ; j<nb_limit ; j++){
        //printf("i %d j %d %d \n", i , j ,adjMatrix[i][j] );
        if(0<adjMatrix[i][j] && adjMatrix[i][j]<INT_MAX) nb_edges[i]++;
    }
    //printf("edge %d\n\n",nb_edges[i]);
    }
    return nb_edges;

}

int* cst_nbEdgesAdj ( int ** adjMatrix , int taille_square ){
    return cst_nbEdges ( adjMatrix ,  taille_square , taille_square);
}





//PROBLEME ICI : 
int** toTabTabInt (int* _mat , size_t taille_r ,int* sz_row ){
   // print_tab_int (sz_row , taille_r);
     //print_tab_int (_mat , taille_r*taille_r);
    int** tabtab  = (int**)malloc(sizeof(int*)*taille_r);
    for(int i =0 ; i< taille_r;i++){
        tabtab[i]=(int*)malloc(sizeof(int)*sz_row[i]);
    }
    int cumul ,index_col ,index_row ;
    index_col=index_row=0;
    cumul=0;

    int i=0;
    for(int i =0 ; ;i++){
  
        if( i == cumul + sz_row[index_row]  ){
            //print_tab_int (tabtab[index_row] ,sz_row[index_row]);
            //printf("index_ row %d \n ",index_row);
            index_row++;
            if(index_row >= taille_r)break;
            cumul+=sz_row[index_row];
            //tabtab[index_row]=(int*)malloc(sizeof(int)*sz_row[index_row]);
        }
        //printf("cumul %d\n",cumul);
        index_col=(i-cumul);
        //printf("i:%d  index_col %d\n ",i,index_col);
        tabtab[index_row][index_col]=_mat[i];
        
    }

    //printTabtab_int( tabtab , taille_r ,sz_row );
    return tabtab;
}




void tabInt_decalH (int* tab ,size_t deb, size_t end , const int shiftH ){
    for(int i =(end-1)+shiftH; i > deb ; i--){
        //printf("ind dA %d  %d %d\n",i,i-shiftH,tab[i+shiftH]);
         tab[i]=tab[i-shiftH];
        
    }
}
 
void tabInt_decalH2 (int* tab , size_t end , const int shiftH ){
     tabInt_decalH(tab,0,end,shiftH);
}







void tabInt_decalV(int** tab ,int* taille_c ,size_t taille_r ,size_t deb, size_t end , const int shiftV){


     for(int i =(end-1)+shiftV; i > deb ; i--){
        for(int k =0 ; k <taille_c[i];k++)tab[i][k]=tab[i-shiftV][k];
        for(int k =taille_c[i] ; k < taille_c[i-shiftV];k++)tab[i][k]=0;
        
    }
   
    // n'initialise pas a 0 la partie shifter


//printTabtab_int( tab ,  taille_r , taille_c );
}


void tabInt_decalV2 (int** tab , int* taille_c ,size_t taille_r,size_t end , const int shiftV ){
     tabInt_decalV(tab,taille_c,taille_r,0,end,shiftV);
}


void tabInt_decalV3 (int** tab , int* taille_c ,size_t taille_r , const int shiftV ){
     tabInt_decalV2(tab,taille_c,taille_r,taille_r,shiftV);
}


int isIn ( int* tab , int val , size_t taille  ){
        for(int i =0 ; i < taille ;i++){
            if(tab[i]==val)return i;
        }
    return -1 ;
}

int intComparator ( const void * first, const void * second ) {
    int firstInt = * (const int *) first;
    int secondInt = * (const int *) second;
    return firstInt - secondInt;
}




int** tabtabInt_RemoveLine_cpy(int** tab , int * taille_r ,int* taille_c , int nb_rmLine){
    int ** cpy_tab = (int**) malloc((*taille_r - nb_rmLine)*sizeof(int));
    for (int i =nb_rmLine ; i < *taille_r ; i++ ){
        cpy_tab[i]=(int*)malloc(taille_c[i]*sizeof(int));
        for ( int j = nb_rmLine ; j < taille_c[i] ; j++){
            cpy_tab[i][j]=tab[i][j];
        }
    }
    return cpy_tab ; 

}


void tabtabInt_AppendVal (int*** tab , int * taille_r ,int* taille_c , int* size2D , const int val  ){

    *tab = (int**)realloc(*tab,(*taille_r+size2D[0])*sizeof(int*));

    
    //printf("val : %d taille  %d \n ",val,*taille_r);
    for(int i =0;i<*taille_r;i++){
         //printf("val %d \n",taille_c[i]);
        if(taille_c[i]>taille_c[i+size2D[0]])(*tab)[i]=(int*)realloc((*tab)[i],(sizeof(int)*taille_c[i])); // JUSTE LE C ENFAIT !
         
         //printf("ind d %d  \n",taille_r+i);

    }

    for(int i =*taille_r;i<*taille_r+size2D[0];i++){
         //printf("val 2\n");
        (*tab)[i]=(int*)malloc((sizeof(int)*taille_c[i]));
         //printf("ind d %d  \n",taille_r+i);
    }


    //printf("val\n");
    tabInt_decalV3 ((*tab) , taille_c , *taille_r , size2D[0] );
 

    for(int i=0;i<size2D[0];i++){
        for (int k =0; k < taille_c[i] ; k++)(*tab)[i][k]=val;
        //print_tab_int ((*tab)[i] , taille_c[i] );
          //printf("\n \n ");
    }
// printTabtab_int ((*tab) , taille_r+size2D[0],taille_c );
 //printf("val : %d taille  %d \n ",val,taille_r);
    for(int i =0;i<*taille_r ;i++){

        //printf("ind d %d  %d %d \n",i,taille_c[i]+size2D[1],taille_c[i+size2D[0]]);
        //print_tab_int ((*tab)[i] , taille_c[i] );
        if(taille_c[i]+size2D[1]>taille_c[i+size2D[0]]){
            (*tab)[i]= (int*)realloc((*tab)[i],((taille_c[i]+size2D[1])*sizeof(int)));
        }
        taille_c[i]+=size2D[1];
        tabInt_decalH2((*tab)[i],taille_c[i],size2D[1]);
        for(int k =0;k<size2D[1];k++)(*tab)[i][k]=val;

    }

    for(int i =*taille_r ;i<*taille_r+size2D[0];i++){
        taille_c[i]+=size2D[1];
        tabInt_decalH2((*tab)[i],taille_c[i],size2D[1]);
        for(int k =0;k<size2D[1];k++)(*tab)[i][k]=val;
    }
   *taille_r+=1;
  // print_tab_int (taille_c , *taille_r );

   //printTabtab_int(  (*tab) ,  *taille_r , taille_c );
}


void tabSquare(int* tab ,size_t taille, int val ){
    for(int i =0; i<taille;i++){
        tab[i]=val;
    }
}


/*
void* taille_bis (void* valeur , size_t taille ){
void* arr_bis = (void*)malloc(sizeof(*valeur)*taille  );
     for(int i =0 ; i< taille ;i++) arr_bis[i]=*valeur ;

return arr_bis;
}*/

int* taille_bisInt (int* valeur , size_t taille ){
int* arr_bisInt = (int*)malloc(sizeof(*valeur)*taille  );
     for(int i =0 ; i< taille ;i++) arr_bisInt[i]=*valeur ;

return arr_bisInt;
}




int* cpy_tab_int (int* tab,size_t taille){
    int* res_tab = (int*)malloc(taille*sizeof(int));
    for(int i =0;i<taille;i++)res_tab[i]=tab[i];

    return res_tab;
}

int** cpy_tabTab_int (int** tab,int* tab_taille , int  taille){
    int** res_tab = (int**)malloc(taille*sizeof(int*));
    for(int i =0;i<taille;i++){
        res_tab[i]=cpy_tab_int ( tab[i], taille);
    }

    return res_tab;
}

int** cpy_tabTab_intSq (int** tab, int  taille){
    int* tab_taille= taille_bisInt (&taille , taille );
    return cpy_tabTab_int ( tab, tab_taille ,  taille);
}



void print_tab_int (int * tab , int taille ){
    printf("[|");
    for (int i =0; i<taille;i++)printf("%d |", tab[i]);
    printf("]\n");

}


void print_tab_int2 (int * tab , int taille ){
    printf("[|");
    for (int i =0; i<taille;i++)printf("%d : %d |", i, tab[i]);
    printf("]\n");

}

int maxOfTabInt (int* tab , size_t taille ){
    int max = tab[0];//float max = -INFINITY;
    if(DEBUG_TABLEAU)print_tab_int (tab , taille );
    int imax =0 ;
    for(int i =0 ;i<taille;i++){
        if(tab[i]> max ){
            imax=i;
            max= tab[imax];
        }
    }
    if(debug_tab)printf("IMAX %d \n",imax);
    return max ; 

}




void printTabtab_int( int ** tabtab , size_t taille , int* taille_tab ){

    //printf("\n-Nombre de noeuds:%d\n-Nombre d'arrêtes:%d\nMatrice d'adjacence: \n",graph.nodesQuantity,graph.edgesQuantity);
    for(int i=0; i< taille; i++){
        print_tab_int (tabtab[i] , taille_tab[i] );
    }
}

void printTabtab_int2( int ** tabtab , size_t taille  ){
    int conv_taille = taille ; 
    int*  tab_taille = taille_bisInt (&conv_taille , taille );

    //printf("\n-Nombre de noeuds:%d\n-Nombre d'arrêtes:%d\nMatrice d'adjacence: \n",graph.nodesQuantity,graph.edgesQuantity);
   
        printTabtab_int(tabtab , taille ,tab_taille);
    
}

void printTabtab_int3( int ** tabtab , size_t taille  ){

            int conv_taille = taille ; 
    int*  tab_taille = taille_bisInt (&conv_taille , taille );

    //printf("\n-Nombre de noeuds:%d\n-Nombre d'arrêtes:%d\nMatrice d'adjacence: \n",graph.nodesQuantity,graph.edgesQuantity);
   
       for(int i=0; i< taille; i++){
        print_tab_int2 (tabtab[i] , tab_taille [i] );
    }

}






void print_tab_double (double * tab , int taille ){
    printf("[|");
    for (int i =0; i<taille;i++)printf("%f |", tab[i]);
    printf("]\n");

}



void printTabtab_double( double ** tabtab , size_t taille , int* taille_tab ){

    //printf("\n-Nombre de noeuds:%d\n-Nombre d'arrêtes:%d\nMatrice d'adjacence: \n",graph.nodesQuantity,graph.edgesQuantity);
   
    for(int i=0; i< taille; i++){

        print_tab_double(tabtab[i] , taille_tab[i] );
    }
}









void freeTabTab(void ** tabtab , size_t taille ){
    for(int i=0;i<taille ;i++){
        freeToNull(&(tabtab[i]));
    }
    freeToNull(tabtab);
}




int caraID (  int idmax   ) {//idmax == nb_cluster

    int max = (idmax==0?0:(int) log10((double)idmax));
    int unit =(int) ( idmax/pow(10,max));
    int rest = (int)  (idmax % (int)pow(10,max));
    //if(max==0)rest=1;
    //printf("IDMAX %d \n max %d unit %d  rest %d %f \n ",idmax,max,unit,rest,log10((double)idmax));
    int sum_cara ,last , cur;
    sum_cara=last=cur=0;
    
    for(int i = 1 ; i <= max ; i++){
        cur=(int)(((i+1)*(pow(10,i)-1-last)));
        //printf("%d \n",cur);
        //printf("res %f %d\n",pow(10,i), (int)((i+1)*(pow(10,i)-1-last)));
        sum_cara+=cur;
        last=cur;
        
    }
    sum_cara+=(max+1)*rest;
    return sum_cara;
}//ATTENTION TODO  CARA ID Sert à rien finalement donc select = 0 tt le temps 





int regularCara (  size_t taille , int max   ) { // borne sup du nb de cara dans un tableau contenant des entiers appartenant à [0;max] pas tous inclus 
    //assert(max!=0);
    return taille* strTailleInt(max ) ;//(max<0 ? max : (max==0?0:(int) log10((double)max)));
}


char* intTabToString ( int* tab , size_t taille , const char delimiter , int idmax  ,int select  ){//idmax == nb_cluster //select==1 pour coloration 

    int idx=0;
    
    char* res = (char*)malloc(1);

    if(tab!=NULL){
        int sum_cara=0; 
        int len =0;
        if(select==0){
            sum_cara=regularCara(taille,idmax);//si c'est un tableau dont l'entier max est idmax 

        }else if (select==1){//si c'est un tableau contenant les entiers de 0 à idmax  tous inclus 
            sum_cara=caraID (   idmax   );
        }
        //printf("%d \n",sum_cara);
        int max = strTailleInt(idmax);//(idmax<0 ? idmax : (idmax==0?0:(int) log10((double)idmax)));
         res = realloc(res,(sum_cara+taille+1)); //sum_cara= taille content , taille = nb_delimiter , last='\0'
        
        char str[(max)+1];//+1)+1];
        
        int str_sz = 0 ; 
        for (int i=0; i < taille ;i++){
            res[idx]='\0';
            //printf("r3 %s c3 %c \n",res,res[idx-1]);
            sprintf(str, "%d", (int)tab[i]);
            //printf("ICIC %s %d\n ",str,tab[i]);
             len = snprintf(NULL, 0, "%d",tab[i] );
            str_sz = len+1 ; // (tab[i]==0? 1: (int)(log10((double)tab[i])+1) )+1;
            //printf("%d str_sz %d vs real %d  \n",tab[i],str_sz,max+2);
            str[str_sz]='\0';
            strncat(res,str,str_sz-1);
            idx+=(str_sz-1);
            //printf("IDX %d \n",idx);
            //printf("tab %d r1 %s c %c \n",tab[i],res,res[idx-1]);
            res[idx++]=delimiter;
            //printf("r2 %s c2 %c \n",res,res[idx-1]);

        }
        idx-=1;
    }
    res[idx]='\0';
    //printf("res %s \n",res);
    return res;

}

int* strToTab(char* str,const char delim){
    int* tab =NULL;
    if(str){
    //printf("LA %s delim %d \n",str,delim);
    char* save_ptr;
    char* strToken = strtok_r ( str, &delim ,&save_ptr);
    char * endPtr;
    int val=0;
    int size_tab =1; 
    int zi=0;
    tab = (int*)malloc(sizeof(int)* size_tab);
    //printf("toTab %s %c \n\n ",str,delim);
    for(;strToken!=NULL;zi++){

        val=strtol(strToken,&endPtr,10);
        //printf("val %d\n",val);

        if(size_tab<=zi){
                size_tab*=2;
                size_tab++;
                tab= realloc(tab, sizeof(int)*size_tab) ;
        }

        tab[zi]=val;

        strToken =strtok_r(NULL, &delim,&save_ptr);
    }
    print_tab_int(tab,zi);
}
    return tab;

}

char* intTabTabToString ( int** tabTab , size_t taille2 , int taille , const char * concatEndDelim , int idmax ,int select  ){ //idmax == nb_cluster
    
    int*  taille_bis = taille_bisInt(&taille,taille2);
    return intTabTabToString2 (  tabTab ,  taille2 , taille_bis ,  concatEndDelim ,  idmax , select  );

}
char* intTabTabToString2 ( int** tabTab , size_t taille2 , int* taille , const char * concatEndDelim , int idmax ,int select  ){ //idmax == nb_cluster
    
    char* str =(char*)malloc(sizeof(char)*1);
   /* printf("LALAA\n");
    printTabtab_int3(tabTab , taille2);
    printf("LALAA\n\n");*/
    int idx=0;
    if(tabTab!=NULL){
    char* ptr_str=NULL;
    for(int i=0;i<taille2;i++){
        ptr_str = intTabToString(tabTab[i],taille[i],concatEndDelim[0],idmax,select );

        if(i>0){str=fusionstr(str,ptr_str,concatEndDelim[1]);}
        else{
            str =realloc(str,strlen(ptr_str)+1);
            strcpy(str,ptr_str);}
        //printf("intTab %s \n",str);
        idx+=(strlen(ptr_str)+1);
    }
}
    str[idx]='\0';
    //printf("intTabTab %s \n",str);
    return str;
    

}


int** strToTabTab(char* str,const char* delims){

    int** tabTab = NULL;
    if(str!=NULL){
 //printf("StrTOTabLA %s  %s \n",str,delims);
 char* save_ptr;
    char* strToken = strtok_r ( str, &(delims[1]),&save_ptr );
    char * endPtr;
    int val=0;
    int size_tab =1; 
    int zi=0;
     tabTab = (int**)malloc(sizeof(int*)* size_tab);

    for(;strToken!=NULL;zi++){

        //val=strtol(strToken,&endPtr,10);
        //printf("StrTOTab %s \n",strToken);

        if(size_tab<=zi){
                size_tab*=2;
                size_tab++;
                tabTab[zi]= realloc(tabTab[zi], sizeof(int*)*size_tab) ;
        }
        //printf("%d %d \n",zi , size_tab);
        tabTab[zi]=strToTab(strToken,delims[0]);

        strToken =strtok_r(NULL, &(delims[1]), &save_ptr);
        //printf("iuoio %s %c \n",strToken,delims[1]);
    }
}

    return tabTab;

}

const char endDelimDf(){return '\n'; }

const char tabDelim(){return ',';}

const char* tabTabDelims(){
    char* delims = (char*)malloc(3);
    delims[0]=tabDelim();
    delims[1]='|';
    delims[2]='\0';
    return delims;}



const char* tabTabDelim2(){
    char* delim = (char*)malloc(2);
    delim[0]=tabDelim();
    delim[1]='\0';
    return delim;}