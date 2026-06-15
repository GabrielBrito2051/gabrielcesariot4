#ifndef filaprioridade_h
#define filaprioridade_h

typedef void* Fila;

/*

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