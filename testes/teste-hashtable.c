#include "../unity/unity.h"
#include "../include/hashtable.h"

Hashtable ht;

void setUp(void) {
    ht = criar_hashtable(10);
}

void tearDown(void) {
    if (ht != NULL) {
        destruir_hashtable(ht);
    }
}

void CriarHashtable(void) {
    TEST_ASSERT_NOT_NULL(ht);
}

void BuscarHashtable_ChaveInexistente(void) {
    int resultado = buscar_hashtable(ht, "chave_inexistente");
    
    TEST_ASSERT_EQUAL_INT(-1, resultado);
}

void InserirEBuscar(void) {
    inserir_hashtable(ht, "alexandre", 1001);
    inserir_hashtable(ht, "leticia", 2002);
    inserir_hashtable(ht, "diego", 3003);
    
    TEST_ASSERT_EQUAL_INT(1001, buscar_hashtable(ht, "alexandre"));
    TEST_ASSERT_EQUAL_INT(2002, buscar_hashtable(ht, "leticia"));
    TEST_ASSERT_EQUAL_INT(3003, buscar_hashtable(ht, "diego"));
}

void InserirChaveExistente(void) {
    inserir_hashtable(ht, "config_id", 42);
    TEST_ASSERT_EQUAL_INT(42, buscar_hashtable(ht, "config_id"));
    
    inserir_hashtable(ht, "config_id", 99);
    
    TEST_ASSERT_EQUAL_INT(99, buscar_hashtable(ht, "config_id"));
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(CriarHashtable);
    RUN_TEST(BuscarHashtable_ChaveInexistente);
    RUN_TEST(InserirEBuscar);
    RUN_TEST(InserirChaveExistente);
    
    return UNITY_END();
}