#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <global.h> MANGLER IMPLEMENTERING!
//#include <language.h> MANGLER IMPLEMENTERING!

typedef struct {
    int id;
    char residence[5];
    char language[5];
    int choice;
    int user_type;
}choices;

typedef struct {
    int price;
}data;
/*Choices.usertype kan indeholde en af disse værdier*/
#define HUMAN       0
#define AUTOMATED   1
/*Choices.choice kan indeholde en af disse værdier*/
#define ERROR_TEST            0
#define USER_HISTORY          1
#define INFO_ENERGY_SAVING    2
#define UPDATE_SETTINGS       3
#define SYSTEM_INFORMATION    4
#define WARNING_ENERGY_SAVING 5
#define MACHINE_ACTIVATION    6
#define CONSUMPTION_CHECK     7
#define FUTURE_DATA           8
/*Konstanter der beskriver en fejlmeddelse i error_message*/
#define ERROR_CONFIRMATION_PASSIVE_MODULE 10
#define ERROR_CHOICE_DOESNT_EXIST         11
#define ERROR_INFO_STR_NOT_FOUND          12
#define ERROR_USER_TYPE                   13

/*Funktionerne herunder skal importeres via header filer*/
int passive_module(choices user_choices, data user_data){return 0;};
char* user_history(choices user_choices, data user_data){return "use";}
char* update_settings(choices user_choices, data user_data){return "upd";}
char* info_energy_settings(choices user_choices, data user_data){return "inf";}

/*Dette er prototyper i programmet.*/
choices load_settings(void);
int set_next_activation(void);
data load_data(int user_id);
int check_user(int activator);
int prompt_user(choices user_choices,data user_data);
void log_data(choices user_choices);
void error_message(int error_type);

int main(void){
    choices user_choices;
    data user_data;
    int next_activation,
        user_type,
        confirmation;

    user_choices = load_settings();
    next_activation = set_next_activation();
    user_data = load_data(user_choices.id);

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

    printf("TEST %s\n",user_choices.residence);
    printf("TEST %d\n",user_data.price);
    
    return EXIT_SUCCESS;
}
/*Loader settings fra settings.txt. Indeholder pt. KUN MOCKDATA!*/
choices load_settings(void){
    choices settings;
    char setting_str[50];

    settings.id = 35;
    strcpy(settings.residence,"DK1");
    strcpy(settings.language,"DK");
    settings.choice = USER_HISTORY;

    return settings;
}
/*Sætter næste automatiske aktivering*/
int set_next_activation(void){

}
/*Loader data fra database_module. Indeholder pt. KUN MOCKDATA!*/
data load_data(int user_id){
    data local_data;
    
    if(user_id == 35){
        local_data.price = 120;
    }
    else{
        local_data.price = 85;
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
void log_data(choices user_choices){

}
/*Funktion der tager en bestemt type fejl og returnere den slags.*/
void error_message(int error_type){

}
/*Funktionen som fungere som en brugers interface*/
int prompt_user(choices user_choices, data user_data){
    char info_str[60];
    int new_command;
    
    //scanf
    
    if(user_choices.choice == USER_HISTORY){
        strcpy(info_str,user_history(user_choices,user_data));
    }
    else if(user_choices.choice == UPDATE_SETTINGS){
        strcpy(info_str,update_settings(user_choices,user_data));
    }
    else if(user_choices.choice == INFO_ENERGY_SAVING){
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