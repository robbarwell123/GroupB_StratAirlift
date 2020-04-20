#include <stdio.h>
#include <stdlib.h>

#include "../../include/data_types.h"
#include "../../include/common_functions.h"
#include "../../include/strat_airlift_functions.h"
#include "../../include/gen_locations.h"
#include "../include/gen_locations_test.h"

struct AIRPORT** set_gen_locations_airports() {
    struct AIRPORT **temp_airports;
    
    temp_airports=(struct AIRPORT**)malloc(sizeof(struct AIRPORT*)*7);
    for(int init=0;init<7;init++){
        temp_airports[init]=(struct AIRPORT*)malloc(sizeof(struct AIRPORT)*5);
        for(int fill=0;fill<5;fill++) {
            temp_airports[init][fill].id=calloc(10,sizeof(char));
            sprintf(temp_airports[init][fill].id,"ICAO %d",fill);
            temp_airports[init][fill].name=calloc(30,sizeof(char));
            sprintf(temp_airports[init][fill].name,"%s %d",continent_names[init],fill);
            temp_airports[init][fill].lat=44.0;
            temp_airports[init][fill].lon=-80.0;
            temp_airports[init][fill].cont="NA";
            temp_airports[init][fill].country="CA";  
        }
        my_sizes->cont[init]=5;
    }
    
    return temp_airports;
}

int gen_locations_test() {
    int rtn_val=0;                                      // The current state of the function to return
    
    /* Creates the initial structures which will be used for all function calls. */
    struct STATE *my_state=malloc(sizeof(struct STATE));
    struct AIRPORT **my_airports;

    if(!my_sizes){
        free(my_sizes);
    }
    /* Initalizes my_sizes to 0 for all dynamic arrays. */
    my_sizes=malloc(sizeof(struct SIZES));
    for(int init=0;init<7;init++){
        my_sizes->cont[init]=0;
    }
    my_sizes->locations=0;
    my_sizes->paths=0;

    my_airports=set_gen_locations_airports();
    my_state->dist_locations[AF]=0.142857143;
    my_state->dist_locations[AN]=0.142857143;
    my_state->dist_locations[AS]=0.142857143;
    my_state->dist_locations[EU]=0.142857143;
    my_state->dist_locations[NA]=0.142857143;
    my_state->dist_locations[OC]=0.142857143;
    my_state->dist_locations[SA]=0.142857143;
    my_state->num_locations=7;
    my_state->airport_list=NULL;
    
    printf("gen_locations test 1 - compare locations: ");
    if(gen_locations(my_airports, my_state)!=0) {
        rtn_val=-1;
    }
    if(my_sizes->locations==my_state->num_locations) {
        printf("PASSED\n");
    }else {
        printf("FAILS (Expected %d locations, generated %d locations)\n",my_state->num_locations,my_sizes->locations);
        rtn_val=-1;
    }
    
    printf("gen_locations test 2 - duplicate locations: ");
    int test_dup[]={5,10,2,3,6,7};
    if(check_used(6, 2,test_dup)==-1) {
        printf("PASSED\n");
    }else {
        printf("FAILS (Expected 2 to be duplicate in array [5,10,2,3,6,7])\n");
    }

    my_state->num_locations=50;
    printf("gen_locations test 3 - exceeds avaliable locations: ");
    if(gen_locations(my_airports, my_state)!=0) {
        printf("PASSED\n");
    }else {
        printf("FAILS (Expected gen_locations to throw error.  Instead recieved pass.)\n");
        rtn_val=-1;
    }    
        
    free(my_sizes);
    free(my_state);
    free(my_airports);

    my_sizes=NULL;
    
    return rtn_val;
}