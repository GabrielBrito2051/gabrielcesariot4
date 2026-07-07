#ifndef hashtable_h
#define hashtable_h

typedef void* Hashtable;

/*
    Uma hashtable e uma estrutura que guarda uma chave (string) e um valor a partir de um hash unico criado a partir da chave. A hashtable
    guarda sua capacidade maxima, a chave do elemento inserido(48 caracteres max.), e o valor do indice do elemento no vetor.

    Para criar uma hashtable, utiliza-se a funcao criar_hashtable(), que aloca memoria para a estrutura. Para realizar sua criacao, e
    necessario passar a capacidade maxima como parametro.

    A hashtable possui duas funcoes, inserir e remover um elemento dela. A funcao inserir_hashtable() guarda uma chave junto com seu
    valor. A funcao buscar_hashtable() faz a busca do elemento baseado na chave passada e retorna o valor que foi passado
    anteriormente na sua insercao.

    Por ultimo, existe a funcao destruir_hashtable() para liberar a memoria da hashtable.
*/

/// @brief Cria uma nova hashtable
/// @param capacidade A capacidade maxima da hashtable
/// @return Retorna um ponteiro para a hashtable criada
Hashtable criar_hashtable(int capacidade);

/// @brief Insere um elemento na hashtable
/// @param h A hashtable
/// @param chave A string do elemento que sera inserido
/// @param valor O id do elemento
void inserir_hashtable(Hashtable h, char* chave, int valor);

/// @brief Faz a busca de um elemento na hashtable
/// @param h A hashtable
/// @param chave A string do elemento que sera buscado
/// @return Retorna o id do elemento buscado. Caso nao encontre o elemento, retorna -1
int buscar_hashtable(Hashtable h, char* chave);

/// @brief Libera a memoria de uma hashtable
/// @param h A hashtable
void destruir_hashtable(Hashtable h);

#endif