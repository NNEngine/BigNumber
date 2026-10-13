#include "./includes/BigNumber.h"
#include "./includes/utilities.h"
#include "./includes/Arithmetic.h"
#include "./includes/Comparison.h"

int main(){
    struct BigNumber *num1 = Number("7879639530");
    struct BigNumber *num2 = Number("7879639530");

    struct BigNumber *result1 = Add(num1, num2);
    print_number(result1);

    struct BigNumber *result2 = Sub(num1, num2);
    print_number(result2);

    struct BigNumber *result3 = Mul(num1, num2);
    print_number(result3);

    struct BigNumber *result4 = Div(num1, num2);
    print_number(result4);

    struct BigNumber *result5 = Mod(num1, num2);
    print_number(result5);

    printf("%d\n", lt(num1, num2));
    printf("%d\n", lte(num1, num2));
    printf("%d\n", gt(num1, num2));
    printf("%d\n", gte(num1, num2));
    printf("%d\n", et(num1, num2));
    printf("%d\n", net(num1, num2));

    return 0;
}
