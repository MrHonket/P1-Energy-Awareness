/*MartinBM*/
#include <string.h>
#include "global.h"
#include "language.h"

/*Funktionerne herunder skal importeres via header filer*/
int passive_module(user user_choices, data user_data){return 0;};
char* user_history(user user_choices, data user_data){return "use";}
char* update_settings(user user_choices, data user_data){return "upd";}
char* info_energy_settings(user user_choices, data user_data){return "inf";}

/*Dette er prototyper i programmet.*/
user load_settings(void);
int set_next_activation(void);
data load_data(user user_choices);
int check_user(int activator);
int prompt_user(user user_choices,data user_data);
void log_data(user user_choices);
/*Funktioner der skal inkluderes i debug.c
char* translate(int choice_of_function);
int error_message(int error);
int debug_print(user user_choice, data user_data, int run_or_not);*/

int main(void){
    user user_choices;
    data user_data;
    int next_activation,
        user_type,
        confirmation;

    user_choices = load_settings();
    next_activation = set_next_activation();
    user_data = load_data(user_choices);

    user_type = check_user(next_activation);
    if (user_type == HUMAN){
        prompt_user(user_choices,user_data);
    }
    else if(user_type == AUTOMATED){
        confirmation = passive_module(user_choices,user_data);
        if(confirmation){
            log_data(user_choices);
        }
        else{
            error_message(ERROR_CONFIRMATION_PASSIVE_MODULE);
        }
    }
    else{
        error_message(ERROR_USER_TYPE);
    }

    debug_print(user_choices,user_data,TRUE);
    
    return EXIT_SUCCESS;
}
/*Loader settings fra settings.txt. Indeholder pt. KUN MOCKDATA!*/
user load_settings(void){
    user settings;
    char setting_str[50];

    settings.id = 35;
    strcpy(settings.residence,"DK1");
    strcpy(settings.language,"DK");
    settings.choice_of_function = USER_HISTORY;

    return settings;
}
/*Sætter næste automatiske aktivering*/
int set_next_activation(void){

}
/*Loader data fra database_module. Indeholder pt. KUN MOCKDATA!*/
data load_data(user user_choices){
    data local_data;

    if(user_choices.id == 35){
        local_data.prize.DK1price = 120;
    }
    else{
        local_data.prize.DK1price = 85;
    }

    return local_data;
}
/*En funktion der checker om brugeren er programmet selv eller en aktiv bruger.*/
int check_user(int activator){
    if (activator == AUTOMATED){
        return 0;
    }
    else{
        return 1;
    }
}
/*Funktion der logger brugen af programmet og de data der måtte komme derigennem.*/
void log_data(user user_choices){

}
/*Funktionen som fungere som en brugers interface*/
int prompt_user(user user_choices, data user_data){
    char info_str[60];
    int new_command;
    
    //scanf
    
    if(user_choices.choice_of_function == USER_HISTORY){
        strcpy(info_str,user_history(user_choices,user_data));
    }
    else if(user_choices.choice_of_function == UPDATE_SETTINGS){
        strcpy(info_str,update_settings(user_choices,user_data));
    }
    else if(user_choices.choice_of_function == INFO_ENERGY_SAVING){
        strcpy(info_str,info_energy_settings(user_choices,user_data));
    }
    else{
        error_message(ERROR_CHOICE_DOESNT_EXIST);
    }

    if(info_str != NULL){
        printf("%s\n",info_str);
    }
    else{
        error_message(ERROR_INFO_STR_NOT_FOUND);
    }

    //scanf for om der ønskes ny kommando.
    new_command = 0;
    if(new_command){
        return prompt_user(user_choices,user_data);
    }
    else{
        return 0;
    }
}
/*
int debug_print(user user_choice, data user_data, int run_or_not){
    if(run_or_not){
        printf("ID = %d ; Sprog = %s ; Bosted = %s\n",user_choice.id,user_choice.language,user_choice.residence);
        printf("Valgte funktion = %s ; Brugeren er %s\n",translate(user_choice.choice_of_function),(user_choice.user_type == HUMAN ? "menneske" : "automatisk"));
    }
    return EXIT_SUCCESS;
}

char* translate(int choice_of_function){
    switch(choice_of_function){
        case ERROR_TEST             : return "error_test";
        case USER_HISTORY           : return "user_history";
        case INFO_ENERGY_SAVING     : return "info_energy_saving";
        case UPDATE_SETTINGS        : return "update_settings";
        case SYSTEM_INFORMATION     : return "system_information";
        case WARNING_ENERGY_SAVING  : return "warning_energy_savings";
        case MACHINE_ACTIVATION     : return "machine_activation";
        case CONSUMPTION_CHECK      : return "consumption_check";
        case FUTURE_DATA            : return "future_data";
    }
}
/*Funktion der tager en bestemt type fejl og returnere den slags.
int error_message(int error){
    return 0;
}*/