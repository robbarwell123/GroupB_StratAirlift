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

#define N   (1024 *4) /* 4 KBytes*/



#define AF 0 /**< Position of the Africa continent in the main list of airports. */
#define AN 1 /**< Position of the Antarctica continent in the main list of airports. */
#define AS 2 /**< Position of the Asia continent in the main list of airports. */
#define EU 3 /**< Position of the Europe continent in the main list of airports. */
#define NA 4 /**< Position of the North America continent in the main list of airports. */
#define OC 5 /**< Position of the Australia continent in the main list of airports. */
#define SA 6 /**< Position of the South America continent in the main list of airports. */

/**
 * @brief Used to store information about individual airports.
 *
 * Information is read in from https://ourairports.com/data/ and filtered for the AIRPORT structure.
 */
struct AIRPORT {
    char *id; /**< Airport ICAO ID.*/
    char *name; /**< Airport name. */
    float lat; /**< Airport latitude. */
    float lon; /**< Airport longitude. */
    char *cont; /**< Airport continent. */
    char *country; /**< Airport country. */
};



