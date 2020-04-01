/**
 * @file strat_airlift_functions_tests.h
 * @author Rob Barwell, Olumide Akinola
 * @date 17 Mar 2020, Last Updated 27 Mar 2020
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
 * @return The value 0 to represent successfully running all the tests.
 */
int gen_locations_test();

#endif // __STRAT_AIRLIFT_FUNCTIONS_TESTS_H__