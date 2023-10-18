


/**
 * fichier:my-file.c
 * auteur: Rambal Julien
 * description : fonctions pour gérer les flux fichiers 
 **/


 #include "my_file.h"


const char fileSeparator(const char* os){
    if (strcmp(os, "LINUX") == 0) return '/';
    else if (strcmp(os, "WINDOW") == 0) return '\\' ; 
    else exit(1); 
}

FILE *open_fichier(const char* n_fichier, const char* param)
{
    FILE *fptr;
    if ((fptr = fopen( n_fichier, param))==NULL)
    {
        fprintf(stderr, "Error: %d file: %s error:%s\n", errno, n_fichier, strerror(errno));

        exit(EXIT_FAILURE);
    }
    else { return fptr; }
}



FILE* openFileFTP(const char* filename, const char* mode) {
    FILE* stream = fopen(filename, mode);
    if (stream == NULL) {
        fprintf(stderr,"Erreur : fopen de: %s.\n", filename);
        if(debug)print_errno ();
        exit(1);
    }
    return stream;
}

size_t readFileFTP(void* buffer, size_t blocSize, size_t blocCount, FILE* fptr) {
    size_t lu = fread(buffer, blocSize, blocCount, fptr);
    printf("ReadFileFTP \n PARAM : BlockSize %ld  Blocount %ld \n",blocSize,blocCount); 
    if (lu < blocCount) {
    		if(debug){printf("blocCount != lu | bloc:%ld  lu :%ld \n",blocCount,lu); print_errno ();}
    		
	
    		if(ferror(fptr)!=0){
		  	perror("Erreur lors de l ecriture du fichier \n");
		  	fclose(fptr);
		  	exit(1);
	  	}
	  	printf("buffer %s  \n taille : %ld \n", (char*)buffer ,strlen(buffer));
		printf("fin de fichier \n");
		return 0;
	}
	printf("buffer %s  \n taille : %ld \n", (char*)buffer ,strlen(buffer));
	printf(" \t lu %ld\n",lu);
    return lu;
}

size_t writeFileFTP(void* buffer, size_t blocSize, size_t blocCount, FILE* fptr) {
printf("WriteFileFTP \n PARAM : BlockSize %ld  Blocount %ld \n",blocSize,blocCount); 
    size_t ecrit = fwrite(buffer, blocSize, blocCount, fptr);
    
  if (ecrit < blocCount) {
    		if(debug){printf("blocCount != lu | bloc:%ld  lu :%ld \n",blocCount,ecrit); print_errno ();}
		  	perror("Erreur lors de l ecriture du fichier \n");
		  	fclose(fptr);
		  	exit(1);
	  	}
	  	
printf("ecrit %ld\n",ecrit);
    return ecrit;
}

/*void  lire_fichier( FILE * fptr , void * buff , size_t size ){

  while(feof(fread(&num, sizeof(struct threeNum), 1, fptr)))
   {
      fread(&num, sizeof(struct threeNum), 1, fptr); 
      printf("n1: %d\tn2: %d\tn3: %d\n", num.n1, num.n2, num.n3);
   }

}*/

// a faire en inline ou en define 
//va_start serait bien pour passer direct args : tous les params à la vrai fonction

