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
#include "../../include/read_airports_funtions.h"
#include "../../include/parse_airports.h"

int parse_airpors_test(){
    

    int size[7] ;

    char line[N];
    char filename_1[100]= "airports_empty.csv";
    char filename_2[100]= "airports_known_number.csv";
    char filename_3[100] = "airports_copy_wider_size_array.csv";
        
    printf("TEST CASE 1: Empty CSV\n");
    printf("OUTPUT EXPECTED: O airports and returns 0 because it runs effectively\n");
    struct AIRPORT** arr_1 = get_2D_array(size, line, filename_1);
    int num_of_airports_1 =parse_airports(arr_1, line);


    printf("TEST CASE 2: known length of CSV\n");
    printf("OUTPUT EXPECTED: 5 airports and returns 0 because it runs effectively\n");
    struct AIRPORT** arr_2 = get_2D_array(size, line,filename_2);
    int num_of_airports_2 =parse_airports(arr_2, line);


    printf("TEST CASE 3: Continet size increased to 8\n");
    printf("OUTPUT EXPECTED: returns -1 as file fails to \n\n");
    struct AIRPORT** arr_3 = get_2D_array(size, line, filename_3);
    int num_of_airports_3 =parse_airports(arr_3, line);

    
    if (num_of_airports_1 == 0 && num_of_airports_2 == 0 && num_of_airports_3 == -1){
           return 0;
    }
    else{
        
            return -1;
    }

}

