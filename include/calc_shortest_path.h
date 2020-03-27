/**
 * @file calc_shortest_path.h
 * @author Rob Barwell
 * @date 17 Mar 2020
 * @brief This file contains the functions required to support the shortest path calculations.
 */

#ifndef __CALC_SHORTEST_PATH_H__
#define __CALC_SHORTEST_PATH_H__

#include "data_types.h"

/**
 * @brief Uses Dijsktra's algorithm to calculate the shortest path between all locations.
 *
 * The shortest path between all locations is required as an input for the strategic airlift simulator.
 * This function takes one specific location and calculates the shortest path to all other locations and adds it to my_paths.
 *
 * @param source The source location to start calculating the shortest path from.
 * @param my_state The generator's current state.
 * @param my_paths The shortest path between all locations.
 * @return The value 0 to represent successfully finding the shortest path and 1 represents an error finding the shortest path.
 */
int dijsktra(int source, struct STATE *my_state, struct PATH **my_paths);

#endif // __CALC_SHORTEST_PATH_H__