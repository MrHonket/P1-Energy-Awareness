/*MartinBM*/
//gcc active_module.c global.c language.c database_module.c passive_module.c update_settings.c info_energy_saving.c user_history.c warning_energy_saving.c system_information.c machine_activation.c future_data.c consumption_check.c debug.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "global.h"                 //Implementeret og brugbart!
#include "language.h"               //tom .h OG .c fil
#include "database_module.h"        //Implementeret og brubart!
#include "user_history.h"           //SYNTAX ERROR! modtager ikke User og Data.
#include "update_settings.h"        // ERROR!
//#include "info_energy_saving.h"     //SYNTAX ERROR! modtager ikke User og Data.
#include "passive_module.h"         //Implementeret med mindre fejl!
//#include "warning_energy_saving.h"//SYNTAX ERROR! modtager ikke User og Data.
#include "system_information.h"     //Implemented som error_message!
#include "machine_activation.h"     //Implemented som error_message!
#include "future_data.h"            //Implemented som error_message!
#include "consumption_check.h"      //Implemented som error_message!
#include "debug.h"                  //implementeret og brugbart!

/*DISSE SKAL SLETTES NÅR DERES .h ER IMPLEMENTERET!!!*/
//int user_history(user User, data *Data){return 0;}
int info_energy_saving(user User, data *Data){return 0;}
//int warning_energy_saving(user User, data *Data){return 0;}

/*Dette er prototyper i programmet.*/
void check_activation(user User);
int prompt_user(user User,data *Data);
void log_data(user User);
/*main vil modtage information om det er en måler eller sig selv (Automatisk) der aktivere eller en app (Human)*/
int main(void){
    user User;
    data *Data;
    int confirmation;

    User.settings = load_settings();
    check_activation(User);
    
    //MockData!
    User.type = Human;
    User.choice.function = UserHistory;
    dato dato1 = {{10,00},12,6,2017};
    dato dato2 = {{18,00},12,6,2017};
    User.choice.lookup = Meter;
    User.choice.mean_or_median = Mean;
    //endmock

    Data = get_price_for_timeinterval_in_area(dato1,dato2,Dk1);

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
    future_data(User,Data);
    system_information(User,Data);
    
    return EXIT_SUCCESS;
}
/*Checker for om der skal aktiveresSætter næste automatiske aktivering
 *Hvis aktivatitionen sker automatisk skal den lave en udregning. 
 *Ellers hvis aktivationen sker af et menneske skal den bare gå videre.
 *Hvis den er automatisk og vurderes til at aktivere nu skal den hurtigt udregne næste gang den vurdere at aktivere hele programmet.
 *Hvis den er automatisk men vurderes til ikke at aktivere nu, så skal den returnere main(Automated) efter X antal tid(1 time?)*/
void check_activation(user User){
    
}
/*Funktion der logger brugen af programmet og de data der måtte komme derigennem.*/
void log_data(user User){

}
/*Funktionen som fungere som en brugers interface*/
int prompt_user(user User, data *Data){
    char info_str[60] = {'T','E','S','T'};
    int info;
    int new_command = 0;
    
    /*Basil was here & coded user interaction*/
    printf("Tryk %d for brugerhistorik\n",UserHistory);
    printf("Tryk %d for brugerindstillinger\n",UpdateSettings);
    printf("Tryk %d for info om dine energibesparelser\n",InfoEnergySaving);
    printf("Tryk %d for at lave et elcheck",ConsumptionCheck);

    scanf(" %d", &User.choice.function);
    
    if(User.choice.function == UserHistory){
        info = user_history(User,Data);
    }
    else if(User.choice.function == UpdateSettings){
        update_settings();
    }
    else if(User.choice.function == InfoEnergySaving){
        info = info_energy_saving(User,Data);
    }
    else if(User.choice.function == ConsumptionCheck){
        info = consumption_check(User,Data);
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