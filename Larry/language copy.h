#ifndef LANGUAGE_H
#define LANGUAGE_H

#include "global.h"


void l_prompt_user(user *User);
void l_prompt_date(user User);
void l_user_history(user *User, data *Data);
void l_info_energy_saving(user *User,data *data_array);
  void cheapest(data data_array[], user *User);
  void print_information(data return_array[], user *User);
void l_update_settings(user *User);
void l_saving_advice(user *User,data *Data);
void l_consumption_check(user *User,data *Data);
void l_warning_energy_saving(user *User, data *Data);
void l_morningProcedure(user *User);
void print_warning(user *User);
void l_machine_activation(user *User, data *Data);
void set_user_date_from(user *User);
void set_user_date_to(user *User);
void set_User_choice_lookup(user *User);
void init_user(user *User);
data *get_data(user *User);
void l_update_Language(user *User);
void l_update_Area(user *User);
void l_update_Id(user *User);


#endif
