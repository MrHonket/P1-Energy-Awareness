/*MartinBM*/
//gcc active_module.c global.c language.c database_module.c passive_module.c update_settings.c info_energy_saving.c user_history.c warning_energy_saving.c system_information.c machine_activation.c future_data.c consumption_check.c debug.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h" //IMPLEMENTERET!
#include "language.h" //tom .h fil
//#include "database_module.h" //ERROR!
//#include "user_history.h" //SYNTAX ERROR!
//#include "update_settings.h" // ERROR!
//#include "info_energy_saving.h" //SYNTAX ERROR!
//#include "passive_module.h" //tom .h fil
//#include "warning_energy_saving.h" //tom .h fil
//#include "system_information.h"//tom .h fil
//#include "machine_activation.h"// .h fil
//#include "future_data.h" //tom .h fil
//#include "consumption_check.h" //tom .h fil
#include "debug.h" //implementeret

/*DISSE SKAL SLETTES NÅR DERES .h ER IMPLEMENTERET!!!*/
data database_module(user User){data Test; return Test;}
int user_history(user User, data Data){return 0;}
settings load_settings(void){settings Test; return Test;}
int update_settings(void){return 0;}
int info_energy_saving(user User, data Data){return 0;}
int passive_module(user User, data Data){return 0;}
int warning_energy_saving(user User, data Data){return 0;}
int system_information(user User, data Data){return 0;}
int machine_activation(user User, data Data){return 0;}
int future_data(user User, data Data){return 0;}
int consumption_check(user User, data Data){return 0;}

/*Dette er prototyper i programmet.*/
user_type set_next_activation(user User);
data load_data(user User);
int prompt_user(user User,data Data);
void log_data(user User);

int main(void){
    user User;
    data Data;
    int next_activation,
        confirmation;

    User.settings = load_settings();
    User.type = set_next_activation(User);
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
user_type set_next_activation(user User){
    user_type local_type;

    local_type = Human;

    return local_type;
}
/*Loader data fra database_module. Indeholder pt. KUN MOCKDATA!*/
data load_data(user User){
    data local_data;

    local_data = database_module(User);

    return local_data;
}
/*Funktion der logger brugen af programmet og de data der måtte komme derigennem.*/
void log_data(user User){

}
/*Funktionen som fungere som en brugers interface*/
int prompt_user(user User, data Data){
    char info_str[60] = {'T','E','S','T'};
    int info;
    int new_command = 0;
    
    /*Basil was here & coded user interaction*/
    printf("Tryk 1 for brugerhistorik\nTryk 2 for brugerindstillinger\nTryk 3 for info om dine energibesparelser\n");
    scanf(" %d", &User.choice.function);
    
    if(User.choice.function == UserHistory){
        info = user_history(User,Data);
    }
    else if(User.choice.function == UpdateSettings){
        info = update_settings();
    }
    else if(User.choice.function == InfoEnergySaving){
        info = info_energy_saving(User,Data);
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

    //scanf for om der ønskes ny kommando. Basil was here
    printf("Tryk paa enhver tast for at kore programmet igen.\nTryk 0 for at lukke programmet");
    scanf("%d", &new_command);

    if(new_command){
        return prompt_user(User,Data);
    }
    else{
        return 0;
    }
}