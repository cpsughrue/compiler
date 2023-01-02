This repository was created as an exercise to learn about compilers and is a work in progress. Right now only simple integer math expressions can be compiled and executed.

## Build

To build compiler and compile a simple math problem. Add math problem to `program.txt` then run the build script.

```bash
./build.sh

# Flags
#
#   -S, --scan-only: the compiler will scan the input file, print each token in a human readable format, and exit
#
#   -V, --verbose: the combiler will print log statements to the consol
#
```
`build.sh` in addtion to generating the assembly output files and calling the assembly build script also compiles the compiler. Compiling the compiler improves iteration speed and helps with debugging.

## Supported Operators
- `+`  <- addition
- `-`  <- subtraction
- `/`  <- floor division
- `*`  <- multiplication
- `^`  <- power
- `%`  <- modulo

## Limitations

- No support for floating point numbers in input or output
    - `2.5 + 3` is an invalid expression
    - `5 / 2` will evaluate to 2 instead of 2.5
- Negative exponents evauate to 0
    - `4 ^ -3 = 0`

## Example Valid Math Expressions
- `3 + -2`
- `6 / 3 + 2`
- `6/3+2`
- `4 ^ 2 - 6 ^ 2 + 3`
- `(8 + 2) * 834`

## Dependencies
In parenthesis are the versions currently being used on my local machine
- gcc (9.4.0)
- nasm (2.14.02)
- ld (2.34)
