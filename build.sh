cd src

gcc main.c scanner.c utils.c -o language

./language ../program.txt

rm ./language