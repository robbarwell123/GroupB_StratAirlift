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
 * @return The number of requested locations without duplicate.
 */
struct AIRPORT** set_gen_locations_airports();

/**
 * @brief Defines the initial state for the test.
 *
 * Uses the default state set in parse_config and adds unduplicated locations based on the number of locations the user specified.
 *
 * @see parse_config
 *
 */

#endif // __GEN_LOCATIONS_TEST_H__
