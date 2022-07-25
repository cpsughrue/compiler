
# -f        specifies the output file format
# elf64     x86_64 64 bit object files

# assemble to object file
nasm -f elf64 -o print_int.o print_int.asm
nasm -f elf64 -o main.o main.asm

# link object files
ld -o print_int print_int.o main.o

# run executable
./print_int

# clean up
rm ./print_int ./print_int.o ./main.o
