/**
 * @file parse_airports.h
 * @author Olumide Akinola
 * @date 15 Mar 2020
 * @brief This file contains the functions required to support reading the common airport list.
 */

#ifndef __PARSE_AIRPORTS_H__
#define __PARSE_AIRPORTS_H__

#include "data_types.h"

/**
 * @brief Returns a specific field after parsing it from a line in the common airport file.
 *
 * @param curr_line which is the current line to parse from the file.
 * @param col index of the item in the line to be added to the struct.
 * @return The value of the field as a string.
 */
char* get_field(char *curr_line, int col);

/**
 * @brief This function is used to get continent indexing from 0 to 6 , i.e AF = 0, AN = 1, AS = 2, EU = 3, OC = 4, NA = 5, SA = 6 .
 *
 * Used to determine the continent to be retured.
 *
 * @param field_value the field value for index of continent for each line in the csv file.
 * @return the continent for each line.
 */
int get_continent(char *field_value);

#endif // __PARSE_AIRPORTS_H__