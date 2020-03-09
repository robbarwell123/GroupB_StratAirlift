#ifndef __DATA_TYPES_H__
#define __DATA_TYPES_H__

#define AF 0
#define AN 1
#define AS 2
#define EU 3
#define NA 4
#define OC 5
#define SA 6

struct AIRPORT {
    char *id;
    char *name;
    float lat;
    float lon;
    char *cont;
    char *country;
};

struct STATE {
    int num_scenarios;
    int num_locations;
    float dist_locations[7];
    int num_main_bases;
    struct AIRPORT **airport_list;
    int **distance_matrix;
};

struct PATH {
    int source_location;
    int dest_location;
    int next_location;
    float next_lat;
    float next_long;
    int aircraft_type;
};

struct SIZES {
    int cont[7];
    int locations;
};

#endif // __DATA_TYPES_H__