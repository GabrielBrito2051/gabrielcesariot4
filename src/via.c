#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/via.h"
#include "../include/grafo.h"

#define TAM_LINHA 256

Grafo leVia(FILE* via){
    Grafo g;
    int nv;
    char id[48], ldir[24], lesq[24], func[4], i[48], j[48];
    double x, y, cmp, vm;
    char* linhaVia = malloc(TAM_LINHA);
    while(fgets(linhaVia, TAM_LINHA, via)!=NULL){
        sscanf(linhaVia, "%s", func);
        if(strcmp(func, "nv")==0){
            sscanf(linhaVia, "%d", &nv);
            g = criar_grafo(nv);
        }
        else if(strcmp(func, "v")==0){
            sscanf(linhaVia, "%*s %s %lf %lf", id, &x, &y);
            inserir_vertice(g, id, x, y);
        }
        else if(strcmp(func, "e")==0){
            sscanf(linhaVia, "%*s %s %s %s %s %lf %lf %s", i, j, ldir, lesq, &cmp, &vm, id);
            inserir_aresta(g, i, j, ldir, lesq, cmp, vm, id);
            inserir_aresta(g, j, i, ldir,lesq, cmp, vm, id);
        }else{
            printf("Comando nao identificado");
        }
    }
    return g;
}