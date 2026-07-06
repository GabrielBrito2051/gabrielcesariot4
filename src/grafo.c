#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

aresta* nova_aresta(char* idDestino, double comprimento, double velocidadeMedia, char* ldir, char* lesq, char* nome){
    aresta* novo = malloc(sizeof(aresta));

    strcpy(novo->destino,idDestino);
    novo->cmp = comprimento;
    novo->vm = velocidadeMedia;
    strcpy(novo->nome, nome);
    strcpy(novo->ldir, ldir);
    strcpy(novo->lesq,lesq);

    return novo;
}

char* buscar_nome_rua(grafo* g, int origem, int destino){
    aresta* rua = g->v[origem].inicio;
    int destinoRua;
    while(rua!=NULL){
        destinoRua = buscar_hashtable(g->mapaIds, rua->destino);
        if(destinoRua==destino){
            return rua->nome;
        }
        rua = rua->prox;
    }
    return "Rua sem nome";
}

void empilha_grafo(Grafo g, int vertice, int* visitados, int* pilha, int* topo, double velocidade){
    visitados[vertice] = 1;
    grafo* var = (grafo*) g;
    aresta* rua = var->v[vertice].inicio;

    while(rua!=NULL){
        if(rua->vm<velocidade){
            int vizinho = buscar_hashtable(var->mapaIds, rua->destino);
            if(vizinho!=-1 && !visitados[vizinho]){
                empilha_grafo(var, vizinho, visitados, pilha, topo, velocidade);
            }
        }
        rua = rua->prox;
    }
    pilha[(*topo)++] = vertice;
}

void desempilha_grafo(Grafo gTransposto, int vertice, int* visitados, double velocidade, double* min_x, double* max_x, double* min_y, double* max_y){
    grafo* transposto = (grafo*) gTransposto;
    visitados[vertice] = 1;

    double vx = transposto->v[vertice].x;
    double vy = transposto->v[vertice].y;
    if (vx < *min_x) *min_x = vx;
    if (vx > *max_x) *max_x = vx;
    if (vy < *min_y) *min_y = vy;
    if (vy > *max_y) *max_y = vy;

    aresta* rua = transposto->v[vertice].inicio;
    while(rua!=NULL){
        if(rua->vm<velocidade){
            int vizinho = buscar_hashtable(transposto->mapaIds, rua->destino);
            if(vizinho!=-1 && !visitados[vizinho]){
                desempilha_grafo(transposto, vizinho, visitados, velocidade, min_x, max_x, min_y, max_y);
            }
        }
        rua = rua->prox;
    }
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

    }

    return g;
}

void inserir_vertice(Grafo g, char* idTexto, double x, double y){
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

    aresta* nova = nova_aresta(destino, comprimento, velocidadeMedia, ldir, lesq, nome);
    if(nova==NULL) return;

    nova->prox = var->v[idOrigem].inicio;
    var->v[idOrigem].inicio = nova;
}

void busca_menor_distancia(Grafo g, int origem, int destino, FILE* svg, char* cc, FILE* txt){
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
            int v = buscar_hashtable(var->mapaIds, rua->destino);
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
        fprintf(txt,"Nao foi encontrada uma rota\n");
    }else{
        fprintf(txt,"Rota de menor distancia encontrada! Instrucoes:\n");

        int* aux = malloc(n*sizeof(int));
        int cont = 0;
        int atual = destino;
        aux[cont++] = atual;

        while(antecessor[atual]!=-1){
            int ant = antecessor[atual];
            insere_aresta_svg(svg, var->v[ant].x,var->v[ant].y, var->v[atual].x, var->v[atual].y, cc);
            aux[cont++] = ant;
            atual = ant;    
        }

        int* caminho = malloc(cont* sizeof(int));
        for(int i=0;i<cont;i++){
            caminho[i] = aux[cont-1-i];
        }

        iniciar_percurso_objeto(svg, 2, var->v[caminho[0]].x, var->v[caminho[0]].y);
        for(int i=1;i<cont;i++){
            adicionar_no_percurso(svg, var->v[caminho[i]].x, var->v[caminho[i]].y);
        }
        finalizar_percurso_objeto(svg, 2);

        char* rua_inicial = buscar_nome_rua(var, caminho[0], caminho[1]);
        fprintf(txt, "Siga pela rua %s", rua_inicial);
        for(int i=0;i<cont-2;i++){
            int a = caminho[i], b = caminho[i+1], c = caminho[i+2];
            double xa = var->v[a].x, ya = var->v[a].y;
            double xb = var->v[b].x, yb = var->v[b].y;
            double xc = var->v[c].x, yc = var->v[c].y;
            double cruzamento = (xb-xa)*(yc - yb) - (yb - ya) * (xc - xb);

            char* proxima_rua = buscar_nome_rua(var, b, c);
            if(cruzamento>0.1){
                print_direcao(txt, "direita", proxima_rua);
            }
            else if(cruzamento<-0.1){
                print_direcao(txt, "esquerda", proxima_rua);
            }else{
                fprintf(txt, "Siga em frente na rua %s\n", proxima_rua);
            }
        }
        fprintf(txt, "Voce chegou ao seu destino!\tDistancia total:%.2lf km\n\n",distancia[destino]);
        free(aux);
        free(caminho);
    }

    destruir_fila(f);
    free(distancia);
    free(antecessor);
    free(visitado);
}

