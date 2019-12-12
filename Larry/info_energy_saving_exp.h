#ifndef INFO_ENERGY_SAVING_H
#define INFO_ENERGY_SAVING_H

#include "global.h"

double info_energy_saving(user User, data* Data);
data *cheapest(data data_array[], user User);
int cmpfunc(const void * a, const void * b);
void print_information(data return_array[], data cheapest_struct, user User);
void dialog_with_user(data data_array[], user User, double info, data cheapest_struct);

#endif //INFO_ENERGY_SAVING_H