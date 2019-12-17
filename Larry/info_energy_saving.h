#ifndef INFO_ENERGY_SAVING_H
#define INFO_ENERGY_SAVING_H

#include "global.h"

double info_energy_saving(user User, data* Data);
int cmpfunc_DK1(const void * a, const void * b);
int cmpfunc_DK2(const void * a, const void * b);
void overview_for_interval(user User,data data_array[]);

#endif //INFO_ENERGY_SAVING_H
