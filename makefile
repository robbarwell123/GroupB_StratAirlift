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
app: main.o parse_config.o common_functions.o calc_shortest_path.o parse_airports.o gen_locations.o find_closest.o 
	$(CC) -g -o bin/StratAirliftInit build/common_functions.o build/main.o build/parse_config.o build/calc_shortest_path.o build/parse_airports.o build/gen_locations.o build/find_closest.o -lm

#Commands to compile all parts of the program
main.o: src/main.c
	$(CC) -g -c $(CFLAGS) src/main.c -o build/main.o

parse_config.o: src/parse_config.c
	$(CC) -g -c $(CFLAGS) src/parse_config.c -o build/parse_config.o

common_functions.o: src/common_functions.c
	$(CC) -g -c $(CFLAGS) src/common_functions.c -o build/common_functions.o

calc_shortest_path.o: src/calc_shortest_path.c
	$(CC) -g -c $(CFLAGS) src/calc_shortest_path.c -o build/calc_shortest_path.o

parse_airports.o: src/parse_airports.c
	$(CC) -g -c $(CFLAGS) src/parse_airports.c -o build/parse_airports.o

gen_locations.o: src/gen_locations.c
	$(CC) -g -c $(CFLAGS) src/gen_locations.c -o build/gen_locations.o

find_closest.o: src/find_closest.c
	$(CC) -g -c $(CFLAGS) src/find_closest.c -o build/find_closest.o

#Test application command
test: test_main.o parse_config.o common_functions.o calc_shortest_path.o calc_shortest_path_test.o parse_airports.o parse_airports_test.o gen_locations.o gen_locations_test.o find_closest.o find_closest_test.o parse_config_test.o integrated.o
	$(CC) -g -o bin/StratAirliftInit_Test build/common_functions.o build/test_main.o build/parse_config.o build/calc_shortest_path.o build/calc_shortest_path_test.o build/parse_airports.o build/parse_airports_test.o build/gen_locations.o build/gen_locations_test.o build/find_closest.o build/find_closest_test.o build/parse_config_test.o build/integrated.o -lm

#Commands to compile all parts of the test
test_main.o: test/src/test_main.c
	$(CC) -g -c $(CFLAGS) test/src/test_main.c -o build/test_main.o

calc_shortest_path_test.o: test/src/calc_shortest_path_test.c
	$(CC) -g -c $(CFLAGS) test/src/calc_shortest_path_test.c -o build/calc_shortest_path_test.o

parse_airports_test.o: test/src/parse_airports_test.c
	$(CC) -g -c $(CFLAGS) test/src/parse_airports_test.c -o build/parse_airports_test.o

gen_locations_test.o: test/src/gen_locations_test.c
	$(CC) -g -c $(CFLAGS) test/src/gen_locations_test.c -o build/gen_locations_test.o

find_closest_test.o: test/src/find_closest_test.c
	$(CC) -g -c $(CFLAGS) test/src/find_closest_test.c -o build/find_closest_test.o

parse_config_test.o: test/src/parse_config_test.c
	$(CC) -g -c $(CFLAGS) test/src/parse_config_test.c -o build/parse_config_test.o

integrated.o: test/src/integrated.c
		$(CC) -g -c $(CFLAGS) test/src/integrated.c -o build/integrated.o

#This command executes the program
run:
	bin/StratAirliftInit

#This command executes the test program
run_test:
	bin/StratAirliftInit_Test

#This command generates the doxygen files
doxygen:
	rm -f -r ./doc/detailed
	doxygen ./doc/doxygen_config.cfg

#This command resets the build to the default state
clean:
	rm -f bin/* build/* output/*
