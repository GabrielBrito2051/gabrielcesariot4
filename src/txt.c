#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/txt.h"

void print_coordenadas_registrador(FILE* txt, double x, double y, int indice){
    fprintf(txt, "Coordenada (%lf,%lf) salva no registrador R%d\n", x, y, (indice+1));
}

void print_numero_componentes(FILE* txt, int numero){
    fprintf(txt,"A quantidade de componentes conexos e de %d\n", numero);
}

void print_direcao(FILE* txt, char* sentido, char* rua){
    fprintf(txt,"Vire a %s na rua %s", sentido, rua);
}