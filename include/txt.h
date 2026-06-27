#ifndef txt_h
#define txt_h

/*

*/

/// @brief Imprime as coordenadas relativas ao endereco obtido pelo registrador
/// @param txt Ponteiro para o arquivo txt
/// @param x Coordenada x obtida pelo registrador
/// @param y Coordenada y obtida pelo registrador
/// @param indice Posicao do registrador no vetor
void print_coordenadas_registrador(FILE* txt, double x, double y, int indice);

/// @brief Imprime o numero de componentes conexos 
/// @param txt Ponteiro para o arquivo txt
/// @param numero A quantidade de componentes conexos
void print_numero_componentes(FILE* txt, int numero);

/// @brief Imprime a descricao do percurso.
/// @param txt Ponteiro para o arquivo txt
/// @param sentido Indica qual sentido deve pegar
/// @param rua Indica qual rua deve-se ir
void print_direcao(FILE* txt, char* sentido, char* rua);

#endif