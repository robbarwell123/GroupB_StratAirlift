#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/data_types.h"
#include "../include/common_functions.h"
#include "../include/strat_airlift_functions.h"
#include "../include/main.h"

/**
 * @brief continent_names is used for error messages to decipher which continent caused the issue.
 */
char* continent_names[]={"Africa","Antarctica","Asia","Europe","North America","Australia","South America"};

/**
 * @brief my_sizes is used to store the sizes of the dynamic arrays used throughout the program.
 */
struct SIZES *my_sizes;

int run_generator(char* config_filename,char* airport_filename,char* output_dir) {
    int rtn_val=0;                                      // The current state of the function to return
    int scenarios=1;                                    // The number of scenarios to generate
    int curr_scenario=0;                                // The current scenario number
    char scenario_dir[MAX_DIR_LENGTH];                  // The directory scenario
    
    for(curr_scenario;curr_scenario<scenarios;curr_scenario++) {        
        printf("===Building Scenario %i===\n",curr_scenario+1);
        sprintf(scenario_dir,"%s%d/",output_dir,curr_scenario);
        
        /* Initalizes my_sizes to 0 for all dynamic arrays. */
        my_sizes=malloc(sizeof(struct SIZES));
        for(int init=0;init<7;init++){
            my_sizes->cont[init]=0;
        }
        my_sizes->locations=0;
        my_sizes->paths=0;

        /* Creates the initial structures which will be used for all function calls. */
        struct STATE *my_state=malloc(sizeof(struct STATE));
        struct AIRPORT **my_airports;
        my_airports=(struct AIRPORT**)malloc(sizeof(struct AIRPORT*)*7);
        for(int init=0;init<7;init++){
            my_airports[init]=NULL;
        }
        struct PATH *my_paths=NULL;

        if(rtn_val==0 && parse_airports(airport_filename,my_airports)) {
            rtn_val=-1;
        }
        #ifdef DEBUG_ENABLED
        printf("Airports per Continent\n");
        for(int print_size=0;print_size<7;print_size++) {
            printf("Continent %d Airports: %d\n",print_size,my_sizes->cont[print_size]);
        }
        #endif
        
        if(rtn_val==0 && parse_config(my_airports, config_filename, my_state)!=0) {
            rtn_val=-2;
        }
        
        /* Updates the number of scenarios to match the config file */
        scenarios=scenarios<my_state->num_scenarios ? my_state->num_scenarios : scenarios;

        if(rtn_val==0 && gen_locations(my_airports, my_state)!=0) {
            rtn_val=-3;
        }

        my_state->distance_matrix=(int**)realloc(my_state->distance_matrix,sizeof(int*)*my_sizes->locations);
        for(int source=0;source<my_sizes->locations;source++) {
            if(source<my_state->num_main_bases){
                my_state->distance_matrix[source]=(int*)realloc(my_state->distance_matrix[source],sizeof(int)*my_sizes->locations);
                for(int dest=my_state->num_main_bases;dest<my_sizes->locations;dest++) {
                    my_state->distance_matrix[source][dest]=0;
                }
            }else{
                my_state->distance_matrix[source]=(int*)calloc(my_sizes->locations,sizeof(int));
            }
        }
        
        if(rtn_val==0 && find_closest(my_state)!=0) {
            rtn_val=-3;
        }

        if(rtn_val==0 && calc_shortest_path(my_state, &my_paths)!=0) {
            rtn_val=-5;
        }

        if(rtn_val==0){
            for(int print_loc=0;print_loc<my_state->num_locations;print_loc++){
                printf("%d,%s,%f,%f\n",print_loc,my_state->airport_list[print_loc]->name,my_state->airport_list[print_loc]->lat,my_state->airport_list[print_loc]->lon);
            }
            print_paths(my_paths);
        }        
/*        
        if(rtn_val==0 && export(my_state, my_paths, scenario_dir)!=0) {
            rtn_val=-6;
        }
*/
        #ifdef DEBUG_ENABLED
        print_state(my_state);
        #endif
  
        printf("Completed building scenario %i\n",curr_scenario+1);
  
        free(my_sizes);
        free(my_state);
        free(my_airports);
        free(my_paths);

        if(rtn_val!=0) {
            break;
        }
    }
    
    return rtn_val;
}

/**
 * @brief The main function to run the strategic airlift input generator.
 *
 * The following are valid command line arguments:
 * Used by flags 
 * -c for users to specify the config file
 * -d for users to specify the common airport file
 * -o for users to specify the output directory
 * -v for users to display the program version
 *
 * @return 0 if the application executed successfully.  Any other number if their was an error.
 */
int main(int argc, char* argv[]) {
    char* airport_filename="./data/airports.csv";       // Location of the airport data file
    char* config_filename="./data/blank.cfg";         // Location of the configuration file
    char* output_dir="./data/output/";                  // The output directory
    
    #ifdef DEBUG_ENABLED
    printf("Debug Enabled\n");
    #endif

    int curr_arg=1;
    while(curr_arg<argc) {
        if(*argv[curr_arg]=='-') {
            if(strcmp(argv[curr_arg],"-v")==0) {
                printf("Strategic Airlift Input Generator v1.0\n");
                printf("Options:\n");
                printf("Note: -c and -o will be avaliable in release 2.\n");
                printf("-v - Prints this message.\n");
                printf("-c {filename} - Used to set the config file.  Default is ./data/default.cfg\n");
                printf("-d {filename} - Used to set the common airport file.  Default is ./data/airports.csv\n");
                printf("-o {filename} - Used to set the output directory.  Default is ./data/output/\n");
                return 0;
            }else if(strcmp(argv[curr_arg],"-c")==0) {
                curr_arg++;
                if(curr_arg<argc && *argv[curr_arg]!='-') {
                    config_filename=argv[curr_arg];
                    printf("Config file set to: %s\n",config_filename);
                    curr_arg++;
                }
            }else if(strcmp(argv[curr_arg],"-d")==0) {
                curr_arg++;
                if(curr_arg<argc && *argv[curr_arg]!='-') {
                    airport_filename=curr_arg<argc ? argv[curr_arg] : "./data/airports.csv";
                    printf("Common airport file set to: %s\n",airport_filename);
                    curr_arg++;
                }
            }else if(strcmp(argv[curr_arg],"-o")==0) {
                curr_arg++;
                if(curr_arg<argc && *argv[curr_arg]!='-') {
                    output_dir=curr_arg<argc ? argv[curr_arg] : "./data/output/";
                    printf("Output directory set to: %s\n",output_dir);
                    curr_arg++;
                }
            }else {
                printf("Invalid option: %s\n",argv[curr_arg]);
                curr_arg++;
            }
        }else {
            printf("Unknown option: %s\n",argv[curr_arg]);
            curr_arg++;
        }
    }

    #ifdef DEBUG_ENABLED
    printf("Config file set to: %s\n",config_filename);
    printf("Common airport file set to: %s\n",airport_filename);
    printf("Output directory set to: %s\n",output_dir);
    #endif

    return run_generator(config_filename,airport_filename,output_dir);
}