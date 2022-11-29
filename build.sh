cd src

gcc -I../include main.c scanner.c parser.c utils.c code_gen.c -o compiler

./compiler ../program.txt

rm ./compiler

cd ../asm
echo "ASSEMBLY OUTPUT"
./build_asm.sh