#ifndef LANGUAGE_H
#define LANGUAGE_H

#include "global.h"

void l_prompt_user(user User);
void l_user_history(user User, data *Data);
void l_info_energy_saving(user User,data *Data);
void l_update_settings(user User,data *Data);
void l_system_information(user User,data *Data);
void l_consumption_check(user User,data *Data);
void l_future_data(user User,data *Data);
void l_warning_energy_saving(user User,data *Data);
void l_machine_activation(user User,data *Data);

#endif