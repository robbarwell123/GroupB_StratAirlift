#ifndef __COMMON_FUNCTIONS_H__
#define __COMMON_FUNCTIONS_H__

#include "data_types.h"

int calc_distance(float lat1, float lon1, float lat2, float lon2);
struct AIRPORT* find_airport(char *id,struct AIRPORT **my_airports); 

void print_state(struct STATE *my_state);

#endif // __COMMON_FUNCTIONS_H__