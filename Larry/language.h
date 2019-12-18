#ifndef LANGUAGE_H
#define LANGUAGE_H

#include "global.h"

void l_prompt_user(user User);
void l_user_history(user User, data *Data);
void l_info_energy_saving(user User,data *Data);
void l_update_settings(user User);
void l_saving_advice(user User,data *Data);
void l_consumption_check(user User,data *Data);
void l_warning_energy_saving(user User, data *Data);
void print_warning(user User);
void l_machine_activation(user User, data *Data);

#endif
