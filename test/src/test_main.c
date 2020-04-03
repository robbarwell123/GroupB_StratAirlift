/**
 * @file test_main.c
 * @author Rob Barwell, Olumide Akinola, Edwin Omoigui
 * @date 17 Mar 2020, Last Updated 31 Mar 2020
 * @brief This file contains the main function to run all tests.
 */

#include <stdio.h>
#include <stdlib.h>

#include "../../include/data_types.h"
#include "../../include/common_functions.h"
#include "../../include/strat_airlift_functions.h"
#include "../../include/parse_airports.h"
#include "../include/strat_airlift_functions_tests.h"
#include "../include/find_closest_test.h"


/**
 * @brief continent_names is used for error messages to decipher which continent caused the issue.
 */
char* continent_names[]={"Africa","Antarctica","Asia","Europe","North America","Australia","South America"};

/**
 * @brief my_sizes is used to store the sizes of the dynamic arrays used throughout the program.
 */
struct SIZES *my_sizes;

/**
 * @brief The main function to run the tests for the strategic airlift input generator.
 *
 * The following are valid command line arguments:
 * TBD - by Edwin
 *
 * @return 0 if the application executed successfully.  Any other number if their was an error.
 */
int main() {    
    int rtn_val=0;              // The current state of the function to return
    
    printf("=== Testing_parse_airports ===\n");
    if(parse_airports_test()==0) {
        printf("parse_airports test PASSED.\n");
    }else {
        printf("parse_airports test FAILED.\n");
        rtn_val=-1;
    }

    printf("=== Testing gen_locations ===\n");
    if(gen_locations_test()==0) {
        printf("gen_locations test PASSED.\n");
    }else {
        printf("gen_locations test FAILED.\n");
        rtn_val=-2;
    }

    printf("=== Testing calc_shortest_path ===\n");
    if(calc_shortest_path_test()==0) {
        printf("calc_shortest_path test PASSED.\n");
    }else {
        printf("calc_shortest_path test FAILED.\n");
        rtn_val=-5;
    }

    printf("=== Testing find_closest_node ===\n");
    if(find_closest_test()==0) {
        printf("find_closest test PASSED.\n");
    }else {
        printf("find_closest test FAILED.\n");
        rtn_val=-6;
    }

    printf("%s\n",rtn_val==0 ? "All tests PASSED." : "One or more tests FAILED.");
    
    return rtn_val;
}
