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
    
    //printf("=== Paths (%d) ===\n",my_sizes->paths);
    
    char string[1000];
    for(int print=0;print<my_sizes->paths;print++) {
        //printf("0/1 %d %d %d %0.5f %0.5f %d\n",my_paths[print].source_location,my_paths[print].dest_location,my_paths[print].next_location,my_paths[print].next_lat,my_paths[print].next_long,my_paths[print].aircraft_type);        
        snprintf(string, sizeof(string), "0/1 %d %d %d %0.5f %0.5f %d\n",my_paths[print].source_location,my_paths[print].dest_location,my_paths[print].next_location,my_paths[print].next_lat,my_paths[print].next_long,my_paths[print].aircraft_type);
        /* Write data to file */
        fputs(string, fPtr);
    }

    /* Close file to save file data */
    fclose(fPtr);

    /* Success message */
    //printf("Text File created and saved successfully. :) \n");

    return 0;
   
   }




void create_port_data(FILE *fb)
{
        fprintf (fb, "<ports>\n");
		fprintf (fb, "<port type=\"in\" name=\"LOC_InputLoads\" message_type=\"oLoad\"></port>\n");
		fprintf (fb, "<port type=\"in\" name=\"LOC_InputACStatus\" message_type=\"oAircraftStatus\"></port>\n");
		fprintf (fb, "<port type=\"in\" name=\"LOC_InputPallets\" message_type=\"oPallet\"></port>\n");
		fprintf (fb, "<port type=\"in\" name=\"LOC_InputLocInfo\" message_type=\"oLocInfo\"></port>\n");
		fprintf (fb, "<port type=\"out\" name=\"LOC_outLoads\" message_type=\"oLoad\"></port>\n");
 		fprintf (fb, "<port type=\"out\" name=\"LOC_outPallets\" message_type=\"oPallet\"></port>\n");
        fprintf (fb, "</ports>\n");
}


void create_component_data(FILE *fb, struct STATE *my_state)
{
        fprintf(fb, "<submodel type=\"atomic\" name=\"<11>\" class_name=\"Location\" xml_implementation=\"Location.devs\">\n");
		fprintf(fb, "<param type=\"int\" name=\"iLocID\" value=\"<11>\" />\n");
		fprintf(fb, "<param type=\"string\" name=\"sLocName\" value=\"&quot;<11>&quot;\" />\n");
		fprintf(fb, "<param type=\"double\" name=\"lat\" value=\"<11>\" />\n");
		fprintf(fb, "<param type=\"double\" name=\"long\" value=\"<11>\" />\n");
		fprintf(fb, "</submodel>\n");
}



 //To export path in a xml file
int export_xml(struct STATE *my_state, char *output_file)
 {
FILE *fb=fopen(output_file,"a");
//struct my_data testData = {32,"Mr.32"};
fprintf ( fb,"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
fprintf ( fb, "<coupledModel name=\"Locations\">\n");
//fprintf ( fb, "</coupledModel>\n");
create_port_data(fb);
fprintf ( fb, "<components>\n");

for(int airport = 0; airport<my_sizes->locations; airport++)
{
create_component_data(fb, my_state);
}

return 0;
 }