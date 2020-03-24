//
//  main.c
//  common_functions
//
//  Created by Olumide Akinola on 2020-03-15.
//  Copyright © 2020 Olumide Akinola. All rights reserved.
//

#include "datafile.h"

/**
* @brief Returns each item of the struct Airport, it takes in a line in the csv and the item index to be read into the struct.
*
*
* @param line, which is the line for each csv.
* @param col, index of the item in the line to be added to the struct.
*/
char* get_field(char *line, int col);

/**
* @brief This function is used to get continent indexing from 0 to 6 , i.e AF = 0, AN = 1, AS = 2, EU = 3, OC = 4, NA = 5, SA = 6 .
*
* Used to determine the continent to be retured.
*
* @param val, which is the val for index of continent for each line in the csv file.
* @return the continent for each line.
*/
int get_continent(char *val);

/**
* @brief Used to increase the size of the row for each continent.
*.
*@param val, which is the val for index of continent for each line in the csv file.
* @param size which is the number of rows of continents, here we have 7.
*/
void increment(char *val, int *size);

/**
* @brief Used to get a 2D array of structures
*
* reads the airport file int struct AIRPORT and aranges the struct in a 2D array based on continents with each row with similar continents.
*
* @param size which is the number of rows of continents, here we have 7
* @param line, which is the line for each csv.
* @param fileName the name of the csv file to be read.
*/
struct AIRPORT** get_2D_array(int *size, char *line, char* fileName);
