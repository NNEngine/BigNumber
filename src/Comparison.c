#include "../includes/Comparison.h"
#include "../includes/utilities.h"

bool lt(struct BigNumber *number1,struct BigNumber *number2){
    if(number1==NULL||number2==NULL||
       !is_valid_number(number1->number)||
       !is_valid_number(number2->number)){
        errno=EDOM;
        fprintf(stderr,
            "lt: Number is not valid (%s)\n",
            strerror(errno));
        return false;
    }

    char *a=number1->number;
    char *b=number2->number;
    int neg1=(*a=='-'),neg2=(*b=='-');

    if(*a=='-'||*a=='+')a++;
    if(*b=='-'||*b=='+')b++;

    if(neg1!=neg2)return neg1;

    int len1=strlen(a),len2=strlen(b);
    int cmp;

    if(len1!=len2)cmp=(len1>len2)?1:-1;
    else{
        cmp=strcmp(a,b);
        cmp=(cmp>0)?1:(cmp<0)?-1:0;
    }

    return neg1?cmp>0:cmp<0;
}

bool lte(struct BigNumber *number1,struct BigNumber *number2){
    if(number1==NULL||number2==NULL||
       !is_valid_number(number1->number)||
       !is_valid_number(number2->number)){
        errno=EDOM;
        fprintf(stderr,
            "lte: Number is not valid (%s)\n",
            strerror(errno));
        return false;
    }

    char *a=number1->number;
    char *b=number2->number;
    int neg1=(*a=='-'),neg2=(*b=='-');

    if(*a=='-'||*a=='+')a++;
    if(*b=='-'||*b=='+')b++;

    if(neg1!=neg2)return neg1;

    int len1=strlen(a),len2=strlen(b);
    int cmp;

    if(len1!=len2)cmp=(len1>len2)?1:-1;
    else{
        cmp=strcmp(a,b);
        cmp=(cmp>0)?1:(cmp<0)?-1:0;
    }

    return neg1?cmp>=0:cmp<=0;
}

bool gt(struct BigNumber *number1,struct BigNumber *number2){
    if(number1==NULL||number2==NULL||
       !is_valid_number(number1->number)||
       !is_valid_number(number2->number)){
        errno=EDOM;
        fprintf(stderr,
            "gt: Number is not valid (%s)\n",
            strerror(errno));
        return false;
    }

    char *a=number1->number;
    char *b=number2->number;
    int neg1=(*a=='-'),neg2=(*b=='-');

    if(*a=='-'||*a=='+')a++;
    if(*b=='-'||*b=='+')b++;

    if(neg1!=neg2)return !neg1;

    int len1=strlen(a),len2=strlen(b);
    int cmp;

    if(len1!=len2)cmp=(len1>len2)?1:-1;
    else{
        cmp=strcmp(a,b);
        cmp=(cmp>0)?1:(cmp<0)?-1:0;
    }

    return neg1?cmp<0:cmp>0;
}

bool gte(struct BigNumber *number1,struct BigNumber *number2){
    if(number1==NULL||number2==NULL||
       !is_valid_number(number1->number)||
       !is_valid_number(number2->number)){
        errno=EDOM;
        fprintf(stderr,
            "gte: Number is not valid (%s)\n",
            strerror(errno));
        return false;
    }

    char *a=number1->number;
    char *b=number2->number;
    int neg1=(*a=='-'),neg2=(*b=='-');

    if(*a=='-'||*a=='+')a++;
    if(*b=='-'||*b=='+')b++;

    if(neg1!=neg2)return !neg1;

    int len1=strlen(a),len2=strlen(b);
    int cmp;

    if(len1!=len2)cmp=(len1>len2)?1:-1;
    else{
        cmp=strcmp(a,b);
        cmp=(cmp>0)?1:(cmp<0)?-1:0;
    }

    return neg1?cmp<=0:cmp>=0;
}

bool et(struct BigNumber *number1,struct BigNumber *number2){
    if(number1==NULL||number2==NULL||
       !is_valid_number(number1->number)||
       !is_valid_number(number2->number)){
        errno=EDOM;
        fprintf(stderr,
            "et: Number is not valid (%s)\n",
            strerror(errno));
        return false;
    }

    char *a=number1->number;
    char *b=number2->number;

    if(*a=='-'||*a=='+')a++;
    if(*b=='-'||*b=='+')b++;

    if(strcmp(a,b)==0)return true;
    return false;
}

bool net(struct BigNumber *number1,struct BigNumber *number2){
    if(number1==NULL||number2==NULL||
       !is_valid_number(number1->number)||
       !is_valid_number(number2->number)){
        errno=EDOM;
        fprintf(stderr,
            "et: Number is not valid (%s)\n",
            strerror(errno));
        return false;
    }

    char *a=number1->number;
    char *b=number2->number;

    if(*a=='-'||*a=='+')a++;
    if(*b=='-'||*b=='+')b++;

    if(strcmp(a,b)!=0)return true;
    return false;
}
