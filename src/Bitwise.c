#include "../includes/BigNumber.h"
#include "../includes/utilities.h"
#include "../includes/Bitwise.h"

static char *magnitude(const char *s){
    if(*s=='-'||*s=='+')s++;
    return (char *)s;
}

static int negative(const char *s){
    return s[0]=='-';
}

static int *to_bits(const char *s,int *len){
    char *d=strdup(magnitude(s));
    if(!d)return NULL;
    int n=strlen(d);
    int cap=n*4+2;
    int *bits=malloc(cap*sizeof(int));
    if(!bits){
        free(d);
        return NULL;
    }
    int k=0;
    while(!(n==1&&d[0]=='0')){
        int rem=0;
        for(int i=0;i<n;i++){
            int v=rem*10+d[i]-'0';
            d[i]=v/2+'0';
            rem=v%2;
        }
        bits[k++]=rem;
        int start=0;
        while(start<n-1&&d[start]=='0')start++;
        if(start){
            memmove(d,d+start,n-start);
            n-=start;
            d[n]='\0';
        }
    }
    if(k==0)bits[k++]=0;
    free(d);
    *len=k;
    return bits;
}

static int *to_twos(const char *s,int width){
    int len;
    int *b=to_bits(s,&len);
    if(!b)return NULL;
    int *r=calloc(width,sizeof(int));
    if(!r){
        free(b);
        return NULL;
    }
    for(int i=0;i<len&&i<width;i++)r[i]=b[i];
    if(negative(s)){
        for(int i=0;i<width;i++)r[i]^=1;
        for(int i=0;i<width;i++){
            r[i]^=0;
            if(r[i]){r[i]=0;continue;}
            r[i]=1;
            break;
        }
    }
    free(b);
    return r;
}

static char *from_twos(int *bits,int width){
    int neg=bits[width-1];
    if(neg){
        for(int i=0;i<width;i++)bits[i]^=1;
        for(int i=0;i<width;i++){
            if(bits[i]){
                bits[i]=0;
                continue;
            }
            bits[i]=1;
            break;
        }
    }
    int cap=width/3+4;
    char *d=calloc(cap,1);
    if(!d)return NULL;
    d[0]='0';
    int n=1;
    for(int i=width-1;i>=0;i--){
        int carry=bits[i];
        for(int j=n-1;j>=0;j--){
            int v=(d[j]-'0')*2+carry;
            d[j]=v%10+'0';
            carry=v/10;
        }
        if(carry){
            memmove(d+1,d,n);
            d[0]=carry+'0';
            n++;
        }
    }
    int start=0;
    while(start<n-1&&d[start]=='0')start++;
    if(start){
        memmove(d,d+start,n-start);
        n-=start;
    }
    d[n]='\0';
    char *r=malloc(n+(neg?2:1));
    if(!r){
        free(d);
        return NULL;
    }
    int k=0;
    if(neg&&!(n==1&&d[0]=='0'))r[k++]='-';
    memcpy(r+k,d,n+1);
    free(d);
    return r;
}

static struct BigNumber *bitwise(struct BigNumber *a,struct BigNumber *b,int op){
    if(!a||!b||!is_valid_number(a->number)||!is_valid_number(b->number)){
        errno=EDOM;
        fprintf(stderr,"bitwise: invalid number (%s)\n",strerror(errno));
        return NULL;
    }
    int la,lb;
    int *ba=to_bits(a->number,&la),*bb=to_bits(b->number,&lb);
    if(!ba||!bb){
        free(ba);
        free(bb);
        errno=ENOMEM;
        return NULL;
    }
    int width=(la>lb?la:lb)+2;
    free(ba);
    free(bb);
    ba=to_twos(a->number,width);
    bb=to_twos(b->number,width);
    int *r=malloc(width*sizeof(int));
    if(!ba||!bb||!r){
        free(ba);
        free(bb);
        free(r);
        errno=ENOMEM;
        return NULL;
    }
    for(int i=0;i<width;i++){
        if(op==0)r[i]=ba[i]&bb[i];
        else if(op==1)r[i]=ba[i]|bb[i];
        else r[i]=ba[i]^bb[i];
    }
    char *s=from_twos(r,width);
    free(ba);
    free(bb);
    free(r);
    if(!s){
        errno=ENOMEM;
        return NULL;
    }
    struct BigNumber *out=Number(s);
    if(out==NULL)free(s);
    return out;
}

