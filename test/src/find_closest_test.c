/**
 * @file find_closest_test.c
 * @author Lukman Hakkim Sheik Alavudeen, Rob Barwell
 * @date 03 Apr 2020, Last updated 4 Apr 2020
 * @brief This file contains all functions to run the find_closest unit tests.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/data_types.h"
#include "../../include/common_functions.h"
#include "../../include/strat_airlift_functions.h"
#include "../include/find_closest_test.h"

struct AIRPORT** find_closest_test_set_airports() {
    struct AIRPORT **temp_airports;
    
    temp_airports=(struct AIRPORT**)malloc(sizeof(struct AIRPORT*)*7);
    for(int init=0;init<7;init++) {
        temp_airports[init]=NULL;
    }
    
    temp_airports[NA]=(struct AIRPORT*)malloc(sizeof(struct AIRPORT));
    temp_airports[EU]=(struct AIRPORT*)malloc(sizeof(struct AIRPORT)*2);
    temp_airports[AF]=(struct AIRPORT*)malloc(sizeof(struct AIRPORT));
    temp_airports[SA]=(struct AIRPORT*)malloc(sizeof(struct AIRPORT));
    
    temp_airports[NA][0].id="CYTR";
    temp_airports[NA][0].name="CFB Trenton";
    temp_airports[NA][0].lat=44.1189003;
    temp_airports[NA][0].lon=-77.52809906;
    temp_airports[NA][0].cont="NA";
    temp_airports[NA][0].country="CA";  

    temp_airports[EU][0].id="EDDK";
    temp_airports[EU][0].name="Cologne Bonn Airport";
    temp_airports[EU][0].lat=50.86589813;
    temp_airports[EU][0].lon=7.142739773;
    temp_airports[EU][0].cont="EU";
    temp_airports[EU][0].country="DE";  

    temp_airports[EU][1].id="EGPF";
    temp_airports[EU][1].name="Glasgow International Airport";
    temp_airports[EU][1].lat=55.871899;
    temp_airports[EU][1].lon=-4.43306;
    temp_airports[EU][1].cont="EU";
    temp_airports[EU][1].country="GB";  

    temp_airports[AF][0].id="HKJK";
    temp_airports[AF][0].name="Jomo Kenyatta International Airport";
    temp_airports[AF][0].lat=-1.319239974;
    temp_airports[AF][0].lon=36.92779922;
    temp_airports[AF][0].cont="AF";
    temp_airports[AF][0].country="KE";  

    temp_airports[SA][0].id="SKBO";
    temp_airports[SA][0].name="El Dorado International Airport";
    temp_airports[SA][0].lat=4.70159;
    temp_airports[SA][0].lon=-74.1469;
    temp_airports[SA][0].cont="SA";
    temp_airports[SA][0].country="CO";  
    
    my_sizes->cont[NA]=1;
    my_sizes->cont[EU]=2;
    my_sizes->cont[AF]=1;
    my_sizes->cont[SA]=1;
    
    return temp_airports;
}

void find_closest_test_set_state(struct AIRPORT** my_airports,struct STATE *my_state) {
    parse_config(my_airports, "./data/blank.cfg", my_state);
    
    my_state->airport_list=(struct AIRPORT**)realloc(my_state->airport_list,sizeof(struct AIRPORT*)*5);

    my_state->airport_list[2]=find_airport("EGPF",my_airports);
    my_state->airport_list[3]=find_airport("HKJK",my_airports);
    my_state->airport_list[4]=find_airport("SKBO",my_airports);
    my_sizes->locations=5;    
    
    my_state->distance_matrix=(int**)realloc(my_state->distance_matrix,sizeof(int*)*my_sizes->locations);
    for(int source=0;source<my_sizes->locations;source++) {
        if(source<my_state->num_main_bases){
            my_state->distance_matrix[source]=(int*)realloc(my_state->distance_matrix[source],sizeof(int)*my_sizes->locations);
            for(int dest=my_state->num_main_bases;dest<my_sizes->locations;dest++) {
                my_state->distance_matrix[source][dest]=0;
            }
        }else{
            my_state->distance_matrix[source]=(int*)calloc(my_sizes->locations,sizeof(int));
        }
    }    
}

int find_closest_test() {
    int rtn_val=0;                                      // The current state of the function to return

    int correct_matrix[5][5]={0,6049,0,0,4395,6049,0,946,6450,0,0,946,0,0,0,0,6450,0,0,0,4395,0,0,0,0};

    /* Creates the initial structures which will be used for all function calls. */
    struct STATE *my_state=malloc(sizeof(struct STATE));
    struct AIRPORT **my_airports;

    free(my_sizes);
    /* Initalizes my_sizes to 0 for all dynamic arrays. */
    my_sizes=malloc(sizeof(struct SIZES));
    for(int init=0;init<7;init++){
        my_sizes->cont[init]=0;
    }
    my_sizes->locations=0;
    my_sizes->paths=0;

    my_airports=find_closest_test_set_airports();
    find_closest_test_set_state(my_airports,my_state);
    
    #ifdef DEBUG_ENABLED
    print_state(my_state);
    #endif

    if(find_closest(my_state)!=0) {
        rtn_val=-1;
    }

    for(int check_row=0;check_row<5;check_row++){
        for(int check_col=0;check_col<5;check_col++){
            if(my_state->distance_matrix[check_row][check_col]!=correct_matrix[check_row][check_col]){
                printf("Expected value: %d in row %d col %d, got value %d instead.\n",correct_matrix[check_row][check_col],check_row,check_col,my_state->distance_matrix[check_row][check_col]);
                rtn_val=-1;
            }
        }
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