#include "../unity/unity.h"
#include "../include/quadra.h"
#include <stdlib.h>

Quadra q = NULL;
Estilo ts = NULL;

void setUp() {
    q = criar_quadra("86050-000", 10.5, 20.5, 100.0, 50.0);
    ts = criar_estilo("2.0", "red", "black");
}

void tearDown() {
    if (q != NULL) {
        liberar_quadra(q);
        q = NULL;
    }
    
    if (ts != NULL) {
        removerEstilo(ts);
        ts = NULL;
    }
}

void test_criar_quadra() {
    TEST_ASSERT_NOT_NULL(q);
}

void test_getters_quadra() {
    TEST_ASSERT_EQUAL_STRING("86050-000", getCepQuadra(q));
    
    TEST_ASSERT_EQUAL_DOUBLE(10.5, getXQuadra(q));
    TEST_ASSERT_EQUAL_DOUBLE(20.5, getYQuadra(q));
    TEST_ASSERT_EQUAL_DOUBLE(100.0, getWQuadra(q));
    TEST_ASSERT_EQUAL_DOUBLE(50.0, getHQuadra(q));
}

void test_criar_estilo() {
    TEST_ASSERT_NOT_NULL(ts);
}

void test_getters_estilo() {
    TEST_ASSERT_EQUAL_STRING("2.0", getSw(ts));
    TEST_ASSERT_EQUAL_STRING("red", getFill(ts));
    TEST_ASSERT_EQUAL_STRING("black", getStrk(ts));
}

void test_setters_estilo() {
    setSw(ts, "5.5");
    setFill(ts, "blue");
    setStrk(ts, "white");

    TEST_ASSERT_EQUAL_STRING("5.5", getSw(ts));
    TEST_ASSERT_EQUAL_STRING("blue", getFill(ts));
    TEST_ASSERT_EQUAL_STRING("white", getStrk(ts));
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_criar_quadra);
    RUN_TEST(test_getters_quadra);

    RUN_TEST(test_criar_estilo);
    RUN_TEST(test_getters_estilo);
    RUN_TEST(test_setters_estilo);

    return UNITY_END();
}