#ifndef UPDATE_SETTINGS_H
#define UPDATE_SETTINGS_H

#include "global.h"

void update_settings(user *User);
void update_Language(user *User);
void update_Area(user *User);
void update_Id(user *User);
settings load_settings(user *User);
void update_next_activation(user *User);
void update_warning_energy_saving(void);
void update_machine_activation(void);

#endif //UPDATE_SETTINGS_H
