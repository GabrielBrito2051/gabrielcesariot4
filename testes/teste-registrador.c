#include "../unity/unity.h"
#include "../include/registrador.h"

Registrador reg;

void setUp(void) {
    reg = criar_registrador("12345-678", 'N', 42, -23.55, -46.63);
}

void tearDown(void) {
    if (reg != NULL) {
        destruir_registrador(reg);
    }
}

void CriarRegistrador(void) {
    TEST_ASSERT_NOT_NULL(reg);
    
    TEST_ASSERT_EQUAL_STRING("12345-678", getCepRegistrador(reg));
    
    TEST_ASSERT_EQUAL_CHAR('N', getFaceRegistrador(reg));
    
    TEST_ASSERT_EQUAL_INT(42, getNumRegistrador(reg));
    
    TEST_ASSERT_EQUAL_DOUBLE(-23.55, getXRegistrador(reg));
    TEST_ASSERT_EQUAL_DOUBLE(-46.63, getYRegistrador(reg));
}

void TesteSetters(void) {
    setCepRegistrador(reg, "98765-432");
    setFaceRegistrador(reg, 'S');
    setNumRegistrador(reg, 999);
    setXRegistrador(reg, 12.34);
    setYRegistrador(reg, 56.78);

    TEST_ASSERT_EQUAL_STRING("98765-432", getCepRegistrador(reg));
    TEST_ASSERT_EQUAL_CHAR('S', getFaceRegistrador(reg));
    TEST_ASSERT_EQUAL_INT(999, getNumRegistrador(reg));
    TEST_ASSERT_EQUAL_DOUBLE(12.34, getXRegistrador(reg));
    TEST_ASSERT_EQUAL_DOUBLE(56.78, getYRegistrador(reg));
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(CriarRegistrador);
    RUN_TEST(TesteSetters);
    
    return UNITY_END();
}