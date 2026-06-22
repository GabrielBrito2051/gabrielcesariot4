#ifndef registrador_h
#define registrador_h

typedef void* Registrador;

/*

*/

/// @brief 
/// @return 
Registrador criar_registrador(char* cep, char face, int num, double x, double y);

/// @brief 
/// @param reg 
/// @return 
char* getCepRegistrador(Registrador reg);

/// @brief 
/// @param reg 
/// @return 
char* getFaceRegistrador(Registrador reg);

/// @brief 
/// @param reg 
/// @return 
int getNumRegistrador(Registrador reg);

/// @brief 
/// @param reg 
/// @return 
double getXRegistrador(Registrador reg);

/// @brief 
/// @param reg 
/// @return 
double getYRegistrador(Registrador reg);

/// @brief 
/// @param reg 
/// @param cep 
void setCepRegistrador(Registrador reg, char* cep);

/// @brief 
/// @param reg 
/// @param face 
void setFaceRegistrador(Registrador reg, char face);

/// @brief 
/// @param reg 
/// @param num 
void setNumRegistrador(Registrador reg, int num);

/// @brief 
/// @param reg 
/// @param x 
void setXRegistrador(Registrador reg, double x);

/// @brief 
/// @param reg 
/// @param y 
void setYRegistrador(Registrador reg, double y);


void destruir_registrador(Registrador reg);

#endif