#include "../include/hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char chave[48];
    int valor;
    int ocupado;
}elemento;

typedef struct{
    elemento* tabela;
    int capacidade;
}hashtable;

unsigned int calcular_hash(hashtable* h, char*chave){
    unsigned long hash = 5381;
    int c;

    while((c=*chave++)){
        hash = ((hash<<5) + hash) + c;
    }

    return (unsigned int)(hash%h->capacidade);
}

Hashtable criar_hashtable(int capacidade){
    hashtable* h = malloc(sizeof(hashtable));
    if(h==NULL) return NULL;

    h->capacidade = capacidade;
    h->tabela = malloc(sizeof(elemento)*capacidade);
    if(h->tabela==NULL){
        free(h);
        return NULL;
    }

    for(int i=0;i<capacidade;i++){
        h->tabela[i].ocupado = 0;
    }

    return h;
}

void inserir_hashtable(Hashtable h, char* chave, int valor){
    if(h==NULL || chave==NULL) return;
    hashtable* var = (hashtable*) h;

    unsigned int indice = calcular_hash(var, chave);
    int tentativa = 0;

    while(var->tabela[indice].ocupado && strcmp(var->tabela[indice].chave, chave) != 0){
        indice = (indice + 1) % var->capacidade;
        tentativa++;

        if(tentativa>=var->capacidade){
            printf("A hashtable esta cheia!");
            return;
        }
    }

    strcpy(var->tabela[indice].chave, chave);
    var->tabela[indice].valor = valor;
    var->tabela[indice].ocupado = 1;
}

int buscar_hashtable(Hashtable h, char* chave){
    if(h==NULL || chave==NULL) return -1;
    hashtable* var = (hashtable*) h;

    unsigned int indice = calcular_hash(var, chave);
    int tentativa = 0;

    while(var->tabela[indice].ocupado){
        if(strcmp(var->tabela[indice].chave, chave)==0){
            return var->tabela[indice].valor;
        }
        indice = (indice + 1) % var->capacidade;
        tentativa++;
        if(tentativa>= var->capacidade) break;
    }
    return -1;
}

void destruir_hashtable(Hashtable h){
    if(h==NULL) return;
    hashtable* var = (hashtable*)h;

    if(var->tabela!=NULL){
        free(var->tabela);
    }

    free(h);
}