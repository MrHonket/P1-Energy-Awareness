/*MartinBM*/
//gcc active_module.c global.c language.c database_module.c passive_module.c update_settings.c info_energy_saving.c user_history.c warning_energy_saving.c system_information.c machine_activation.c future_data.c consumption_check.c debug.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "language.h"
#include "database_module.h"
#include "passive_module.h"
#include "update_settings.h"
#include "info_energy_saving.h"
#include "user_history.h"
#include "warning_energy_saving.h"
#include "system_information.h"
#include "machine_activation.h"
#include "future_data.h"
#include "consumption_check.h"
#include "debug.h"

/*Funktionerne herunder skal importeres via header filer*/
int passive_module(user User, data Data){return 0;};
char* user_history(user User, data Data){return "use";}
//char* update_settings(user User, data Data){return "upd";}
char* info_energy_settings(user User, data Data){return "inf";}

/*Dette er prototyper i programmet.*/
void set_next_activation(user User);
data load_data(user User);
int prompt_user(user User,data Data);
void log_data(user User);

int main(void){
    user User;
    data Data;
    int next_activation,
        confirmation;

    User.settings = load_settings();
    set_next_activation(User);
    Data = load_data(User);

    if (User.type == Human){
        prompt_user(User,Data);
    }
    else if(User.type == Automated){
        confirmation = passive_module(User,Data);
        if(confirmation){
            log_data(User);
        }
        else{
            error_message(ErrorConfirmationPassiveModule);
        }
    }
    else{
        error_message(ErrorUserType);
    }

    debug_user(User);
    
    return EXIT_SUCCESS;
}
/*Sætter næste automatiske aktivering*/
void set_next_activation(user User){
    User.type = Human;
}
/*Loader data fra database_module. Indeholder pt. KUN MOCKDATA!*/
data load_data(user User){
    data local_data;

    //LAVER INFINITE LOOP PT!!!!
    //init_database();

    return local_data;
}
/*Funktion der logger brugen af programmet og de data der måtte komme derigennem.*/
void log_data(user User){

}
/*Funktionen som fungere som en brugers interface*/
int prompt_user(user User, data Data){
    char info_str[60];
    int new_command;
    
    printf("Tryk 1 for brugerhistorik\nTryk 2 for brugerindstillinger\nTryk 3 for info om dine energibesparelser\n");
    scanf(" %d", User.choice.function);
    
    if(User.choice.function == UserHistory){
        strcpy(info_str,user_history(User,Data));
    }
    else if(User.choice.function == UpdateSettings){
        update_settings();
    }
    else if(User.choice.function == InfoEnergySaving){
        strcpy(info_str,info_energy_settings(User,Data));
    }
    else{
        error_message(ErrorChoiceDoesntExist);
    }

    //Test af om info_str er blevet retuneret korrekt
    if(info_str != NULL){
        printf("%s\n",info_str);
    }
    else{
        error_message(ErrorInfoStrNotFound);
    }

    //scanf for om der ønskes ny kommando.
    printf("Koer igen?");

    new_command = 0;
    if(new_command){
        return prompt_user(User,Data);
    }
    else{
        return 0;
    }
}