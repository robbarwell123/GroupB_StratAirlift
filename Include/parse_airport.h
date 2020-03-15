//
//  main.c
//  Read line
//
//  Created by Olumide Akinola on 2020-02-28.
//  Copyright © 2020 Olumide Akinola. All rights reserved.
//

#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <stdbool.h>

/* structure to store the airport information */
struct data {
    int id;
    char* name;
    double latitude;
    double longitude;
    char* country;
};
/* array to save size of each continent */
int size[7] = { 0 };
/* array to save count of each continent */
int count[7] = { 0 };
int N = 4096; // Maximum line lenght


struct data** get_2D_array(void);
char* get_field(char line[N], int col);
int get_continent(char *val);
void increment(char *val);

char* get_field(char line[N], int col)
{
    /* This function is used to get a cell in each line of the CSV file to be read */
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
    /* This function is used to get continent indexing from 0 to 6 , i.e AF = 0, AN = 1, AS = 2, EU = 3, OC = 4, NA = 5, SA = 6 */
    
    if (val[0] == 'A' && val[1] == 'F'){
        return 0; // 0 index for AF
    }
    else if (val[0] == 'A' && val[1] == 'N'){
        return 1; // 1 index for AN
    }
    else if (val[0] == 'A' && val[1] == 'S'){
        return 2; // 2 index for AS
        
    }
    else if (val[0] == 'E' && val[1] == 'U'){
        return 3; // 3 index for EU
    }
    else if (val[0] == 'O' && val[1] == 'C'){
        return 4; // 4 index for OC
    }
    else if (val[0] == 'N' && val[1] == 'A'){
        return 5; // 5 index for NA
    }
    else{
        return 6; // 6 index for SA
    }
}

void increment(char *val)
{
    /* This function is used to increment the size of each row of continents */
    
    if (val[0] == 'A' && val[1] == 'F'){
        size[0]++; // increment in AF array size
    }
    else if (val[0] == 'A' && val[1] == 'N'){
        size[1]++; // increment in AN array size
    }
    else if (val[0] == 'A' && val[1] == 'S'){
        size[2]++; // increment in AS array size
    }
    else if (val[0] == 'E' && val[1] == 'U'){
        size[3]++; // increment in EU array size
    }
    else if (val[0] == 'O' && val[1] == 'C'){
        size[4]++; // increment in OC array size
    }
    else if (val[0] == 'N' && val[1] == 'A'){
        size[5]++; // increment in NA array size
    }
    else if (val[0] == 'S' && val[1] == 'A'){
        size[6]++; // increment in SA array size
    }
}

struct data** get_2D_array()
{
    /* this function is used to get 2DArray of struct objects */
    char *fileName = "airports.csv";
    FILE *pfile;
    char line[N];
    pfile = fopen(fileName, "r");
    if (pfile == NULL){
        printf("%s file failed to open.", fileName);
    }
    else {
        /* skip first line */
        fgets(line, N, pfile);
        /* read all lines */
        while (fgets(line, N, pfile) != NULL) {
            /* find size of each continent array */
            char* val = getField(line, 8);
            increment(val);
            free(val);
        }
        fclose(pfile);
        
        struct data** arr = (struct data **)malloc(7 * sizeof(struct data*));
        for (int i = 0; i < 7; i++)
            arr[i] = (struct data *)malloc(size[i] * sizeof(struct data));
    
        pfile = fopen(fileName, "r");
        fgets(line, N, pfile);
        while (fgets(line, N, pfile) != NULL) {
            
            char *id = getField(line, 1);
            
            char *name = getField(line, 4);
            
            char *latitude = getField(line, 5);
            
            char *longitude = getField(line, 6);
            
            char *continent = getField(line, 8);
            
            char *country = getField(line, 9);
            int a = get_continent(continent);
            /* store data into 2D array */
            arr[a][count[a]].id = atoi(id);
            arr[a][count[a]].name = name;
            arr[a][count[a]].latitude = atoi(latitude);
            arr[a][count[a]].longitude = atoi(longitude);
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

