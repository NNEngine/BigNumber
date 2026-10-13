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
*/

static void mul_small(char *s,int m){
    int len=strlen(s),carry=0;
    for(int i=len-1;i>=0;i--){
        int v=(s[i]-'0')*m+carry;
        s[i]=v%10+'0';
        carry=v/10;
    }
    if(carry){
        memmove(s+1,s,len+1);
        s[0]=carry+'0';
    }
}

static void add_small(char *s,int n){
    int i=strlen(s)-1;
    while(n&&i>=0){
        int v=s[i]-'0'+n;
        s[i--]=v%10+'0';
        n=v/10;
    }
    while(n){
        int len=strlen(s);
        memmove(s+1,s,len+1);
        s[0]=n%10+'0';
        n/=10;
    }
}

static int cmp_num(char *a,char *b){
    int la=strlen(a),lb=strlen(b);
    if(la!=lb)return la>lb?1:-1;
    int c=strcmp(a,b);
    return c>0?1:c<0?-1:0;
}

static void sub_num(char *a,char *b){
    int i=strlen(a)-1,j=strlen(b)-1,borrow=0;
    while(i>=0){
        int v=a[i]-'0'-borrow;
        if(j>=0)v-=b[j--]-'0';
        if(v<0)v+=10,borrow=1;
        else borrow=0;
        a[i--]=v+'0';
    }
    int start=0,len=strlen(a);
    while(start<len-1&&a[start]=='0')start++;
    if(start)memmove(a,a+start,len-start+1);
}


struct BigNumber *Sqrt(struct BigNumber *number){
    if(number==NULL||!is_valid_number(number->number)){
        errno=EDOM;
        fprintf(stderr,"Sqrt: Number is not valid (%s)\n",strerror(errno));
        return NULL;
    }

    char *s=number->number;
    if(s[0]=='-'){
        errno=EDOM;
        fprintf(stderr,"Sqrt: Negative input is not supported\n");
        return NULL;
    }
    if(s[0]=='+')s++;

    int len=strlen(s);
    int pairs=(len+1)/2;
    char *root=calloc(pairs+2,1);
    char *rem=calloc(len+3,1);
    char *trial=calloc(len+5,1);
    char *product=calloc(len+5,1);

    if(!root||!rem||!trial||!product){
        free(root);
        free(rem);
        free(trial);
        free(product);
        errno=ENOMEM;
        fprintf(stderr,"Sqrt: Memory allocation failed (%s)\n",strerror(errno));
        return NULL;
    }

    strcpy(root,"0");
    strcpy(rem,"0");
    int pos=0;

    for(int p=0;p<pairs;p++){
        int group;
        if(len%2&&p==0)group=s[pos++]-'0';
        else group=(s[pos]-'0')*10+s[pos+1]-'0';

        int rlen=strlen(rem);
        if(rlen==1&&rem[0]=='0')rem[0]='\0';
        rlen=strlen(rem);
        rem[rlen++]=group/10+'0';
        rem[rlen++]=group%10+'0';
        rem[rlen]='\0';

        int start=0;
        while(rem[start]=='0'&&rem[start+1])start++;
        if(start)memmove(rem,rem+start,strlen(rem+start)+1);

        int digit;
        for(digit=9;digit>=0;digit--){
            strcpy(trial,root);
            mul_small(trial,20);
            add_small(trial,digit);
            strcpy(product,trial);
            mul_small(product,digit);
            if(cmp_num(product,rem)<=0)break;
        }

        sub_num(rem,product);
        mul_small(root,10);
        add_small(root,digit);
    }

    struct BigNumber *result=Number(root);

    if(result == NULL)free(root);
    free(rem);
    free(trial);
    free(product);

    return result;
}
