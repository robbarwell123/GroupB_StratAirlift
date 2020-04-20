#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/data_types.h"
#include "../include/common_functions.h"
#include "../include/gen_locations.h"

int check_used(int curr_pos, int curr_rand,int* selected_airports) {
    int rtn_val=0;
    
    for(int check=0;check<curr_pos;check++) {
        if(curr_rand==selected_airports[check]) {
            rtn_val=-1;
            break;
        }
    }
    
    return rtn_val;
}

int gen_locations(struct AIRPORT **my_airports, struct STATE *my_state) {
    int rtn_val=0;                                      // The current state of the function to return    
    int num_to_gen;                                     // The number of locations to generate per continent
    int curr_rand;                                      // The current randomly selected location
    int* selected_airports;                             // List of selected airports
    int used;                                           // Whether the airport has been used or not
    
    srand(time(0));
    
    for(int curr_continent=0;curr_continent<7;curr_continent++) {
        num_to_gen=my_state->num_locations*my_state->dist_locations[curr_continent];

        if(num_to_gen>my_sizes->cont[curr_continent]) {
            printf("Not enough locations for continent %s\n",continent_names[curr_continent]);
            rtn_val=-1;
            break;
        }

        selected_airports=malloc(sizeof(int)*num_to_gen);
        for(int gen_loc=0;gen_loc<num_to_gen;gen_loc++) {
                do {
                    curr_rand=rand() % my_sizes->cont[curr_continent];
                    used=check_used(gen_loc,curr_rand,selected_airports);
                }while(used!=0);
                my_sizes->locations++;
                my_state->airport_list=(struct AIRPORT**)realloc(my_state->airport_list,sizeof(struct AIRPORT*)*my_sizes->locations); 
                if(my_state->airport_list!=NULL) {
                    my_state->airport_list[my_sizes->locations-1]=&my_airports[curr_continent][curr_rand];
                }
                selected_airports[gen_loc]=curr_rand;
        }
    }

    return rtn_val;
}
