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
user load_settings(void){
    user User;
    char setting_str[50];

    User.settings.id = 35;
    strcpy(User.settings.residence,"DK1");
    strcpy(User.settings.language,"DK");
    User.choice.function = UserHistory;

    return User;
}
/*Sætter næste automatiske aktivering*/
int set_next_activation(void){

}
/*Loader data fra database_module. Indeholder pt. KUN MOCKDATA!*/
data load_data(user user_choices){
    data local_data;

    if(user_choices.settings.id == 35){
        local_data.prize.DK1price = 120;
    }
    else{
        local_data.prize.DK1price = 85;
    }

    return local_data;
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