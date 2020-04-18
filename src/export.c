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


int create_port_data(FILE *fb)
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

int create_component_data(FILE *fb, struct STATE *my_state, int air_count)
{
        fprintf(fb, "<submodel type=\"atomic\" name=\"%s\" class_name=\"Location\" xml_implementation=\"Location.devs\">\n", my_state->airport_list[air_count]->id);
		fprintf(fb, "<param type=\"int\" name=\"iLocID\" value=\"%d\" />\n", air_count);
		fprintf(fb, "<param type=\"string\" name=\"sLocName\" value=\"&quot;%s&quot;\" />\n", my_state->airport_list[air_count]->name);
		fprintf(fb, "<param type=\"double\" name=\"lat\" value=\"%0.4f\" />\n", my_state->airport_list[air_count]->lat);
		fprintf(fb, "<param type=\"double\" name=\"long\" value=\"%0.4f\" />\n", my_state->airport_list[air_count]->lon);
		fprintf(fb, "</submodel>\n");
}

int create_connection_eic_data(FILE *fb, struct STATE *my_state, int air_count)
{
    fprintf(fb, "<eic in_port_coupled=\"LOC_InputLoads\" submodel=\"%s\" in_port_submodel=\"Locations_defs::inLoads\" />\n", my_state->airport_list[air_count]->id);
    fprintf(fb, "<eic in_port_coupled=\"LOC_InputACStatus\" submodel=\"%s\" in_port_submodel=\"Locations_defs::inACStatus\" />\n", my_state->airport_list[air_count]->id);
	fprintf(fb, "<eic in_port_coupled=\"LOC_InputPallets\" submodel=\"%s\" in_port_submodel=\"Locations_defs::inPallets\" />\n", my_state->airport_list[air_count]->id);
	fprintf(fb, "<eic in_port_coupled=\"LOC_InputLocInfo\" submodel=\"%s\" in_port_submodel=\"Locations_defs::inLocInfo\" />\n", my_state->airport_list[air_count]->id);
}

int create_connection_eoc_data(FILE *fb, struct STATE *my_state, int air_count)
{ 
	fprintf(fb, "<eoc submodel=\"%s\" out_port_submodel=\"Locations_defs::outLoads\" out_port_coupled=\"LOC_outLoads\" />\n", my_state->airport_list[air_count]->id);		
	fprintf(fb, "<eoc submodel=\"%s\" out_port_submodel=\"Locations_defs::outPallets\" out_port_coupled=\"LOC_outPallets\" />\n", my_state->airport_list[air_count]->id); 
}


//To export path in a xml file
int export_xml(struct STATE *my_state, char *output_file)
 {
FILE *fb=fopen(output_file,"a");

fprintf ( fb,"\n<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
fprintf ( fb, "\n<coupledModel name=\"Locations\">\n");
create_port_data(fb);


fprintf ( fb, "<components>\n");
for(int air_count = 0; air_count<my_sizes->locations; air_count++)
{
create_component_data(fb, my_state, air_count);
}
fprintf ( fb, "</components>\n");


fprintf ( fb, "<connections>\n");
for(int air_count = 0; air_count<my_sizes->locations; air_count++)
{
create_connection_eic_data(fb, my_state, air_count);
}
for(int air_count = 0; air_count<my_sizes->locations; air_count++)
{
create_connection_eoc_data(fb, my_state, air_count);
}
fprintf ( fb, "\n</connections>\n");
fprintf ( fb, "\n</coupledModel>\n");


return 0;
 }
