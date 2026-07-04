#ifndef qry_h
#define qry_h

#include <stdio.h>
#include "../include/quadra.h"
#include "../include/grafo.h"
#include "../include/registrador.h"
#include "../include/hashtable.h"

/*

*/

/// @brief Faz a leitura do arquivo qry
/// @param qry Ponteiro para o arquivo qry
/// @param txt Ponteiro para o arquivo txt
/// @param svgQry Ponteiro para o arquivo svg do qry
/// @param g O grafo
/// @param vetReg Vetor que armazena os registradores
/// @param vetQuadras Vetor que armzena as quadras
/// @param htQuadras Hashtable de quadras
/// @param naoDirecionado Grafo nao direcionado "identico" ao grafo original
/// @param transposto Grafo com as direcoes invertidas ao do original
void leQry(FILE* qry, FILE* txt, FILE* svgQry, Grafo g, Registrador* vetReg, Quadra* vetQuadras, Hashtable htQuadras, Grafo naoDirecionado, Grafo transposto);

#endif