//
//
//  datafile
//
//  Created by Olumide Akinola on 2020-03-15.
//  Copyright © 2020 Olumide Akinola. All rights reserved.
//

#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <stdbool.h>

#define N    (1024 *4) /* 4 KBytes */

struct AIRPORT {
    int id;
    char* name;
    float latitude;
    float lon;
    char* country;
};



