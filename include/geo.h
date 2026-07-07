#ifndef geo_h
#define geo_h
#include <stdio.h>
#include "../include/hashtable.h"
#include "../include/quadra.h"

/*
    Esse modulo cuida da funcao de ler um arquivo de quadras .geo.

    A funcao leNumeroQuadras() faz a leitura do arquivo .geo por completo e durante esse processo verifica a quantidade de quadras
    a, alem disso, tambem verifica quais sao as maiores coordenadas x e y para poder criar o arquivo .svg do tamanho correto. Os
    parametros utilizados para armazenar essas coordenadas devem ser passado por referencia. A funcao leGeo() le as linhas do 
    arquivo .geo e vai criando e aramazenando os objetos lidos.

    Alem disso, essa funcao insere os objetos criados num arquivo .svg.
*/

/// @brief Le a quantidade total de quadras do arquivo geo
/// @param geo Ponteiro para o arquivo geo
/// @param max_x Maior coordenada x das quadras
/// @param max_y Maior coordenada y das quadras
/// @return Retorna a quantidade de qudras no arquivo
int leNumeroQuadras(FILE* geo, double* max_x, double* man_y);

/// @brief Faz a leitura do arquivo .geo
/// @param geo Ponteiro para o arquivo geo
/// @param hash_quadras A hashtable de guarda as quadras
/// @param svgGeo Ponteiro para o arquivo svgGeo 
/// @param vetQuadras Vetor que armazena as quadras
/// @param ts Estilo das quadras
void leGeo(FILE* geo, Hashtable hash_quadras, FILE* svgGeo,Quadra* vetQuadras, Estilo ts);

#endif