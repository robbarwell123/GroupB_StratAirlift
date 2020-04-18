/**
 * @file export_test.c
 * @author Rob Barwell, Lukeman Hakkim Sheik Alavudeen
 * @date 16 Apr 2020, Last updated 18 Apr 2020
 * @brief This file contains all functions to run the export_test unit tests.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/data_types.h"
#include "../../include/common_functions.h"
#include "../../include/strat_airlift_functions.h"
#include "../include/calc_shortest_path_test.h"


int export_files_test() {
    int rtn_val=0;                                      // The current state of the function to return

    char *valid_result[]={"0/1 0 1 2 55.87190 -4.43306 1","0/1 0 2 2 55.87190 -4.43306 2","0/1 0 3 3 -1.31924 36.92780 2","0/1 0 4 2 55.87190 -4.43306 2","0/1 1 0 4 4.70159 -74.14690 1","0/1 1 2 4 4.70159 -74.14690 2","0/1 1 3 4 4.70159 -74.14690 2","0/1 1 4 4 4.70159 -74.14690 2","0/1 2 0 0 44.11890 -77.52810 2","0/1 2 1 4 4.70159 -74.14690 2","0/1 2 3 3 -1.31924 36.92780 2","0/1 2 4 4 4.70159 -74.14690 2","0/1 3 0 0 44.11890 -77.52810 2","0/1 3 1 4 4.70159 -74.14690 2","0/1 3 2 2 55.87190 -4.43306 2","0/1 3 4 4 4.70159 -74.14690 2","0/1 4 0 2 55.87190 -4.43306 2","0/1 4 1 1 50.86590 7.14274 2","0/1 4 2 2 55.87190 -4.43306 2","0/1 4 3 3 -1.31924 36.92780 2"};
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

    my_airports=calc_shortest_path_test_set_airports();
    calc_shortest_path_test_set_state(my_airports,my_state);

    #ifdef DEBUG_ENABLED
    print_state(my_state);
    #endif

    if(calc_shortest_path(my_state, &my_paths)!=0) {
        rtn_val=-1;
    }


    #ifdef DEBUG_ENABLED
    print_paths(my_paths);
    #endif

    /* To test the export_text function */
    if (export_text(my_paths, "C:\\Users\\LUCKMAN HAKKIM\\Desktop\\test_file.txt")!=0){
        rtn_val=-2;
    }

    /* To test the export_xml function */
    if (export_xml(my_state,"C:\\Users\\LUCKMAN HAKKIM\\Desktop\\test_file.xml")!=0){
        rtn_val=-3;
    }


    free(my_sizes);
    free(my_state);
    free(my_airports);
    free(my_paths);

    my_sizes=NULL;
    
    return rtn_val;
}