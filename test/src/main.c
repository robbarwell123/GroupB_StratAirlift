//
//  main.c
//  set_aiports
//
//  Created by Olumide Akinola on 2020-03-21.
//  Copyright © 2020 Olumide Akinola. All rights reserved.
//

#include "../include/set_airports.h"
#include "../include/set_airports_as_null.h"

int main()
{
    /* get 2D array of objects */

    int size[7] ;


    struct AIRPORT** arr = set_airports(size);


    int num_of_airports =parse_airports();

    int num_of_airports2 =parse_airports_as_null();
    
    printf("\nSet airport returns: %d\n\n",num_of_airports);
    
    printf("Set airport as Null returs: %d\n\n",num_of_airports2);
    

    if (arr != NULL) {
        /* print 2D array data */
        printf("\n\t LIST OF AIRPORTS UNDER SET AIRPORTS\n\n");
        printf("   ID , NAME , LATITUDE , LONGITUDE , CONTINENT , COUNTRY\n");
        printf("------------------------------------------\n");
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < size[i]; j++) {
                printf("row %d: %s , %s , %f , %f , %s , %s\n \n", i+1, arr[i][j].id, arr[i][j].name, arr[i][j].lat, arr[i][j].lon, arr[i][j].cont, arr[i][j].country);
            }
        }
      
    }


    return 0;
}
