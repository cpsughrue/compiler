# exit script if any simple command returns a non-zero exit code
set -e

cd src

gcc -I../include main.c scanner.c parser.c utils.c code_gen.c -o compiler

./compiler ../program.txt $1

rm ./compiler

if [[ $1 != "-s" ]]; then
    echo "ASSEMBLY OUTPUT"
    cd ../asm && ./build_asm.sh
fi