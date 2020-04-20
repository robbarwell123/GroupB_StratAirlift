#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/data_types.h"
#include "../include/common_functions.h"
#include "../include/parse_config.h"

int parse_scenario_number(char *value, struct STATE *my_state) {
    my_state->num_scenarios=atoi(value);
    if(my_state->num_scenarios>0 && my_state->num_scenarios<=10000) {
        return CONFIG_OK;
    }else{
        return CONFIG_SCENARIO_ERROR;
    }
}

int parse_location_number(char *value, struct STATE *my_state) {
    my_state->num_locations=atoi(value);
    if(my_state->num_locations>0 && my_state->num_locations<=100) {
        return CONFIG_OK;
    }else{
        return CONFIG_LOCATION_ERROR;
    }
}

int parse_distribution(char *value, struct STATE *my_state) {
    char* all_cont=value;           // All continent tokens
    char* curr_cont;                // The current continent token 
    char* parse_cont;               // Parsing continents
    char* parse_curr_cont;          // Parsing the current continent
    int curr_cont_idx;              // The continent index in the main distribution array
    float total_dist=0.0;           // The total distribution of all continents added together
    
    // Zeros out the default continent distribution
    for(int zero=0;zero<7;zero++){
        my_state->dist_locations[zero]=0.0;
    }

    while((parse_cont=strtok_r(all_cont,",",&all_cont))){
        curr_cont=parse_cont;
        parse_curr_cont=strtok_r(curr_cont,":",&curr_cont);
        if(parse_curr_cont!=NULL){
            if(strcmp(parse_curr_cont,"AF")==0){
                curr_cont_idx=AF;
            }else if(strcmp(parse_curr_cont,"AN")==0){
                curr_cont_idx=AN;
            }else if(strcmp(parse_curr_cont,"AS")==0){
                curr_cont_idx=AS;
            }else if(strcmp(parse_curr_cont,"EU")==0){
                curr_cont_idx=EU;
            }else if(strcmp(parse_curr_cont,"NA")==0){
                curr_cont_idx=NA;
            }else if(strcmp(parse_curr_cont,"OC")==0){
                curr_cont_idx=OC;
            }else if(strcmp(parse_curr_cont,"SA")==0){
                curr_cont_idx=SA;
            }else{
                printf("CONFIG ERROR: Unknown Continent: %s\n",parse_curr_cont);
                return CONFIG_DISTRIBUTION_ERROR;
            }
            my_state->dist_locations[curr_cont_idx]=atof(strtok_r(curr_cont,":",&curr_cont));
        }
    }
    
    // Adds up the total continent distribution.
    for(int count=0;count<7;count++){
        total_dist+=my_state->dist_locations[count];
    }
    
    // Ensure the total continent distribution is between 0.98 and 1.0 to account for slight addition errors due to float accuracy.
    if(total_dist>=0.98 && total_dist<=1.0){
        return CONFIG_OK;
    }else{
        printf("CONFIG ERROR: Continent distribution total needs to be between 0.98 and 1.0\n");
        return CONFIG_DISTRIBUTION_ERROR;
    }
}

int add_airport(char* airport_id, struct AIRPORT **my_airports, struct STATE *my_state) {
    int airport_idx;                // The index of the airport in the my_state->airport_list array

    // Checks to see if the airport already exists.  If so it returns the array position.
    for(int check=0;check<my_sizes->locations;check++){
        if(strcmp(my_state->airport_list[check]->id,airport_id)==0){
            return check;
        }
    }
    
    // Adds the list to the my_state->airport_list array
    my_state->airport_list=(struct AIRPORT**)realloc(my_state->airport_list,sizeof(struct AIRPORT*)*(my_sizes->locations+1));
    my_state->airport_list[my_sizes->locations]=find_airport(airport_id,my_airports);
    if(my_state->airport_list[my_sizes->locations]==NULL){
        printf("CONFIG ERROR: Invalid airport id %s\n",airport_id);
        return CONFIG_BASE_ERROR;
    }
    airport_idx=my_sizes->locations;
    my_sizes->locations++;

    // Updates the my_state->distance_matrix with the new airport and defaults all distances to 0
    my_state->distance_matrix=(int**)realloc(my_state->distance_matrix,sizeof(int*)*my_sizes->locations);
    for(int resize=0;resize<(my_sizes->locations-1);resize++) {
        my_state->distance_matrix[resize]=(int*)realloc(my_state->distance_matrix[resize],sizeof(int)*my_sizes->locations);
        my_state->distance_matrix[resize][my_sizes->locations-1]=0;
    }
    my_state->distance_matrix[my_sizes->locations-1]=(int*)calloc(my_sizes->locations,sizeof(int));
    
    return airport_idx;
}

