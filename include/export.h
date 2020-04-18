#include "data_types.h"

#include <stdio.h>




int export_text(struct PATH *my_path, char *output_file);


/**
 * @brief create the text file with paths.
 *
 * 
 *
 * @param my_path list of paths
 * @return The value 0 to represent successfully writing into th etext file
*/

int export_xml(struct PATH *my_path, char *output_file);



int create_port_data(FILE *fb);

int create_component_data(FILE *fb, struct STATE *my_state, int air_count);

int create_connection_eic_data(FILE *fb, struct STATE *my_state, int air_count);




