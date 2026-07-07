#ifndef filaprioridade_h
#define filaprioridade_h

typedef void* Fila;

/*
    Uma lista de prioridade e uma estrutura de dados que guarda as informacoes em uma determinada ordem a partir da prioridade
    atribuida ao elemento. A lista guarda seu tamanho atual, sua capacidade maxima e um elemento.

    Para criar uma lista de prioridade, utiliza-se a funcao criar_fila(), que aloca a memoria para uma nova lista a partir da quantidade
    de elementos que poderao caber nela, passados como parametro.

    A lista possui uma funcao auxiliar que verifica se a lista esta vazia.

    A funcao inserir_fila() insere um elemento na lista de prioridade a partir da prioridade passada por parametro. A funcao
    remove_minimo() remove o elemento de maior prioridade da lista.

    Por fim, a funcao destruir_fila() libera a memoria alocada da fila.
*/

/// @brief Cria uma nova fila de prioridade
/// @param numVertices A capacidade maxima de vertices que a fila tera
/// @return Retorna um ponteiro para a fila cirada
Fila criar_fila(int numVertices);

/// @brief Verifica se uma fila esta vaza
/// @param f A fila
/// @return Retorna 1 se estiver vazia e 0 caso contrario
int fila_vazia(Fila f);

/// @brief Insere um elemento na fila de prioridade
/// @param f A fila
/// @param idVertice O id do vertice que sera inserido 
/// @param prioridade A prioridade do vertice
void inserir_fila(Fila f, int idVertice, double prioridade);

/// @brief Remove o vertice de maior prioridade da fila de prioridade
/// @param f A fila
/// @return Retorna o id do vertice removido
int remove_minimo(Fila f);

/// @brief Libera a memoria de uma fila
/// @param f A fila
void destruir_fila(Fila f);

#endif