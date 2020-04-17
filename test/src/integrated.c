/**
 * @file integrated.c
 * @author Olumide Akinola
 * @date 13 Apr 2020
 * @brief This file contains all functions to run the integrated tests.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/data_types.h"
#include "../../include/common_functions.h"
#include "../../include/strat_airlift_functions.h"
#include "../include/strat_airlift_functions_tests.h"


/**
 * @brief my_sizes is used to store the sizes of the dynamic arrays used throughout the program.
 */
struct SIZES *my_sizes;

int integrated_test(void) {
    int rtn_val=0;                                      // The current state of the function to return
    
    my_sizes=malloc(sizeof(struct SIZES));
    for(int init=0;init<7;init++){
            my_sizes->cont[init]=0;
    }
    my_sizes->locations=0;
    my_sizes->paths=0;

    /* Creates the initial structures which will be used for all function calls. */
    struct STATE *my_state=malloc(sizeof(struct STATE));
    struct AIRPORT **my_airports;
    my_airports=(struct AIRPORT**)malloc(sizeof(struct AIRPORT*)*7);
    for(int init=0;init<7;init++){
            my_airports[init]=NULL;
    }
    struct PATH *my_paths=NULL;

    if(rtn_val==0 && parse_airports("./data/airports.csv",my_airports)) {
            rtn_val=-1;
    }

    printf("Airports per Continent\n");
    for(int print_size=0;print_size<7;print_size++) {
        printf("Continent %d Airports: %d\n",print_size,my_sizes->cont[print_size]);
    }

        
    /* Release 1 of parse_config uses the default values specified in the requirements document. */
    if(rtn_val==0 && parse_config(my_airports,"./data/blank.cfg", my_state)!=0) {
            rtn_val=-2;
    }
        

    my_state->airport_list=(struct AIRPORT**)realloc(my_state->airport_list,sizeof(struct AIRPORT*)*9);

    my_state->airport_list[2]=find_airport("DAOF",my_airports);
    my_state->airport_list[3]=find_airport("EFPO",my_airports);
    my_state->airport_list[4]=find_airport("FAVR",my_airports);
    my_state->airport_list[5]=find_airport("KNKT",my_airports);
    my_state->airport_list[6]=find_airport("SJTC",my_airports);
    my_state->airport_list[7]=find_airport("SPST",my_airports);
    my_state->airport_list[8]=find_airport("SPQT",my_airports);
    my_sizes->locations=9;

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
        
    if(rtn_val==0 && find_closest(my_state)!=0) {
            rtn_val=-3;
    }

    if(rtn_val==0 && calc_shortest_path(my_state, &my_paths)!=0) {
            rtn_val=-4;
    }

    FILE *fp;
    FILE *fp2;
    char str[1000];
    char str2[1000];
    char* filename = "./data/Locationstxt.xml";
    char* filename2 = "./data/Locationstxt_copy.xml";
    int fail = 0;
    
    fp = fopen(filename, "r");
    fp2= fopen(filename2, "r");
    if (fp == NULL|| fp2 == NULL){
        printf("Could not open file %s",filename);
        rtn_val= -5;
        return rtn_val;
    }
    while (fgets(str, 1000, fp) != NULL && fgets(str2, 1000, fp2) != NULL){
        if (strcmp(str,str2)!=0){
            fail++;
        }
        
    }
    if(fail==0){
        rtn_val = 0;
    }else{
        rtn_val = -6;
    }
       
    fclose(fp);
    fclose(fp2);
        

        
    free(my_sizes);
    free(my_state);
    free(my_airports);
    free(my_paths);
    
    return rtn_val;
}


