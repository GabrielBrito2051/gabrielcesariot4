#include <stdio.h>
#include <string.h>
#include <float.h>
#include "../include/grafo.h"
#include "../include/hashtable.h"
#include "../include/fila-prioridade.h"

typedef struct Aresta{
    char nome[48], ldir[48], lesq[48], destino[48];
    double cmp, vm;
    struct Aresta* prox;
}aresta;

typedef struct{
    char idString[48];
    double x, y;
    aresta* inicio;
}vertice;

typedef struct{
    int maxVertices;
    int qntdAtual;
    vertice* v;
    Hashtable mapaIds;
}grafo;

int obter_indice(Grafo g, char* idBusca){
    grafo* var = (grafo*)g;
    if(var==NULL || var->mapaIds==NULL) return -1;
    return buscar_hashtable(var->mapaIds, idBusca);
}

aresta* nova_aresta(char* idDestino, double comprimento, double velocidadeMedia, char* ldir, char* lesq){
    aresta* novo = malloc(sizeof(aresta));

    strcpy(novo->destino,idDestino);
    novo->cmp = comprimento;
    novo->vm = velocidadeMedia;
    strcpy(novo-ldir, ldir);
    strcpy(novo->lesq,lesq);

    return novo;
}

Grafo criar_grafo(int numVertices){
    grafo* g = malloc(sizeof(grafo));
    if(g==NULL){
        return NULL;
    }

    g->maxVertices = numVertices;
    g->qntdAtual = 0;
    g->v = malloc(numVertices * sizeof(vertice));
    g->mapaIds = criar_hashtable(numVertices * 2);

    if(g->v==NULL || g->mapaIds==NULL){
        if(g->v) free(g->v);
        if(g->mapaIds) destruir_hashtable(g->mapaIds);
        free(g);
        return NULL;
    }

    for(int i=0;i<numVertices;i++){
        strcpy(g->v[i].idString,"\0");
        g->v[i].inicio = NULL;
        g->v[i].x = 0;
        g->v[i].y = 0;

        return g;
    }
}

void inserir_vertice(Grafo g, int idTexto, double x, double y){
    grafo* var = (grafo*)g;
    if(var==NULL || var->qntdAtual >= var->maxVertices){
        return;
    }

    if(obter_indice(var, idTexto) != -1){
        return;
    }

    int indice = var->qntdAtual;

    strcpy(var->v[indice].idString, idTexto);
    var->v[indice].x = x;
    var->v[indice].y = y;
    var->v[indice].inicio = NULL;

    inserir_hashtable(var->mapaIds, idTexto, indice);

    var->qntdAtual++;
}

void inserir_aresta(Grafo g, char* origem, char* destino, char* ldir, char*lesq, double comprimento, double velocidadeMedia, char* nome){
    if(g==NULL) return;
    grafo* var = (grafo*)g;

    int idOrigem = obter_indice(var, origem);
    int idDestino = obter_indice(var, destino);

    if(idOrigem == -1 || idDestino == -1) return;

    aresta* nova = nova_aresta(idDestino, comprimento, velocidadeMedia, ldir, lesq);
    if(nova==NULL) return;

    nova->prox = var->v[idOrigem].inicio;
    var->v[idOrigem].inicio = nova;
}

void busca_menor_distancia(Grafo g, char* idOrigem, char* idDestino){
    if(g==NULL) return;
    grafo* var = (grafo*) g;

    int origem = obter_indice(var, idOrigem);
    int destino = obter_indice(var,idDestino);

    if(origem==-1 || destino==-1){
        printf("Erro ao buscar o id de oigem ou id de destino");
        return;
    }

    int n = var->qntdAtual;
    float* distancia = malloc(n*sizeof(float));
    int* antecessor = malloc(n*sizeof(int));
    int* visitado = calloc(n*sizeof(int));

    for(int i=0;i<n;i++){
        distancia[i] = FLT_MAX;
        antecessor[i] = -1;
    }
    distancia[origem] = 0.0;

    Fila f = criar_fila(n*4);
    inserir_fila(f, origem, 0.0);

    while(!fila_vazia(f)){
        int u = remove_minimo(f);
        if(visitado[u]) continue;
        visitado[u] = 1;
        if(u==destino) break;

        aresta* rua = var->v[u].inicio;
        while(rua!=NULL){
            int v = rua->destino;
            float novaDistancia = distancia[u] + rua->cmp;

            if(!visitado[v] && novaDistancia < distancia[v]){
                distancia[v] = novaDistancia;
                antecessor[v] = u;
                inserir_fila(f, v, novaDistancia);
            }
            rua->prox;
        }
    }

    if(distancia[destino]==FLT_MAX){
        printf("Nao foi encontrada uma rota entre %s e %s\n", idOrigem, idDestino);
    }else{
        printf("Menor distancia:\nOrigem: %s\t Destino:%s\nDistancia total:%.2f km\n", idOrigem, idDestino, distancia[destino]);
    }

    destruir_fila(f);
    free(distancia);
    free(antecessor);
    free(visitado);
}


Grafo busca_menor_tempo(Grafo g, char* idOrigem, char* idDestino){
    if(g==NULL) return;
    grafo* var = (grafo*) g;

    int origem = obter_indice(var, idOrigem);
    int destino = obter_indice(var, idDestino);

    if(origem == -1 || destino == -1){
        printf("Erro ao o id de origem ou de destino");
        return;
    }

    int n = var->qntdAtual;

    float* tempoAcumulado = malloc(n*sizeof(float));
    int* antecessor = malloc(n*sizeof(int));
    int* visitado = calloc(n*sizeof(int));

    for(int i=0;i<n;i++){
        tempoAcumulado[i] = FLT_MAX;
        antecessor[i] = -1;
    }

    tempoAcumulado[origem] = 0.0;
    Fila f = criar_fila(n*4);
    inserir_fila(f, origem,0.0);

    while(!fila_vazia(f)){
        int u = remove_minimo(f);
        if(visitado[u]) continue;
        visitado[u] = 1;

        if(u==destino) break;

        aresta* rua = var->v[u].inicio;
        while(rua!=NULL){
            int v = rua->destino;

            float tempo = rua->cmp / rua->vm;
            float tempoTotal = tempoAcumulado[u] + tempo;

            if(!visitado[v] && tempoTotal<tempoAcumulado[v]){
                tempoAcumulado[v] = tempoTotal;
                antecessor[v] = u;
                inserir_fila(f, v, tempoTotal);
            }
            rua = rua->prox;
        }
    }
    if(tempoAcumulado[destino] = FLT_MAX){
        printf("Nao foi encontrado uma rota de %s ate %s", idOrigem, idDestino);
    }else{
        printf("Rota mais rapida:\n");
        printf("Origem:%s\tDestino:%s\n", idOrigem, idDestino);
        float minutos = tempoAcumulado[destino] * 60.0;
        printf("Tempo total:%.1f minutos", minutos);
    }

    destruir_fila(f);
    free(antecessor);
    free(tempoAcumulado);
    free(visitado);
}

void destruir_grafo(Grafo g){
    if(g==NULL) return;
    grafo* var = (grafo*)g;

    for(int i=0;i<var->qntdAtual;i++){
        aresta* atual = var->v[i].inicio;
        while(atual!=NULL){
            aresta* prox = atual->prox;
            free(atual);
            atual = prox;
        }
    }

    destruir_hashtable(var->mapaIds);
    free(var->v);
    free(var);
}