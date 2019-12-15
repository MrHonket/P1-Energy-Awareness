/* switch module */
#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "language.h"
#include "update_settings.h"
#include "warning_energy_saving.h"
#include "machine_activation.h"

int passive_module(user User, data *Data);

/*Returnere enten Failure eller Success nu men kan udvides til at returnere et Output struct*/
int passive_module(user User, data *Data)
{
    int response;

    if(User.choice.function == WarningEnergySaving)
        {
        response = warning_energy_saving(User, Data);
        print_warning(response);
        return Success;
        }
    else if(User.choice.function == MachineActivation)
        {
        l_machine_activation(User, Data);
        return Success;  
        }
    else{
        error_message(ErrorPassiveModuleFuncChoice);
        return Failure;
    }
}