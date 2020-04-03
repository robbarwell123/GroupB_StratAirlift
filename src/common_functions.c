#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define pi 3.14159265358979323846


#include "../include/data_types.h"
#include "../include/common_functions.h"

extern struct SIZES *my_sizes;

struct AIRPORT* find_airport(char *id,struct AIRPORT **my_airports) {
    for(int continent=0;continent<7;continent++) {
        if(my_airports[continent]!=NULL){
            for(int check_airport=0;check_airport<my_sizes->cont[continent];check_airport++){
                if(strcmp(id,my_airports[continent][check_airport].id)==0){
                    return &my_airports[continent][check_airport];
                }
            }
        }
    }
    
    return NULL;
}

int Calc_distance( float lat1, float lon1, float lat2, float lon2 )
{
/* Function to calculate the distance between two coordinates in Kilometers*/

    // Earth's radius in Kilometers
	float Radius = 6371;

    //Difference between the two points
	float R_Lat = ToRadConv(lat2 - lat1);
	float R_Lon = ToRadConv(lon2 - lon1);

	//From degree to radian conversion
	lat1 =  ToRadConv(lat1);
	lat2 =  ToRadConv(lat2);

	float R_1 = pow ( sin(R_Lat/2), 2 ) + cos(lat1) * cos(lat2) * pow ( sin(R_Lon/2), 2 );

	float R_2 = 2 * atan2( sqrt(R_1), sqrt( 1 - R_1 ));
	float dis = Radius * R_2;

    //Returning the distance
	return dis;
}

//Degree to radian helper function
float ToRadConv(float deg) {
  /* Function to convert radian to degree*/
  return (deg * pi / 180);
}

//To calculate minimum element in the array
int minimum_array(int min_array[], int array_size)
{
    /*Function to calculate the minimum element in the array*/
    int c, minimum;

    minimum = min_array[0];

    for (c = 1; c < array_size; c++)
    {
        if (min_array[c] < minimum)
        {
           minimum = min_array[c];
        }
    }
    return minimum;
}


#ifdef DEBUG_ENABLED
void print_state(struct STATE *my_state) {
    char *cont;
    
    printf("Number of scenarios to generate: %d\n",my_state->num_scenarios);
    printf("Number of locations per scenario: %d\n",my_state->num_locations);

    printf("Distribution per location:\n");
    for(int print=0;print<7;print++) {
        switch(print) {
            case AF:
                cont="Africa";
                break;
            case AN:
                cont="Antarctica";
                break;
            case AS:
                cont="Asia";
                break;
            case EU:
                cont="Europe";
                break;
            case NA:
                cont="North America";
                break;
            case OC:
                cont="Australia";
                break;
            case SA:
                cont="South America";
                break;
        }
        printf("\t%s: %0.2f\n",cont,my_state->dist_locations[print]);
    }

    printf("Number of main logistics bases: %d\n",my_state->num_main_bases);

    printf("List of airports:\n");
    
    for(int print=0;print<my_sizes->locations;print++) {
        printf("\t%d - %s (%s)\n",print,my_state->airport_list[print]->name,my_state->airport_list[print]->id);
    }

    printf("Adjacency matrix:\n\t");
    for(int print=0;print<my_sizes->locations;print++) {
        printf("% 11d\t",print);
    }
    printf("\n");
    for(int print_row=0;print_row<my_sizes->locations;print_row++) {
        printf("%d\t",print_row);
        for(int print_col=0;print_col<my_sizes->locations;print_col++) {
            printf("% 11d\t",my_state->distance_matrix[print_row][print_col]);
        }
        printf("\n");
    }
}

void print_paths(struct PATH *my_paths) {
    printf("=== Paths (%d) ===\n",my_sizes->paths);
    
    for(int print=0;print<my_sizes->paths;print++) {
        printf("0/1 %d %d %d %0.5f %0.5f %d\n",my_paths[print].source_location,my_paths[print].dest_location,my_paths[print].next_location,my_paths[print].next_lat,my_paths[print].next_long,my_paths[print].aircraft_type);        
    }
}
#endif
