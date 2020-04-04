/**
 * @file strat_airlift_functions_tests.h
 * @author Rob Barwell, Olumide Akinola, Edwin Omoigui, Lukeman Hakkim Sheik Alavudeen
 * @date 17 Mar 2020, Last Updated 04 Apr 2020
 * @brief This file contains the functions required for the tests to function.
 */

#ifndef __STRAT_AIRLIFT_FUNCTIONS_TESTS_H__
#define __STRAT_AIRLIFT_FUNCTIONS_TESTS_H__

#include "../../include/data_types.h"

/**
 * @brief Runs the unit tests for calculating the shortest path between all locations.
 *
 * The test uses a basic scenario with a main operating base connection from Trenton Ontario
 * to Cologne Germany and additional locations in Nairobi Kenya, Glasgow Scotland, and Bogota Colombia.
 *
 * The test produces 20 paths which are compared to a known result.
 *
 * @return The value 0 to represent successfully finding the shortest path and -1 represents an error finding the shortest path.
 */
int calc_shortest_path_test();

/**
 * @brief Runs the unit tests for parsing the common airport file.
 *
 * This unit test runs 3 individual tests:
 * 1. To ensure the file exists before trying to process
 * 2. To check if malformed records are ignored
 * 3. To check it reads in the correct number of records
 *
 * @return The value 0 to represent successfully running all the tests.
 */
int parse_airports_test();

/**
 * @brief Runs the unit tests for gen_locations.
 *
 * This unit test validates three steps:
 * 1. To ensure the correct number of locations are generated
 * 2. To check for errors when the number of requested locations exceed the number of available locations
 * 3. To ensure there are no duplicate locations
 * @return The value 0 to represent successfully running all the tests.
 */
int gen_locations_test();

/**
 * @brief Runs the unit tests for find_closest
 *
 * The test uses a basic scenario with a main operating base connection from Trenton Ontario
 * to Cologne Germany and additional locations in Nairobi Kenya, Glasgow Scotland, and Bogota Colombia.
 *
 * The test produces a distance matrix which is compared to a the correct distance matrix for the scenario.
 *
 * @return The value 0 to represent successfully finding the closest main bases and -1 represents an error.
 */
int find_closest_test();


#endif // __STRAT_AIRLIFT_FUNCTIONS_TESTS_H__
