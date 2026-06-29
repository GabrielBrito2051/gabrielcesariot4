#include <stdio.h>
#include "../include/svg.h"
#include "../include/quadra.h"

void start_svg(FILE* svg, int max_x, int max_y){
    if(max_x == 0 && max_y == 0){
        fprintf(svg, "<svg viewBox=\"0 0 12000 12000\" xmlns=\"http://www.w3.org/2000/svg\">\n");
    }else{
        fprintf(svg, "<svg viewBox=\"0 0 %d %d\" xmlns=\"http://www.w3.org/2000/svg\">\n", max_x + 51, max_y + 51);
    }
}

void insere_quadra_svg(FILE *svg, Quadra q, Estilo e){
    fprintf(svg, "<rect style=\"fill:%s;fill-opacity:0.8;stroke:%s;stroke-opacity:%s\" height=\"%lf\" width=\"%lf\" y=\"%lf\" x=\"%lf\" />\n",getFill(e), getStrk(e), getSw(e), getHQuadra(q), getWQuadra(q), getYQuadra(q), getXQuadra(q));
}

void insere_registrador_svg(FILE* svg, double x, double y, int indice){
    fprintf(svg, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%d\" stroke=\"black\" stroke-width=\"2\" stroke-dasharray=\"5,5\" />\n", x, y, x, 5);
    fprintf(svg, "<text x=\"%lf\" y=\"%d\" font-family=\"Arial\" font-size=\"16\" fill=\"black\">%d</text>\n", x, 5, (indice-1));
}

void insere_bounding_box(FILE* svg, double x, double y, double largura, double altura, char* cor){
    fprintf(svg, "<rect style=\"fill:%s;fill-opacity:0.5;stroke:\"red\";stroke-opacity:0.5\" height=\"%lf\" width=\"%lf\" y=\"%lf\" x=\"%lf\" />\n",cor, altura, largura, y, x);
}

void insere_aresta_svg(FILE* svg, double xi, double yi, double xf, double yf, char* cor){
    fprintf(svg, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"8\" />\n", xi, yi, xf, yf, cor);
}

void fecha_svg(FILE* svg){
    fprintf(svg,"</svg>\n");
}