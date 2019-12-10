/*MartinBM*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "language.h"

/*Funktionerne herunder skal importeres via header filer*/
int passive_module(user user_choices, data user_data){return 0;};
char* user_history(user user_choices, data user_data){return "use";}
char* update_settings(user user_choices, data user_data){return "upd";}
char* info_energy_settings(user user_choices, data user_data){return "inf";}

/*Dette er prototyper i programmet.*/
settings load_settings(void);
void set_next_activation(user user_choice);
data load_data(user user_choices);
int check_user(int activator);
int prompt_user(user user_choices,data user_data);
void log_data(user user_choices);

int main(void){
    user user_choices;
    data user_data;
    int next_activation,
        user_type,
        confirmation;

    user_choices.settings = load_settings();
    set_next_activation(user_choices);
    user_data = load_data(user_choices);

    user_type = check_user(user_choices.type);
    if (user_type == Human){
        prompt_user(user_choices,user_data);
    }
    else if(user_type == Automated){
        confirmation = passive_module(user_choices,user_data);
        if(confirmation){
            log_data(user_choices);
        }
        else{
            error_message(ErrorConfirmationPassiveModule);
        }
    }
    else{
        error_message(ErrorUserType);
    }

    debug_print(user_choices,user_data,TRUE);
    
    return EXIT_SUCCESS;
}
/*Loader settings fra settings.txt. Indeholder pt. KUN MOCKDATA!*/
settings load_settings(void){
    settings settings;

    settings.id = 35;
    strcpy(settings.residence,"DK1");
    strcpy(settings.language,"DK");

    return settings;
}
/*Sætter næste automatiske aktivering*/
void set_next_activation(user user_choices){
    user_choices.type = Human;
}
/*Loader data fra database_module. Indeholder pt. KUN MOCKDATA!*/
data load_data(user user_choices){
    data data;

    if(user_choices.settings.id == 35){
        data.prize.DK1price = 120;
    }
    else{
        data.prize.DK1price = 85;
    }

    return data;
}
/*En funktion der checker om brugeren er programmet selv eller en aktiv bruger.*/
int check_user(int activator){
    if (activator == Automated){
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
    
    if(user_choices.choice.function == UserHistory){
        strcpy(info_str,user_history(user_choices,user_data));
    }
    else if(user_choices.choice.function == UpdateSettings){
        strcpy(info_str,update_settings(user_choices,user_data));
    }
    else if(user_choices.choice.function == InfoEnergySaving){
        strcpy(info_str,info_energy_settings(user_choices,user_data));
    }
    else{
        error_message(ErrorChoiceDoesntExist);
    }

    if(info_str != NULL){
        printf("%s\n",info_str);
    }
    else{
        error_message(ErrorInfoStrNotFound);
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