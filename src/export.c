#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>


#include "../include/data_types.h"
#include "../include/common_functions.h"

//int mkdir(const char *pathname, mode_t mode);

/*To generate the output text file for the strategic airlift simulator..*/

 int export_text(struct PATH *my_paths, char *output_file)
   {

    /* File pointer to hold reference to our file */
    FILE * fPtr;

    /* Open file in append mode */
    fPtr = fopen(output_file, "w");


    /* fopen() return NULL if last operation was unsuccessful */
    if(fPtr == NULL)
    {
        /* File not created hence return -1 */
        printf("Unable to create file.\n");
        return -1;
    }
    
    
    char string[1000];
    for(int print=0;print<my_sizes->paths;print++) {
        snprintf(string, sizeof(string), "0/1 %d %d %d %0.5f %0.5f %d\n",my_paths[print].source_location,my_paths[print].dest_location,my_paths[print].next_location,my_paths[print].next_lat,my_paths[print].next_long,my_paths[print].aircraft_type);
        /* Write data to file */
        fputs(string, fPtr);
    }

    /* Close file to save file data */
    fclose(fPtr);

    return 0;
   
   }


/* To write port data in a xml file */
void create_port_data(FILE *fb)
{
        fprintf (fb, "     <ports>\n");
		fprintf (fb, "              <port type=\"in\" name=\"LOC_InputLoads\" message_type=\"oLoad\"></port>\n");
		fprintf (fb, "              <port type=\"in\" name=\"LOC_InputACStatus\" message_type=\"oAircraftStatus\"></port>\n");
		fprintf (fb, "              <port type=\"in\" name=\"LOC_InputPallets\" message_type=\"oPallet\"></port>\n");
		fprintf (fb, "              <port type=\"in\" name=\"LOC_InputLocInfo\" message_type=\"oLocInfo\"></port>\n");
		fprintf (fb, "              <port type=\"out\" name=\"LOC_outLoads\" message_type=\"oLoad\"></port>\n");
 		fprintf (fb, "              <port type=\"out\" name=\"LOC_outPallets\" message_type=\"oPallet\"></port>\n");
        fprintf (fb, "     </ports>\n");
}

/* To write component data in a xml file */
void create_component_data(FILE *fb, struct STATE *my_state, int air_count)
{
        fprintf(fb, "               <submodel type=\"atomic\" name=\"%s\" class_name=\"Location\" xml_implementation=\"Location.devs\">\n", my_state->airport_list[air_count]->id);
		fprintf(fb, "                       <param type=\"int\" name=\"iLocID\" value=\"%d\" />\n", air_count);
		fprintf(fb, "                       <param type=\"string\" name=\"sLocName\" value=\"&quot;%s&quot;\" />\n", my_state->airport_list[air_count]->name);
		fprintf(fb, "                       <param type=\"double\" name=\"lat\" value=\"%0.4f\" />\n", my_state->airport_list[air_count]->lat);
		fprintf(fb, "                       <param type=\"double\" name=\"long\" value=\"%0.4f\" />\n", my_state->airport_list[air_count]->lon);
		fprintf(fb, "               </submodel>\n");
}

/* To write the connection eic data in a xml file */
void create_connection_eic_data(FILE *fb, struct STATE *my_state, int air_count)
{
    fprintf(fb, "               <eic in_port_coupled=\"LOC_InputLoads\" submodel=\"%s\" in_port_submodel=\"Locations_defs::inLoads\" />\n", my_state->airport_list[air_count]->id);
    fprintf(fb, "               <eic in_port_coupled=\"LOC_InputACStatus\" submodel=\"%s\" in_port_submodel=\"Locations_defs::inACStatus\" />\n", my_state->airport_list[air_count]->id);
	fprintf(fb, "               <eic in_port_coupled=\"LOC_InputPallets\" submodel=\"%s\" in_port_submodel=\"Locations_defs::inPallets\" />\n", my_state->airport_list[air_count]->id);
	fprintf(fb, "               <eic in_port_coupled=\"LOC_InputLocInfo\" submodel=\"%s\" in_port_submodel=\"Locations_defs::inLocInfo\" />\n", my_state->airport_list[air_count]->id);
}

/* To write the connection eoc data in a xml file */
void create_connection_eoc_data(FILE *fb, struct STATE *my_state, int air_count)
{ 
	fprintf(fb, "               <eoc submodel=\"%s\" out_port_submodel=\"Locations_defs::outLoads\" out_port_coupled=\"LOC_outLoads\" />\n", my_state->airport_list[air_count]->id);		
	fprintf(fb, "               <eoc submodel=\"%s\" out_port_submodel=\"Locations_defs::outPallets\" out_port_coupled=\"LOC_outPallets\" />\n", my_state->airport_list[air_count]->id); 
}


/* To generate the output xml file for the strategic airlift simulator.. */
int export_xml(struct STATE *my_state, char *output_file)
 {
FILE *fb=fopen(output_file,"w");

/* fopen() return NULL if last operation was unsuccessful */
    if(fb == NULL)
    {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        return -1;
    }

/*Root tag for the xml*/
fprintf ( fb,"\n<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
fprintf ( fb, "<coupledModel name=\"Locations\">\n");
create_port_data(fb);

/*child tag components data*/
fprintf ( fb, "     <components>\n");
for(int air_count = 0; air_count<my_sizes->locations; air_count++)
{
create_component_data(fb, my_state, air_count);
}
fprintf ( fb, "     </components>\n");

/*child tag connections with eic and eoc data*/
fprintf ( fb, "     <connections>\n");
for(int air_count = 0; air_count<my_sizes->locations; air_count++)
{
create_connection_eic_data(fb, my_state, air_count);
}
for(int air_count = 0; air_count<my_sizes->locations; air_count++)
{
create_connection_eoc_data(fb, my_state, air_count);
}
fprintf ( fb, "     </connections>\n");
fprintf ( fb, "</coupledModel>\n");

return 0;
 }



int export(struct STATE *my_state, struct PATH *my_paths, char *output_directory)
{

    int rtn_val = 0;
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
  
    /*To generate the LocInfo.txt file*/

     if(export_text(my_paths, dir_with_textfile)!=0){
            rtn_val = -1;
        }

    /*To generate the Locations.xml file*/
     if(export_xml(my_state, dir_with_xmlfile)!=0){
            rtn_val = -2;
     }

     return rtn_val;
}
