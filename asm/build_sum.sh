
# -f        specifies the output file format
# elf32     ELF32 (i386) object files
nasm -f elf64 -o print_int.o print_int.asm


# -m EMULATOR
ld -o print_int print_int.o


./print_int

# clean up
rm ./print_int ./print_int.o