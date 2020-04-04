#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../include/data_types.h"
#include "../include/common_functions.h"

int find_closest(struct STATE *my_state){
    int rtn_val=0;                                      // The current state of the function to return
    int closest_distance;                               // The current best distance between a random location and main base
    int closest_index;                                  // The current best main base to attach the random location to
    int main_base;                                      // The main base for loop index
    int distance;                                       // Result of the distance calculations
    
    for(int gen_loc=my_state->num_main_bases;gen_loc<my_sizes->locations;gen_loc++){
        closest_distance=INT_MAX;
        closest_index=-1;
        for(main_base=0;main_base<my_state->num_main_bases;main_base++){
            distance=calc_distance(my_state->airport_list[gen_loc]->lat,my_state->airport_list[gen_loc]->lon,my_state->airport_list[main_base]->lat,my_state->airport_list[main_base]->lon);
            if(distance<closest_distance){
                closest_distance=distance;
                closest_index=main_base;
            }
        }
        if(closest_index!=-1){
            distance=calc_distance(my_state->airport_list[gen_loc]->lat,my_state->airport_list[gen_loc]->lon,my_state->airport_list[closest_index]->lat,my_state->airport_list[closest_index]->lon);            
            my_state->distance_matrix[gen_loc][closest_index]=distance;
            my_state->distance_matrix[closest_index][gen_loc]=distance;
        }else{
            printf("Error could not find a closest node for %s.\n",my_state->airport_list[gen_loc]->name);
            rtn_val=-1;
        }
    }
    
    return rtn_val;
}