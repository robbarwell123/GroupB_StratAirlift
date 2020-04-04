/**
 * @file find_closest_test.c
 * @author Lukman Hakkim Sheik Alavudeen
 * @date 03 APRIL 2020
 * @brief This file contains all functions to run the find_closest unit tests.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/data_types.h"
#include "../../include/common_functions.h"
#include "../../include/strat_airlift_functions.h"
#include "../../include/find_closest.h"
#include "../include/calc_shortest_path_test.h"
#include "../include/find_closest_test.h"


// Defined in the test_main.c file
extern struct SIZES *my_sizes;


int find_closest_test() {
    int rtn_val=0;                                      // The current state of the function to return
    
    int ** a = find_closest();
    
    if(a!=0) {
       rtn_val=-1;
    }

    return rtn_val;
}