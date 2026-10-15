# BigNumber

A Big Number library written in **C** for performing arithmetic, comparison, unary, bitwise, and bit-shift operations on integers beyond the limits of built-in integer types.

## Features

- **Arithmetic Operations:** Addition, subtraction, multiplication, division, and modulo.
- **Comparison Operations:** Less than, less than or equal to, greater than, greater than or equal to, equality, and inequality.
- **Unary Operations:** Absolute value, negation, sign detection, increment, and decrement.
- **Square Root:** Integer square root calculation.
- **Bitwise Operations:** AND, OR, XOR, and NOT.
- **Bit Shifts:** Left shift and right shift.
- **Number Construction:** Create BigNumber objects from decimal strings.

## Project Structure

```text
.
├── includes/
│   ├── BigNumber.h
│   ├── utilities.h
│   ├── Arithmetic.h
│   ├── Comparison.h
│   ├── Unary.h
│   └── Bitwise.h
├── src/
│   ├── Arithmetic.c
│   ├── BigNumber.c
│   ├── Bitwise.c
│   ├── Comparison.c
│   ├── Unary.c
│   └── utilities.c
├── main.c
├── Makefile
└── README.md
```

## Getting Started

### Prerequisites

- GCC or another compatible C compiler
- GNU Make

### Build

Clone the repository and navigate to its directory.

```bash
git clone <repository-url>
cd <repository-directory>
```

Compile the project using the provided Makefile:

```bash
make
```

### Run

```bash
make run
```

### Clean

Remove the generated executable:

```bash
make clean
```

## Usage

Include the required headers in your C program:

```c
#include "./includes/BigNumber.h"
#include "./includes/utilities.h"
#include "./includes/Arithmetic.h"
#include "./includes/Comparison.h"
#include "./includes/Unary.h"
#include "./includes/Bitwise.h"
```

### Example

```c
#include <stdio.h>
#include "./includes/BigNumber.h"
#include "./includes/utilities.h"
#include "./includes/Arithmetic.h"
#include "./includes/Comparison.h"
#include "./includes/Unary.h"
#include "./includes/Bitwise.h"

int main(){
    struct BigNumber *a=Number("1234567890123456838473828374772283847565838384747478901234567890");
    struct BigNumber *b=Number("987654321092884757382900009384747289198347483399876543210");

    print_number(Add(a,b));
    print_number(Sub(a,b));
    print_number(Mul(a,b));
    print_number(Div(a,b));
    print_number(Mod(a,b));

    printf("%d\n",lt(a,b));
    printf("%d\n",et(a,b));

    print_number(Sqrt(a));

    print_number(And(a,b));
    print_number(Or(a,b));
    print_number(Xor(a,b));
    print_number(LeftShift(a,1));
    print_number(RightShift(a,1));

    return 0;
}
```

## API Reference

### Arithmetic

| Function | Description |
|---|---|
| `Add(a,b)` | Adds two numbers |
| `Sub(a,b)` | Subtracts `b` from `a` |
| `Mul(a,b)` | Multiplies two numbers |
| `Div(a,b)` | Divides `a` by `b` |
| `Mod(a,b)` | Returns the remainder of `a` divided by `b` |

### Comparison

| Function | Description |
|---|---|
| `lt(a,b)` | Checks whether `a < b` |
| `lte(a,b)` | Checks whether `a <= b` |
| `gt(a,b)` | Checks whether `a > b` |
| `gte(a,b)` | Checks whether `a >= b` |
| `et(a,b)` | Checks whether `a == b` |
| `net(a,b)` | Checks whether `a != b` |

### Unary Operations

| Function | Description |
|---|---|
| `Abs(a)` | Returns the absolute value |
| `Negate(a)` | Negates the number |
| `Sign(a)` | Returns the sign of the number |
| `Inc(a)` | Increments the number |
| `Dec(a)` | Decrements the number |
| `Sqrt(a)` | Computes the integer square root |

### Bitwise Operations

| Function | Description |
|---|---|
| `And(a,b)` | Bitwise AND |
| `Or(a,b)` | Bitwise OR |
| `Xor(a,b)` | Bitwise XOR |
| `Not(a)` | Bitwise NOT |
| `LeftShift(a,n)` | Shifts bits to the left by `n` positions |
| `RightShift(a,n)` | Shifts bits to the right by `n` positions |

### Utilities

| Function | Description |
|---|---|
| `Number(str)` | Constructs a BigNumber from a decimal string |
| `print_number(a)` | Prints a BigNumber |

Refer to the header files in `includes/` for the exact function signatures and type definitions.

## Important Notes

- Numbers are constructed from strings to support values beyond standard integer limits.
- Division and modulo by zero should be avoided.
- `Sqrt()` computes an integer square root, discarding any fractional component.
- Bitwise operations and shifts follow the implementation's representation and semantics.
- Check the implementation for memory ownership and cleanup requirements when using returned `BigNumber` objects.

## Roadmap

- Expand test coverage across arithmetic, comparison, unary, and bitwise operations.
- Test edge cases involving zero, negative numbers, and very large inputs.
- Optimize performance and memory usage.

## Contributing

Contributions, bug reports, and suggestions are welcome. Feel free to open an issue or submit a pull request.
