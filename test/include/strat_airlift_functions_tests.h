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
 * @return The value 0 to represent successfully finding the shortest path and any other value represents an error finding the shortest path.
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
 * @return The value 0 to represent successfully running all the tests and any other value represents an error.
 */
int parse_airports_test();

/**
 * @brief Runs the unit tests for gen_locations.
 *
 * This unit test validates three steps:
 * 1. To ensure the correct number of locations are generated
 * 2. To check for errors when the number of requested locations exceed the number of available locations
 * 3. To ensure there are no duplicate locations
 *
 * @return The value 0 to represent successfully running all the tests and any other value represents an error.
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
 * @return The value 0 to represent successfully finding the closest main bases and any other value represents an error .
 */
int find_closest_test();

/**
 * @brief Runs the unit tests for parsing config files.
 *
 * The following tests are run as part of this test:
 * 1. my_state not NULL;
 * 2. Configuration file doesn’t exist;
 * 3. Invalid parameter / value pair;
 * 4. Blank line;
 * 5. Invalid number_of_scenarios;
 * 6. Invalid number_of_locations;
 * 7. Invalid location_distribution continent code;
 * 8. Invalid location_distribution sum;
 * 9. Invalid connections list;
 * 10. Valid config file; and
 * 11. Default values.
 *
 * @return The value 0 to represent successfully parsing the config and all other values represent an error.
 */
int parse_config_test();

/**
* @brief Runs the integrated test for all the funtions;
*
* The integration test validates:
* 1. Calls all the functions and returns expected output;
* 2. Compares the Locations.xml file returned based on the inputs and the expected Locations_correct.xml;
* 3. Compares the LocInfo.txt file returned based on the inputs and the expected LocInfo_correct.txt;
*
* @return The value 0 to represent successfully parsing the config and all other values represent an error.
*/
int integrated_test();


/**
 * @brief Runs the unit tests for export_files_test
 *
 * The test uses a basic scenario with a main operating base connection from Trenton Ontario
 * to Cologne Germany and additional locations in Nairobi Kenya, Glasgow Scotland, and Bogota Colombia.
 *
 * The test generates an output text and xml file for the strategic airlift simulator...
 *
 * @return The value 0 to represent successfull generation of an output text and xml file for the strategic airlift simulator..
 */
int export_test();


#endif // __STRAT_AIRLIFT_FUNCTIONS_TESTS_H__
