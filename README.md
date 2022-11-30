This repository was created as an exercise to learn about compilers and is a BIG work in progress. Right now only simple math expressions can be compiled and executed. 

## Build

To build compiler and compile a simple math problem. Add math problem to `program.txt` then simply run the build script.

```bash
./build.sh
```

## Supported Operators
- `+`  <- addition
- `-`  <- subtraction
- `/`  <- floor division
- `*`  <- multiplication
- `^`  <- power
- `%`  <- modulo

## Limitations

Current limitations all of which will be addressed
- No suport for negative numbers in input
    - `-3 + 5` is an invalid expression
    - NOTE: output can print negative numbers
- No support for floating point numbers in input or output
    - `2.5 + 3` is an invalid expression
- No support for negative exponents
    - `4 ^ (2 - 6)` is an invalid expression because `2 - 6` evaluates to a negative number and is used as an exponent

## Example Valid Math Expressions
- `3 + 2`
- `6 / 3 + 2`
- `6/3+2`
- `4 ^ 2 - 6 ^ 2 + 3`
- `(8 + 2) * 834`
