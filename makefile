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
all: app test

#Production application command
app: main.o parse_config.o common_functions.o calc_shortest_path.o gen_locations.o
	$(CC) -g -o bin/StratAirliftInit build/common_functions.o build/main.o build/parse_config.o build/calc_shortest_path.o build/gen_locations.o

#Commands to compile all parts of the program
main.o: src/main.c
	$(CC) -g -c $(CFLAGS) src/main.c -o build/main.o

parse_config.o: src/parse_config.c
	$(CC) -g -c $(CFLAGS) src/parse_config.c -o build/parse_config.o	

common_functions.o: src/common_functions.c
	$(CC) -g -c $(CFLAGS) src/common_functions.c -o build/common_functions.o	

calc_shortest_path.o: src/calc_shortest_path.c
	$(CC) -g -c $(CFLAGS) src/calc_shortest_path.c -o build/calc_shortest_path.o	
    
gen_locations.o: src/gen_locations.c
	$(CC) -g -c $(CFLAGS) src/gen_locations.c -o build/gen_locations.o

#Test application command
test: test_main.o parse_config.o common_functions.o calc_shortest_path.o calc_shortest_path_test.o gen_locations.o gen_locations_test.o
	$(CC) -g -o bin/StratAirliftInit_Test build/common_functions.o build/test_main.o build/parse_config.o build/calc_shortest_path.o build/calc_shortest_path_test.o build/gen_locations.o build/gen_locations_test.o

#Commands to compile all parts of the test
test_main.o: test/src/test_main.c
	$(CC) -g -c $(CFLAGS) test/src/test_main.c -o build/test_main.o

calc_shortest_path_test.o: test/src/calc_shortest_path_test.c
	$(CC) -g -c $(CFLAGS) test/src/calc_shortest_path_test.c -o build/calc_shortest_path_test.o	

gen_locations_test.o: test/src/gen_locations_test.c
	$(CC) -g -c $(CFLAGS) test/src/gen_locations_test.c -o build/gen_locations_test.o	

#This command executes the program
run:
	bin/StratAirliftInit.exe

#This command executes the test program
run_test:
	bin/StratAirliftInit_Test.exe

#This command generates the doxygen files
doxygen:
	rm -f -r ./doc/detailed
	doxygen ./doc/doxygen_config.cfg

#This command resets the build to the default state
clean: 
	rm -f bin/* build/* output/*