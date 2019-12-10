/* Jakob */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "global.h"

void init_database(void);
data *get_price_for_timeinterval_in_area(dato from, dato to,  area area);
data *get_consumption_for_timeinterval_at_id(dato from, dato to, char *id);