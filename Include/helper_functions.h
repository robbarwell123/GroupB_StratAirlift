//
//  main.c
//  common_functions
//
//  Created by Olumide Akinola on 2020-03-15.
//  Copyright © 2020 Olumide Akinola. All rights reserved.
//

#include "datafile.h"

struct AIRPORT** get_2D_array(int *size, char *line);
char* get_field(char *line, int col);
int get_continent(char *val);
void increment(char *val, int *size);
