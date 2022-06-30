
# -f        specifies the output file format
# elf32     ELF32 (i386) object files
nasm -f elf32 -o hello_world.o hello_world.asm


# -m EMULATOR
ld -m elf_i386 -o hello_world hello_world.o


./hello_world

# clean up
rm ./hello_world ./hello_world.o