This repository was created as an exercise to learn about compilers and is a work in progress. Right now only simple integer math expressions can be compiled and executed.

## Build

To build the math compiler and compile a simple math problem. Add the math problem to `program.txt` then run the build script: `build.sh`. 
```bash
./build.sh

# Flags
#
#   -s, --scan-only: the compiler will scan the input file, print each token in 
#                    a human readable format, and exit. assembly is not generated
#                    and ./build_asm.sh will not be executed
#
#   -v, --verbose: the combiler will print log statements to the consol
#
```
The build script has three parts. The first part handles flags/arguments passed to `build.sh` by the user. The second part compiles the compiler with gcc and executes the binary with the path to `program.txt` as the first argument. The third and last part calls `asm/build_asm.sh` when appropriate. The script `build_asm.sh` uses nasm and ld to assemble and link the generated and prewritten x86_64 assembly. Generated asembly can be found in `asm/program.asm`.

## Supported Operators
- `+`  <- addition
- `-`  <- subtraction
- `/`  <- floor division
- `*`  <- multiplication
- `^`  <- power
- `%`  <- modulo

## Known Limitations

- No support for floating point numbers in input or output
    - `2.5 + 3` is an invalid expression
    - `5 / 2` will evaluate to 2 instead of 2.5
- Negative exponents evauate to 0 (related to the lack of floating point support)
    - `4 ^ -3 = 0`
- Limited error detection
    - if there are multiple invalid tokens or multiple syntax errors compiler will only output the first one then exit

## Example Valid Math Expressions
- `3 + -2`
- `6 / 3 + 2`
- `6/3+2`
- `4 ^ 2 - 6 ^ 2 + 3`
- `(8 + 2) * 834`
- `4-2`

## Dependencies
In parenthesis are the versions currently being used on my local machine
- gcc (9.4.0)
- nasm (2.14.02)
- ld (2.34)
