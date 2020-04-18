#include "data_types.h"
#include <stdio.h>


/**
 * @brief generate the output text file for the strategic airlift simulator..
 *
 * 
 * @para, my_paths It represents the shortest path between two locations.
 *
 * @param, output_file The path for the generated text file 
 * @return The value 0 to represent successfully generating the text file
*/

int export_text(struct PATH *my_path, char *output_file);


/**
 * @brief generate the output text file for the strategic airlift simulator..
 *
 * 
 * @para, my_paths It represents the shortest path between two locations.
 *
 * @param, output_file The path for the generated text file 
 * @return The value 0 to represent successfully generating the text file
*/

int export_xml(struct PATH *my_paths, char *output_file);



/**
 * @brief generate the output text file for the strategic airlift simulator..
 *
 * 
 * @para, my_paths It represents the shortest path between two locations.
 *
 * @param, output_file The path for the generated text file 
 * @return The value 0 to represent successfully generating the text file
*/
int create_port_data(FILE *fb);


/**
 * @brief generate the output text file for the strategic airlift simulator..
 *
 * 
 * @para, my_paths It represents the shortest path between two locations.
 *
 * @param, output_file The path for the generated text file 
 * @return The value 0 to represent successfully generating the text file
*/
int create_component_data(FILE *fb, struct STATE *my_state, int air_count);


/**
 * @brief generate the output text file for the strategic airlift simulator..
 *
 * 
 * @para, my_paths It represents the shortest path between two locations.
 *
 * @param, output_file The path for the generated text file 
 * @return The value 0 to represent successfully generating the text file
*/
int create_connection_eic_data(FILE *fb, struct STATE *my_state, int air_count);




