#include <stdio.h>
#include <stdlib.h>

#include "../include/data_types.h"
#include "../include/common_functions.h"
#include "../include/parse_config.h"

// Defined in the main.c file
extern struct SIZES *my_sizes;

int parse_scenario_number(char *input_line, struct STATE *my_state) {
    my_state->num_scenarios=3;
    return 0;
}

int parse_location_number(char *input_line, struct STATE *my_state) {
    my_state->num_locations=7;
    return 0;
}

int parse_distribution(char *input_line, struct STATE *my_state) {
    my_state->dist_locations[AF]=0.142857143;
    my_state->dist_locations[AN]=0.142857143;
    my_state->dist_locations[AS]=0.142857143;
    my_state->dist_locations[EU]=0.142857143;
    my_state->dist_locations[NA]=0.142857143;
    my_state->dist_locations[OC]=0.142857143;
    my_state->dist_locations[SA]=0.142857143;
    return 0;
}

int parse_base(char *input_line, struct AIRPORT **my_airports, struct STATE *my_state) {
        
    my_state->airport_list=(struct AIRPORT**)malloc(sizeof(struct AIRPORT*)*2);

    my_state->airport_list[0]=find_airport("CYTZ",my_airports);
    my_state->airport_list[1]=find_airport("EDDK",my_airports);
    
    my_state->distance_matrix=(int**)malloc(sizeof(int*)*2);
    for(int init=0;init<2;init++) {
        my_state->distance_matrix[init]=(int*)malloc(sizeof(int)*2);
        for(int zero=0;zero<2;zero++) {
            my_state->distance_matrix[init][zero]=0;
        }
    }
    
    my_state->distance_matrix[0][1]=calc_distance(my_state->airport_list[0]->lat,my_state->airport_list[0]->lon,my_state->airport_list[1]->lat,my_state->airport_list[1]->lon);
    my_state->distance_matrix[1][0]=calc_distance(my_state->airport_list[1]->lat,my_state->airport_list[1]->lon,my_state->airport_list[0]->lat,my_state->airport_list[0]->lon);
    
    my_state->num_main_bases=2;
    my_sizes->locations=2;
    
    return 0;
}

int parse_config(struct AIRPORT **my_airports, char *config_file, struct STATE *my_state) {

    char *input_line="";
    int result;

    result=parse_scenario_number(input_line,my_state);
    result=parse_location_number(input_line,my_state);
    result=parse_distribution(input_line,my_state);
    result=parse_base(input_line,my_airports,my_state);
        
    return 0;
}
