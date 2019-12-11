/* Jakob */
#ifndef DATABASE_MODULE_H
#define DATABASE_MODULE_H

void init_database(void);
data *get_price_for_timeinterval_in_area(dato from, dato to,  area area);
data *get_consumption_for_timeinterval_at_id(dato from, dato to, char *id);
dato date_from_string(char *date, int time);


#endif //DATABASE_MODULE_H