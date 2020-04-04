/**
 * @file strat_airlift_functions.h
 * @author Rob Barwell, Olumide Akinola, Edwin Omoigui
 * @date 15 Mar 2020, Last Updated 31 Mar 2020
 * @brief This file contains the functions required for the generator to function.
 */

#ifndef __STRAT_AIRLIFT_FUNCTIONS_H__
#define __STRAT_AIRLIFT_FUNCTIONS_H__

#include "data_types.h"

/**
 * @brief Parses the configuration file.
 *
 * The following are the only valid parameters for the config file.
 * Each parameter is separated from its value by the equal sign. Duplicate parameters will override previous values.
 * Any parameter omitted from the config file will result in the default value being used as documented in the requirements.
 * 1. number_of_scenarios – This is an integer value between 1 and 10 000
 * 2. location_distribution – Is the distribution of locations to generate between valid continents listed below.
 * Each continent is listed by short name with a colon separating the distribution value and short name.
 * A comma separates each continent.
 *     a. AF - Africia
 *     b. NA = North America
 *     c. OC = Oceania
 *     d. AN = Antarctica
 *     e. AS = Asia
 *     f. SA = South America
 *     g. EU = Europe
 * 3. number_of_locations – This is the number of locations to generate between 1 and 100
 * 4. connections – This is the list of connections between main logistics bases.
 * The list of main logistics bases is automatically inferred from the set of connections.
 * If the scenario only includes one base it will be self-referenced (i.e. CYTR:CYTR).
 * ICAO airport codes will be used to denote airports and their connection pair will be separated by a colon.
 * Each connection pair will be separated by a comma.
 *
 * Below is an example configuration file (defaultconfig.cfg)
 * number_of_scenarios=3
 * location_distribution=NA:0.2,AS:0.5,AF:0.2,EU:0.1,OC:0.0,AN:0.0,SA:0.0
 * number_of_locations=7
 * connections=CYTR:EDDK,CYTR:CYYZ
 *
 * @param my_airports Main airport list.
 * @param config_file The full path to a configuration file.
 * @param my_state The generator's current state.
 * @return The value 0 to represent successfully parsing the file and any other value represents an error parsing the file.
 */
int parse_config(struct AIRPORT **my_airports, char *config_file, struct STATE *my_state);

/**
 * @brief Calculates the shortest path between all locations.
 *
 * The shortest path between all locations is required as an input for the strategic airlift simulator.
 *
 * @param my_state The generator's current state.
 * @param my_paths The shortest path between all locations.
 * @return The value 0 to represent successfully finding the shortest path and any other value represents an error finding the shortest path.
 */
int calc_shortest_path(struct STATE *my_state, struct PATH **my_paths);

/**
 * @brief Reads in the airport list from the common airport list file.
 *
 * This list follows the format specified at https://ourairports.com/data/.  Further details are in the user and developer documentation.
 *
 * @param airport_file The airport file to be run.
 * @param my_airports The 2D array of struct for airports.
 * @return The value 0 to represent successfully parsing the airport file and any other value represents an error.
*/
int parse_airports(char *airport_file,struct AIRPORT** my_airports);

/**
 * @brief Generates a random list of locations to use in the scenario.
 *
 * The generate location produces a random list of locations based on the common airport list
 *
 * @param my_airports Main airport list.
 * @param my_state The generator's current state.
 * @return The value 0 to represent successfully generating airports and any other value represents an error.
*/
int gen_locations(struct AIRPORT **my_airports, struct STATE *my_state);

/**
 * @brief Attaches the list of random locations to the closest main base.
 *
 * Checks the shortest straight path distance between the random location and all the main bases to find the closest one.
 *
 * @param my_state The generator's current state.
 * @return The value 0 to represent successfully generating the distance matrix and any other value represents an error.
*/
int find_closest(struct STATE *my_state);

#endif // __STRAT_AIRLIFT_FUNCTIONS_H__
