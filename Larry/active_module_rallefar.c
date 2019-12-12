/*MartinBM*/
//"Rigtige" gcc compilation
//gcc active_module.c global.c language.c database_module.c passive_module.c update_settings.c info_energy_saving.c user_history.c warning_energy_saving.c system_information.c machine_activation.c future_data.c consumption_check.c debug.c
//"Experimental" gcc compilation
//gcc active_module.c global.c language.c database_module.c user_history_exp.c update_settings.c info_energy_saving_exp.c passive_module.c warning_energy_saving_exp.c system_information.c machine_activation.c future_data.c consumption_check.c debug.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "global.h"                 //Implementeret og brugbart!
#include "language.h"               //tom .h OG .c fil

#include "database_module.h"        //Implementeret og brugbart men giver forskellige fejlmeddelser.
#include "user_history_exp.h"       //ERROR SYNTAX! IMPLEMENTERET SOM EXP!
#include "update_settings.h"        //Implementeret, men load_data loader ikke data korrekt. MockData skabt i main() for at omgå.
#include "info_energy_saving_exp.h" //IMPLEMENTERET SOM EXP! Der sker fejl ved linje 51
#include "passive_module.h"         //Implementeret og brugbart
#include "warning_energy_saving_exp.h"//IMPLEMENTERET SOM EXP! Der bruges dog pt. MockData i funktionen for at kalde underfunktioner.

#include "system_information.h"     //Implemented som error_message!
#include "machine_activation.h"     //Implemented som error_message!
#include "future_data.h"            //Implemented som error_message!
#include "consumption_check.h"      //Implemented som error_message!
#include "debug.h"                  //implementeret og brugbart!

/*Dette er prototyper i programmet.*/
void check_activation(user User);
int prompt_user(user User, data *Data, data cheapest, double user_price);
void log_data(user User);
/*main vil modtage information om det er en måler eller sig selv (Automatisk) der aktivere eller en app (Human)*/
int main(void){
    user User = { {200, "DK1", "DK"}, InfoEnergySaving, Mean, Human};       
    dato from = {{04, 00}, 20, Januar, 2017};
    dato to = {{05, 00}, 20, Januar, 2017};                      
    data *Data;
    data cheapest_struct;
    int confirmation;
    double user_price;
    double info;
    
    // User.settings = load_settings();
    //check_activation(User);
    
    /*MockData!
    User.type = Human;
    User.choice.function = InfoEnergySaving;
    dato dato1 = {{18, 00}, 5, Januar, 2018};
    dato dato2 = {{19, 00}, 5, Januar, 2018};
    User.choice.lookup = Price;
    User.choice.mean_or_median = Mean;
    User.settings.id = 200;
    strcpy(User.settings.language,"DK");
    strcpy(User.settings.residence,"DK1");
     End mock */

    

    Data = get_price_for_timeinterval_in_area(from, to, Dk1);

    for (int i = 0; i < 100; i++)
        printf("Priser: %.1f\n", Data[i].prize.DK1price);
        
    printf("\n\n");
    for (int i = 0; i < 100; i++)
        printf("Forbrug: %.1f\n", Data[i].meter.value);

        cheapest_struct = *cheapest(Data);
        print_information(Data, cheapest_struct, user_price, User);
        info = info_energy_saving(User, Data);
        printf("Din besparelse er: %.5f DKK\n", info);

    if (User.type == Human){
        prompt_user(User, Data, cheapest_struct, user_price);
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
int prompt_user(user User, data *Data, data cheapest_struct, double user_price){
    char info_str[60] = {'T','E','S','T'};
    double info;
    int new_command = 0;
    
    /*Basil was here & coded user interaction*/
    printf("Tryk %d for brugerhistorik\n",UserHistory);
    printf("Tryk %d for brugerindstillinger\n",UpdateSettings);
    printf("Tryk %d for info om dine energibesparelser\n",InfoEnergySaving);
    printf("Tryk %d for at lave et elcheck",ConsumptionCheck);
    printf("Tryk %d for informationer om dette system\n",SystemInformation);
    printf("Tryk %d for et gaet om fremtidige priser",FutureData);

    scanf(" %d", &User.choice.function);
    /*Ja, dette kunne godt være en switch :P*/
    if(User.choice.function == UserHistory){
        info = user_history(User, Data);
    }
    else if(User.choice.function == UpdateSettings){
        update_settings();
    }
    else if(User.choice.function == InfoEnergySaving){
        cheapest_struct = *cheapest(Data);
        print_information(Data, cheapest_struct, user_price, User);
        info = info_energy_saving(User, Data);
        printf("Din besparelse er: %.5f DKK\n", info);
    }
    else if(User.choice.function == ConsumptionCheck){
        info = consumption_check(User, Data);
    }
    else if(User.choice.function == SystemInformation){
        info = system_information(User, Data);
    }
    else if(User.choice.function == FutureData){
        future_data(User, Data);
    }    
    else if(User.choice.function == 0){
        return 0;
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
        return prompt_user(User,Data, cheapest_struct, user_price);
    }
    else{
        return 0;
    }
}