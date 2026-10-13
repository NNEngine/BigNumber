#include "./includes/BigNumber.h"
#include "./includes/utilities.h"
#include "./includes/Arithmetic.h"

int main(){
    struct BigNumber *num1 = Number("123456789283747892848774293384743938384776789912393842113443");
    struct BigNumber *num2 = Number("9384743722910973923928374382837848009384847392837474912938");

    struct BigNumber *result1 = Add(num1, num2);
    print_number(result1);

    struct BigNumber *result2 = Sub(num1, num2);
    print_number(result2);

    struct BigNumber *result3 = Mul(num1, num2);
    print_number(result3);

    struct BigNumber *result4 = Div(num1, num2);
    print_number(result4);

    return 0;
}
