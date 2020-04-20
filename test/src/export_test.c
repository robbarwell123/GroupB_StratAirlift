/**
 * @file export_test.c
 * @author Lukeman Hakkim Sheik Alavudeen
 * @date 16 Apr 2020, Last updated 20 Apr 2020
 * @brief This file contains all functions to run the export_test unit tests.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../../include/data_types.h"
#include "../../include/common_functions.h"
#include "../../include/strat_airlift_functions.h"
#include "../include/common_test_functions.h"

int export_test() {
    int rtn_val=0;                                      // The current state of the function to return

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

    my_airports=set_test_airports();
    set_test_state(my_airports,my_state);

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
    if(rtn_val==0 && export(my_state, my_paths, output_directory)!=0){
       rtn_val=-2;
    }

    int dir_status;
    const char* text_filename = "LocInfo.txt";
    const char* xml_filename = "Locations.xml";
    char* dir_with_textfile;
    char* dir_with_xmlfile;

    /*To create a new directory*/
    dir_status = mkdir(output_directory, 0777);

    /*To construct the directory structure with static file names (LocInfo.txt and Locations.xml)*/
    dir_with_textfile = malloc(strlen(output_directory)+20);
    dir_with_xmlfile = malloc(strlen(output_directory)+20);

    strcpy(dir_with_textfile, output_directory);
    strcat(dir_with_textfile, text_filename);

    strcpy(dir_with_xmlfile, output_directory);
    strcat(dir_with_xmlfile, xml_filename);
  
    printf("export_test test 1 - check existence of the generated text file: ");
    FILE *text_file = fopen(dir_with_textfile, "r");
    if (text_file == NULL) {
        rtn_val = -3;
        printf("FAILED Expected file ./test/output/LocInfo.txt, file does not exist.\n");        
    }else{
        printf("PASSED\n");
    }
    fclose(text_file);
    
    printf("export_test test 2 - check existence of the generated xml file: ");
    FILE *xml_file = fopen(dir_with_xmlfile, "r");
    if (xml_file == NULL){
        rtn_val = -4;
        printf("FAILED Expected file ./test/output/Locations.xml, file does not exist.\n");        
    }else{
        printf("PASSED\n");
    }
    fclose(xml_file);
    
    if(rtn_val==0)
    {
        FILE *output_returned_xml;
        FILE *expected_output_xml;
        FILE *output_returned_txt;
        FILE *expected_output_txt;

        char* location_file = "./test/output/Locations.xml";
        char* location_file_correct = "./test/data/Locations_correct.xml";
        char* locinfo_file = "./test/output/LocInfo.txt";
        char* locinfo_file_correct = "./test/data/LocInfo_correct.txt";

        output_returned_xml = fopen(location_file, "r");
        expected_output_xml= fopen(location_file_correct, "r");
        output_returned_txt = fopen(locinfo_file, "r");
        expected_output_txt = fopen(locinfo_file_correct, "r");
            
        printf("export_test test 3 - comparison of generated text file: ");
        if (output_returned_txt == NULL|| expected_output_txt == NULL){
            rtn_val= -5;
            printf("FAILED Unable to open ./test/output/LocInfo.xml or ./test/data/LocInfo_correct.txt.\n");        
        }else{
            int txt_err_count = compare_files(output_returned_txt, expected_output_txt);
            if(txt_err_count==0){
                printf("PASSED\n");
            }else{
                rtn_val= -7;
                printf("FAILED ./test/output/LocInfo.txt is different from correct version ./test/data/LocInfo_correct.txt.\n");        
            }
        }

        printf("export_test test 4 - comparison of generated xml file: ");
        if (output_returned_xml == NULL|| expected_output_xml == NULL){
            rtn_val= -8;
            printf("FAILED Unable to open ./test/output/Locations.xml or ./test/data/Locations.xml.\n");        
        }else{
            int xml_err_count = compare_files(output_returned_xml, expected_output_xml);
            if(xml_err_count==0){
                printf("PASSED\n");
            }else{
                rtn_val= -9;
                printf("FAILED ./test/output/Locations.xml is different from correct version ./test/data/Locations.xml.\n");        
            }
        }
        
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