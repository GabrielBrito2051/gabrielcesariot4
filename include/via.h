#ifndef via_h
#define via_h

#include <stdio.h>
#include "../include/grafo.h"

/*

*/

/// @brief Faz a leitura do arquivo .via
/// @param via Ponteiro para o arquivo .via
/// @param original Grafo original
/// @param naoDirecionado Copia do grafo, porem nao direcionado
/// @param transposto Copia do grafo porem com o sentido invertido
void leVia(FILE* via,Grafo original, Grafo naoDirecionado, Grafo transposto);

#endif