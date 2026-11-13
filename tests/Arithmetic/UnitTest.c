#include "../../includes/Arithmetic.h"
#include "../../includes/utilities.h"


int main(){
    struct BigNumber *num = Number("123456789");

    assert(num!=NULL);
    assert(num->length==9);
    assert(strcmp(num->number, "123456789")==0);
    printf("All TEST CASES PASSED\n");
    
    FreeNumber(num);
    
    return 0;
}
