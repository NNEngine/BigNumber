#include "../includes/BigNumber.h"
#include "../includes/utilities.h"
#include "../includes/Unary.h"

struct BigNumber *Abs(struct BigNumber *number){
    if(number==NULL||!is_valid_number(number->number)){
        errno=EDOM;
        fprintf(stderr,
            "Abs: Number is not valid (%s)\n",
            strerror(errno));
        return NULL;
    }
    char *s=number->number;
    if(s[0]!='-')return Number(s);
    return Number(s+1);
}

struct BigNumber *Negate(struct BigNumber *number){
    if(number==NULL||!is_valid_number(number->number)){
        errno=EDOM;
        fprintf(stderr,
            "Negate: Number is not valid (%s)\n",
            strerror(errno));
        return NULL;
    }

    char *s=number->number;
    if(strcmp(s,"0")==0||strcmp(s,"+0")==0||strcmp(s,"-0")==0)return Number("0");

    int len=strlen(s);
    if(s[0]=='-')return Number(s+1);
    if(s[0]=='+')s++,len--;

    char *result=malloc(len+2);
    if(result==NULL){
        errno=ENOMEM;
        fprintf(stderr,
            "Negate: failed to allocate memory (%s)\n",
            strerror(errno));
        return NULL;
    }

    result[0]='-';
    memcpy(result+1,s,len);
    result[len+1]='\0';

    struct BigNumber *r=Number(result);
    if(r==NULL)free(result);
    return r;
}


int Sign(struct BigNumber *number){
    if(number==NULL||!is_valid_number(number->number)){
        errno=EDOM;
        fprintf(stderr,
            "Sign: Number is not valid (%s)\n",
            strerror(errno));
        return 0;
    }
    if(number->number[0]=='-')return -1;
    if(number->number[0]=='+')return number->number[1]=='0'?0:1;
    return number->number[0]=='0'?0:1;
}
