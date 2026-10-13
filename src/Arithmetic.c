#include "../includes/BigNumber.h"
#include "../includes/utilities.h"
#include "../includes/Arithmetic.h"

struct BigNumber *Add(struct BigNumber *Number1,struct BigNumber *Number2){
    if(Number1 ==NULL || Number2 == NULL ||
       !is_valid_number(Number1->number) ||
       !is_valid_number(Number2->number)){
        errno = EDOM;
        fprintf(stderr,
                "Add: Number is not Valid (%s)\n",
                strerror(errno));
        return NULL;
    }

    int len1 = strlen(Number1->number);
    int len2 = strlen(Number2->number);

    int max_len = max(len1, len2);
    char *result = (char *)malloc((max_len+2)*sizeof(char));
    if(result==NULL){
        errno = ENOMEM;
        fprintf(stderr,
                "Add: failed to allocate memory (%s\n)",
                strerror(errno));
        return NULL;
    }
    int k = 0;
    int carry = 0;
    int i = len1-1;
    int j = len2-1;
    while(i>=0||j>=0||carry){
        int sum = carry;
        if(i>=0)sum+=(Number1->number[i--]-'0');
        if(j>=0)sum+=(Number2->number[j--]-'0');
        result[k++] = sum%10 + '0';
        carry = sum/10;
    }
    result[k]='\0';
    
    for(int l=0, r=k-1;l<r;l++,r--){
        char t=result[l];
        result[l]=result[r];
        result[r]=t;
    }
    
    struct BigNumber *add_result = Number(result);
    if(add_result == NULL) free(result);
    return add_result;
}

struct BigNumber *Sub(struct BigNumber *Number1,struct BigNumber *Number2){
    if(Number1 == NULL || Number2 == NULL ||
       !is_valid_number(Number1->number) ||
       !is_valid_number(Number2->number)){
        errno = EDOM;
        fprintf(stderr,
            "Sub: Number is not valid (%s)\n",
            strerror(errno));
        return NULL;
    }

    int len1=strlen(Number1->number);
    int len2=strlen(Number2->number);
    int cmp=0;

    if(len1!=len2)cmp=(len1>len2)?1:-1;
    else{
        cmp=strcmp(Number1->number,Number2->number);
        cmp=(cmp>0)?1:(cmp<0)?-1:0;
    }

    if(cmp==0) return Number("0");

    struct BigNumber *A=(cmp>0)?Number1:Number2;
    struct BigNumber *B=(cmp>0)?Number2:Number1;
    int length=max(len1,len2);
    char *result=malloc((length+2)*sizeof(char));

    if(result==NULL){
        errno=ENOMEM;
        fprintf(stderr,
            "Sub: failed to allocate memory (%s)\n",
            strerror(errno));
        return NULL;
    }

    int i=strlen(A->number)-1;
    int j=strlen(B->number)-1;
    int k=0,borrow=0;

    while(i>=0){
        int digit=A->number[i--]-'0'-borrow;
        if(j>=0)digit-=B->number[j--]-'0';
        if(digit<0){
            digit+=10;
            borrow=1;
        }else borrow=0;
        result[k++]=digit+'0';
    }

    while(k>1&&result[k-1]=='0')k--;
    if(cmp<0)result[k++]='-';
    result[k]='\0';

    for(int l=0,r=k-1;l<r;l++,r--){
        char t=result[l];
        result[l]=result[r];
        result[r]=t;
    }

    struct BigNumber *sub_result=Number(result);
    
    if(sub_result==NULL)free(result);
    return sub_result;
}

struct BigNumber *Mul(struct BigNumber *Number1,struct BigNumber *Number2){
    if(Number1==NULL||Number2==NULL||
       !is_valid_number(Number1->number)||
       !is_valid_number(Number2->number)){
        errno=EDOM;
        fprintf(stderr,
                "Mul: Number is not valid (%s)\n",
                strerror(errno));
        return NULL;
    }

    char *a=Number1->number;
    char *b=Number2->number;
    int neg=(a[0]=='-')^(b[0]=='-');
    int i=(a[0]=='-'||a[0]=='+')?1:0;
    int j=(b[0]=='-'||b[0]=='+')?1:0;
    a+=i;
    b+=j;

    int len1=strlen(a),len2=strlen(b);
    if((len1==1&&a[0]=='0')||(len2==1&&b[0]=='0'))return Number("0");

    int length=len1+len2;
    int *digits=calloc(length,sizeof(int));
    if(digits==NULL){
        errno=ENOMEM;
        fprintf(stderr,
            "Mul: failed to allocate memory (%s)\n",
            strerror(errno));
        return NULL;
    }

    for(i=len1-1;i>=0;i--){
        for(j=len2-1;j>=0;j--){
            int p=(a[i]-'0')*(b[j]-'0')+digits[i+j+1];
            digits[i+j+1]=p%10;
            digits[i+j]+=p/10;
        }
    }

    char *result=malloc(length+2);
    if(result==NULL){
        free(digits);
        errno=ENOMEM;
        fprintf(stderr,
            "Mul: failed to allocate memory (%s)\n",
            strerror(errno));
        return NULL;
    }

    i=0;
    while(i<length-1&&digits[i]==0)i++;
    int k=0;
    if(neg)result[k++]='-';
    for(;i<length;i++)result[k++]=digits[i]+'0';
    result[k]='\0';

    free(digits);
    struct BigNumber *mul_result=Number(result);
    if(mul_result==NULL)free(result);
    return mul_result;
}


