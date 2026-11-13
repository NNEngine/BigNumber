#include "../includes/BigNumber.h"
#include "../includes/utilities.h"

struct BigNumber *Number(char *number){
    if(!is_valid_number(number)){
        errno = EDOM;
        fprintf(stderr,
                "is_valid_number: Number is not valid (%s)\n",
                strerror(errno));
        return NULL;
    }
    
    struct BigNumber *num = (struct BigNumber *)malloc(sizeof(struct BigNumber));
    if(num==NULL){
        errno = ENOMEM;
        fprintf(stderr,
                "Input: failed to allocate num (%s)\n",
                strerror(errno));
        return NULL;
    }

    num->number = malloc(strlen(number) + 1);
    if(num->number==NULL){
        free(num);
        errno = ENOMEM;
        return NULL;
    }
    
    strcpy(num->number, number);
    num->length = strlen(number);
    
    return num;
}

void FreeNumber(struct BigNumber *num){
    if(num==NULL) return;
    free(num->number);
    free(num);
}