int parse_base(char *value, struct AIRPORT **my_airports, struct STATE *my_state) {
    char* all_main_bases=value;             // All main bases
    char* curr_main_bases;                  // The current main base
    char* curr_pair;                        // The current main base pair
    char* airport1;                         // The first airport ICAO id from the pair
    char* airport2;                         // The second airport ICAO id from the pair
    int airport1_idx;                       // The airport index in my_state->airport_list for the 1st airport
    int airport2_idx;                       // The airport index in my_state->airport_list for the 2nd airport
    
    // Resets my_state->airport_list to nothing
    free(my_state->airport_list);
    my_state->airport_list=(struct AIRPORT**)malloc(sizeof(struct AIRPORT*)*0);
    free(my_state->distance_matrix[0]);
    free(my_state->distance_matrix[1]);
    free(my_state->distance_matrix);
    my_state->distance_matrix=(int**)malloc(sizeof(int*)*0);
    my_state->num_main_bases=0;
    my_sizes->locations=0;

    while((curr_main_bases=strtok_r(all_main_bases,",",&all_main_bases))){
        curr_pair=curr_main_bases;
        airport1=strtok_r(curr_pair,":",&curr_pair);
        if(airport1!=NULL){
            airport2=strtok_r(curr_pair,":",&curr_pair);
            airport1_idx=add_airport(airport1, my_airports, my_state);
            airport2_idx=add_airport(airport2, my_airports, my_state);
            if(airport1_idx==CONFIG_BASE_ERROR || airport2_idx==CONFIG_BASE_ERROR){
                return CONFIG_BASE_ERROR;
            }
            if(airport1_idx!=airport2_idx){
                my_state->distance_matrix[airport1_idx][airport2_idx]=calc_distance(my_state->airport_list[airport1_idx]->lat,my_state->airport_list[airport1_idx]->lon,my_state->airport_list[airport2_idx]->lat,my_state->airport_list[airport2_idx]->lon);
                my_state->distance_matrix[airport2_idx][airport1_idx]=calc_distance(my_state->airport_list[airport2_idx]->lat,my_state->airport_list[airport2_idx]->lon,my_state->airport_list[airport1_idx]->lat,my_state->airport_list[airport1_idx]->lon);
            }
        }else{
            printf("CONFIG ERROR: Invalid pair %s\n",curr_pair);
            return CONFIG_BASE_ERROR;
        }
    }

    my_state->num_main_bases=my_sizes->locations;

    return CONFIG_OK;
}

int split_key_value(char* input_line,char* key_value[]){
    char* token=strtok(input_line,"=");

    key_value[CONFIG_KEY]=token;
    if(token!=NULL) {
        token = strtok(NULL, "-");         
        key_value[CONFIG_VALUE]=token;
    }else{
        printf("CONFIG ERROR: Unable to parse key/value %s\n",token);
        return CONFIG_KEY_ERROR;
    }
      
    return CONFIG_OK;
}

