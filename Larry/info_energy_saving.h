#ifndef INFO_ENERGY_SAVING_H
#define INFO_ENERGY_SAVING_H

#include "global.h"

double info_energy_saving(user User, data* Data, int hour_choice);
void cheapest(data data_array[], user User);
int cmpfunc(const void * a, const void * b);
void print_information(data return_array[], user User, int hour_choice);
void dialog_with_user(data data_array[], user User, double info);
void overview_for_interval(data data_array[], user User, int from_hour, int to_hour);

#endif //INFO_ENERGY_SAVING_H