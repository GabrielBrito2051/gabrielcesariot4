#ifndef svg_h
#define svg_h

#include "../include/quadra.h"
#include "../include/registrador.h"

/*

*/

/// @brief Adiciona a tag inicial do arquivo svg
/// @param svg Poneitro para o arquivo svg
/// @param max_x Valor que indica a maior coordenada x das quadras
/// @param max_y Valor que indica a maior coordenada y das quadras
void start_svg(FILE* svg, int max_x, int max_y);

/// @brief Insere uma quadra no arquivo svg
/// @param svg Ponteiro para o arquivo svg
/// @param q A quadra
/// @param e O estilo das quadras
void insere_quadra_svg(FILE *svg, Quadra q, Estilo e);

/// @brief Insere as informacoes de um registrador no svg
/// @param svg Ponteiro para o arquivo svg
/// @param x Coordenada x do registrador 
/// @param y Coordenada y do registrador
void insere_registrador_svg(FILE* svg, double x, double y,int indice);

/// @brief Insere uma bounding box no arquivo svg
/// @param svg Ponteiro para o arquivo svg
/// @param x Coordenada x da ancora da bounding box
/// @param y Coordenada y da ancora da bounding box
/// @param largura Largura da caixa
/// @param altura Altura da caixa
/// @param cor Cor que sera utilizada na insercao da caixa
void insere_bounding_box(FILE* svg, double x, double y, double largura, double altura, char* cor);

/// @brief Insere uma aresta no svg
/// @param svg Ponteiro para o arquivo svg
/// @param xi Coordenada x do inicio da aresta
/// @param yi Coordenada y do inicio da aresta
/// @param xf Coodenada x do fim da aresta
/// @param yf Coordenada y do fim da aresta
/// @param cor Cor que sera utilizada na aresta
void insere_aresta_svg(FILE* svg, double xi, double yi, double xf, double yf, char* cor);

/// @brief Insere as "placas" de inicio e fim no arquivo svg
/// @param svg Ponteiro para o arquivo svg
/// @param xi Coordenada x de inicio do endereco
/// @param yi Coordenada y de fim do endereco
/// @param xf Coordenada x de inicio do endereco
/// @param yf Coordenada y de fim do endereco
void insere_inicio_fim_svg(FILE* svg,double xi,double yi,double xf,double yf);

/// @brief Insere a tag final no arquivo sg
/// @param svg Ponteiro para o arquivo svg
void fecha_svg(FILE* svg);

#endif