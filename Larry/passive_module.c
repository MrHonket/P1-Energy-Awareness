/* switch module */
#include <stdio.h>
#include <stdlib.h>
#include "global.h"
//#include "warning_energy_saving.h"
#include "machine_activation.h"

int passive_module(user User, data Data);
/*DEM HERUNDER SLETTES NÅR DERES INCLUDE ER IMPLEMENTERET!*/
void warning_energy_saving(user User, data Data){int test = 0;}
//void machine_activation(user User, data Data){int test = 0;}

/* returns 1 for exit_succes and 0 for exit_failure */
int passive_module(user User, data Data)
{
   if(User.choice.function == WarningEnergySaving)
      {
      warning_energy_saving(User, Data);
      return 1;
      }
   else if(User.choice.function == MachineActivation)
      {
      machine_activation(User, Data);
      return 1;  
      }
   else
      return 0;

}

