#ifndef BITWISE_H
#define BITWISE_H

#include "BigNumber.h"

static char *magnitude(const char *s);
static int negative(const char *s);
static int *to_bits(const char *s,int *len);
static int *to_twos(const char *s,int width);
static char *from_twos(int *bits,int width);
static struct BigNumber *bitwise(struct BigNumber *a,struct BigNumber *b,int op);
struct BigNumber *And(struct BigNumber *Number1,struct BigNumber *Number2);
struct BigNumber *Or(struct BigNumber *Number1,struct BigNumber *Number2);
struct BigNumber *Xor(struct BigNumber *Number1,struct BigNumber *Number2);
struct BigNumber *Not(struct BigNumber *number);
struct BigNumber *LeftShift(struct BigNumber *number,unsigned long long shift);
struct BigNumber *RightShift(struct BigNumber *number,unsigned long long shift);

#endif
