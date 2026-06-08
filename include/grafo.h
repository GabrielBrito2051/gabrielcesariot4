#ifndef grafo_h
#define grafo_h

typedef void* Grafo;

/*

*/

/// @brief Cria um novo grafo com um determinado numero de vertices
/// @param numVertices A quantidade de vertices do grafo
/// @return Retorna o grafo criado
Grafo criar_grafo(int numVertices);

/// @brief Insere um vertice no grafo
/// @param g O grafo
/// @param idTexto O id do vertice
/// @param x A coordenada x do vertice
/// @param y Acoordenada y do vertice
void inserir_vertice(Grafo g, int idTexto, double x, double y);

/// @brief Insere uma aresta no grafo
/// @param g O grafo
/// @param origem O id de origem da aresta
/// @param destino O id de destino da aresta
/// @param ldir A quadra que fica na direita da rua
/// @param lesq A quadra que fica na esquerda da rua
/// @param comprimento O comprimento da aresta
/// @param velocidadeMedia A velocidade media da aresta
/// @param nome O nome da rua
void inserir_aresta(Grafo g, char* origem, char* destino, char* ldir, char*lesq, double comprimento, double velocidadeMedia, char* nome);


//Grafo busca_menor_caminho(Grafo g);


//Grafo busca_menor_tempo(Grafo g);

/// @brief Libera a memoria de um grafo
/// @param g O grafo que sera destruido
void destruir_grafo(Grafo g);

#endif