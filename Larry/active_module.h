#ifndef ACTIVE_H
#define ACTIVE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "global.h"                 //Implementeret og brugbart!
#include "language.h"               //Implementeret og brugbart!
#include "database_module.h"        //Implementeret og brugbart!
#include "user_history.h"           //Implementeret og brugbart!
#include "update_settings.h"        //Implementeret og brugbart!
#include "info_energy_saving.h"     //Implementeret og brugbart!
#include "passive_module.h"         //Implementeret og brugbart!
#include "warning_energy_saving.h"  //Implementeret og brugbart!
#include "saving_advice.h"     //Implemented som error_message!
#include "machine_activation.h"     //Implemented som error_message!
#include "consumption_check.h"      //Implemented som error_message!
#include "debug.h"                  //implementeret og brugbart!


/*Dette er prototyper i programmet.*/
int check_for_run_module(user *User);
int prompt_user(user *User,data *Data);
    data* copy_data(user User,data *Data);
void log_data_use(data Output);

#endif