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

// structure to store data
struct data {
    int id;
    char* name;
    double latitude;
    double longitude;
    char* country;
};
// array to save size of each continent
int size[7] = { 0 };
// array to save count of each continent
int count[7] = { 0 };
int N = 4096;

struct data** get2DArray(void);
char* getField(char line[N], int col);
int getContinent(char *val);
void increment(char *val);

char* getField(char line[N], int col)
{
    // this function is used to get a cell/field in given line/row/record
    int k = 1, j = 0;
    char *val = (char *)malloc(100 * sizeof(char));
    bool flag = true;
    for (int i = 0; line[i] != '\0'; i++) {
        if (flag && line[i] == ',') k++;
        else if (line[i] == '\"') flag = !flag;
        else if (k == col) val[j++] = line[i];
    }
    val[j] = '\0';
    return val;
}

int getContinent(char *val)
{
    // this function is used to get continent index 0 to 6
    if (val[0] == 'A' && val[1] == 'F')return 0; // 0 index for AF
    else if (val[0] == 'A' && val[1] == 'N')return 1; // 1 index for AN
    else if (val[0] == 'A' && val[1] == 'S')return 2; // 2 index for AS
    else if (val[0] == 'E' && val[1] == 'U')return 3; // 3 index for EU
    else if (val[0] == 'O' && val[1] == 'C')return 4; // 4 index for OC
    else if (val[0] == 'N' && val[1] == 'A')return 5; // 5 index for NA
    else return 6; // 6 index for SA
}

void increment(char *val)
{
    // this function is used to increment in the continent size
    if (val[0] == 'A' && val[1] == 'F')size[0]++; // increment in AF array size
    else if (val[0] == 'A' && val[1] == 'N')size[1]++; // increment in AN array size
    else if (val[0] == 'A' && val[1] == 'S')size[2]++; // increment in AS array size
    else if (val[0] == 'E' && val[1] == 'U')size[3]++; // increment in EU array size
    else if (val[0] == 'O' && val[1] == 'C')size[4]++; // increment in OC array size
    else if (val[0] == 'N' && val[1] == 'A')size[5]++; // increment in NA array size
    else if (val[0] == 'S' && val[1] == 'A')size[6]++; // increment in SA array size
}

struct data** get2DArray()
{
    // this function is used to get 2DArray of struct objects
    char *fileName = "airports.csv";
    FILE *pfile;
    char line[N];
    // open file
    pfile = fopen(fileName, "r");
    if (pfile == NULL)
        printf("%s file failed to open.", fileName);
    else {
        // skip first line
        fgets(line, N, pfile);
        // read all lines
        while (fgets(line, N, pfile) != NULL) {
            // find size of each continent array
            char* val = getField(line, 8);
            increment(val);
            free(val);
        }
        // file close
        fclose(pfile);
        struct data** arr = (struct data **)malloc(7 * sizeof(struct data*));
        for (int i = 0; i < 7; i++)
            arr[i] = (struct data *)malloc(size[i] * sizeof(struct data));
        // file open
        pfile = fopen(fileName, "r");
        fgets(line, N, pfile);
        while (fgets(line, N, pfile) != NULL) {
            // get id
            char *id = getField(line, 1);
            // get name
            char *name = getField(line, 4);
            // get latitude
            char *latitude = getField(line, 5);
            // get longitude
            char *longitude = getField(line, 6);
            // get continent
            char *continent = getField(line, 8);
            // get country
            char *country = getField(line, 9);
            int a = getContinent(continent);
            // store data into object
            arr[a][count[a]].id = atoi(id);
            arr[a][count[a]].name = name;
            arr[a][count[a]].latitude = atoi(latitude);
            arr[a][count[a]].longitude = atoi(longitude);
            arr[a][count[a]].country = country;
            // increment in respective array count
            count[a]++;
        }
        // file close
        fclose(pfile);
        // return 2D array of objects
        return arr;
    }
    return NULL;
}


