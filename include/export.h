/**
 * @file export.h
 * @author Lukeman Hakkim Sheik Alavudeen
 * @date 17 Apr 2020, Last Updated 18 Apr 2020
 * @brief This file contains all support functions to export text and xml file for the strategic airlift simulator
 */

#ifndef __EXPORT_H__
#define __EXPORT_H__

#include "data_types.h"
#include <stdio.h>

/**
 * @brief generate the output text file for the strategic airlift simulator..
 * 
 * It generates the output text file with shortest path for each scenario.
 *
 * @param my_path It represents the shortest path between two locations.
 * @param output_file The path for the generated text file 
 * @return The value 0 to represent successfully generating the text file any other value represents an error.
 */
int export_text(struct PATH *my_path, char *output_file);

/**
 * @brief generate the output xml file for the strategic airlift simulator..
 * 
 * It generates the output xml file with all data for each scenario.
 *
 * @param my_state It represents the current state of the generator.
 * @param output_file The path for the generated xml file 
 * @return The value 0 to represent successfully generating the xml file any other value represents an error
 */
int export_xml(struct PATH *my_state, char *output_file);

/**
 * @brief To generate port data in output xml file for the strategic airlift simulator..
 * 
 * It generates port data for output xml file.
 *
 * @param fb The xml file where the port data will be written.  
 */
void create_port_data(FILE *fb);

/**
 * @brief To generate component data in output xml file for the strategic airlift simulator..
 * 
 * It generates port data for output xml file.
 *
 * @param fb The xml file where the port data will be written. 
 * @param my_state It represents the current state of the generator.
 * @param air_count It represents the airport count in the airport_list
 */
void create_component_data(FILE *fb, struct STATE *my_state, int air_count);

/**
 * @brief To generate connection eic data in output xml file for the strategic airlift simulator..
 * 
 * It generates connection eic data in output xml file
 *
 * @param fb The xml file where the port data will be written. 
 * @param my_state It represents the current state of the generator.
 * @param air_count It represents the airport count in the airport_list
 */
void create_connection_eic_data(FILE *fb, struct STATE *my_state, int air_count);

/**
 * @brief To generate connection eoc data in output xml file for the strategic airlift simulator..
 *
 * It generates connection eoc data in output xml file
 * 
 * @param fb The xml file where the port data will be written. 
 * @param my_state It represents the current state of the generator.
 * @param air_count It represents the airport count in the airport_list
 */
void create_connection_eoc_data(FILE *fb, struct STATE *my_state, int air_count);

#endif // __EXPORT_H__