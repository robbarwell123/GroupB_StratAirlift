#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/data_types.h"
#include "../include/common_functions.h"



int **find_closest()
{

        struct AIRPORT {
        char *id;
        char *name;
        double latitude;
        double longitude;
        char *cont;
        char *country;
        } AIRPORT;

//Declaring array of pointers

    struct AIRPORT *(ap_array[10]);

    struct AIRPORT airport1 = {"1", "ATL/KATL", 33.6407, 84.4277, "1", "US"};
    struct AIRPORT airport2 = {"2", "PEK/ZBAA", 40.0799, 116.6031, "2", "China"};
    struct AIRPORT airport3 = {"3", "HND/RJTT", 35.5494, 139.7798, "3", "Japan"};
    struct AIRPORT airport4 = {"4", "LHR/EGLL", 51.4700, 0.4543, "4", "UK"};
    struct AIRPORT airport5 = {"5", "CDG/LFPG", 49.0097, 2.5479, "5", "France"};
    struct AIRPORT airport6 = {"6", "FRA/EDDF", 50.0379, 8.5622, "6", "Germany"};


    struct AIRPORT *AP_ptr1;
    struct AIRPORT *AP_ptr2;
    struct AIRPORT *AP_ptr3;
    struct AIRPORT *AP_ptr4;
    struct AIRPORT *AP_ptr5;
    struct AIRPORT *AP_ptr6;


    AP_ptr1 = &airport1;
    AP_ptr2 = &airport2;
    AP_ptr3 = &airport3;
    AP_ptr4 = &airport4;
    AP_ptr5 = &airport5;
    AP_ptr6 = &airport6;

    ap_array[0] = AP_ptr1;
    ap_array[1] = AP_ptr2;
    ap_array[2] = AP_ptr3;
    ap_array[3] = AP_ptr4;
    ap_array[4] = AP_ptr5;
    ap_array[5] = AP_ptr6;

    /*-------------------------------------------------------------------*/

    int location = 2, main_bases = 4, my_size=6;
    int k = 0, l=0, k1=0; //counters to keep in track of index in 2D array
    int dis_array[main_bases]; // Array to store the distance calculated
    int min_dist_array[my_size]; // Array to store min distance

    double nLat1, nLon1, nLat2, nLon2, distance; //Latitude and longitude

    int **distance_matrix = NULL; // 2D dynamic matrix
    int nRow = my_size; //variable store number of Row
    int nColumn = location; //variable store number of Row
    int iRow = 0; //Variable for looping Row
    int iCol = 0; //Variable for looping column

    //Allocate memory for row
    distance_matrix = (int **)malloc(nRow * sizeof(int*));

    //Allocate memory for column
    for (iRow =0 ; iRow < nRow ; iRow++)
    {
        distance_matrix[iRow] = (int *)malloc(nColumn * sizeof(int));
    }


    for(int i=nColumn; i<my_size; i++){
        for(int j=0; j<nColumn; j++){

            nLat1 = ap_array[i]->latitude;
            nLon1 = ap_array[i]->longitude;
            nLat2 = ap_array[j]->latitude;
            nLon2 = ap_array[j]->longitude;

            //Distamce calculation betweem two locations
            distance = Calc_distance(nLat1 , nLon1, nLat2, nLon2 );

            //Distance calculated is stored in a 1D array for minimum calculation
            dis_array[k] = distance;
            k+=1;
        }
        l+=1;

        // To calculate the minimum element in an array
        min_dist_array[i] = minimum_array(dis_array, k);
        distance_matrix[k1][l] = min_dist_array[i];
        distance_matrix[l][k1] = min_dist_array[i];
        printf("\nElements in the  distance_matrix[%d][%d] : %d\n", k1, l, min_dist_array[i]);
        printf("\nElements in the  distance_matrix[%d][%d] : %d\n", l, k1, min_dist_array[i]);
        k=0;
        k1+=1;
    }

    //free the 2D array;
    free(distance_matrix);

    return 0;
    }
