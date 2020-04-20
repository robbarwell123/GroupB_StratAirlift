/**
 * @file common_test_functions.h
 * @author Rob Barwell, Lukeman Hakkim Sheik Alavudeen
 * @date 17 Mar 2020, Last updated 20 Apr 2020
 * @brief This file contains common functions required to support multiple unit tests.
 */

#ifndef __COMMON_TEST_FUNCTIONS_H__
#define __COMMON_TEST_FUNCTIONS_H__

#include "../../include/data_types.h"

/**
 * @brief Defines an initial set of airports for the test.
 *
 * Includes airports for: Trenton Ontario, Cologne Germany, Nairobi Kenya, Glasgow Scotland, and Bogota Colombia.
 *
 * @return The initial set of airports.
 */
struct AIRPORT** set_test_airports();

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
void set_test_state(struct AIRPORT** my_airports,struct STATE *my_state);

/**
 * @brief Used to compare the contents of two files.
 *
 * It is used to compare the contents of two files.
 *
 * @param output_file It represents the generated output file.
 * @param expected_file It represents the expected output file.
 * @return It returns number of mismatch by comparing two files as an integer.
 */
int compare_files(FILE *output_file, FILE *expected_file);

#endif // __COMMON_TEST_FUNCTIONS_H__