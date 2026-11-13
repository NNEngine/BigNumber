#include "../../includes/Arithmetic.h"
#include "../../includes/utilities.h"

const unsigned int total_tests = 3;
static unsigned int test_counter = 0;

void TEST_NOT_NULL(struct BigNumber *number){
    assert(number!=NULL);
    ++test_counter;
    printf("PASSED: TEST_NOT_NULL\n");
}

void TEST_EQUAL_LENGTH(struct BigNumber *number, int len){
    assert(number!=NULL);
    assert(number->length==len);
    ++test_counter;
    printf("PASSED: TEST_EQUAL_LENGTH\n");
}

void TEST_EQUAL_NUMBER(struct BigNumber *number, const char *num){
    assert(number!=NULL);
    assert(strcmp(number->number,num)==0);
    ++test_counter;
    printf("PASSED: TEST_EQUAL_NUMBER\n");
}

int main(){
    struct BigNumber *num=Number("123456789");

    TEST_NOT_NULL(num);
    TEST_EQUAL_LENGTH(num,9);
    TEST_EQUAL_NUMBER(num,"123456789");

    printf("\nTOTAL TEST CASES PASSED : %u/%u\n", test_counter, total_tests);

    FreeNumber(num);
    return 0;
}