struct BigNumber *And(struct BigNumber *Number1,struct BigNumber *Number2){
    return bitwise(Number1,Number2,0);
}

struct BigNumber *Or(struct BigNumber *Number1,struct BigNumber *Number2){
    return bitwise(Number1,Number2,1);
}

struct BigNumber *Xor(struct BigNumber *Number1,struct BigNumber *Number2){
    return bitwise(Number1,Number2,2);
}

struct BigNumber *Not(struct BigNumber *number){
    if(!number||!is_valid_number(number->number)){
        errno=EDOM;
        fprintf(stderr,"Not: invalid number (%s)\n",strerror(errno));
        return NULL;
    }
    int len;
    int *b=to_bits(number->number,&len);
    if(!b){
        errno=ENOMEM;
        return NULL;
    }
    int width=len+2;
    free(b);
    b=to_twos(number->number,width);
    if(!b){errno=ENOMEM;return NULL;}
    for(int i=0;i<width;i++)b[i]^=1;
    char *s=from_twos(b,width);
    free(b);
    if(!s){
        errno=ENOMEM;
        return NULL;
    }
    struct BigNumber *out=Number(s);
    if(out==NULL)free(s);
    return out;
}

struct BigNumber *LeftShift(struct BigNumber *number,unsigned long long shift){
    if(!number||!is_valid_number(number->number)){
        errno=EDOM;
        fprintf(stderr,"LeftShift: invalid number (%s)\n",strerror(errno));
        return NULL;
    }
    int len;
    int *b=to_bits(number->number,&len);
    if(!b){errno=ENOMEM;return NULL;}
    if(shift>(unsigned long long)(2147483647-len-2)){
        free(b);errno=ERANGE;return NULL;
    }
    int width=len+(int)shift+2;
    free(b);
    b=to_twos(number->number,width);
    if(!b){
        errno=ENOMEM;
        return NULL;
    }
    for(int i=width-1;i>=0;i--)
        b[i]=(i>=(int)shift)?b[i-(int)shift]:0;
    char *s=from_twos(b,width);
    free(b);
    if(!s){
        errno=ENOMEM;
        return NULL;
    }
    struct BigNumber *out=Number(s);
    if(out==NULL)free(s);
    return out;
}

struct BigNumber *RightShift(struct BigNumber *number,unsigned long long shift){
    if(!number||!is_valid_number(number->number)){
        errno=EDOM;
        fprintf(stderr,"RightShift: invalid number (%s)\n",strerror(errno));
        return NULL;
    }
    int len;
    int *b=to_bits(number->number,&len);
    if(!b){
        errno=ENOMEM;
        return NULL;
    }
    int width=len+2;
    free(b);
    b=to_twos(number->number,width);
    if(!b){
        errno=ENOMEM;
        return NULL;
    }
    int sign=b[width-1];
    if(shift>=(unsigned long long)width){
        for(int i=0;i<width;i++)b[i]=sign;
    }else{
        for(int i=0;i<width-(int)shift;i++)
            b[i]=b[i+(int)shift];
        for(int i=width-(int)shift;i<width;i++)b[i]=sign;
    }
    char *s=from_twos(b,width);
    free(b);
    if(!s){
        errno=ENOMEM;
        return NULL;
    }
    struct BigNumber *out=Number(s);
    if(out==NULL)free(s);
    return out;
}
