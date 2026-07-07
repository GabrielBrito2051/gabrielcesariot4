#ifndef svg_h
#define svg_h

#include "../include/quadra.h"
#include "../include/registrador.h"

/*
    Esse modulo trata de arquivos .svg. Um arquivo .svg e um arquivo no qual e impresso formas geometricas, formando assim uma
    ilustracao.

    Para comecar a escrever num arquivo .svg, primeiro e necessario inicializa-lo, utilizando a funcao start_svg().

    Nesse arquivo, e possivel inserir quadras, inserir a coordenada de um registrador, inserir um bounding box para os componentes
    conexos, inserir as arestas do percurso e MST, inserir 'placas' de inicio e fim do percurso e inserir uma animacao que percorre os
    caminhos encontrados.

    Para utilizar os percursos animados, primeiro deve-se utilizar a funcao iniciar_percurso_objeto(), que insere a tag de inicio do
    percurso, em sequencia, chama-se a funcao adicionar_no_percurso() para cada vertice presente no caminho e, por fim, utilizar
    a funcao finalizar_percurso_objeto() para terminar a tag do percurso.

    Antes de liberar o ponteiro e fechar o arquivo .svg, e necessario chamar a funcao fechaSVG() para inserir a tag final no arquivo. 
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

/// @brief Inicia o percurso animado
/// @param svg O arquivo svg
/// @param idPercurso Id do percurso
/// @param x A coordenada x inicial
/// @param y A coordenada y inicial
void iniciar_percurso_objeto(FILE* svg, int idPercurso, int x, int y);

/// @brief Adiciona o proximo vertice no percurso
/// @param svg Ponteiro para o arquivo svg
/// @param x A coordenada x do vertice
/// @param y A coordenada y do vertice
void adicionar_no_percurso(FILE* svg, int x, int y);

/// @brief Insere a tag para finalizar o percuso animado
/// @param svg Ponteiro para o arquivo svg
/// @param duracao Duracao da animacao
void finalizar_percurso_objeto(FILE* svg, int idPercurso);

/// @brief Insere a tag final no arquivo sg
/// @param svg Ponteiro para o arquivo svg
void fecha_svg(FILE* svg);

#endif