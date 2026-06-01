#ifndef quadra_h
#define quadra_h

typedef  void* Quadra;
typedef void* Estilo;

/*

*/

/// @brief Cria uma nova quadra
/// @param cep O cep da quadra
/// @param x A coordenada x da ancora da quadra
/// @param y A coordenada y da ancora da quadra
/// @param w A largura da quadra
/// @param h A altura da quadra
/// @return Retorna um pornteiro para a quadra criada
Quadra criar_quadra(char* cep, double x, double y, double w, double h);

/// @brief Obtem o cep de uma quadra
/// @param q A quadra
/// @return Retorna uma string contendo o cep da quadra
char* getCepQuadra(Quadra q);

/// @brief Obtem o valor da coordenada x da ancora de uma quadra
/// @param q A quadra
/// @return Retorna o double contendo a coordenada x da quadra
double getXQuadra(Quadra q);

/// @brief Obtem o valor da coordenada y da ancora de uma quadra
/// @param q A quadra
/// @return Retorna a coordenada y da quadra
double getYQuadra(Quadra q);

/// @brief Obtem o valor da largura de uma quadra
/// @param q A quadra
/// @return Retorna a largura da quadra
double getWQuadra(Quadra q);

/// @brief Obtem o valor da altura de uma quadra
/// @param q A quadra
/// @return Retorna a altura da quadra
double getHQuadra(Quadra q);

/// @brief Libera a memoria de uma quadra
/// @param q A quadra
void liberar_quadra(Quadra q);

/// @brief Cria um novo estilo para a impressao das quadras no arquivo .svg
/// @param sw Espessura da borda da quadra
/// @param fill Cor de preenchimento da quadra
/// @param strk Cor da borda da quadra
/// @return Retorna um ponteiro para o estilo criado
Estilo criar_estilo(char* sw, char* fill, char* strk);

/// @brief Obtem o valor da espessura da borda das quadras
/// @param ts O estilo
/// @return Retorna uma string contendo a espessura da borda das quadras
char* getSw(Estilo ts);

/// @brief Obtem o valor da cor de preenchimento das quadras
/// @param ts O estilo
/// @return Retorna uma string contendo a cor de preenchimento das quadras
char* getFill(Estilo ts);

/// @brief Obtem o valor da cor da borda das quadras
/// @param ts O estilo
/// @return Retorna uma string contendo a cor da borda das quadras
char* getStrk(Estilo ts);

/// @brief Define o valor da espessura da borda das quadras
/// @param ts O estilo
/// @param sw String contendo o novo valor da borda das quadras
void setSw(Estilo ts, char* sw);

/// @brief Define o valor da cor de preenchimento das quadras
/// @param ts O estilo
/// @param fill String contendo o novo valor da cor de preenchimento das quadras
void setFill(Estilo ts, char* fill);

/// @brief Define o valor da cor de borda das quadras
/// @param ts O estilo
/// @param strk String contendo o novo valor da cor de borda das quadras
void setStrk(Estilo ts, char* strk);

/// @brief Libera a memoria do estilo
/// @param e O estilo
void removerEstilo(Estilo ts);

#endif