#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <stdbool.h>

#include "../include/data_types.h"
#include "../include/parse_airports.h"

char* get_field(char *curr_line, int col) {
    int curr_field = 1, copy_char = 0;
    char *field_value = (char *)malloc(100 * sizeof(char));
    bool found_field = true;

    for (int curr_char = 0; curr_line[curr_char] != '\0'; curr_char++) {
        if (found_field && curr_line[curr_char] == ',') {
            curr_field++;
        }else if (curr_line[curr_char] == '\"') {
            found_field = !found_field;
        }else if (curr_field == col) {
            field_value[copy_char++] = curr_line[curr_char];
        }
    }
    field_value[copy_char] = '\0';

    return field_value;
}

int get_continent(char *field_value) {
    if (field_value[0] == 'A' && field_value[1] == 'F'){
        return AF;
    }else if (field_value[0] == 'A' && field_value[1] == 'N'){
        return AN;
    }else if (field_value[0] == 'A' && field_value[1] == 'S'){
        return AS;  
    }else if (field_value[0] == 'E' && field_value[1] == 'U'){
        return EU;
    }else if (field_value[0] == 'N' && field_value[1] == 'A'){
        return NA;
    }else if (field_value[0] == 'O' && field_value[1] == 'C'){
        return OC;
    }else if (field_value[0] == 'S' && field_value[1] == 'A'){
        return SA;
    }else{
        return -1;
    }
}

int parse_airports(char *airport_file,struct AIRPORT** my_airports) {    
    char curr_line[MAX_LINE_LENGTH];
    char *id;
    char *type;
    char *name;
    char *latitude;
    char *lon;
    char *continent;
    char *country;
    int continent_index;
    int valid_type;
    
    FILE *curr_airport_file;
    
    curr_airport_file = fopen(airport_file, "r");
    if (curr_airport_file == NULL){
        printf("Failed to open common airport file: %s.\n", airport_file);
        return -1;
    } else {
        /* skip first curr_line */
        fgets(curr_line, MAX_LINE_LENGTH, curr_airport_file);
        while (fgets(curr_line, MAX_LINE_LENGTH, curr_airport_file) != NULL){
            id = get_field(curr_line, 2);
            name = get_field(curr_line, 4);
            latitude = get_field(curr_line, 5);
            lon = get_field(curr_line, 6);
            continent = get_field(curr_line, 8);
            country = get_field(curr_line, 9);
            continent_index = get_continent(continent);
            type = get_field(curr_line,3);
            if(strcmp(type,"medium_airport")==0 || strcmp(type,"large_airport")==0) {
                valid_type=1;
            }else{
                valid_type=0;
            }
            free(type);
            if (continent_index != -1 && valid_type){
                if(my_airports[continent_index]==NULL) {
                    my_airports[continent_index]=(struct AIRPORT*)malloc(sizeof(struct AIRPORT));
                }else {
                    my_airports[continent_index]=(struct AIRPORT*)realloc(my_airports[continent_index],sizeof(struct AIRPORT)*(my_sizes->cont[continent_index]+1));
                }
                if(my_airports[continent_index]!=NULL) {
                    my_airports[continent_index][my_sizes->cont[continent_index]].id=id;
                    my_airports[continent_index][my_sizes->cont[continent_index]].name=name;
                    my_airports[continent_index][my_sizes->cont[continent_index]].lat=atoi(latitude);
                    my_airports[continent_index][my_sizes->cont[continent_index]].lon=atoi(lon);
                    my_airports[continent_index][my_sizes->cont[continent_index]].cont=continent;
                    my_airports[continent_index][my_sizes->cont[continent_index]].country=country;
                    my_sizes->cont[continent_index]++;
                }
            }
        }
        fclose(curr_airport_file);
        return 0;
    }

}