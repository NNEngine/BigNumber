#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "BigNumber.h"

struct BigNumber *Add(struct BigNumber *Number1, struct BigNumber *Number2);
struct BigNumber *Sub(struct BigNumber *Number1, struct BigNumber *Number2);
struct BigNumber *Mul(struct BigNumber *Number1, struct BigNumber *Number2);
struct BigNumber *Div(struct BigNumber *Number1, struct BigNumber *Number2);
struct BigNumber *Mod(struct BigNumber *Number1, struct BigNumber *Number2);

#endif
