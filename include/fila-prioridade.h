#ifndef filaprioridade_h
#define filaprioridade_h

typedef void* Fila;

/*

*/


Fila criar_fila(int numVertices);


int fila_vazia(Fila f);


void inserir_fila(Fila f, int idVertice, double prioridade);


int remove_minimo(Fila f);


void destruir_fila(Fila f);

#endif