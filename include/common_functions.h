/**
 * @file common_functions.h
 * @author Rob Barwell, Lukeman Hakkim Sheik Alavudeen
 * @date 15 Mar 2020, Last updated 4 Apr 2020
 * @brief This file contains all the common functions shared between functions within the generator.
 */

#ifndef __COMMON_FUNCTIONS_H__
#define __COMMON_FUNCTIONS_H__

#include "data_types.h"

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
 * @brief Helper function for calc_distance to convert degrees to radians.
 *
 * Uses mathematical calculation to convert degrees to radians
 *
 * @param deg Degree value to convert to radians.
 * @return Value as radians.
 */
float deg_to_rad(float deg);

#ifdef DEBUG_ENABLED
/**
 * @brief Used to print the current STATE structure if DEBUG_ENABLED is defined.
 *
 * Writes a user understandable version of the STATE structure if DEBUG_ENABLED is defined.
 *
 * @param my_state The STATE structure to print.
 */
void print_state(struct STATE *my_state);
#endif

/**
 * @brief Used to print the current set of paths if DEBUG_ENABLED is defined.
 *
 * Writes a user understandable version of the PATH structure if DEBUG_ENABLED is defined.
 *
 * @param my_paths The PATH structure to print.
 */
void print_paths(struct PATH *my_paths);

#endif // __COMMON_FUNCTIONS_H__