#ifndef registrador_h
#define registrador_h

typedef void* Registrador;

/*

*/

/// @brief Cria um novo registrador
/// @param cep O cep que sera salvo no registrador
/// @param face A face que sera salva no registrador
/// @param num O numero que sera salvo no registrador
/// @param x A coordenada x que sera salva no registrador
/// @param y A coordenada y que sera salva no registrador
/// @return Retorna um ponteiro para o registrador criado
Registrador criar_registrador(char* cep, char face, int num, double x, double y);

/// @brief Obtem o cep de um registrador
/// @param reg O registrador
/// @return Retorna o cep
char* getCepRegistrador(Registrador reg);

/// @brief Obtem a face de um registrador
/// @param reg O registrador
/// @return Retorna a face
char getFaceRegistrador(Registrador reg);

/// @brief Obtem o numero de um registrador
/// @param reg O registrador
/// @return Retorna o numero
int getNumRegistrador(Registrador reg);

/// @brief Obtem a coordenada x de um registrador
/// @param reg O registrador
/// @return Retorna a coordenada x
double getXRegistrador(Registrador reg);

/// @brief Obtem a coordenada y do registrador
/// @param reg O registrador
/// @return Retorna a coordenada y
double getYRegistrador(Registrador reg);

/// @brief Define o cep de um registrador
/// @param reg O registrador
/// @param cep O cep
void setCepRegistrador(Registrador reg, char* cep);

/// @brief Define a face de um registrador
/// @param reg O registrador
/// @param face A face
void setFaceRegistrador(Registrador reg, char face);

/// @brief Define o numero de um registrador
/// @param reg O registrador
/// @param num O numero 
void setNumRegistrador(Registrador reg, int num);

/// @brief Define a coordenada x de um registrador
/// @param reg O registrador
/// @param x A coordenada x
void setXRegistrador(Registrador reg, double x);

/// @brief Define a coordenada y de um registrador
/// @param reg O registrador
/// @param y A coordenada y
void setYRegistrador(Registrador reg, double y);

/// @brief Libera a memoria de um registrador
/// @param reg O registrador
void destruir_registrador(Registrador reg);

#endif