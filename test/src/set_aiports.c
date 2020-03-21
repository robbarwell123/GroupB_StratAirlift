//
//  main.c
//  set_aiports
//
//  Created by Olumide Akinola on 2020-03-21.
//  Copyright © 2020 Olumide Akinola. All rights reserved.
//

#include "../include/set_airports.h"


struct AIRPORT** set_airports(int* size) {
    struct AIRPORT **temp_airports;
    
    temp_airports=(struct AIRPORT**)malloc(sizeof(struct AIRPORT*)*7);
    
    for(int init=0;init<7;init++)
    {
        temp_airports[init]=NULL;
    }
    
    
    temp_airports[NA]=(struct AIRPORT*)malloc(sizeof(struct AIRPORT));
    temp_airports[EU]=(struct AIRPORT*)malloc(sizeof(struct AIRPORT)*2);
    temp_airports[AF]=(struct AIRPORT*)malloc(sizeof(struct AIRPORT));
    temp_airports[SA]=(struct AIRPORT*)malloc(sizeof(struct AIRPORT));
    
    temp_airports[NA][0].id="CYTZ";
    temp_airports[NA][0].name="CFB Trenton";
    temp_airports[NA][0].lat=44.1189003;
    temp_airports[NA][0].lon=-77.52809906;
    temp_airports[NA][0].cont="NA";
    temp_airports[NA][0].country="CA";

    temp_airports[EU][0].id="EDDK";
    temp_airports[EU][0].name="Cologne Bonn Airport";
    temp_airports[EU][0].lat=50.86589813;
    temp_airports[EU][0].lon=7.142739773;
    temp_airports[EU][0].cont="EU";
    temp_airports[EU][0].country="DE";
    
    temp_airports[EU][1].id="EGPF";
    temp_airports[EU][1].name="Glasgow International Airport";
    temp_airports[EU][1].lat=55.871899;
    temp_airports[EU][1].lon=-4.43306;
    temp_airports[EU][1].cont="AF";
    temp_airports[EU][1].country="GB";

    temp_airports[AF][0].id="HKJK";
    temp_airports[AF][0].name="Jomo Kenyatta International Airport";
    temp_airports[AF][0].lat=-1.319239974;
    temp_airports[AF][0].lon=36.92779922;
    temp_airports[AF][0].cont="AF";
    temp_airports[AF][0].country="KE";

    temp_airports[SA][0].id="SKBO";
    temp_airports[SA][0].name="El Dorado International Airport";
    temp_airports[SA][0].lat=4.70159;
    temp_airports[SA][0].lon=-74.1469;
    temp_airports[SA][0].cont="SA";
    temp_airports[SA][0].country="CO";
    



    size[AF]=1;
    size[AN]=0;
    size[AS]=0;
    size[EU]=2;
    size[NA]=1;
    size[OC]=0;
    size[SA]=1;
    
  
    
    return temp_airports;
}

int parse_airports()
{

    int size[7] ;
    
    struct AIRPORT** my_airports = set_airports(size);

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
