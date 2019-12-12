/* switch module */
#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "warning_energy_saving_exp.h" //IMPLEMENTERET SOM EXP!!!!
#include "machine_activation.h"  
#include "update_settings.h"
int passive_module(user User, data *Data);

/* returns 1 for exit_succes and 0 for exit_failure */
int passive_module(user User, data *Data)
{
   update_next_activation();

   if(User.choice.function == WarningEnergySaving)
      {
      printf("IMPLEMENTERET SOM EXP VERSION I PASSIVE_MODULE!!!\n");
      warning_energy_saving(User, Data);
      printf("IMPLEMENTERET SOM EXP VERSION I PASSIVE_MODULE!!!\n");
      return 1;
      }
   else if(User.choice.function == MachineActivation)
      {
      machine_activation(User, Data);
      return 1;  
      }
   else
      return 0;

   update_next_activation();
}
