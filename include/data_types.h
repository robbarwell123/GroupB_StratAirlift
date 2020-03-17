/**
 * @file data_types.h
 * @author Rob Barwell
 * @date 15 Mar 2020
 * @brief This file contains all user defined data types for the application and common defines.
 */

#ifndef __DATA_TYPES_H__
#define __DATA_TYPES_H__

#define AF 0 /**< Position of the Africa continent in the main list of airports. */
#define AN 1 /**< Position of the Antarctica continent in the main list of airports. */
#define AS 2 /**< Position of the Asia continent in the main list of airports. */
#define EU 3 /**< Position of the Europe continent in the main list of airports. */
#define NA 4 /**< Position of the North America continent in the main list of airports. */
#define OC 5 /**< Position of the Australia continent in the main list of airports. */
#define SA 6 /**< Position of the South America continent in the main list of airports. */

/**
 * @brief Used to store information about individual airports.
 *
 * Information is read in from https://ourairports.com/data/ and filtered for the AIRPORT structure.
 */
struct AIRPORT {
    char *id; /**< Airport ICAO ID.*/
    char *name; /**< Airport name. */
    float lat; /**< Airport latitude. */
    float lon; /**< Airport longitude. */
    char *cont; /**< Airport continent. */
    char *country; /**< Airport country. */
};

/**
 * @brief Used to store the current state of the generator.
 *
 * The current state is continually updated throughout the application life cycle.
 */
struct STATE {
    int num_scenarios; /**< The number of scenarios to generate.*/
    int num_locations; /**< The number of random locations to generate.*/
    float dist_locations[7]; /**< A one dimensional array containing the distribution of generated locations by continent.*/
    int num_main_bases; /**< The number of main bases specified in the config file.*/
    struct AIRPORT **airport_list; /**< Stores the list of airports used in the scenarios.  Starts with the main bases from the config file and has random generated locations added to it.*/
    int **distance_matrix; /**< An adjacency matrix representation of the connections between locations.*/
};

/**
 * @brief Used to store shortest path between two locations.
 *
 * This represents the input format required for the strategic airlift simulator.
 */
struct PATH {
    int source_location; /**< The source location.*/
    int dest_location; /**< The destination location.*/
    int next_location; /**< The next location on the shortest path between source and destination location.*/
    float next_lat; /**< The next location's latitude.*/
    float next_long; /**< The next location's longitude.*/
    int aircraft_type; /**< The type of aircraft used between locations.  1 represents a Globemaster and 2 represents a Hercules.*/
};

/**
 * @brief Used to store the size of dynamic arrays used in the application.
 *
 * The sizes are tracked for the following dynamic arrays:
 * 1.  The main list of airports stored by continents.
 * 2.  The number of locations in the airport_list of the current generator state.
 * 3.  The list of paths found after the shortest path algorithm is run.
 */
struct SIZES {
    int cont[7]; /**< The number of airports for each continent in the main airport list.*/
    int locations; /**< The number of locations stored in airport_list for the generator state.*/
    int paths; /**< The number of paths found between locations.*/
};

#endif // __DATA_TYPES_H__