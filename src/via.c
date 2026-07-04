#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/via.h"
#include "../include/grafo.h"

#define TAM_LINHA 256

void leVia(FILE* via,Grafo original, Grafo naoDirecionado, Grafo transposto){
    char id[48], ldir[24], lesq[24], func[4], i[48], j[48];
    double x, y, cmp, vm;
    char* linhaVia = malloc(TAM_LINHA);
    while(fgets(linhaVia, TAM_LINHA, via)!=NULL){
        func[0] = '\0';
        sscanf(linhaVia, "%s", func);
        if(strcmp(func, "v")==0){
            sscanf(linhaVia, "%*s %s %lf %lf", id, &x, &y);
            inserir_vertice(original, id, x, y);
            inserir_vertice(naoDirecionado, id, x, y);
            inserir_vertice(transposto, id, x, y);
        }
        else if(strcmp(func, "e")==0){
            sscanf(linhaVia, "%*s %s %s %s %s %lf %lf %s", i, j, ldir, lesq, &cmp, &vm, id);
            inserir_aresta(original, i, j, ldir, lesq, cmp, vm, id);
            inserir_aresta(naoDirecionado, i, j, ldir, lesq, cmp, vm, id);
            inserir_aresta(naoDirecionado, j, i, ldir, lesq, cmp, vm, id);
            inserir_aresta(transposto, j, i, ldir, lesq, cmp, vm, id);
        }else{
            printf("Comando nao identificado");
        }
    }
    free(linhaVia);
}