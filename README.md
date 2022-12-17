This repository was created as an exercise to learn about compilers and is a work in progress. Right now only simple math expressions can be compiled and executed.

## Build

To build compiler and compile a simple math problem. Add math problem to `program.txt` then simply run the build script.

```bash
./build.sh
```
`build.sh` in addtion to generating the assembly output files and calling the assembly build script also compiles the compiler. This helps with debugging and is temporary. Currently only one flag is supported. When the `-s` flag is specified the compiler will scan the input file, print each token in a human readable format, and exit. The flag `-s` was implemented to simplify the development of new tokens. 
```bash
./build.sh -s
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
    - `5 / 2` will evaluate to 2 instead of 2.5  
- No support for negative exponents
    - `4 ^ (2 - 6)` is an invalid expression

## Example Valid Math Expressions
- `3 + 2`
- `6 / 3 + 2`
- `6/3+2`
- `4 ^ 2 - 6 ^ 2 + 3`
- `(8 + 2) * 834`

## Dependencies
In parenthesis are the versions currently installed on my local machine
- gcc (9.4.0)
- nasm (2.14.02)
- ld (2.34)
