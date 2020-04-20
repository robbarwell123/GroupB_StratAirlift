/**
 * @file parse_config.h
 * @author Rob Barwell
 * @date 17 Mar 2020, Last updated 4 Apr 2020
 * @brief This file contains the functions required to support parsing the configuration.
 */

#ifndef __PARSE_CONFIG_H__
#define __PARSE_CONFIG_H__

#include "data_types.h"

/**
 * @brief Used to define errors with the config file.
 *
 * The following types of errors can be encountered when reading in a config file.
 */
enum CONFIG_ERRORS {
    CONFIG_OK=0, /**< No issue with the config.*/
    CONFIG_FILE_ERROR=-1, /**< File doesn't exist.*/
    CONFIG_STATE_ERROR=-2, /**< Unknown state error.*/
    CONFIG_KEY_ERROR=-3, /**< Config parameter is invalid.*/
    CONFIG_SCENARIO_ERROR=-4, /**< Error parsing the scenario number.*/
    CONFIG_LOCATION_ERROR=-5, /**< Error parsing number of locations.*/
    CONFIG_DISTRIBUTION_ERROR=-6, /**< Error parsing distributions.*/
    CONFIG_BASE_ERROR=-7, /**< Error parsing main base.*/
    CONFIG_SET_DEFAULT_ERROR=-8 /**< Error setting default values.*/
};

#define CONFIG_KEY 0 /**< Position of the key in key/value array. */
#define CONFIG_VALUE 1 /**< Position of the value in key/value array. */

/**
 * @brief Config file parameters.
 *
 * The following is a list of configuration parameters.  More detail can be found in the user documentation.
 */
enum CONFIG_KEYS {
    KEY_SCENARIOS, /**< number_of_scenarios*/
    KEY_DISTRIBUTION, /**< location_distribution*/
    KEY_LOCATIONS, /**< number_of_locations*/
    KEY_CONNECTIONS /**< connections*/
};

/**
 * @brief Parses the scenario number from the config file.
 *
 * number_of_scenarios – This is an integer value between 1 and 10 000
 *
 * @param value The input line from the config file to parse. 
 * @param my_state The generator's current state.
 *
 * @return The value 0 to represent successfully parsing the line and any other value represents an error parsing the line.
 */
int parse_scenario_number(char *value, struct STATE *my_state);

/**
 * @brief Parses the number of locations from the config file.
 *
 * number_of_locations – This is the number of locations to generate between 1 and 100
 *
 * @param value The input line from the config file to parse. 
 * @param my_state The generator's current state.
 *
 * @return The value 0 to represent successfully parsing the line and  any other value represents an error parsing the line.
 */
int parse_location_number(char *value, struct STATE *my_state);

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
 * @param value The input line from the config file to parse. 
 * @param my_state The generator's current state.
 *
 * @return The value 0 to represent successfully parsing the line and  any other value represents an error parsing the line.
 */
int parse_distribution(char *value, struct STATE *my_state);

/**
 * @brief Parses the initial list of main logistics bases from the config file.
 *
 * connections – This is the list of connections between main logistics bases.
 * The list of main logistics bases is automatically inferred from the set of connections.
 * If the scenario only includes one base it will be self-referenced (i.e. CYTR:CYTR).
 * ICAO airport codes will be used to denote airports and their connection pair will be separated by a colon.
 * Each connection pair will be separated by a comma.
 *
 * @param value The input line from the config file to parse. 
 * @param my_airports The main list of airports.
 * @param my_state The generator's current state.
 *
 * @return The value 0 to represent successfully parsing the line and  any other value represents an error parsing the line.
 */
int parse_base(char *value, struct AIRPORT **my_airports, struct STATE *my_state);

/**
 * @brief Adds an airport to the main base list.
 *
 * @param airport_id The ICAO id of the airport to add to the list.
 * @param my_airports The main list of airports.
 * @param my_state The generator's current state.
 *
 * @return The value 0 to represent successfully parsing the line and  any other value represents an error parsing the line.
 */
int add_airport(char* airport_id, struct AIRPORT **my_airports, struct STATE *my_state);

/**
 * @brief Sets the default parameters for all configuration options.
 *
 * @param my_airports The main list of airports.
 * @param my_state The generator's current state.
 *
 * @return The value 0 to represent successfully parsing the line and  any other value represents an error parsing the line.
 */
int set_default(struct AIRPORT **my_airports, struct STATE *my_state);

/**
 * @brief Splits the configuration parameter key name and value.
 *
 * @param input_line The line from the file to split the key/value pair from.
 * @param key_value The key/value pair with index 0 holding the key and index 1 holding the value.
 *
 * @return The value 0 to represent successfully parsing the line and 1 represents an error parsing the line.
 */
int split_key_value(char* input_line,char* key_value[]);

#endif // __PARSE_CONFIG_H__