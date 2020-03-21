//
//  main.c
//  set_aiports
//
//  Created by Olumide Akinola on 2020-03-21.
//  Copyright © 2020 Olumide Akinola. All rights reserved.
//

#include "../include/set_airports_as_null.h"

struct AIRPORT** set_airports_as_null(int* size) {
    struct AIRPORT **temp_airports;
    
    temp_airports=(struct AIRPORT**)malloc(sizeof(struct AIRPORT*)*7);
    
    for(int init=0;init<7;init++)
    {
        temp_airports[init]=NULL;
    }
    
    temp_airports= NULL;
    
  
    
    return temp_airports;
}


int parse_airports_as_null()
{

    int size[7] ;
    
    struct AIRPORT** my_airports = set_airports_as_null(size);

    int arr_size =0;

    if (my_airports != NULL) {

        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < size[i]; j++) {
                arr_size++;
            }
        }
        printf("The total aiports are: %d\n ", arr_size);
        return 0;
    }
    else{

    return -1;
    }
}
