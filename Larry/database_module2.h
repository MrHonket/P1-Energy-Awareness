#include "global.h"

#define HOURS_PR_YEAR (365*24)

void init(void);
int  init_datab(pricedata *price_data, meterdata *meter_data, production *production_data);
void init_price_array(pricedata *price_data[]);


void print_index(int index);
dato date_from_string(char *str);