struct BigNumber *Div(struct BigNumber *Number1,struct BigNumber *Number2){
    if(Number1==NULL||Number2==NULL||
       !is_valid_number(Number1->number)||
       !is_valid_number(Number2->number)){
        errno=EDOM;
        fprintf(stderr,
            "Div: Number is not valid (%s)\n",
            strerror(errno));
        return NULL;
    }

    char *a=Number1->number;
    char *b=Number2->number;
    int neg=(a[0]=='-')^(b[0]=='-');
    if(a[0]=='-'||a[0]=='+')a++;
    if(b[0]=='-'||b[0]=='+')b++;

    int len1=strlen(a),len2=strlen(b);
    if(len2==1&&b[0]=='0'){
        errno=EDOM;
        fprintf(stderr,"Div: division by zero (%s)\n",strerror(errno));
        return NULL;
    }

    char *result=malloc(len1+2);
    char *rem=malloc(len2+2);
    if(result==NULL||rem==NULL){
        free(result);
        free(rem);
        errno=ENOMEM;
        fprintf(stderr,"Div: failed to allocate memory (%s)\n",strerror(errno));
        return NULL;
    }

    int rlen=0,k=0;
    rem[0]='\0';

    for(int i=0;i<len1;i++){
        rem[rlen++]=a[i];
        rem[rlen]='\0';

        int start=0;
        while(start<rlen-1&&rem[start]=='0')start++;
        if(start){
            memmove(rem,rem+start,rlen-start+1);
            rlen-=start;
        }

        int q=0;
        while(rlen>len2||(rlen==len2&&strcmp(rem,b)>=0)){
            int borrow=0;
            for(int j=rlen-1;j>=0;j--){
                int d=rem[j]-'0'-borrow;
                int bd=(j>=rlen-len2)?b[j-(rlen-len2)]-'0':0;
                d-=bd;
                if(d<0){
                    d+=10;
                    borrow=1;
                }else borrow=0;
                rem[j]=d+'0';
            }
            start=0;
            while(start<rlen-1&&rem[start]=='0')start++;
            if(start){
                memmove(rem,rem+start,rlen-start+1);
                rlen-=start;
            }
            q++;
        }
        result[k++]=q+'0';
    }

    int start=0;
    while(start<k-1&&result[start]=='0')start++;
    if(neg){
        int zero=1;
        for(int i=start;i<k;i++)if(result[i]!='0'){zero=0;break;}
        if(!zero){
            memmove(result+1,result+start,k-start);
            result[0]='-';
            k=k-start+1;
        }else{
            memmove(result,result+start,k-start);
            k=k-start;
        }
    }else{
        memmove(result,result+start,k-start);
        k=k-start;
    }
    result[k]='\0';

    struct BigNumber *div_result=Number(result);
    if(div_result == NULL)free(result);
    free(rem);
    return div_result;
}

struct BigNumber *Mod(struct BigNumber *Number1,struct BigNumber *Number2){
    if(Number1==NULL||Number2==NULL||
       !is_valid_number(Number1->number)||
       !is_valid_number(Number2->number)){
        errno=EDOM;
        fprintf(stderr,
            "Mod: Number is not valid (%s)\n",
            strerror(errno));
        return NULL;
    }

    char *a=Number1->number;
    char *b=Number2->number;
    int neg=a[0]=='-';
    if(a[0]=='-'||a[0]=='+')a++;
    if(b[0]=='-'||b[0]=='+')b++;

    int len1=strlen(a),len2=strlen(b);
    if(len2==1&&b[0]=='0'){
        errno=EDOM;
        fprintf(stderr,
            "Mod: division by zero (%s)\n",    
            strerror(errno));
        return NULL;
    }

    char *rem=malloc(len1+2);
    if(rem==NULL){
        errno=ENOMEM;
        fprintf(stderr,
            "Mod: failed to allocate memory (%s)\n",
            strerror(errno));
        return NULL;
    }

    int rlen=0;
    rem[0]='\0';

    for(int i=0;i<len1;i++){
        rem[rlen++]=a[i];
        rem[rlen]='\0';

        int start=0;
        while(start<rlen-1&&rem[start]=='0')start++;
        if(start){
            memmove(rem,rem+start,rlen-start+1);
            rlen-=start;
        }

        while(rlen>len2||(rlen==len2&&strcmp(rem,b)>=0)){
            int borrow=0;
            for(int j=rlen-1;j>=0;j--){
                int d=rem[j]-'0'-borrow;
                int bj=j-(rlen-len2);
                if(bj>=0)d-=b[bj]-'0';
                if(d<0){
                    d+=10;
                    borrow=1;
                }else borrow=0;
                rem[j]=d+'0';
            }

            start=0;
            while(start<rlen-1&&rem[start]=='0')start++;
            if(start){
                memmove(rem,rem+start,rlen-start+1);
                rlen-=start;
            }
        }
    }

    int zero=(rlen==1&&rem[0]=='0');
    char *result=malloc(rlen+2);
    if(result==NULL){
        free(rem);
        errno=ENOMEM;
        fprintf(stderr,
            "Mod: failed to allocate memory (%s)\n",
            strerror(errno));
        return NULL;
    }

    int k=0;
    if(neg&&!zero)result[k++]='-';
    memcpy(result+k,rem,rlen);
    result[k+rlen]='\0';

    struct BigNumber *mod_result=Number(result);
    if(mod_result==NULL)free(result);
    free(rem);
    return mod_result;
}
