#include "../includes/utilities.h"
#include "../includes/Arithmetic.h"
#include "../includes/Comparison.h"

bool is_valid_number(char *number){
    if(number==NULL || number[0]=='\0') return false;
    int i=(number[0]=='-'||number[0]=='+') ? 1 : 0;
    if(number[i]=='\0')return false;
    if(number[i]=='0'&&number[i+1]!='\0')return false;
    for(;number[i];i++){
        if(!isdigit((unsigned char)number[i]))return false;
    }
    return true;
}

bool are_equal_in_length(char *Number1, char *Number2){
    if(strlen(Number1) != strlen(Number2)) return false;
    return true;
}

int max(int a, int b){
    return (a>b)?a:b;
}
int min(int a, int b){
    return (a<b)?a:b;
}

void print_number(struct BigNumber *num){
    if(num==NULL) return;
    puts(num->number);
}

struct BigNumber *Inc(struct BigNumber *number){
    if(number==NULL||!is_valid_number(number->number)){
        errno=EDOM;
        fprintf(stderr,"Inc: Number is not valid (%s)\n",strerror(errno));
        return NULL;
    }

    struct BigNumber *one=Number("1");
    if(one==NULL)return NULL;
    struct BigNumber *result=Add(number,one);
    if(result==NULL) free(one);
    return result;
}

struct BigNumber *Dec(struct BigNumber *number){
    if(number==NULL||!is_valid_number(number->number)){
        errno=EDOM;
        fprintf(stderr,"Dec: Number is not valid (%s)\n",strerror(errno));
        return NULL;
    }

    struct BigNumber *one=Number("1");
    if(one==NULL)return NULL;
    struct BigNumber *result=Sub(number,one);
    if(result==NULL) free(one);
    return result;
}

/*
    Function Under Development, Advised not to Use
    
struct BigNumber *Pow(struct BigNumber *Number1,struct BigNumber *Number2){
    if(Number1==NULL||Number2==NULL||
       !is_valid_number(Number1->number)||
       !is_valid_number(Number2->number)){
        errno=EDOM;
        fprintf(stderr,
            "Pow: Number is not valid (%s)\n",
            strerror(errno));
        return NULL;
    }

    if(Number2->number[0]=='-'){
        errno=EDOM;
        fprintf(stderr,
            "Pow: Negative exponent is not supported (%s)\n",
            strerror(errno));
        return NULL;
    }

    struct BigNumber *result=Number("1");
    struct BigNumber *base=Number(Number1->number);
    struct BigNumber *exponent=Number(Number2->number);
    struct BigNumber *two=Number("2");
    struct BigNumber *zero=Number("0");

    if(!result||!base||!exponent||!two||!zero)return NULL;

    while(gt(exponent,zero)){
        struct BigNumber *rem=Mod(exponent,two);
        if(!rem)return NULL;

        if(!et(rem,zero)){
            struct BigNumber *temp=Mul(result,base);
            if(!temp)return NULL;
            result=temp;
        }

        struct BigNumber *temp=Mul(base,base);
        if(!temp)return NULL;
        base=temp;

        temp=Div(exponent,two);
        if(!temp)return NULL;
        exponent=temp;
    }

    return result;
}
/*
