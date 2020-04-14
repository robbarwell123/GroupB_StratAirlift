/**
 * @file integrated.h
 * @author Olumide Akinola
 * @date 13 Apr 2020
 * @brief This file contains the functions required to for the intgration test.
 */

#ifndef __INTEGRATED_H__
#define __INTEGRATED_H__

#include "../../include/data_types.h"

/**
 * @brief Defines an initial set of airports for the test.
 *
 * Includes airports for: Trenton Ontario, Cologne Germany, Nairobi Kenya, Glasgow Scotland, and Bogota Colombia.
 *
 * @return The initial set of airports.
 */
struct AIRPORT** calc_shortest_path_test_set_airports();

/**
 * @brief Defines the initial state for the test.
 *
 * Uses the default state set in parse_config and adds in the following locations: Nairobi Kenya, Glasgow Scotland, and Bogota Colombia.
 *
 * @see parse_config
 *
 * @param my_airports Initial set of aiports for the test.
 * @param my_state The tests current state.
 */
void calc_shortest_path_test_set_state(struct AIRPORT** my_airports,struct STATE *my_state);

#endif // __INTEGRATED_H__
