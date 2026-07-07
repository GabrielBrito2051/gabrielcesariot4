#ifndef via_h
#define via_h

#include <stdio.h>
#include "../include/grafo.h"

/*
    Esse modulo cuida da funcao de ler o arquivo de pessoas .pm.

    A funcao leVia le as linhas do arquivo .via e vai criando e armazenando os objetos de acordo com o que e lido. E necessario que os
    tres grafos passados como parametro ja estejam inicializados para realizar as insercoes dos vertices e arestas neles.
*/

/// @brief Faz a leitura do arquivo .via
/// @param via Ponteiro para o arquivo .via
/// @param original Grafo original
/// @param naoDirecionado Copia do grafo, porem nao direcionado
/// @param transposto Copia do grafo porem com o sentido invertido
void leVia(FILE* via,Grafo original, Grafo naoDirecionado, Grafo transposto);

#endif