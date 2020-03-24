//
//  main.c
//  helper_functions
//
//  Created by Olumide Akinola on 2020-03-16.
//  Copyright © 2020 Olumide Akinola. All rights reserved.
//

#include "../include/datafile.h"
#include "../include/helper_functions.h"


char* get_field(char *line, int col)
{
 
    int k = 1, j = 0;
    char *val = (char *)malloc(100 * sizeof(char));
    bool flag = true;
    for (int i = 0; line[i] != '\0'; i++) {
        if (flag && line[i] == ',') {
            k++;
        }
        else if (line[i] == '\"') {
            flag = !flag;
        }
        else if (k == col) {
            val[j++] = line[i];
        }
    }
    val[j] = '\0';
    return val;
}

int get_continent(char *val)
{

    
    if (val[0] == 'A' && val[1] == 'F'){
        return AF; // 0 index for AF
    }
    else if (val[0] == 'A' && val[1] == 'N'){
        return AN; // 1 index for AN
    }
    else if (val[0] == 'A' && val[1] == 'S'){
        return AS; // 2 index for AS
        
    }
    else if (val[0] == 'E' && val[1] == 'U'){
        return EU; // 3 index for EU
    }
    else if (val[0] == 'N' && val[1] == 'A'){
        return NA; // 4 index for OC
    }
    else if (val[0] == 'O' && val[1] == 'C'){
        return OC; // 5 index for NA
    }
    else if (val[0] == 'S' && val[1] == 'A'){
        return SA; // 6 index for SA
    }
    else{
        return -1;
        exit(-1);
    }
}

void increment(char *val, int *size)
{
 
    
    
    if (val[0] == 'A' && val[1] == 'F'){
        size[AF]++; // increment in AF array size
    }
    else if (val[0] == 'A' && val[1] == 'N'){
        size[AN]++; // increment in AN array size
    }
    else if (val[0] == 'A' && val[1] == 'S'){
        size[AS]++; // increment in AS array size
    }
    else if (val[0] == 'E' && val[1] == 'U'){
        size[EU]++; // increment in EU array size
    }
    else if (val[0] == 'N' && val[1] == 'A'){
        size[NA]++; // increment in OC array size
    }
    else if (val[0] == 'O' && val[1] == 'C'){
        size[OC]++; // increment in NA array size
    }
    else if (val[0] == 'S' && val[1] == 'A'){
        size[SA]++; // increment in SA array size
    }
}

struct AIRPORT** get_2D_array(int *size, char *line, char* fileName)
{
  
    

    FILE *pfile;
    
    /* array to save count of each continent */
    int count[7] = { 0 };
    pfile = fopen(fileName, "r");
    if (pfile == NULL){
        printf("%s file failed to open.\n", fileName);
    }
    else {
        /* skip first line */
        fgets(line, N, pfile);
        /* read all lines */
        while (fgets(line, N, pfile) != NULL) {
            /* find size of each continent array */
            char* val = get_field(line, 8);
            increment(val, size);
            free(val);
        }
        fclose(pfile);
        
        struct AIRPORT** arr = (struct AIRPORT **)malloc(7 * sizeof(struct AIRPORT*));
        for (int i = 0; i < 7; i++)
            arr[i] = (struct AIRPORT *)malloc(size[i] * sizeof(struct AIRPORT));
        
        pfile = fopen(fileName, "r");
        fgets(line, N, pfile);
        while (fgets(line, N, pfile) != NULL) {
            
            char *id = get_field(line, 2);
            
            char *name = get_field(line, 4);
            
            char *latitude = get_field(line, 5);
            
            char *lon = get_field(line, 6);
            
            char *continent = get_field(line, 8);
            
            char *country = get_field(line, 9);
            int a = get_continent(continent);
            /* store data into 2D array */
            arr[a][count[a]].id = id;
            arr[a][count[a]].name = name;
            arr[a][count[a]].lat = atoi(latitude);
            arr[a][count[a]].lon = atoi(lon);
            arr[a][count[a]].cont = continent;
            arr[a][count[a]].country = country;
            /* increment in respective array count */
            count[a]++;
        }
        
        fclose(pfile);
        /* return 2D array of objects */
        return arr;
    }
    return NULL;
}
