/* Jakob */
#ifndef DATABASE_MODULE_H
#define DATABASE_MODULE_H
#include "global.h"

void init_database(void);
data *get_price_for_timeinterval_in_area(dato from, dato to,  area area);

/* HELPER functions */
/* 01-01-2017  22 */
dato    date_from_stringDMYI(char *str,int time);
/* 2017 01 01 22.00 */
dato    date_from_stringYMDH(char *date);

void    print_price_index(int index);
void    print_consump_index(int index);
/* int     calc_time(dato from, dato to);

int     calc_time(dato from, dato to); */





#endif //DATABASE_MODULE_H
