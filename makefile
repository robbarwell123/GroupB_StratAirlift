CC=gcc

CFLAGS=
ifeq ($(DEBUG),1)
	CFLAGS=-DDEBUG_ENABLED
endif

#Creates bin, build, and output folders required to compile and execute the program.
bin_folder := $(shell mkdir -p bin)
build_folder := $(shell mkdir -p build)
output_folder := $(shell mkdir -p output)

#Default command
dev: main.o parse_config.o common_functions.o
	$(CC) -g -o bin/StratAirliftInit build/main.o build/parse_config.o build/common_functions.o

#Commands to compile all parts of the program
main.o: src/main.c
	$(CC) -g -c $(CFLAGS) src/main.c -o build/main.o

parse_config.o: src/parse_config.c
	$(CC) -g -c $(CFLAGS) src/parse_config.c -o build/parse_config.o	

common_functions.o: src/common_functions.c
	$(CC) -g -c $(CFLAGS) src/common_functions.c -o build/common_functions.o	

prod: main.o parse_config.o common_functions.o
	$(CC) -g -o bin/StratAirliftInit build/main.o build/parse_config.o build/common_functions.o


#This command executes the program
run:
	bin/StratAirliftInit.exe

#This command generates the doxygen files
doxygen:
	rm -f -r ./doc/detailed
	doxygen ./doc/doxygen_config.cfg

#This command resets the build to the default state
clean: 
	rm -f bin/* build/* output/*