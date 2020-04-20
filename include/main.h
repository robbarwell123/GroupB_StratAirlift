/**
 * @file main.h
 * @author Rob Barwell, Olumide Akinola, Edwin Omoigui, Lukeman Hakkim Sheik Alavudeen
 * @date 15 Mar 2020, Last Updated 18 Apr 2020
 * @brief This file contains the functions required for the main file and calling all the sub-functions.
 */

#ifndef __MAIN_H__
#define __MAIN_H__

#define MAX_DIR_LENGTH 256 /**< Defines the maximum length of a directory name */

/**
 * @brief Takes command line arguments for calling and passing functions required for the strategic airlift simulator.
 *
 * @param config_filename The user-specified configuration file using ./data/blank.cfg as default.
 * @param airport_filename The user-specified common airport file using ./data/airport.csv as default.
 * @param output_dir The output directory to be used.
 * @return The value 0 represents success and any other number represents an error.
 */

int run_generator(char* config_filename,char* airport_filename,char* output_dir);

#endif // __MAIN_H__

