cd src

gcc -I../include main.c scanner.c parser.c utils.c -o compiler

./compiler ../program.txt

rm ./compiler