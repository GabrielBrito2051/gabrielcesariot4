#ifndef via_h
#define via_h

#include <stdio.h>
#include "../include/grafo.h"

/*

*/

/// @brief Faz a leitura do arquivo .via
/// @param via Ponteiro para o arquivo .via
/// @param svgGeo Ponteiro para o arquivo svgGeo
/// @return Retorna o grafo criado com os vertices e arestas lidos
Grafo leVia(FILE* via, FILE* svgGeo);

#endif