#ifndef COMPARISON_H
#define COMPARISON_H

#include "BigNumber.h"

bool lt(struct BigNumber *number1, struct BigNumber *number2);
bool lte(struct BigNumber *number1, struct BigNumber *number2);
bool gt(struct BigNumber *number1, struct BigNumber *number2);
bool gte(struct BigNumber *number1, struct BigNumber *number2);
bool et(struct BigNumber *number1, struct BigNumber *number2);
bool net(struct BigNumber *number1, struct BigNumber *number2);

#endif
