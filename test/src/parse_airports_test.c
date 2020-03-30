#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../../include/data_types.h"
#include "../../include/common_functions.h"
#include "../../include/strat_airlift_functions.h"

int parse_airports_test(){
    int rtn_val=0;                                      // The current state of the function to return
    int test_val=0;                                     // Keep track of the number of airports read in
    
    my_sizes=malloc(sizeof(struct SIZES));
    for(int init=0;init<7;init++)
    {
        my_sizes->cont[init]=0;
    }
    
    struct AIRPORT **my_airports;
    my_airports=(struct AIRPORT**)malloc(sizeof(struct AIRPORT*)*7);
    for(int init=0;init<7;init++){
        my_airports[init]=NULL;
    }
    
    printf("parse_airports test 1 - airport file doesn't exist: ");
    if(parse_airports("garbage.txt",my_airports)==-1){
        printf("PASSED\n");
    }else {
        printf("FAILS (Expected error code -1 file doesn't exist.  Recieved 0 passed code.)\n");
    }

    printf("parse_airports test 2 - airport file with different length rows: ");
    if(parse_airports("./test/data/airports_diff_sizes.csv",my_airports)==0){
        for(int count=0;count<7;count++) {
            test_val+=my_sizes->cont[count];
        }
        if(test_val==0) {
            printf("PASSED\n");
        }else{
            printf("FAILS (Expected 0 records read.  Recieved %d records.)\n",test_val);
        }
    }else {
        printf("FAILS unexpected error.\n");
    }
    
    printf("parse_airports test 3 - airport file with known number of airports: ");
    if(parse_airports("./test/data/airports_known_number.csv",my_airports)==0){
        for(int count=0;count<7;count++) {
            test_val+=my_sizes->cont[count];
        }
        if(test_val==11) {
            printf("PASSED\n");
        }else{
            printf("FAILS (Expected 11 records read.  Recieved %d records.)\n",test_val);
        }
    }else {
        printf("FAILS unexpected error.\n");
    }

    free(my_airports);
    free(my_sizes);
    
    return rtn_val;
}

