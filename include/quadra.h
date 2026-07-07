#ifndef quadra_h
#define quadra_h

typedef  void* Quadra;
typedef void* Estilo;

/*
    Uma quadra e um espaco que possui variados enderecos dependendo da face e numero. A quadra possui um cep,coordenadas x e y,
    comprimento e largura.As quadras possuem um estilo, que e utilizado para a impressao delas no arquivo .svg.O estilo guarda as
    informacoes de sw, fill e strk.

    O cep possui uma quantidade maxima de caracteres, sendo ela 48. O sw possui uma quantidade maxima de caracteres de 8, e o fill e strk
    uma quantidade maxima de 32 caracteres.

    Para criar uma quadra, utiliza-se a funcao criar_quadra(), que aloca memoria para uma nova quadra. Para criar essa quadra, e
    necessario informar o cep, coordenadas x e y, largura e comprimento. Para criar um estilo, utiliza-se a funcao criar_estilo(). Que
    aloca memoria para um novo estilo de texto. Para realizar essa criacao, e necessario informar o sw, fill e strk.

    Para cada um desses objetos descritos, existem funcoes getter e setters para obter e modificar suas informacoes. Alem dessas
    funcoes, existem funcoes para calcular as coordenadas X e Y de um determinado endereco, utilizando o cep, face e numero da quadra
    para realizar o calculo.

    Finalmente, para remover uma quadra, utiliza-se a funcao liberar_quadra(), que, como o nome sugere, libera a memoria de uma quadra.
    Para liberar a memoria do estilo das quadras, utiliza-se a funcao removerEstilo().
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

/// @brief Calcula a coordenada x de um endereco a partir da sua quadra, face e numero
/// @param q A quadra
/// @param face A face
/// @param num O numero
/// @return Retrona o valor da coordenada x do endereco
double calculaXEndereco(Quadra q, char face, int num);

/// @brief Calcula a coordenada y de um endereco a partir da sua quadra, face e endereco
/// @param q A quadra
/// @param face A face
/// @param num O numero
/// @return Retorna o valor da coordenada y do endereco
double calculaYEndereco(Quadra q, char face, int num);

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