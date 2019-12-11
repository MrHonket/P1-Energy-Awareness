#include <stdio.h>
#include <stdlib.h>
#include "global.h"

char* translate(int choice_of_function);
int debug_print(user User, data Data, int run_or_not);

int debug_print(user User, data Data, int run_or_not){
    if(run_or_not){
        printf("ID = %d ; Sprog = %s ; Bosted = %s\n",User.settings.id,User.settings.language,User.settings.residence);
        printf("Valgte funktion = %s ; Brugeren er %s\n",translate(User.choice.function),(User.type == Human ? "menneske" : "automatisk"));
    }
    return EXIT_SUCCESS;
}

char* translate(int choice_of_function){
    switch(choice_of_function){
        case ErrorTest           : return "error_test";
        case UserHistory         : return "user_history";
        case InfoEnergySaving    : return "info_energy_saving";
        case UpdateSettings      : return "update_settings";
        case SystemInformation   : return "system_information";
        case WarningEnergySaving : return "warning_energy_savings";
        case MachineActivation   : return "machine_activation";
        case ConsumptionCheck    : return "consumption_check";
        case FutureData          : return "future_data";
    }
    return "";
}