#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/geo.h"
#include "../include/hashtable.h"
#include "../include/quadra.h"
#include "../include/svg.h"

#define TAM_LINHA 256

int leNumeroQuadras(FILE* geo, double* max_x, double* max_y){
    int nQuadras = 0;
    char func[4];
    char* linhaGeo = malloc(TAM_LINHA);
    double x, y, h, w;
    while(fgets(linhaGeo, TAM_LINHA, geo)!=NULL){
        sscanf(linhaGeo, "%s", func);
        if(strcmp(func, "q")==0){
            nQuadras++;
            sscanf(linhaGeo, "%*s %*s %lf %lf %lf %lf", &x, &y, &w, &h);
            if(x + w > *max_x) *max_x = x+w;
            if(y + h > *max_y) *max_y = y+h;
        }
    }
    free(linhaGeo);

    return nQuadras;
}

void leGeo(FILE* geo, Hashtable ht, FILE* svgGeo, Quadra* vetQuadras, Estilo ts){
    char cep[48], sw[8], fill[32], strk[32], func[4];
    double x, y, w, h;
    char* linhaGeo = malloc(TAM_LINHA);
    int i=0;
    while(fgets(linhaGeo, TAM_LINHA, geo)!=NULL){
        func[0] = '\0';
        sscanf(linhaGeo, "%s", func);
        if(strcmp(func,"q")==0){
            sscanf(linhaGeo, "%*s %s %lf %lf %lf %lf", cep, &x, &y, &w, &h);
            Quadra q = criar_quadra(cep, x, y, w, h);
            vetQuadras[i] = q;
            inserir_hashtable(ht, cep, i);
            i++;
            insere_quadra_svg(svgGeo, q, ts);
        }else if(strcmp(func, "cq")==0){
            sscanf(linhaGeo,"%*s %s %s %s", sw, fill, strk);
            setSw(ts, sw);
            setFill(ts, fill);
            setStrk(ts,strk);
        }else{
            printf("Comando nao identificado!");
        }
    }
    free(linhaGeo);
}