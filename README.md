This repository was created as an exercise to learn about compilers and is a work in progress. The compiler compiles math expressions to x86_64 assembly - Intel Syntax. 

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

# Example
cat program.txt
4 ^ 2 - 6 ^ 2 + 3

./build.sh
(((4^2)-(6^2))+3)
ASSEMBLY OUTPUT:  -17
```
The build script has three parts. Part one handles flags/arguments passed to `build.sh` by the user. Part two compiles the compiler with `gcc` and executes the binary. The path to `program.txt` is provided to the compiler as its first command line argument. During the code generation stage of execution the compiler will save the generated assembly to `asm/program.asm`. The third part calls `asm/build_asm.sh` which assembles, linkes, and executes the assembly. `build_asm.sh` uses `nasm` to assemble and `ld` to link the generated and prewritten x86_64 assembly. The prewritten assembly provides a built in way to print the result of the generated assembly.

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
    - If there are multiple invalid tokens or multiple syntax errors the compiler will only identify the first one, print the error to the consol, and exit

## Example Valid Math Expressions
- `3 + -2`
- `6 / 3 + 2`
- `6/3+2`
- `4 ^ 2 - 6 ^ 2 + 3`
- `(8 + 2) * 834`
- `4-2`

## Dependencies
In parenthesis are the versions used during development
- gcc (9.4.0)
- nasm (2.14.02)
- ld (2.34)
