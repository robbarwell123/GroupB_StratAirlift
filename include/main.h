/**
 * @file main.h
 * @author Edwin Omoigui
 * @date 31 Mar 2020
 * @brief This file contains the functions required for the main file and calling all the sub-functions.
 */

#ifndef __MAIN_H__
#define __MAIN_H__

/**
 * @brief Takes command line arguments for calling and passing functions required for the strategic airlift simulator.
 *
 * @param config_filename The user's specified configuration file with default file being the generator.cfg within the directory of execution.
 * @param airport_filename The user's specified common airport file.
 * @param output_dir The output directory to be used.
 * @return The value 0 to represent error while any other values represent successfully calling all functions without any error.
 */

int run_generator(char* config_filename,char* airport_filename,char* output_dir);

#endif // __MAIN_H__

