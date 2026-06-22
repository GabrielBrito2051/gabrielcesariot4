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

/// @brief Calcula o caminho de menor distancia entre dois pontos
/// @param g O grafo
/// @param idOrigem Id do vertice de origem
/// @param idDestino Id do vertice de destino
void busca_menor_distancia(Grafo g, char* idOrigem, char* idDestino);

/// @brief Calcula o caminho de menor tempo entre dois pontos
/// @param g O grafo
/// @param idOrigem Id do vertice de origem
/// @param idDestino Id do vertice de destino
void busca_menor_tempo(Grafo g, char* idOrigem, char* idDestino);

/// @brief Altera as velocidades medias de todas as arestas dentro de uma bounding box
/// @param g O grafo
/// @param x Coordenada x da ancora da bounding box
/// @param y Coordenada y da ancora da bounding box
/// @param w Largura da bounding box
/// @param h Altura da bounding box
/// @param vm A nova velocidade media das arestas
void alterar_velocidade_media(Grafo g, double x, double y, double w, double h, double vm);

/// @brief Libera a memoria de um grafo
/// @param g O grafo que sera destruido
void destruir_grafo(Grafo g);

#endif