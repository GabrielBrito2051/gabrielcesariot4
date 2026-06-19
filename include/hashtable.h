#ifndef hashtable_h
#define hashtable_h

typedef void* Hashtable;

/*

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
/// @return Retorna o id do elemento buscado
int buscar_hashtable(Hashtable h, char* chave);

/// @brief Libera a memoria de uma hashtable
/// @param h A hashtable
void destruir_hashtable(Hashtable h);

#endif