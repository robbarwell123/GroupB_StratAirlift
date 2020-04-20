/**
 * @file calc_shortest_path_test.c
 * @author Rob Barwell
 * @date 17 Mar 2020, Last updated 20 Apr 2020
 * @brief This file contains all functions to run the calc_shortest_path unit tests.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/data_types.h"
#include "../../include/common_functions.h"
#include "../../include/strat_airlift_functions.h"
#include "../include/common_test_functions.h"

int calc_shortest_path_test() {
    int rtn_val=0;                                      // The current state of the function to return

    char *valid_result[]={"0/1 0 1 1 50.86590 7.14274 1","0/1 0 2 1 50.86590 7.14274 2","0/1 0 3 1 50.86590 7.14274 2","0/1 0 4 4 4.70159 -74.14690 2","0/1 1 0 0 44.11890 -77.52810 1","0/1 1 2 2 55.87190 -4.43306 2","0/1 1 3 3 -1.31924 36.92780 2","0/1 1 4 0 44.11890 -77.52810 2","0/1 2 0 1 50.86590 7.14274 2","0/1 2 1 1 50.86590 7.14274 2","0/1 2 3 1 50.86590 7.14274 2","0/1 2 4 1 50.86590 7.14274 2","0/1 3 0 1 50.86590 7.14274 2","0/1 3 1 1 50.86590 7.14274 2","0/1 3 2 1 50.86590 7.14274 2","0/1 3 4 1 50.86590 7.14274 2","0/1 4 0 0 44.11890 -77.52810 2","0/1 4 1 0 44.11890 -77.52810 2","0/1 4 2 0 44.11890 -77.52810 2","0/1 4 3 0 44.11890 -77.52810 2"};
    char compare_to[50];
    
    /* Creates the initial structures which will be used for all function calls. */
    struct STATE *my_state=malloc(sizeof(struct STATE));
    struct AIRPORT **my_airports;
    struct PATH *my_paths=NULL;

    free(my_sizes);
    /* Initalizes my_sizes to 0 for all dynamic arrays. */
    my_sizes=malloc(sizeof(struct SIZES));
    for(int init=0;init<7;init++){
        my_sizes->cont[init]=0;
    }
    my_sizes->locations=0;
    my_sizes->paths=0;

    my_airports=set_test_airports();
    set_test_state(my_airports,my_state);

    #ifdef DEBUG_ENABLED
    print_state(my_state);
    #endif

    if(calc_shortest_path(my_state, &my_paths)!=0) {
        rtn_val=-1;
    }

    #ifdef DEBUG_ENABLED
    print_paths(my_paths);
    #endif

    for(int compare=0;compare<my_sizes->paths;compare++) {
        sprintf(compare_to,"0/1 %d %d %d %0.5f %0.5f %d",my_paths[compare].source_location,my_paths[compare].dest_location,my_paths[compare].next_location,my_paths[compare].next_lat,my_paths[compare].next_long,my_paths[compare].aircraft_type);
        if(strcmp(valid_result[compare],compare_to)!=0) {
            printf("calc_shortest_path test failed on comparison: %d.\n",compare);
            rtn_val=-2;
        }
    }
    
    free(my_sizes);
    free(my_state);
    free(my_airports);
    free(my_paths);

    my_sizes=NULL;
    
    return rtn_val;
}