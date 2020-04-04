/**
 * @file common_functions.h
 * @author Rob Barwell
 * @date 15 Mar 2020
 * @brief This file contains all the common functions shared between functions within the generator.
 */

#ifndef __COMMON_FUNCTIONS_H__
#define __COMMON_FUNCTIONS_H__

#include "data_types.h"
#include <math.h>

/**
 * @brief Searches by ICAO code for an airport in the main airport list and if found returns a pointer to the AIRPORT structure.
 *
 * An example of an ICAO code is "CYTR" for Trenton, Ontario.
 *
 * @param id ICAO code to search for.
 * @param my_airports Main airport list.
 * @return A pointer to the AIRPORT structure if found, if not NULL is returned.
 */
struct AIRPORT* find_airport(char *id,struct AIRPORT **my_airports); 

/**
 * @brief Calculates the distance in kilometers between two points specified by latitude and longitude.
 *
 * Uses standard geometry to calculate the distance between two points on a globe.
 *
 * @param lat1 Latitude of point A.
 * @param lon1 Longitude of point A.
 * @param lat2 Latitude of point B.
 * @param lon2 Longitude of point B.
 * @return The distance between point A and B as an integer.
 */

int calc_distance( float lat1, float lon1, float lat2, float lon2 );


/**
 * @brief Helper function to convert degree to radian.
 *
 * Uses mathematical calculation from convert degree to radian
 *
 * @param Input as degree unit
 * @return Outputs as radian unit.
 */
float ToRadConv(float deg);


/**
 * @brief Helper function to find minimum element in the array.
 *
 * @param Input as array of integers
 * @return Outputs as interger element.
 */

int minimum_array(int min_array[], int array_size);


#ifdef DEBUG_ENABLED
/**
 * @brief Used to print the current STATE structure if DEBUG_ENABLED is defined.
 *
 * Writes a user understandable version of the STATE structure if DEBUG_ENABLED is defined.
 *
 * @param my_state The STATE structure to print.
 */
void print_state(struct STATE *my_state);

/**
 * @brief Used to print the current set of paths if DEBUG_ENABLED is defined.
 *
 * Writes a user understandable version of the PATH structure if DEBUG_ENABLED is defined.
 *
 * @param my_paths The PATH structure to print.
 */

void print_paths(struct PATH *my_paths);
#endif

#endif // __COMMON_FUNCTIONS_H__