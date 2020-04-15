/**
 * @file calc_shortest_path_test.c
 * @author Rob Barwell
 * @date 17 Mar 2020, Last updated 4 Apr 2020
 * @brief This file contains all functions to run the calc_shortest_path unit tests.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/data_types.h"
#include "../../include/common_functions.h"
#include "../../include/strat_airlift_functions.h"
#include "../include/calc_shortest_path_test.h"

struct AIRPORT** calc_shortest_path_test_set_airports() {
    struct AIRPORT **temp_airports;
    
    temp_airports=(struct AIRPORT**)malloc(sizeof(struct AIRPORT*)*7);
    for(int init=0;init<7;init++){
        temp_airports[init]=NULL;
    }
    
    temp_airports[NA]=(struct AIRPORT*)malloc(sizeof(struct AIRPORT));
    temp_airports[EU]=(struct AIRPORT*)malloc(sizeof(struct AIRPORT)*2);
    temp_airports[AF]=(struct AIRPORT*)malloc(sizeof(struct AIRPORT));
    temp_airports[SA]=(struct AIRPORT*)malloc(sizeof(struct AIRPORT));
    
    temp_airports[NA][0].id="CYTZ";
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

void calc_shortest_path_test_set_state(struct AIRPORT** my_airports,struct STATE *my_state){
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

    // Connection from CYTZ to EDDK
    my_state->distance_matrix[0][1]=calc_distance(my_state->airport_list[0]->lat,my_state->airport_list[0]->lon,my_state->airport_list[1]->lat,my_state->airport_list[1]->lon);
    my_state->distance_matrix[1][0]=calc_distance(my_state->airport_list[1]->lat,my_state->airport_list[1]->lon,my_state->airport_list[0]->lat,my_state->airport_list[0]->lon);

    // Connection from CYTZ to SKBO
    my_state->distance_matrix[0][4]=calc_distance(my_state->airport_list[0]->lat,my_state->airport_list[0]->lon,my_state->airport_list[4]->lat,my_state->airport_list[4]->lon);
    my_state->distance_matrix[4][0]=calc_distance(my_state->airport_list[4]->lat,my_state->airport_list[4]->lon,my_state->airport_list[0]->lat,my_state->airport_list[0]->lon);

    // Connection from EDDK to EGPF
    my_state->distance_matrix[1][2]=calc_distance(my_state->airport_list[1]->lat,my_state->airport_list[1]->lon,my_state->airport_list[2]->lat,my_state->airport_list[2]->lon);
    my_state->distance_matrix[2][1]=calc_distance(my_state->airport_list[2]->lat,my_state->airport_list[2]->lon,my_state->airport_list[1]->lat,my_state->airport_list[1]->lon);

    // Connection from EDDK to HKJK
    my_state->distance_matrix[1][3]=calc_distance(my_state->airport_list[1]->lat,my_state->airport_list[1]->lon,my_state->airport_list[3]->lat,my_state->airport_list[3]->lon);
    my_state->distance_matrix[3][1]=calc_distance(my_state->airport_list[3]->lat,my_state->airport_list[3]->lon,my_state->airport_list[1]->lat,my_state->airport_list[1]->lon);    
}

int export_test() {
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

    for(int compare=0;compare<my_sizes->paths;compare++) {
        sprintf(compare_to,"0/1 %d %d %d %0.5f %0.5f %d",my_paths[compare].source_location,my_paths[compare].dest_location,my_paths[compare].next_location,my_paths[compare].next_lat,my_paths[compare].next_long,my_paths[compare].aircraft_type);
        if(strcmp(valid_result[compare],compare_to)!=0) {
            printf("calc_shortest_path test failed on comparison: %d.\n",compare);
            rtn_val=-2;
        }
    }


    for(int print_loc=0;print_loc<my_state->num_locations;print_loc++){
        printf("%d,%s,%f,%f\n",print_loc,my_state->airport_list[print_loc]->name,my_state->airport_list[print_loc]->lat,my_state->airport_list[print_loc]->lon);
        }
        printf("Inside the the export file testcase - 3");
        print_paths(my_paths);


    free(my_sizes);
    free(my_state);
    free(my_airports);
    free(my_paths);

    my_sizes=NULL;
    
    return rtn_val;
}