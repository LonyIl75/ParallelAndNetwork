


/**
 * fichier:my-file.h
 * auteur: Rambal Julien
 * description : fonctions pour gérer les flux fichiers 
 **/


#ifndef MYFILE_H
#define MYFILE_H


#include <stdio.h> 
#include <stdlib.h>
#include<string.h>
#include <errno.h>
#include"my-util.h"


const char fileSeparator(const char* os);
FILE *open_fichier(const char* n_fichier, const char* param);

FILE* openFileFTP(const char* filename, const char* mode) ;
size_t readFileFTP(void* buffer, size_t blocSize, size_t blocCount, FILE* fptr) ;

size_t writeFileFTP(void* buffer, size_t blocSize, size_t blocCount, FILE* fptr) ;

#endif