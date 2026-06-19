#ifndef geo_h
#define geo_h
#include <stdio.h>
#include "../include/hashtable.h"
#include "../include/quadra.h"

/*

*/

/// @brief Le a quantidade total de quadras do arquivo geo
/// @param geo Ponteiro para o arquivo geo
/// @return Retorna a quantidade de qudras no arquivo
int leNumeroQuadras(FILE* geo);

/// @brief Faz a leitura do arquivo .geo
/// @param geo Ponteiro para o arquivo geo
/// @param hash_quadras A hashtable de guarda as quadras
/// @param svgGeo Ponteiro para o arquivo svgGeo
void leGeo(FILE* geo, Hashtable hash_quadras, FILE* svgGeo);

#endif