
# -f        specifies the output file format
# elf64     x86_64 64 bit object files
nasm -f elf64 -o print_int.o print_int.asm
nasm -f elf64 -o main.o main.asm

# -m EMULATOR
ld -o print_int print_int.o main.o


./print_int

# clean up
rm ./print_int ./print_int.o ./main.o
