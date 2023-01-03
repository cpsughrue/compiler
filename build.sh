# process comand line arguments
for arg in $@; do
    case $arg in
        -s | --scan-only)   # when -s is prvided compiler will only scan
        scan="-s"    
        log="-D VERBOSE"        # there will be no output if logs are diabbles during a scan only
        ;;
        -v | --verbose)
        log="-D VERBOSE"        # macros are defined in utils.h and are enabled when VERBOSE is defined
        ;;
        *)
        echo "unknown argument $arg"
        exit
        ;;
    esac
done

cd src

# compile and execute
gcc -I../include main.c scanner.c parser.c utils.c code_gen.c -o compiler $log
./compiler ../program.txt $scan

# execute generated assembly if compiler successfully generated assembly
# compiler does not generate assembly if -s flag is set
if [[ $scan != "-s" && $? == 0 ]]; then
    echo -n "ASSEMBLY OUTPUT:  "
    cd ../asm && ./build_asm.sh
fi

# clean
rm ../src/compiler
