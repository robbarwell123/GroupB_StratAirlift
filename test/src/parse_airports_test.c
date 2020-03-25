//
//  main.c
//  parse_Aiprorts
//
//  Created by Olumide Akinola on 2020-03-16.
//  Copyright © 2020 Olumide Akinola. All rights reserved.
//

#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <stdbool.h>

#include "../../include/data_types.h"



int parse_airports(struct AIRPORT** my_airports, char *airport_file)
{
    
    int size[7] ;
    
    // get 2D array of objects
    int arr_size =0;
    
    if (my_airports != NULL) {
     
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < size[i]; j++) {
                arr_size++;
            }
        }
        printf("The total aiprorts are: %d\n ", arr_size);
        return 0;
    }
    else{
        
    return -1;
    }
}

