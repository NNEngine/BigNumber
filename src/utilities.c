#include "../includes/utilities.h"

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
