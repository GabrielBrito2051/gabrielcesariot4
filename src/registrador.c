#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/registrador.h"

typedef struct{
    char cep[48], face;
    int num;
    double x, y;
}registrador;

char* getCepRegistrador(Registrador reg){
    return ((registrador*)reg)->cep;
}

char* getFaceRegistrador(Registrador reg){
    return ((registrador*)reg)->face;
}

int getNumRegistrador(Registrador reg){
    return ((registrador*)reg)->num;
}

double getXRegistrador(Registrador reg){
    return ((registrador*)reg)->x;
}

double getYRegistrador(Registrador reg){
    return ((registrador*)reg)->y;
}

void setCepRegistrador(Registrador reg, char* cep){
    strcpy(((registrador*)reg)->cep,cep);
}

void setFaceRegistrador(Registrador reg, char face){
    ((registrador*)reg)->face = face;
}

void setNumRegistrador(Registrador reg, int num){
    ((registrador*)reg)->num = num;
}

void setXRegistrador(Registrador reg, double x){
    ((registrador*)reg)->x = x;
}

void setYRegistrador(Registrador reg, double y){
    ((registrador*)reg)->y = y;
}