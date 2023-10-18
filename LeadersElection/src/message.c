
/**
 * fichier:message.c
 * auteur: Rambal Julien
 * description : implemente une requete (pas aboutit TODO )
 **/


#include "message.h"

enum header  strtoHeader (char* str ){
    //printf("encore |%s| \n",str);
    if (strcmp(str, "CONNECTION_N") == 0) return _CONNECT_N ;
    else if (strcmp(str, "CONNECTION_CL" ) == 0) return _CONNECT_CL;  
    else if (strcmp(str, "OPERATION") == 0) return _OPERATION;   //OPERATION : contient suite d'id message= params , id message => attends ce message avant op        
    else if (strcmp(str, "RESULTAT") == 0) return _RESULTAT; //RESULTAT : le resultat attendu 
    else if (strcmp(str, "ASK") == 0) return _ASK; 
    else if (strcmp(str, "EVENT") == 0) return _EVENT; 
    else if (strcmp(str, "OTHER") == 0) return _OTHER; 
    else if (strcmp(str, "COLORATION") == 0) return _COLORATION; 
    else if (strcmp(str, "CLUSTERING") == 0) return _CLUSTERING;
    /*
    else if (strcmp(str, "AF_APPLETALK") == 0) return AF_APPLETALK; 
    else if (strcmp(str, "AF_PACKET") == 0) return AF_PACKET;       
    else if (strcmp(str, "AF_ALG") == 0) return AF_ALG;  */
    else return _OTHER;



}


const char * messageDelim2(){
    char* delim = (char*)malloc(2);
    delim[0]= messageDelim();
    delim[1]='\0';
    return delim;
}
const char messageDelim(){return ':';}

const char * headerToStr (enum header _hd ){

    switch(_hd){

       case _CONNECT_N :
            return "CONNECTION_N";
        /*case AF_LOCAL :  
            return "AF_LOCAL";*/
        case _CONNECT_CL : 
            return "CONNECTION_CL";           
        case _OPERATION  :     
            return "OPERATION";
        case _RESULTAT :         
            return "RESULTAT";
        case _ASK :         
            return "ASK";
        case _EVENT :              
            return "EVENT";
        case _OTHER :             
            return "OTHER";
        case _COLORATION :          
            return "COLORATION";
        case _CLUSTERING :        
            return "CLUSTERING";/*
        case AF_PACKET :           
            return "AF_PACKET";
        case AF_ALG :
            return "AF_ALG";*/
        default : 
            return "UNKNOW";

   }
   return "";

}
