#include "../unity/unity.h"
#include "../include/fila-prioridade.h"

Fila fila;

void setUp(void) {
    fila = criar_fila(10);
}

void tearDown(void) {
    if (fila != NULL) {
        destruir_fila(fila);
    }
}

void CriarFilaVazia(void) {
    TEST_ASSERT_NOT_NULL(fila);
    
    TEST_ASSERT_EQUAL_INT(1, fila_vazia(fila));
}

void InserirFila(void) {
    inserir_fila(fila, 1, 5.0);
    
    TEST_ASSERT_EQUAL_INT(0, fila_vazia(fila));
}

void RemoveMinimo(void) {
    inserir_fila(fila, 42, 10.5);
    
    int id_removido = remove_minimo(fila);
    
    TEST_ASSERT_EQUAL_INT(42, id_removido);
    TEST_ASSERT_EQUAL_INT(1, fila_vazia(fila));
}

void RemoveMinimoRespeitandoPrioridade(void) {
    inserir_fila(fila, 1, 50.0);
    inserir_fila(fila, 2, 10.0);
    inserir_fila(fila, 3, 25.0);
    
    TEST_ASSERT_EQUAL_INT(2, remove_minimo(fila));
    
    TEST_ASSERT_EQUAL_INT(3, remove_minimo(fila));
    
    TEST_ASSERT_EQUAL_INT(1, remove_minimo(fila));
    
    TEST_ASSERT_EQUAL_INT(1, fila_vazia(fila));
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(CriarFilaVazia);
    RUN_TEST(InserirFila);
    RUN_TEST(RemoveMinimo);
    RUN_TEST(RemoveMinimoRespeitandoPrioridade);
    
    return UNITY_END();
}