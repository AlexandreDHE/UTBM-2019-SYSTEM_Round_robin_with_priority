executable: executable.o 
    gcc -o executable executable.o 

executable.o : executable.c
    gcc -o executable.o executable.c