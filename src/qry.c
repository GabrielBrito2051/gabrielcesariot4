#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/qry.h"
#include "../include/quadra.h"
#include "../include/grafo.h"
#include "../include/registrador.h"
#include "../include/hashtable.h"
#include "../include/svg.h"
#include "../include/txt.h"

#define TAM_LINHA 256

void leQry(FILE* qry, FILE* txt, FILE* svgQry, Grafo direcionado, Registrador* vetReg, Quadra* vetQuadras, Hashtable htQuadras, Grafo naoDirecionado, Grafo transposto){
    char func[8], reg[4], cep[48], face, reg2[4], cc[48], cr[48];
    int num;
    double x, y, w, h, vm;
    char* linhaQry = malloc(TAM_LINHA);
    Hashtable htRegs = criar_hashtable(11);
    Registrador regist;
    int i=0, indice, indice2;
    while(fgets(linhaQry, TAM_LINHA, qry)!=NULL){
        func[0] = '\0';
        sscanf(linhaQry, "%s", func);
        if(strcmp(func, "@o?")==0){
            sscanf(linhaQry, "%*s %s %s %c %d", reg, cep, &face, &num);
            indice = buscar_hashtable(htQuadras, cep);
            if(indice>=0){
                x = calculaXEndereco(vetQuadras[indice],face, num);
                y = calculaYEndereco(vetQuadras[indice],face, num);
                if(buscar_hashtable(htRegs, reg)<0){
                    regist = criar_registrador(cep, face, num, x, y);
                    inserir_hashtable(htRegs, reg, i);
                    vetReg[i] = regist;
                    indice = i;
                    i++;
                }else{
                    indice = buscar_hashtable(htRegs, reg);
                    setCepRegistrador(vetReg[indice], cep);
                    setFaceRegistrador(vetReg[indice], face);
                    setNumRegistrador(vetReg[indice], num);
                    setXRegistrador(vetReg[indice], x);
                    setYRegistrador(vetReg[indice], y);
                }
                insere_registrador_svg(svgQry, x, y, indice);
                print_coordenadas_registrador(txt, x, y, indice);
            }else printf("CEP '%s' nao encontrado para o registrador '%s'\n", cep, reg);
        }
        else if(strcmp(func, "mvm")==0){
            sscanf(linhaQry, "%*s %lf %lf %lf %lf %lf", &vm, &x, &y, &w, &h);
            alterar_velocidade_media(direcionado, x, y, w, h, vm);
            alterar_velocidade_media(naoDirecionado, x, y, w, h, vm);
            alterar_velocidade_media(transposto, x, y, w, h, vm);
        }
        else if(strcmp(func, "regs")==0){
            sscanf(linhaQry, "%*s %lf", &vm);
            int qntdComp = calcula_componentes_conexos(direcionado, transposto, vm, svgQry);
            print_numero_componentes(txt, qntdComp);
        }
        else if(strcmp(func, "exp")==0){
            sscanf(linhaQry, "%*s %lf", &vm);
            calcula_arvore_geradora_minima(naoDirecionado, vm, svgQry);
        }
        else if(strcmp(func, "p?")==0){
            sscanf(linhaQry, "%*s %s %s %s %s", reg, reg2, cc, cr);
            indice = buscar_hashtable(htRegs, reg);
            indice2 = buscar_hashtable(htRegs, reg2);
            if(indice>=0 && indice2>=0){
                int origem = encontra_vertice_mais_proximo(direcionado,getXRegistrador(vetReg[indice]), getYRegistrador(vetReg[indice]));
                int destino = encontra_vertice_mais_proximo(direcionado, getXRegistrador(vetReg[indice2]), getYRegistrador(vetReg[indice2]));

                iniciar_percurso_objeto(svgQry, 1, getXRegistrador(vetReg[indice]), getYRegistrador(vetReg[indice]));
                busca_menor_distancia(direcionado, origem, destino, svgQry,cc, txt);
                finalizar_percurso_objeto(svgQry, 1);
                iniciar_percurso_objeto(svgQry, 2, getXRegistrador(vetReg[indice2]), getYRegistrador(vetReg[indice2]));
                busca_menor_tempo(direcionado, origem, destino, svgQry,cr, txt);
                finalizar_percurso_objeto(svgQry, 2);
                insere_inicio_fim_svg(svgQry, getXRegistrador(vetReg[indice]), getYRegistrador(vetReg[indice]),getXRegistrador(vetReg[indice2]), getYRegistrador(vetReg[indice2]));
            }else printf("Registrador nao encontrado\n");
        }else{
            printf("Comando nao identificado!\n");
        }
    }
    destruir_hashtable(htRegs);
    for(int j=0;j<11;j++){
        destruir_registrador(vetReg[j]);
    }
    free(linhaQry);
}