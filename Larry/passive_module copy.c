/* switch module */
#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "language.h"
#include "update_settings.h"
#include "warning_energy_saving.h"
#include "machine_activation.h"

int passive_module(user *User, data *Data);

/*Returnere enten Failure eller Success nu men kan udvides til at returnere et Output struct*/
int passive_module(user *User, data *Data)
{
    int response;//skulle have været data output struct

    if(User->choice.function == WarningEnergySaving)
        {
        User->choice.warning = warning_energy_saving(*User, Data);//skal der være en varning eller ej
        print_warning(User);
        return Success;
        }
    else if(User->choice.function == MachineActivation)
        {
        l_machine_activation(User, Data); //der burde ikke vises et view
        return Success;  
        }
    else{
        error_message(ErrorPassiveModuleFuncChoice);
        return Failure;
    }
}
