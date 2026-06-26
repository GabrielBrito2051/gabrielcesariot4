#include <stdio.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include "../include/grafo.h"
#include "../include/hashtable.h"
#include "../include/fila-prioridade.h"
#include "../include/svg.h"
#include "../include/txt.h"

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

void busca_menor_distancia(Grafo g, int origem, int destino, FILE* svg, char* cc){
    if(g==NULL) return;
    grafo* var = (grafo*) g;

    int n = var->qntdAtual;
    float* distancia = malloc(n*sizeof(float));
    int* antecessor = malloc(n*sizeof(int));
    int* visitado = calloc(n,sizeof(int));

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
            rua = rua->prox;
        }
    }

    if(distancia[destino]==FLT_MAX){
        printf("Nao foi encontrada uma rota\n");
    }else{
        printf("Menor distancia:%.2f km\n",distancia[destino]);

        int atual = destino;
        while(antecessor[atual]!=-1){
            int ant = antecessor[atual];
            insere_aresta_svg(svg, var->v[ant].x,var->v[ant].y, var->v[atual].x, var->v[atual].y, cc);
            atual = ant;    
        }
    }

    destruir_fila(f);
    free(distancia);
    free(antecessor);
    free(visitado);
}

void busca_menor_tempo(Grafo g, int origem, int destino, FILE* svg, char* cr){
    if(g==NULL) return;
    grafo* var = (grafo*) g;

    int n = var->qntdAtual;

    float* tempoAcumulado = malloc(n*sizeof(float));
    int* antecessor = malloc(n*sizeof(int));
    int* visitado = calloc(n,sizeof(int));

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
        printf("Nao foi encontrado uma rota");
    }else{
        printf("Rota mais rapida: %.1f minutos\n");
        float minutos = tempoAcumulado[destino] * 60.0;

        int atual = destino;
        while(antecessor[atual]!=-1){
            int ant = antecessor[atual];
            insere_aresta_svg(svg, var->v[ant].x,var->v[ant].y, var->v[atual].x, var->v[atual].y, cr);
            atual = ant;    
        }
    }

    destruir_fila(f);
    free(antecessor);
    free(tempoAcumulado);
    free(visitado);
}

void alterar_velocidade_media(Grafo g, double x, double y, double w, double h, double vm){
    if(g==NULL) return;
    grafo* var = (grafo*) g;

    for(int i=0;i<var->qntdAtual;i++){
        vertice origem = var->v[i];
        if(origem.x >= x && origem.x <= (x+w) && origem.y >= y && origem.y <= (y+h)){
            aresta* atual = origem.inicio;
            while(atual!=NULL){
                int indice = atual->destino;
                vertice destino = var->v[indice];
                if(destino.x >= x && destino.x <= (x + w) && destino.y >= y && destino.y <= (y + h)){
                    atual->vm = vm;
                }
                atual = atual->prox;
            }
        }
    }
}

int calcula_componentes_conexos(Grafo g, double velocidade, FILE* svg){
    if(g==NULL) return -1;
    grafo* var = (grafo*)g;

    int n = var->qntdAtual;
    int* visitado = calloc(n,sizeof(int));
    int* fila = malloc(n*sizeof(int));
    int qntdComp = 0;

    char* cores[] = {"red", "cyan", "green", "orange", "purple",  "cyan", "magenta", "brown", "darkgreen", "teal"};
    int totalCores = 10;

    for(int i=0;i<n;i++){
        if(!visitado[i]){
            qntdComp++;

            double min_x = DBL_MAX, max_x = -DBL_MAX, min_y = DBL_MAX, max_y = -DBL_MAX;
            int inicio = 0;
            int fim = 0;

            fila[fim++] = i;
            visitado[i] = 1;

            while(inicio<fim){
                int u = fila[inicio++];

                double vx = var->v[u].x;
                double vy = var->v[u].y;
                if (vx < min_x) min_x = vx;
                if (vx > max_x) max_x = vx;
                if (vy < min_y) min_y = vy;
                if (vy > max_y) max_y = vy;

                aresta* rua = var->v[u].inicio;
                while(rua!=NULL){
                    if(rua->vm<velocidade){
                        int v = rua->destino;
                        if(!visitado[v]){
                            visitado[v] = 1;
                            fila[fim++] = v;
                        }
                    }
                    rua = rua->prox;
                }
            }
            if (min_x != DBL_MAX) {
                double largura = max_x - min_x;
                double altura = max_y - min_y;

                if (largura == 0) largura = 5.0; 
                if (altura == 0) altura = 5.0;

                char* cor = cores[(qntdComp-1)%totalCores];
                insere_bounding_box(svg, min_x, min_y, largura, altura, cor);
            }
        }
    }

    free(fila);
    free(visitado);
    return qntdComp;
}

void calcula_arvore_geradora_minima(Grafo g, double velocidade, FILE* svg){
    if(g==NULL) return;
    grafo* var = (grafo*) g;

    int n = var->qntdAtual; 

    double* chave = malloc(n*sizeof(double));
    int* pai = malloc(n* sizeof(int));
    int* contido = calloc(n,sizeof(int));

    for(int i=0;i<n;i++){
        chave[i] = DBL_MAX;
        pai[i] = -1;
    }
    Fila f = criar_fila(n*4);

    for(int i=0;i<n;i++){
        if(contido[i]) continue;
        chave[i] = 0.0;
        inserir_fila(f, i, 0.0);

        while(!fila_vazia(f)){
            int u = remove_minimo(f);
            if(contido[u]) continue;
            contido[u] = 1;

            aresta* rua = var->v[u].inicio;
            while(rua!=NULL){
                int v = rua->destino;
                double peso = rua->vm;

                if(!contido[v] && peso<chave[v]){
                    chave[v] = peso;
                    pai[v] = u;
                    inserir_fila(f, v, peso);
                }
                rua = rua->prox;
            }
        }
    }

    for(int v = 0; v<n; v++){
        int u = pai[v];
        if(u!=-1){
            aresta* rua = var->v[u].inicio;
            while(rua!=NULL){
                if(rua->destino==v){
                    if(rua->vm<velocidade){
                        rua->vm *= 1.5;
                        insere_aresta_svg(svg, var->v[u].x, var->v[u].y, var->v[v].x, var->v[v].y, "red");
                    }
                    break;
                }
                rua = rua->prox;
            }

            rua = var->v[v].inicio;
            while(rua!=NULL){
                if(rua->destino==u){
                    if(rua->vm<velocidade){
                        rua->vm *= 1.5;
                    }
                    break;
                }
                rua = rua->prox;
            }
        }
    }

    destruir_fila(f);
    free(chave);
    free(pai);
    free(contido);
}

int encontra_vertice_mais_proximo(Grafo g, double x, double y){
    if(g==NULL) return -1;
    grafo* var = (grafo*) g;

    int maisProximo = -1;
    double menorDist = DBL_MAX;

    for(int i=0;i<var->qntdAtual;i++){
        double dx = var->v[i].x -x;
        double dy = var->v[i].y - y;
        double dist = dx * dx + dy * dy;
        if(dist<menorDist){
            menorDist = dist;
            maisProximo = i;
        }
    }
    return maisProximo;
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