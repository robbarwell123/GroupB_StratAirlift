/**
 * @file parse_config.h
 * @author Rob Barwell
 * @date 17 Mar 2020
 * @brief This file contains the functions required to support parsing the configuration.
 */

#ifndef __PARSE_CONFIG_H__
#define __PARSE_CONFIG_H__

#include "data_types.h"

/**
 * @brief Parses the scenario number from the config file.
 *
 * number_of_scenarios – This is an integer value between 1 and 10 000
 *
 * @param input_line The input line from the config file to parse. 
 * @param my_state The generator's current state.
 * @return The value 0 to represent successfully parsing the line and 1 represents an error parsing the line.
 */
int parse_scenario_number(char *input_line, struct STATE *my_state);

/**
 * @brief Parses the number of locations from the config file.
 *
 * number_of_locations – This is the number of locations to generate between 1 and 100
 *
 * @param input_line The input line from the config file to parse. 
 * @param my_state The generator's current state.
 * @return The value 0 to represent successfully parsing the line and 1 represents an error parsing the line.
 */
int parse_location_number(char *input_line, struct STATE *my_state);

/**
 * @brief Parses the location distribution from the config file.
 *
 * location_distribution – Is the distribution of locations to generate between valid continents listed below.
 * Each continent is listed by short name with a colon separating the distribution value and short name.
 * A comma separates each continent.
 *     a. AF - Africia
 *     b. NA = North America
 *     c. OC = Oceania
 *     d. AN = Antarctica
 *     e. AS = Asia
 *     f. SA = South America
 *     g. EU = Europe
 *
 * @param input_line The input line from the config file to parse. 
 * @param my_state The generator's current state.
 * @return The value 0 to represent successfully parsing the line and 1 represents an error parsing the line.
 */
int parse_distribution(char *input_line, struct STATE *my_state);

/**
 * @brief Parses the initial list of main logistics bases from the config file.
 *
 * connections – This is the list of connections between main logistics bases.
 * The list of main logistics bases is automatically inferred from the set of connections.
 * If the scenario only includes one base it will be self-referenced (i.e. CYTR:CYTR).
 * ICAO airport codes will be used to denote airports and their connection pair will be separated by a colon.
 * Each connection pair will be separated by a comma.
 *
 * @param input_line The input line from the config file to parse. 
 * @param my_airports The main list of airports.
 * @param my_state The generator's current state.
 * @return The value 0 to represent successfully parsing the line and 1 represents an error parsing the line.
 */
int parse_base(char *input_line, struct AIRPORT **my_airports, struct STATE *my_state);

#endif // __PARSE_CONFIG_H__