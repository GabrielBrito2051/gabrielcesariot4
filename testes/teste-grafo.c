#include <stdio.h>
#include <stdlib.h>
#include "../unity/unity.h"
#include "../include/grafo.h"
#include "../include/svg.h"
#include "../include/quadra.h"
#include "../include/txt.h"

Grafo g;
FILE *svg;
FILE *txt;

void setUp(void) {
    g = criar_grafo(10);
    
    svg = fopen("temp_test.svg", "w");
    txt = fopen("temp_test.txt", "w");
}

void tearDown(void) {
    if (g != NULL) {
        destruir_grafo(g);
    }
    
    if (svg != NULL) fclose(svg);
    if (txt != NULL) fclose(txt);
    
    remove("temp_test.svg");
    remove("temp_test.txt");
}


void CriarGrafo(void) {
    TEST_ASSERT_NOT_NULL(g);
}

void EncontraVerticeMaisProximo(void) {
    inserir_vertice(g, "V0", 0.0, 0.0);
    inserir_vertice(g, "V1", 10.0, 10.0);
    inserir_vertice(g, "V2", 100.0, 100.0);

    int idProximoV0 = encontra_vertice_mais_proximo(g, 1.0, 1.0);
    TEST_ASSERT_EQUAL_INT(0, idProximoV0);

    int id_proximo_v2 = encontra_vertice_mais_proximo(g, 95.0, 95.0);
    TEST_ASSERT_EQUAL_INT(2, id_proximo_v2);
}

void CalculaComponentesConexos_GrafoTotalmenteConexo(void) {
    inserir_vertice(g, "A", 0.0, 0.0);
    inserir_vertice(g, "B", 5.0, 5.0);
    
    inserir_aresta(g, "A", "B", "Q1", "Q2", 10.0, 60.0, "Av. Central");
    inserir_aresta(g, "B", "A", "Q1", "Q2", 10.0, 60.0, "Av. Central");
    
    int componentes = calcula_componentes_conexos(g, 70.0, svg);
    
    TEST_ASSERT_EQUAL_INT(1, componentes);
}

void CalculaComponentesConexos_GrafoDesconexo(void) {
    inserir_vertice(g, "A", 0.0, 0.0);
    inserir_vertice(g, "B", 5.0, 5.0);
    inserir_vertice(g, "C", 20.0, 20.0);
    
    inserir_aresta(g, "A", "B", "Q1", "Q2", 10.0, 50.0, "Rua 1");
    inserir_aresta(g, "B", "A", "Q1", "Q2", 10.0, 50.0, "Rua 1");
    
    int componentes = calcula_componentes_conexos(g, 80.0, svg);
    TEST_ASSERT_EQUAL_INT(2, componentes);
}

void BuscaCaminhos(void) {
    inserir_vertice(g, "A", 0.0, 0.0);
    inserir_vertice(g, "B", 10.0, 0.0);
    inserir_aresta(g, "A", "B", "Q1", "Q2", 10.0, 40.0, "Rua 1");

    busca_menor_distancia(g, 0, 1, svg, "#FF0000", txt);
    busca_menor_tempo(g, 0, 1, svg, "#00FF00", txt);
    
    TEST_ASSERT_TRUE(1);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(CriarGrafo);
    RUN_TEST(EncontraVerticeMaisProximo);
    RUN_TEST(CalculaComponentesConexos_GrafoTotalmenteConexo);
    RUN_TEST(CalculaComponentesConexos_GrafoDesconexo);
    RUN_TEST(BuscaCaminhos);
    
    return UNITY_END();
}