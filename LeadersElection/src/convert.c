/**
 * fichier:convert.c
 * auteur: Rambal Julien
 * description : Des fonctions de conversion pour le C 
 **/



#include "convert.h"

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



int  strTailleInt(int nb ){
    return ((nb!=0?(int)log10((double)abs(nb)):1)+(nb<0))+1;
}


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
		if(DEBUG_CONVERT)printf("%d \n",sum_cara);
		int max = strTailleInt(idmax);//(idmax<0 ? idmax : (idmax==0?0:(int) log10((double)idmax)));
		 res = realloc(res,(sum_cara+taille+1)); //sum_cara= taille content , taille = nb_delimiter , last='\0'
		
		char str[(max)];//+1)+1];
		
		int str_sz = 0 ; 
		for (int i=0; i < taille ;i++){
			res[idx]='\0';
			//printf("r3 %s c3 %c \n",res,res[idx-1]);
			sprintf(str, "%d", (int)tab[i]);
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
	return res;

}

int* strToTab(char* str,const char delim){

	char* strToken = strtok ( str, &delim );
	char * endPtr;
	int val=0;
	int size_tab =1; 
	int zi=0;
	int* tab = (int*)malloc(sizeof(int)* size_tab);
	for(;strToken!=NULL;zi++){

		val=strtol(strToken,&endPtr,10);
		

		if(size_tab<=zi){
                size_tab*=2;
                size_tab++;
               	tab= realloc(tab, sizeof(int)*size_tab) ;
        }

        tab[zi]=val;

		strToken =strtok(NULL, &delim);
	}
	return tab;

}

char* intTabTabToString ( int** tabTab , size_t taille2 , int taille , const char * concatEndDelim , int idmax ,int select  ){ //idmax == nb_cluster
	
	int*  taille_bis = taille_bisInt(&taille,taille2);
	return intTabTabToString2 (  tabTab ,  taille2 , taille_bis ,  concatEndDelim ,  idmax , select  );

}
char* intTabTabToString2 ( int** tabTab , size_t taille2 , int* taille , const char * concatEndDelim , int idmax ,int select  ){ //idmax == nb_cluster
	
	char* str =(char*)malloc(sizeof(char)*1);
	int idx=0;
	if(tabTab!=NULL){
	char* ptr_str=NULL;
	for(int i=0;i<taille2;i++){
		ptr_str = intTabToString(tabTab[i],taille[i],concatEndDelim[0],idmax,select );
		str=fusionstr(str,ptr_str,concatEndDelim[1]);
		idx+=(strlen(ptr_str)+1);
	}
}
	str[idx]='\0';
	return str;
	

}


int** strToTabTab(char* str,const char* delims){

	char* strToken = strtok ( str, &(delims[1]) );
	char * endPtr;
	int val=0;
	int size_tab =1; 
	int zi=0;
	int** tabTab = (int**)malloc(sizeof(int*)* size_tab);
	for(;strToken!=NULL;zi++){

		val=strtol(strToken,&endPtr,10);
		

		if(size_tab<=zi){
                size_tab*=2;
                size_tab++;
               	tabTab[zi]= realloc(tabTab, sizeof(int*)*size_tab) ;
        }

        tabTab[zi]=strToTab(strToken,delims[1]);

		strToken =strtok(NULL, &(delims[1]));
	}

	return tabTab;

}

const char endDelimDf(){return '\n'; }

const char tabDelim(){return ',';}

const char* tabTabDelims(){
    char* delims = (char*)malloc(2);
    delims[0]=tabDelim();
    delims[1]='|';
    return delims;}








