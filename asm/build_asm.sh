# -f        specifies the output file format
# elf64     x86_64 64 bit object files

# assemble to object file
nasm -f elf64 -o printRAX.o printRAX.asm
nasm -f elf64 -o main.o     main.asm
nasm -f elf64 -o program.o  program.asm

# link object files
ld -o print_int printRAX.o main.o program.o

# run executable
./print_int

# clean up
rm ./print_int ./printRAX.o ./main.o ./program.o
