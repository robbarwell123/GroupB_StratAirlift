#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../include/data_types.h"
#include "../include/common_functions.h"
#include "../include/calc_shortest_path.h"

// Defined in the main.c file
extern struct SIZES *my_sizes;

int dijsktra(int source, struct STATE *my_state, struct PATH **my_paths) {
    int dist[my_sizes->locations];                      // Current shortest distance between the source and locations
    int visited[my_sizes->locations];                   // Whether the current location has been visited
    int next[my_sizes->locations];                      // The first location on the shortest path to destination
    int curr=source;                                    // The current location being visited
    int smallest_value=0;                               // The next smallest distance to visit
    int rtn_val=0;                                      // The current state of the function to return

    // Initialization for arrays
    for(int init=0;init<my_sizes->locations;init++) {
        dist[init]=INT_MAX;
        visited[init]=0;
    }
    
    dist[curr]=0;
    next[curr]=0;
    
    // Loops through until all locations have been visited
    while(curr!=INT_MAX) {
        for(int check=0;check<my_sizes->locations;check++) {
            if(visited[check]!=1 && my_state->distance_matrix[curr][check]!=INT_MAX && (dist[curr]+my_state->distance_matrix[curr][check])<dist[check]) {
                dist[check]=(dist[curr]+my_state->distance_matrix[curr][check]);
                if(curr==source) {
                    next[check]=check;
                }else {
                    next[check]=next[curr];
                }
            }
        }

        visited[curr]=1;
        
        smallest_value=INT_MAX;
        curr=INT_MAX;
        for(int check=0;check<my_sizes->locations;check++) {
            if(visited[check]!=1 && dist[check]<smallest_value) {
                smallest_value=dist[check];
                curr=check;
            }
        }
    }
    
    #ifdef DEBUG_ENABLED
    printf("Shortest Path Distance\n");
    for(int print=0;print<my_sizes->locations;print++) {
        printf("Dist[%d]=%d\n",print,dist[print]);
    }
    printf("Next Location\n");
    for(int print=0;print<my_sizes->locations;print++) {
        printf("Next[%d]=%d\n",print,next[print]);
    }
    #endif

    // Converts the shortest paths into the path format required for the strategic airlift simulator
    for(int convert=0;convert<my_sizes->locations;convert++) {
        if(convert!=source) {
            my_sizes->paths++;
            *my_paths=realloc(*my_paths,sizeof(struct PATH)*my_sizes->paths);
            if((*my_paths)!=NULL && rtn_val==0) {
                (*my_paths)[my_sizes->paths-1].source_location=source;
                (*my_paths)[my_sizes->paths-1].dest_location=convert;
                (*my_paths)[my_sizes->paths-1].next_location=next[convert];
                (*my_paths)[my_sizes->paths-1].next_lat=my_state->airport_list[next[convert]]->lat;
                (*my_paths)[my_sizes->paths-1].next_long=my_state->airport_list[next[convert]]->lon;
                (*my_paths)[my_sizes->paths-1].aircraft_type=(source<my_state->num_main_bases && convert<my_state->num_main_bases) ? 1 : 2;
            }else {
                printf("Error allocating memory to store paths.\n");
                rtn_val=-1;
            }
        }
    }
    
    return rtn_val;
}

int calc_shortest_path(struct STATE *my_state, struct PATH **my_paths) {
    int rtn_val=0;                                      // The current state of the function to return
    
    for(int calc_paths=0;calc_paths<my_sizes->locations;calc_paths++) {
        if(rtn_val==0) {
            rtn_val=dijsktra(calc_paths,my_state,my_paths);        
        }
    }
    
    return rtn_val;
}