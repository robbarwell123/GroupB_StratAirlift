/**
 * @file gen_locations_test.h
 * @author Edwin
 * @date 31 Mar 2020
 * @brief This file contains the functions required to support the gen_locations_test.
 */

#ifndef __GEN_LOCATIONS_TEST_H__
#define __GEN_LOCATIONS_TEST_H__

#include "../../include/data_types.h"

/**
 * @brief Defines the number of locations generated for the test.
 *
 * Will include airport locations Trenton Ontario, Cologne Germany, Nairobi Kenya, Glasgow Scotland, and Bogota Colombia.
 *
 * @return The number of requested locations.
 */
struct AIRPORT** set_gen_locations_airports();

/**
 * @brief Defines the initial state for the test.
 *
 * Uses the default state set in parse_config and adds unduplicated locations based on the users location number specification
 *
 * @see parse_config
 *
 */

#endif // __GEN_LOCATIONS_TEST_H__
