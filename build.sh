# exit script if any simple command returns a non-zero exit code
set -eo pipefail

# process comand line arguments
for arg in $@; do
    case $arg in
        -s | --scan-only)   # when -s is prvided compiler will only scan
        scan="-s"    
        log="-D VERBOSE"        # there will be no output if logs are diabbles during a scan only
        ;;
        -v | --verbose)
        log="-D VERBOSE"        # macros are defined in utils.h and are enabled when LOG is defined
        ;;
        *)
        echo "unknown argument $arg"
        exit
        ;;
    esac
done

cd src

# compile and execute
# surrounding $log and $scan with double quotes cause an error
gcc -I../include main.c scanner.c parser.c utils.c code_gen.c -o compiler $log
./compiler ../program.txt $scan
rm ./compiler

# execute generated assembly if compiler did not only scan
if [[ $scan != "-s" ]]; then
    echo -n "ASSEMBLY OUTPUT:  "
    cd ../asm && ./build_asm.sh
fi