int set_default(struct AIRPORT **my_airports, struct STATE *my_state){
    struct AIRPORT* CYTR;
    struct AIRPORT* EDDK;
    
    my_state->num_scenarios=3;
    my_state->num_locations=7;
    my_state->dist_locations[AF]=0.142857143;
    my_state->dist_locations[AN]=0.142857143;
    my_state->dist_locations[AS]=0.142857143;
    my_state->dist_locations[EU]=0.142857143;
    my_state->dist_locations[NA]=0.142857143;
    my_state->dist_locations[OC]=0.142857143;
    my_state->dist_locations[SA]=0.142857143;

    my_state->airport_list=(struct AIRPORT**)malloc(sizeof(struct AIRPORT*)*2);

    CYTR=find_airport("CYTR",my_airports);
    EDDK=find_airport("EDDK",my_airports);
   
    if(CYTR!=NULL && EDDK!=NULL){
        my_state->airport_list[0]=CYTR;
        my_state->airport_list[1]=EDDK;
        
        my_state->distance_matrix=(int**)malloc(sizeof(int*)*2);
        for(int init=0;init<2;init++) {
            my_state->distance_matrix[init]=(int*)malloc(sizeof(int)*2);
            for(int zero=0;zero<2;zero++) {
                my_state->distance_matrix[init][zero]=0;
            }
        }
        
        my_state->distance_matrix[0][1]=calc_distance(my_state->airport_list[0]->lat,my_state->airport_list[0]->lon,my_state->airport_list[1]->lat,my_state->airport_list[1]->lon);
        my_state->distance_matrix[1][0]=calc_distance(my_state->airport_list[1]->lat,my_state->airport_list[1]->lon,my_state->airport_list[0]->lat,my_state->airport_list[0]->lon);
        
        my_state->num_main_bases=2;
        my_sizes->locations=2;
        return CONFIG_OK;
    }else{
        printf("CONFIG ERROR: Default airports CYTZ or EDDK do not exist.\n");
        return CONFIG_SET_DEFAULT_ERROR;
    }
}

int parse_config(struct AIRPORT **my_airports, char *config_file, struct STATE *my_state) {
    int rtn_val=CONFIG_OK;                      // the value to return from this function
    char curr_line[MAX_LINE_LENGTH];            // the current line in the file
    char* key_value[2];                         // the current key/value pair of config parameter / value
    int func_rtn_val;                           // the return value from called functions
    
    FILE *curr_config_file;                     // file handle for the config file
    
    if(my_state==NULL){
        rtn_val=CONFIG_STATE_ERROR;
    }else{    
        curr_config_file = fopen(config_file, "r");
        if (curr_config_file == NULL){
            printf("Failed to open config file: %s.\n", config_file);
            rtn_val=CONFIG_FILE_ERROR;
        } else {
            if(set_default(my_airports,my_state)==CONFIG_OK){
                while(fgets(curr_line, MAX_LINE_LENGTH, curr_config_file) != NULL){
                    func_rtn_val=split_key_value(curr_line,key_value);
                    if(func_rtn_val==CONFIG_OK){
                        if(strcmp(key_value[CONFIG_KEY],"number_of_scenarios")==0){
                            func_rtn_val=parse_scenario_number(key_value[CONFIG_VALUE], my_state);
                            if(func_rtn_val!=CONFIG_OK) {
                                rtn_val=CONFIG_SCENARIO_ERROR;
                                break;
                            }
                        }else if(strcmp(key_value[CONFIG_KEY],"location_distribution")==0){
                            func_rtn_val=parse_distribution(key_value[CONFIG_VALUE], my_state);
                            if(func_rtn_val!=CONFIG_OK) {
                                rtn_val=CONFIG_DISTRIBUTION_ERROR;
                                break;
                            }
                        }else if(strcmp(key_value[CONFIG_KEY],"number_of_locations")==0){
                            func_rtn_val=parse_location_number(key_value[CONFIG_VALUE], my_state);
                            if(func_rtn_val!=CONFIG_OK) {
                                rtn_val=CONFIG_LOCATION_ERROR;
                                break;
                            }
                        }else if(strcmp(key_value[CONFIG_KEY],"connections")==0){
                            func_rtn_val=parse_base(key_value[CONFIG_VALUE],my_airports,my_state);
                            if(func_rtn_val!=CONFIG_OK) {
                                rtn_val=CONFIG_BASE_ERROR;
                                break;
                            }
                        }else{
                            printf("CONFIG ERROR: Unknown configuration option: %s\n",key_value[CONFIG_KEY]);
                            rtn_val=CONFIG_KEY_ERROR;
                            break;
                        }
                    }else{
                        rtn_val=CONFIG_KEY_ERROR;
                        break;
                    }
                }
            }else{
                rtn_val=CONFIG_SET_DEFAULT_ERROR;
            }
            fclose(curr_config_file);
        }
    }
    
    return rtn_val;
}
