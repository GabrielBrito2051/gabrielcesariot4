#include "../include/fila-prioridade.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int idVertice;
    double prioridade;
}elemento;

typedef struct{
    elemento* dado;
    int capacidade;
    int tamanho;
}fila;

void trocar(fila* f, int i, int j){
    elemento temp = f->dado[i];
    f->dado[i] = f->dado[j];
    f->dado[j] = temp;
}

void subir (fila* f, int posicao){
    while(posicao>0){
        int pai = (posicao-1)/2;
        if(f->dado[posicao].prioridade<f->dado[pai].prioridade){
            trocar(f, posicao, pai);
            posicao = pai;
        }else{
            break;
        }
    }
}

void descer(fila* f, int posicao){
    int menor = posicao;
    int esquerda = 2 * posicao + 1;
    int direita = 2 * posicao + 2;

    if(esquerda<f->tamanho && f->dado[esquerda].prioridade < f->dado[menor].prioridade){
        menor = esquerda;
    }

    if(direita<f->tamanho && f->dado[direita].prioridade < f->dado[menor].prioridade){
        menor = direita;
    }

    if(menor!=posicao){
        trocar(f, posicao, menor);
        descer(f, menor);
    }
}

Fila criar_fila(int numVertices){
    fila* f = malloc(sizeof(fila));
    if(f==NULL) return NULL;

    f->capacidade = numVertices;
    f->tamanho = 0;
    f->dado = malloc(numVertices * sizeof(elemento));

    if(f->dado==NULL){
        free(f);
        return NULL;
    }

    return f;
}

int fila_vazia(Fila f){
    if(f==NULL) return 1;
    fila* var = (fila*)f;

    return (var->tamanho==0);
}

void inserir_fila(Fila f, int idVertice, double prioridade){
    if(f==NULL) return;
    fila* var = (fila*)f;

    if(var->tamanho>=var->capacidade){
        return;
    }

    int posicaoInsercao = var->tamanho;
    var->dado[posicaoInsercao].idVertice = idVertice;
    var->dado[posicaoInsercao].prioridade = prioridade;

    var->tamanho++;
    subir(f, posicaoInsercao);
}

int remove_minimo(Fila f){
    if(f==NULL || fila_vazia(f)) return -1;
    fila* var =(fila*)f;

    int idMinimo = var->dado[0].idVertice;
    var->dado[0] = var->dado[var->tamanho -1];
    var->tamanho--;

    if(var->tamanho>0){
        descer(f, 0);
    }

    return idMinimo;
}

void destruir_fila(Fila f){
    if(f==NULL) return;
    fila* var = (fila*) f;

    if(var->dado!=NULL){
        free(var->dado);
    }

    free(f);
}