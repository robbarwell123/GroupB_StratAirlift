/**
 * @file calc_shortest_path_test.h
 * @author Rob Barwell
 * @date 17 Mar 2020
 * @brief This file contains the functions required to support the calc_shortest_path_test.
 */

#ifndef __CALC_SHORTEST_PATH_TEST_H__
#define __CALC_SHORTEST_PATH_TEST_H__

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

#endif // __CALC_SHORTEST_PATH_TEST_H__