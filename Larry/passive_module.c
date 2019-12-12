/* switch module */
#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "warning_energy_saving.h"
#include "machine_activation.h"  
#include "update_settings.h"
int passive_module(user User, data *Data);

/*Returnere enten Failure, Success eller en response for om der skal laves en warning som defineret i passive_warnings*/
int passive_module(user User, data *Data)
{
    int response;

    if(User.choice.function == WarningEnergySaving)
        {
        response = warning_energy_saving(User, Data);
        return response;
        }
    else if(User.choice.function == MachineActivation)
        {
        machine_activation(User, Data);
        return Success;  
        }
    else{
        error_message(ErrorPassiveModuleFuncChoice);
        return Failure;
    }
    update_next_activation();
}
