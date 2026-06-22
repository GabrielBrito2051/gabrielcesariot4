#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/qry.h"
#include "../include/quadra.h"
#include "../include/grafo.h"
#include "../include/registrador.h"
#include "../include/hashtable.h"

#define TAM_LINHA 256

void leQry(FILE* qry, FILE* txt, FILE* svgQry, Grafo g, Registrador* vetReg, Quadra* vetQuadras, Hashtable htQuadras){
    char func[8], reg[4], cep[48], face, id[48];
    int num;
    double x, y, w, h, vm;
    char* linhaQry = malloc(TAM_LINHA);
    Hashtable htRegs = criar_hashtable(11);
    Registrador regist;
    int i=0, indice;
    while(fgets(linhaQry, TAM_LINHA, qry)!=NULL){
        sscanf(linhaQry, "%s", func);
        if(strcmp(func, "@o?")==0){
            sscanf(linhaQry, "%*s %s %s %c %d", reg, cep, &face, &num);
            indice = buscar_hashtable(htQuadras, cep);
            x = calculaXEndereco(vetQuadras[indice],face, num);
            y = calculaYEndereco(vetQuadras[indice],face, num);
            if(buscar_hashtable(htRegs, reg)<0){
                regist = criar_registrador(cep, face, num, x, y);
                inserir_hashtable(htRegs, reg, i);
                i++;
            }else{
                regist = buscar_hashtable(htRegs, reg);
                setCepRegistrador(regist, cep);
                setFaceRegistrador(regist, face);
                setNumRegistrador(regist, num);
                setXRegistrador(regist, x);
                setYRegistrador(regist, y);
            }
        }
        else if(strcmp(func, "mvm")==0){
            sscanf(linhaQry, "%*s %lf %lf %lf %lf %lf", &vm, &x, &y, &w, &h);
            alterar_velocidade_media(g, x, y, w, h, vm);
        }
        else if(strcmp(func, "regs")==0){

        }
        else if(strcmp(func, "exp")==0){

        }
        else if(strcmp(func, "p?")==0){

        }else{
            printf("Comando nao identificado!");
        }
    }
}