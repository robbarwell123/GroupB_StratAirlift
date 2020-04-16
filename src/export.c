#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../include/data_types.h"
#include "../include/common_functions.h"

//To export path in a text file

 int export_text(struct PATH *my_paths, char *output_file)
   {

    /* File pointer to hold reference to our file */
    FILE * fPtr;

    /* Open file in append mode */
    fPtr = fopen(output_file, "w");


    /* fopen() return NULL if last operation was unsuccessful */
    if(fPtr == NULL)
    {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }
    
    printf("=== Paths (%d) ===\n",my_sizes->paths);
    
    for(int print=0;print<my_sizes->paths;print++) {
        printf("0/1 %d %d %d %0.5f %0.5f %d\n",my_paths[print].source_location,my_paths[print].dest_location,my_paths[print].next_location,my_paths[print].next_lat,my_paths[print].next_long,my_paths[print].aircraft_type);        
    }
  
    /* Write data to file */
    fputs("Hi", fPtr);

    /* Close file to save file data */
    fclose(fPtr);

    /* Success message */
    printf("File created and saved successfully. :) \n");

      
   // for(int print_loc=0;print_loc<my_state->num_locations;print_loc++){
        //printf("%d,%s,%f,%f\n",print_loc,my_state->airport_list[print_loc]->name,my_state->airport_list[print_loc]->lat,my_state->airport_list[print_loc]->lon);
      //  }
        printf("Inside the the export file testcase - 3");
       // print_paths(my_paths);

    return 0;
   
   }


 //To export path in a xml file
 int export_xml(struct PATH *my_path, char *output_file)
 {

 return 0;
 }