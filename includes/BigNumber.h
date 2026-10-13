#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include "libs.h"

struct BigNumber{
    char *number;
    int length;
};

struct BigNumber *Number(char *number);

#endif
