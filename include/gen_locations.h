/**
 * @file gen_locations.h
 * @author Edwin Omoigui
 * @date 31 Mar 2020
 * @brief This file contains the functions required to generate random locations for the airlift simulator based on the airport list.
 */
#ifndef __GEN_LOCATIONS_H__
#define __GEN_LOCATIONS_H__

#include "data_types.h"

/**
 * @brief Generates a random non-duplicative list of locations requested from the airport list.
 *
 * The generated locations are required as an input for the strategic airlift simulator.
 * This function takes the number of locations requested for the generator with statistical distribution ensuring no location duplication.
 *
 * @param curr_pos The current position selected before the next random airport.
 * @param curr_rand The current randomly generated airport selected.
 * @param selected_airports The selected unique airport after checking non-duplication.
 * @return The value 0 to represent the selected airport has not been used already and 1 represents it has been used.
 */
int check_used(int curr_pos, int curr_rand,int* selected_airports);

#endif // __GEN_LOCATIONS_H__
