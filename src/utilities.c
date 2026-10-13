#include "../includes/utilities.h"
#include "../includes/Arithmetic.h"

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
