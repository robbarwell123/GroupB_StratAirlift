//
//  mainfile.c
//  
//
//  Created by Olumide Akinola on 2020-03-14.
//

#include "../include/datafile.h"
#include "../include/helper_functions.h"


int main()
{
    /* get 2D array of objects */
    
    int size[7] ;
    
    char line[N];
    
    struct AIRPORT** arr = get_2D_array(size, line);
    if (arr != NULL) {
        /* print 2D array data */
        printf("   ID , NAME , LATITUDE , LONGITUDE , COUNTRY\n");
        printf("------------------------------------------\n");
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < size[i]; j++) {
                printf("row %d: %d , %s , %f , %f , %s\n \n", i+1, arr[i][j].id, arr[i][j].name, arr[i][j].latitude, arr[i][j].lon, arr[i][j].country);
            }
        }
    }
    
    return 0;
}
