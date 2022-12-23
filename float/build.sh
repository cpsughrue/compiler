
nasm printFloat.asm -f elf64 -o printf.o

gcc printf.o

./a.out

rm ./a.out 

rm ./printf.o

