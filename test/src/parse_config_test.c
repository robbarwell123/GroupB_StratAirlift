/**
 * @file calc_shortest_path_test.c
 * @author Rob Barwell
 * @date 17 Mar 2020, Last updated 30 Mar 2020
 * @brief This file contains all functions to run the calc_shortest_path unit tests.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/data_types.h"
#include "../../include/common_functions.h"
#include "../../include/strat_airlift_functions.h"
#include "../../include/parse_config.h"

int parse_config_test() {
    int rtn_val=CONFIG_OK;                      // The current state of the function to return
    int func_rtn_val;                           // the return value from called functions

    /* Creates the initial structures which will be used for all function calls. */
    struct STATE *my_state=malloc(sizeof(struct STATE));
    struct AIRPORT **my_airports;
    my_airports=(struct AIRPORT**)malloc(sizeof(struct AIRPORT*)*7);
    for(int init=0;init<7;init++){
        my_airports[init]=NULL;
    }

    if(!my_sizes){
        free(my_sizes);
    }
    /* Initalizes my_sizes to 0 for all dynamic arrays. */
    my_sizes=malloc(sizeof(struct SIZES));
    for(int init=0;init<7;init++) {
        my_sizes->cont[init]=0;
    }
    my_sizes->locations=0;
    my_sizes->paths=0;

    if(rtn_val==0 && parse_airports("./data/airports.csv",my_airports)!=0) {
        rtn_val=-1;
    }

    printf("parse_config test 1 - my_state not NULL: ");
    func_rtn_val=parse_config(my_airports, "./test/data/blank.cfg", NULL);
    if(func_rtn_val==CONFIG_STATE_ERROR){
        printf("PASSED\n");
    }else{
        printf("FAILED Expected CONFIG_STATE_ERROR, recieved %d\n",func_rtn_val);
        rtn_val=-1;
    }

    printf("parse_config test 2 - Configuration file doesn’t exist: ");
    func_rtn_val=parse_config(my_airports, "dummy.cfg", my_state);
    if(func_rtn_val==CONFIG_FILE_ERROR){
        printf("PASSED\n");
    }else{
        printf("FAILED Expected CONFIG_FILE_ERROR, recieved %d\n",func_rtn_val);
        rtn_val=-1;
    }

    printf("parse_config test 3A - Invalid parameter / value pair: ");
    func_rtn_val=parse_config(my_airports, "./test/data/3A.cfg", my_state);
    if(func_rtn_val==CONFIG_KEY_ERROR){
        printf("PASSED\n");
    }else{
        printf("FAILED Expected CONFIG_KEY_ERROR, recieved %d\n",func_rtn_val);
        rtn_val=-1;
    }
    
    printf("parse_config test 3B - Invalid parameter / value pair: ");
    func_rtn_val=parse_config(my_airports, "./test/data/3B.cfg", my_state);
    if(func_rtn_val==CONFIG_KEY_ERROR){
        printf("PASSED\n");
    }else{
        printf("FAILED Expected CONFIG_KEY_ERROR, recieved %d\n",func_rtn_val);
        rtn_val=-1;
    }
    
    printf("parse_config test 4 - Blank line: ");
    func_rtn_val=parse_config(my_airports, "./test/data/4.cfg", my_state);
    if(func_rtn_val==CONFIG_KEY_ERROR){
        printf("PASSED\n");
    }else{
        printf("FAILED Expected CONFIG_KEY_ERROR, recieved %d\n",func_rtn_val);
        rtn_val=-1;
    }
    
    printf("parse_config test 5A - Invalid number_of_scenarios: ");
    func_rtn_val=parse_config(my_airports, "./test/data/5A.cfg", my_state);
    if(func_rtn_val==CONFIG_SCENARIO_ERROR){
        printf("PASSED\n");
    }else{
        printf("FAILED Expected CONFIG_SCENARIO_ERROR, recieved %d\n",func_rtn_val);
        rtn_val=-1;
    }

    printf("parse_config test 5B - Invalid number_of_scenarios: ");
    func_rtn_val=parse_config(my_airports, "./test/data/5B.cfg", my_state);
    if(func_rtn_val==CONFIG_SCENARIO_ERROR){
        printf("PASSED\n");
    }else{
        printf("FAILED Expected CONFIG_SCENARIO_ERROR, recieved %d\n",func_rtn_val);
        rtn_val=-1;
    }
    
    printf("parse_config test 6A - Invalid number_of_locations: ");
    func_rtn_val=parse_config(my_airports, "./test/data/6A.cfg", my_state);
    if(func_rtn_val==CONFIG_LOCATION_ERROR){
        printf("PASSED\n");
    }else{
        printf("FAILED Expected CONFIG_LOCATION_ERROR, recieved %d\n",func_rtn_val);
        rtn_val=-1;
    }

    printf("parse_config test 6B - Invalid number_of_locations: ");
    func_rtn_val=parse_config(my_airports, "./test/data/6B.cfg", my_state);
    if(func_rtn_val==CONFIG_LOCATION_ERROR){
        printf("PASSED\n");
    }else{
        printf("FAILED Expected CONFIG_LOCATION_ERROR, recieved %d\n",func_rtn_val);
        rtn_val=-1;
    }

    printf("parse_config test 7 - Invalid location_distribution continent code: ");
    func_rtn_val=parse_config(my_airports, "./test/data/7.cfg", my_state);
    if(func_rtn_val==CONFIG_DISTRIBUTION_ERROR){
        printf("PASSED\n");
    }else{
        printf("FAILED Expected CONFIG_DISTRIBUTION_ERROR, recieved %d\n",func_rtn_val);
        rtn_val=-1;
    }
    
    printf("parse_config test 8 - Invalid location_distribution sum: ");
    func_rtn_val=parse_config(my_airports, "./test/data/8.cfg", my_state);
    if(func_rtn_val==CONFIG_DISTRIBUTION_ERROR){
        printf("PASSED\n");
    }else{
        printf("FAILED Expected CONFIG_DISTRIBUTION_ERROR, recieved %d\n",func_rtn_val);
        rtn_val=-1;
    }
    
    printf("parse_config test 9 - Invalid connections list: ");
    func_rtn_val=parse_config(my_airports, "./test/data/9.cfg", my_state);
    if(func_rtn_val==CONFIG_BASE_ERROR){
        printf("PASSED\n");
    }else{
        printf("FAILED Expected CONFIG_BASE_ERROR, recieved %d\n",func_rtn_val);
        rtn_val=-1;
    }
    
    printf("parse_config test 10 - Valid config file: ");
    func_rtn_val=parse_config(my_airports, "./test/data/10.cfg", my_state);
    if(func_rtn_val==CONFIG_OK && my_state->num_locations==14 && my_state->num_scenarios==10 && my_sizes->locations==4){
        printf("PASSED\n");
    }else{
        printf("FAILED Expected CONFIG_OK, recieved %d\n",func_rtn_val);
        rtn_val=-1;
    }
    
    printf("parse_config test 11 - Default values: ");
    func_rtn_val=parse_config(my_airports, "./test/data/blank.cfg", my_state);
    if(func_rtn_val==CONFIG_OK && my_state->num_locations==7 && my_state->num_scenarios==3 && my_sizes->locations==2){
        printf("PASSED\n");
    }else{
        printf("FAILED Expected CONFIG_OK, recieved %d\n",func_rtn_val);
        rtn_val=-1;
    }    

    #ifdef DEBUG_ENABLED
    print_state(my_state);
    #endif

    free(my_sizes);
    free(my_state);
    free(my_airports);

    my_sizes=NULL;

    return rtn_val;
}