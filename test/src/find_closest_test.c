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
#include "../include/calc_shortest_path_test.h"

// Defined in the test_main.c file
extern struct SIZES *my_sizes;

struct AIRPORT** set_airports() {
    struct AIRPORT **temp_airports;
    
    temp_airports=(struct AIRPORT**)malloc(sizeof(struct AIRPORT*)*7);
    for(int init=0;init<7;init++)
    {
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

void set_state(struct AIRPORT** my_airports,struct STATE *my_state)
{
    parse_config(my_airports, "", my_state);
    
    my_state->airport_list=(struct AIRPORT**)realloc(my_state->airport_list,sizeof(struct AIRPORT*)*5);

    my_state->airport_list[2]=find_airport("EGPF",my_airports);
    my_state->airport_list[3]=find_airport("HKJK",my_airports);
    my_state->airport_list[4]=find_airport("SKBO",my_airports);
    my_sizes->locations=5;
    
    my_state->distance_matrix=(int**)realloc(my_state->distance_matrix,sizeof(int*)*my_sizes->locations);
    for(int source=0;source<my_sizes->locations;source++) {
        my_state->distance_matrix[source]=(int*)realloc(my_state->distance_matrix[source],sizeof(int)*my_sizes->locations);
        for(int dest=0;dest<my_sizes->locations;dest++) {
            my_state->distance_matrix[source][dest]=0;
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


int find_closest_test() {
    int rtn_val=0;                                      // The current state of the function to return

     /* Creates the initial structures which will be used for all function calls. */
    struct STATE *my_state=malloc(sizeof(struct STATE));
    struct AIRPORT **my_airports;
    struct PATH *my_paths=NULL;

    free(my_sizes);
    /* Initalizes my_sizes to 0 for all dynamic arrays. */
    my_sizes=malloc(sizeof(struct SIZES));
    for(int init=0;init<7;init++)
    {
        my_sizes->cont[init]=0;
    }
    my_sizes->locations=0;
    my_sizes->paths=0;

    my_airports=set_airports();
    set_state(my_airports,my_state);


    //if(find_closest()!=0) {
   //     rtn_val=-1;
   // }

    return rtn_val;
}