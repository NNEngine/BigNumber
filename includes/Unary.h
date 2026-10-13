#ifndef UNARY_H
#define UNARY_H

#include "BigNumber.h"

struct BigNumber *Abs(struct BigNumber *number);
struct BigNumber *Negate(struct BigNumber *number);
int Sign(struct BigNumber *number);

#endif
