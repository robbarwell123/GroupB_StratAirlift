/**
 * @file test_main.c
 * @author Rob Barwell
 * @date 17 Mar 2020
 * @brief This file contains the main function to run all tests.
 */

#include <stdio.h>
#include <stdlib.h>

#include "../../include/data_types.h"
#include "../../include/common_functions.h"
#include "../../include/helper_functions.h"
#include "../../include/parse_airports.h"
#include "../../include/strat_airlift_functions.h"
#include "../include/strat_airlift_functions_tests.h"
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
    
    /* get 2D array of objects */

    int size[7] ;

    char line[N];
    char filename_1[100]= "airports_empty.csv";
    char filename_2[100]= "airports_known_number.csv";
    char filename_3[100] = "airports_copy_wider_size_array.csv";
        
    printf("TEST CASE 1: Empty CSV\n");
    printf("OUTPUT EXPECTED: O airports and returns 0 because it runs effectively\n");
    struct AIRPORT** arr_1 = get_2D_array(size, line, filename_1);
    int num_of_airports_1 =parse_airports(arr_1, line);
    printf("%d\n\n",num_of_airports_1);

    printf("TEST CASE 2: known length of CSV\n");
    printf("OUTPUT EXPECTED: 5 airports and returns 0 because it runs effectively\n");
    struct AIRPORT** arr_2 = get_2D_array(size, line,filename_2);
    int num_of_airports_2 =parse_airports(arr_2, line);
    printf("%d\n\n",num_of_airports_2);

    printf("TEST CASE 3: Continet size increased to 8\n");
    printf("OUTPUT EXPECTED: returns -1 as file fails to \n\n");
    struct AIRPORT** arr_3 = get_2D_array(size, line, filename_3);
    int num_of_airports_3 =parse_airports(arr_3, line);
    printf("%d\n\n",num_of_airports_3);
    
    
    int rtn_val=0;                                      // The current state of the function to return

    printf("=== Testing calc_shortest_path ===\n");
    if(calc_shortest_path_test()==0) {
        printf("calc_shortest_path test PASSED.\n");
    }else {
        printf("calc_shortest_path test FAILED.\n");
        rtn_val=-5;
    }

    printf("%s\n",rtn_val==0 ? "All tests PASSED." : "One or more tests FAILED.");
    
    return rtn_val;
}
