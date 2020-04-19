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

int integrated_test(void) {    
    int rtn_val=0;                                       // The current state of the function to return
    
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

/*
    NOTE: The following lines of code will be uncommented once Lukeman's export function is complete.

    if(rtn_val==0 && export(my_state, my_paths,"./test/output/")!=0) {
            rtn_val=-5;
    }

    if(rtn_val==0)
    {
        FILE *output_returned_xml;
        FILE *expected_output_xml;
        FILE *output_returned_txt;
        FILE *expected_output_txt;
        
        char curr_line_returned_xml[MAX_LINE_LENGTH];
        char curr_line_expected_xml[MAX_LINE_LENGTH];
        
        char curr_line_returned_txt[MAX_LINE_LENGTH];
        char curr_line_expected_txt[MAX_LINE_LENGTH];
        
        char* location_file = "./test/output/Locations.xml";
        char* location_file_correct = "./test/data/Locations_correct.xml";
        char* locinfo_file = "./test/output/LocInfo.txt";
        char* locinfo_file_correct = "./test/data/LocInfo_correct.txt";

        int fail_xml = 0;
        int fail_txt = 0;

        output_returned_xml = fopen(location_file, "r");
        expected_output_xml= fopen(location_file_correct, "r");

        output_returned_txt = fopen(locinfo_file, "r");
        expected_output_txt = fopen(locinfo_file_correct, "r");
        
        if (output_returned_xml == NULL|| expected_output_xml == NULL){
            printf("Could not openone of the xml files");
            rtn_val= -5;
        }
        
        if (output_returned_txt == NULL|| expected_output_txt == NULL){
            printf("Could not openone of the LocInfo files");
            rtn_val= -6;
        }
        
        while (fgets(curr_line_returned_xml, MAX_LINE_LENGTH, output_returned_xml) != NULL){
            if(fgets(curr_line_expected_xml, MAX_LINE_LENGTH, expected_output_xml)!= NULL){
                if (strcmp(curr_line_returned_xml,curr_line_expected_xml)!=0){
                    fail_xml++;
                }
            }
        }
        
        while (fgets(curr_line_returned_txt, MAX_LINE_LENGTH, output_returned_txt) != NULL){
            if(fgets(curr_line_expected_txt, MAX_LINE_LENGTH, expected_output_txt)!= NULL){
                if (strcmp(curr_line_returned_txt,curr_line_expected_txt)!=0){
                    fail_txt++;
                }
            }
        }
        
        if(fail_xml==0 && fail_txt ==0){
            rtn_val = 0;
        }else{
            rtn_val = -7;
        }

        fclose(output_returned_xml);
        fclose(expected_output_xml);
        fclose(output_returned_txt);
        fclose(expected_output_txt);
    }
*/
        
    free(my_sizes);
    free(my_state);
    free(my_airports);
    free(my_paths);
    
    return rtn_val;
}


