# exit script if any simple command returns a non-zero exit code
set -eo pipefail

# process comand line arguments
for arg in $@; do
    case $arg in
        -s)
        scan="-s"    # when -s is prvided compiler will only scan
        ;;
        -v)
        log="-D LOG" # macros are defined in utils.h and are enabled when LOG is defined
        ;;
    esac
done

cd src

# compile and execute
gcc -I../include main.c scanner.c parser.c utils.c code_gen.c -o compiler "$log"
./compiler ../program.txt "$scan"
rm ./compiler

# execute generated assembly if compiler did not only scan
if [[ $1 != "-s" ]]; then
    echo -n "ASSEMBLY OUTPUT:  "
    cd ../asm && ./build_asm.sh
fi