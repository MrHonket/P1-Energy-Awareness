#include <stdio.h>
#include <stdlib.h>
#include "global.h"

char* translate(int choice_of_function);
int debug_user(user *User);
//viser de data der er i user
int debug_user(user *User){
    printf("_____________________________\n\n");
    printf("\nDebugger for user structs!\n");
    printf("ID = %d ; Sprog = %s ; Bosted = %s\n",User->settings.id,language_txt[User->settings.language],area_txt[User->settings.residence]);
    printf("next_activation: ");
    print_date(User->settings.next_activation);
    printf("Valgte funktion = %s ; Brugeren er %s\n",translate(User->choice.function),(User->type == Human ? "menneske" : "automatisk"));
    printf("_____________________________\n\n");
    printf("data hentes i tidsrummet:\n");
    print_date( User->choice.from);
    print_date(User->choice.to);
    printf("hours: %d\n",User->choice.hour);
    printf("nu:\n");
    print_date(User->choice.now);
    printf("_____________________________\n\n");
    printf("lookup: %d  Mean/Median: %d  Warning: %d\n",User->choice.lookup,User->choice.mean_or_median, User->choice.warning);
    printf("_____________________________\n\n");
    

    return EXIT_SUCCESS;
}

char* translate(int choice_of_function){
    switch(choice_of_function){
        case Presentation        : return "presentation of function";
        case Exit                : return "exit from function";
        case UserHistory         : return "user_history";
        case InfoEnergySaving    : return "info_energy_saving";
        case UpdateSettings      : return "update_settings";
        case SavingAdvice        : return "saving_advice";
        case WarningEnergySaving : return "warning_energy_savings";
        case MachineActivation   : return "machine_activation";
        case ConsumptionCheck    : return "consumption_check";
    }
    return "Error_Translate";
}
