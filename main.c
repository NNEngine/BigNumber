#include "./includes/BigNumber.h"
#include "./includes/utilities.h"
#include "./includes/Arithmetic.h"
#include "./includes/Comparison.h"
#include "./includes/Unary.h"

int main(){
    struct BigNumber *num1 = Number("787963282478248273826486483683643435952784727327834836483630");
    struct BigNumber *num2 = Number("78796313264823286487391738648274917483683624648368249114649530");

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

    struct BigNumber *num3 = Number("8372938463291364292836");
    print_number(Abs(num3));
    print_number(Negate(num3));
    printf("%d\n",Sign(num3));

    print_number(Inc(num3));
    print_number(Dec(num3));

    print_number(Sqrt(num3));

    return 0;
}
