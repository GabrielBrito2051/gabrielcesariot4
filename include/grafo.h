#ifndef grafo_h
#define grafo_h

typedef void* Grafo;

/*
    Um grafo e uma estrutura de dados que armazena vertices e arestas. O grafo conta com uma lista de vertices e uma hashtable para
    auxiliar na busca dos vertices da lista. Tambem temos no grafo sua quantidade atual e capacidade maxima. Os vertices do grafo
    possuem um id, coordenadas x e y e e uma lista de arestas que saem dele. A aresta possui um nome, ceps
    das quadras esquerda e direita, id do vertice de destino, e valores de valocidade media e comprimento da aresta.

    Os valores maximos do id do vertice e de 48 caracteres. Os valores maximos de todas as strings das arestas sao de 48 caracteres
    que sao: id, cep das quadras esquerda e direita e id do vertice de destino.
    
    Para criar um grafo, utiliza-se a funcao criar_grafo(). Essa funcao aloca memoria para o grafo com base na quantidade total de
    vertices qu existirao. A criacao de vertices e arestas estao presentes nas funcoes criar_vertice() e criar_aresta(), que alem
    de criar o elemento, tambem ja insere-o no grafo. A criacao de vertices precisa do id e coordenadas x e y para realizar a criacao.
    Ja a criacao de arestas, alem de seu id, necessita tambem  do id de origem e destino dos vertices que ela liga, do cep das quadras
    direita e esquerda e dos valores de sua velocdade media e comprimento.

    O grafo conta com funcoes matematicas para calcular diversas coisas. Sao elas: busca de menor distancia entre dois pontos, busca
    de menor tempo entre dois pontos, alteracao da velocidade de arestas interiores  uma bounding box, calculo da qunatidade de
    componentes conexos e arvore gereadora minima, e calculo do vertice mais proximo a um determinado endereco.

    Finalmente, temos tambem a funcao destruir_grafo(), que libera a memoria de todas as estruturas (vertices, arestas e hashtable),
    alem de si proprio.
*/

/// @brief Cria um novo grafo com um determinado numero de vertices
/// @param numVertices A quantidade de vertices do grafo
/// @return Retorna o grafo criado
Grafo criar_grafo(int numVertices);

/// @brief Insere um vertice no grafo
/// @param g O grafo
/// @param idTexto O nome(id) do vertice
/// @param x A coordenada x do vertice
/// @param y Acoordenada y do vertice
void inserir_vertice(Grafo g, char* idTexto, double x, double y);

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
/// @param cc Cor que sera pintadas as arestas
/// @param txt Ponteiro para o arquivo com as intrucoes do percurso
void busca_menor_distancia(Grafo g, int origem, int destino, FILE* svg,char* cc, FILE* txt);

/// @brief Calcula o caminho de menor tempo entre dois pontos
/// @param g O grafo
/// @param origem Posicao do vertice de origem na lista de vertices do grafo
/// @param destino Posicao do vertice de destino na lista de vertices do grafo
/// @param svg Ponteiro para o arquivo svg que sera impresso o percurso
/// @param cr Cor que sera pintadas as arestas
/// @param txt Ponteiro para o arquivo com as intrucoes do percurso
void busca_menor_tempo(Grafo g, int origem, int destino, FILE* svg,char* cr, FILE* txt);

/// @brief Altera as velocidades medias de todas as arestas dentro de uma bounding box
/// @param g O grafo
/// @param x Coordenada x da ancora da bounding box
/// @param y Coordenada y da ancora da bounding box
/// @param w Largura da bounding box
/// @param h Altura da bounding box
/// @param vm A nova velocidade media das arestas
void alterar_velocidade_media(Grafo g, double x, double y, double w, double h, double vm);

/// @brief Calcula os componentes conexos do grafo
/// @param gOriginal O grafo original
/// @param gTransposto O grafo transposto
/// @param velocidade A velocidade maxima dos componentes
/// @param svg Ponteiro para o arquivo svg para imprimir a bounding box
/// @return Retorna a quantidade de elementos conexos. Retorna -1 em caso de erro
int calcula_componentes_conexos(Grafo gOriginal, Grafo gTransposto, double velocidade, FILE* svg);

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