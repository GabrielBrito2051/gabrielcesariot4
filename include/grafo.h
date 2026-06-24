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
/// @param origem Posicao do vertice de origem na losta de vertices do grafo
/// @param destino Posicao do vertice de destino na lista de vertices do grafo
/// @param svg Ponteiro para o arquivo svg que sera impresso o percurso
/// @param txt Ponteiro para o arquivo com as intrucoes do percurso
void busca_menor_distancia(Grafo g, int origem, int destino, FILE* svg, FILE* txt);

/// @brief Calcula o caminho de menor tempo entre dois pontos
/// @param g O grafo
/// @param origem Posicao do vertice de origem na lista de vertices do grafo
/// @param destino Posicao do vertice de destino na lista de vertices do grafo
/// @param svg Ponteiro para o arquivo svg que sera impresso o percurso
/// @param txt Ponteiro para o arquivo com as intrucoes do percurso
void busca_menor_tempo(Grafo g, int origem, int destino, FILE* svg, FILE* txt);

/// @brief Altera as velocidades medias de todas as arestas dentro de uma bounding box
/// @param g O grafo
/// @param x Coordenada x da ancora da bounding box
/// @param y Coordenada y da ancora da bounding box
/// @param w Largura da bounding box
/// @param h Altura da bounding box
/// @param vm A nova velocidade media das arestas
void alterar_velocidade_media(Grafo g, double x, double y, double w, double h, double vm);

/// @brief Calcula os componentes conexos do grafo
/// @param g O grafo
/// @param velocidade A velocidade maxima dos componentes
/// @param svg Ponteiro para o arquivo svg para imprimir a bounding box
/// @return Retorna a quantidade de elementos conexos. Retorna -1 em caso de erro
int calcula_componentes_conexos(Grafo g, double velocidade, FILE* svg);

/// @brief Calcula a arvore geradora minima, seleciona as arestas com menor velocidade media e aumenta sua velocidade em 50%
/// @param g O grafo
/// @param velocidade A velocidade minima
/// @param svg Ponteiro para o arquivo svg para imprimir as arestaas que terao sua velocidade media aumentada
void calcula_arvore_geradora_minima(Grafo g, double velocidade, FILE* svg);

/// @brief Encontra o vertice mais proximo de uma coordenada qualquer
/// @param g O grafo
/// @param x A coordenada x
/// @param y A coordenada y
/// @return Retorna o id numerico do vertice
int encontra_vertice_mais_proximo(Grafo g, double x, double y);

/// @brief Libera a memoria de um grafo
/// @param g O grafo que sera destruido
void destruir_grafo(Grafo g);

#endif