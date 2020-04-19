/**
 * @file export_test.c
 * @author Rob Barwell, Lukeman Hakkim Sheik Alavudeen
 * @date 16 Apr 2020, Last updated 18 Apr 2020
 * @brief This file contains all functions to run the export_test unit tests.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/data_types.h"
#include "../../include/common_functions.h"
#include "../../include/strat_airlift_functions.h"
#include "../include/calc_shortest_path_test.h"


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

    /* Testcase to test the export function */
    char* output_directory = "./test/output/";
    if (export(my_state, my_paths, output_directory)!=0){
       rtn_val=-2;
      }


    /* To test the file existence in the directory*/

    int dir_status;
    const char* text_filename = "LocInfo.txt";
    const char* xml_filename = "Locations.xml";
    char* dir_with_textfile;
    char* dir_with_xmlfile;

    /*To check if the directory exists, if not create a new directory*/

    dir_status = mkdir(output_directory, 0777);

    /*To construct the directory structure with static file names (LocInfo.txt and Locations.xml)*/

    dir_with_textfile = malloc(strlen(output_directory)+20);
    dir_with_xmlfile = malloc(strlen(output_directory)+20);

    strcpy(dir_with_textfile, output_directory);
    strcat(dir_with_textfile, text_filename);

    strcpy(dir_with_xmlfile, output_directory);
    strcat(dir_with_xmlfile, xml_filename);
  

    /* Testcase to test the text file existence in the directory*/
    FILE *fptr = fopen(dir_with_textfile, "r");
    if (fptr == NULL)
        rtn_val = -3;
    fclose(fptr);

    
    /* Testcase to test the xml file existence in the directory*/
    FILE *fptr1 = fopen(dir_with_xmlfile, "r");
    if (fptr1 == NULL)
        rtn_val = -4;
    fclose(fptr1);


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
                
        if(fail_txt ==0){
            rtn_val = 0;
        }else{
            rtn_val = -7;
        }

        /*if(fail_xml==0 && fail_txt ==0){
            rtn_val = 0;
        }else{
            rtn_val = -7;
        }*/

        fclose(output_returned_xml);
        fclose(expected_output_xml);
        fclose(output_returned_txt);
        fclose(expected_output_txt);
    }

    free(my_sizes);
    free(my_state);
    free(my_airports);
    free(my_paths);

    my_sizes=NULL;
    
    return rtn_val;
}