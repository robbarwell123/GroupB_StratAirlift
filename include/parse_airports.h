//
//  main.c
//  Parse_Airports
//
//  Created by Olumide Akinola on 2020-03-16.
//  Copyright © 2020 Olumide Akinola. All rights reserved.
//

#include "datafile.h"
/**
* @brief calculates the number of airports in our csv file.
*
* The 2D array of airports is needed as input in int gen_locations.

*
* @param my_airports The 2D array of struct for airports.
* @param airport_file The airport file to be run.
* @return The value 0 to represent successfully counting the number of airports and -1 represents an error finding the number of airports.
*/

int parse_airports(struct AIRPORT** my_airports, char *airport_file);