void busca_menor_tempo(Grafo g, int origem, int destino, FILE* svg, char* cr,FILE* txt){
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
            int v = buscar_hashtable(var->mapaIds, rua->destino);

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
    if(tempoAcumulado[destino] == FLT_MAX){
        fprintf(txt,"Nao foi encontrado uma rota\n");
    }else{
        fprintf(txt,"Rota de menor tempo encontrada! Instrucoes:\n");
        float minutos = tempoAcumulado[destino] * 60.0;

        int* aux = malloc(n*sizeof(int));
        int cont = 0;
        int atual = destino;
        aux[cont++] = atual;

        while(antecessor[atual]!=-1){
            int ant = antecessor[atual];
            insere_aresta_svg(svg, var->v[ant].x,var->v[ant].y, var->v[atual].x, var->v[atual].y, cr);
            aux[cont++] = ant;
            atual = ant;    
        }

        int* caminho = malloc(cont* sizeof(int));
        for(int i=0;i<cont;i++){
            caminho[i] = aux[cont-1-i];
        }

        iniciar_percurso_objeto(svg, 1, var->v[caminho[0]].x, var->v[caminho[0]].y);
        for(int i=1;i<cont;i++){
            adicionar_no_percurso(svg, var->v[caminho[i]].x, var->v[caminho[i]].y);
        }
        finalizar_percurso_objeto(svg, 1);

        char* rua_inicial = buscar_nome_rua(var, caminho[0], caminho[1]);
        fprintf(txt, "Siga pela rua %s", rua_inicial);
        for(int i=0;i<cont-2;i++){
            int a = caminho[i], b = caminho[i+1], c = caminho[i+2];
            double xa = var->v[a].x, ya = var->v[a].y;
            double xb = var->v[b].x, yb = var->v[b].y;
            double xc = var->v[c].x, yc = var->v[c].y;
            double cruzamento = (xb-xa)*(yc - yb) - (yb - ya) * (xc - xb);

            char* proxima_rua = buscar_nome_rua(var, b, c);
            if(cruzamento>0.1){
                print_direcao(txt, "direita", proxima_rua);
            }
            else if(cruzamento<-0.1){
                print_direcao(txt, "esquerda", proxima_rua);
            }else{
                fprintf(txt, "Siga em frente na rua %s\n", proxima_rua);
            }
        }
        fprintf(txt, "Voce chegou ao seu destino!\tTempo total:%.1lf minutos\n\n",minutos);
        free(aux);
        free(caminho);
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
                int indice = buscar_hashtable(var->mapaIds, atual->destino);
                vertice destino = var->v[indice];
                if(destino.x >= x && destino.x <= (x + w) && destino.y >= y && destino.y <= (y + h)){
                    atual->vm = vm;
                }
                atual = atual->prox;
            }
        }
    }
}

int calcula_componentes_conexos(Grafo gOriginal, Grafo gTransposto, double velocidade, FILE* svg){
    if(gOriginal==NULL) return -1;
    grafo* original = (grafo*)gOriginal;
    grafo* transposto = (grafo*) gTransposto;

    int n = original->qntdAtual;
    int* visitados = calloc(n, sizeof(int));
    int* pilha = malloc(n * sizeof(int));
    int topo = 0;
    int qntdComp = 0;

    char* cores[] = {"red", "cyan", "green", "orange", "purple",  "yellow", "magenta", "brown", "darkgreen", "teal"};
    int totalCores = 10;

    for(int i=0;i<n;i++){
        if(!visitados[i]){
            empilha_grafo(original, i, visitados, pilha, &topo, velocidade);
        }
    }

    for(int i=0;i<n;i++) visitados[i]=0;

    while(topo>0){
        int v = pilha[--topo];
        if(!visitados[v]){
            qntdComp++;
            double min_x = DBL_MAX, max_x = -DBL_MAX;
            double min_y = DBL_MAX, max_y = -DBL_MAX;
            desempilha_grafo(transposto, v, visitados, velocidade, &min_x, &max_x, &min_y, &max_y);
            double largura = max_x - min_x;
            double altura = max_y - min_y;

            if (largura == 0) largura = 5.0; 
            if (altura == 0) altura = 5.0;

            if(largura>0 && altura>0){
                char* cor = cores[(qntdComp-1)%totalCores];
                insere_bounding_box(svg, min_x, min_y, largura, altura, cor);
            }
        }
    }
    free(visitados);
    free(pilha);

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
                int v = buscar_hashtable(var->mapaIds, rua->destino);
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
                if(buscar_hashtable(var->mapaIds, rua->destino)==v){
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
                if(buscar_hashtable(var->mapaIds, rua->destino)==u){
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