/*MartinBM*/
//"Rigtige" gcc compilation
//gcc active_module.c global.c language.c database_module.c passive_module.c update_settings.c info_energy_saving.c user_history.c warning_energy_saving.c system_information.c machine_activation.c future_data.c consumption_check.c debug.c -o larry

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "global.h"                 //Implementeret og brugbart!
#include "language.h"               //Implementeret og brugbart!
#include "database_module.h"        //Implementeret og brugbart!
#include "user_history.h"           //Implementeret og brugbart!
#include "update_settings.h"        //Implementeret og brugbart!
#include "info_energy_saving.h"     //Implementeret og brugbart!
#include "passive_module.h"         //Implementeret og brugbart!
#include "warning_energy_saving.h"  //Implementeret og brugbart!
#include "system_information.h"     //Implemented som error_message!
#include "machine_activation.h"     //Implemented som error_message!
#include "future_data.h"            //Implemented som error_message!
#include "consumption_check.h"      //Implemented som error_message!
#include "debug.h"                  //implementeret og brugbart!

/*Dette er prototyper i programmet.*/
int check_for_run_module(user User);
int prompt_user(user User,data *Data);
    data* copy_data(user User,data *Data);
void log_data_use(data Output);
/*main vil modtage information om det er en måler eller sig selv (Automatisk) der aktivere eller en app (Human)*/
int main(int user_type){
    user User;
    User.type = Human;
    User.choice.lookup = Meter;
    dato dato_from = {{00, 00}, 15, Januar, 2017};
    User.choice.from = dato_from;
    dato dato_to = {{00, 00}, 16, Januar, 2017};    
    User.choice.to = dato_to;                
    data *Data;
    data Output; //Dette vil være et struct som evt. kunne returneres i passiv_modulet til brug i log_data.
    int confirmation;

    if(access("settings.txt",F_OK) == 0){
        User.settings = load_settings();
    }
    else{
        l_update_settings(User);
        update_next_activation(User);
    }
    confirmation = check_for_run_module(User);

    if(confirmation){
        Data = get_price_for_timeinterval_in_area(dato_from, dato_to, Dk1);
        if (User.type == Human){
            prompt_user(User,Data);
        }
        else if(User.type == Automated){
            confirmation = passive_module(User,Data);
            if(confirmation){                         
                log_data_use(Output);                 
            }
            else{
                error_message(ErrorConfirmationPassiveModule);
            }
        }
        else{
            error_message(ErrorUserType);
        }
    }
    else{
        //don't run, evt. log_data_use(User); alt efter hvordan den implementeres.
    }

    update_next_activation(User);         //update next activation vil tage settings og planlægge næste aktivering.

    User.settings = load_settings();
    debug_user(User);
    
    free(Data);
    return EXIT_SUCCESS;
    
}
/*Checker for om der skal aktiveresSætter næste automatiske aktivering
 *Hvis aktivatitionen sker automatisk skal den vurdere om next activation stemmer overens med nuværende tidspunkt
 *Ellers hvis aktivationen sker af et menneske skal den bare gå videre.
 *Hvis den er automatisk og vurderes til at aktivere nu skal den hurtigt udregne næste gang den vurdere at aktivere hele programmet.
 *Hvis den er automatisk men vurderes til ikke at aktivere nu, så skal den returnere main(Automated) efter X antal tid(1 time?)*/
int check_for_run_module(user User){
    if(User.type == Automated){
        dato time_now=User.settings.next_activation;/*rigtig tid skal hentes fra time library*/
        if(User.settings.next_activation.time.hour == time_now.time.hour){
            return TRUE;
        }
        else if(User.settings.next_activation.day < time_now.day){
            update_next_activation(User);
            check_for_run_module(User);
        }
        else{
            //pause for 1 times tid for at simulere måler
            //return main(Automated) (når det er muligt)
            return 0;
        }
    }
    else if(User.type == Human){
        return 1;
    }
    else{
        error_message(ErrorUserType);
    }
}
/*Funktion der logger brugen af programmet og måden de data der måtte komme derigennem.*/
/*Disse data vil være relevante at vise i funktionen system_information.c når den implementeres*/
void log_data_use(data Output){
    error_message(ErrorLogDataNotImplemented);
}
/*Funktionen som fungere som en brugers interface
 Kunne overvejes at lægges ind i language.c istedet for.*/
int prompt_user(user User, data *Data){
   
    data *data_copy;
    data_copy = copy_data(User,Data);

    User.settings = load_settings();
    l_prompt_user(User);
    scanf(" %d", &User.choice.function);
    
    if(User.choice.function == Exit){
        return EXIT_SUCCESS;
    }
    else if(User.choice.function == UserHistory){
        l_user_history(User,data_copy);
    }
    else if(User.choice.function == UpdateSettings){
        l_update_settings(User);
    }
    else if(User.choice.function == InfoEnergySaving){
        l_info_energy_saving(User,data_copy);
    }
    else if(User.choice.function == ConsumptionCheck){
        l_consumption_check(User, data_copy);
    }
    else if(User.choice.function == SystemInformation){
        l_system_information(User, data_copy);
    }
    else if(User.choice.function == FutureData){
        l_future_data(User, data_copy);
    }    
    else if(User.choice.function == WarningEnergySaving){
        l_warning_energy_saving(User,data_copy);
    }
    else if(User.choice.function == MachineActivation){
        l_machine_activation(User,data_copy);
    }
    else{
        error_message(ErrorChoiceDoesntExist);
    }

    free(data_copy);
    return prompt_user(User,Data);
}

/* Funktionen lægger en kopi af dataene fra database modulet over i et tmp array, således at den sorterede data fra funktionerne 
 * i eksempelvis l_info_energy_saving ikke overlever fra kørsel til kørsel */
data* copy_data(user User,data *Data)
{
    int interval = hours_between(User.choice.from,User.choice.to);
    data *data_copy= malloc(sizeof(data) * HOURS_PR_YEAR);
    int i;

    for (i = 0; i < interval; i++){
        data_copy[i].meter.from.time = Data[i].meter.from.time;
        data_copy[i].meter.from.day = Data[i].meter.from.day;
        data_copy[i].meter.from.month = Data[i].meter.from.month;
        data_copy[i].meter.from.year = Data[i].meter.from.year;
        data_copy[i].meter.to.time = Data[i].meter.to.time;
        data_copy[i].meter.to.day = Data[i].meter.to.day;
        data_copy[i].meter.to.month = Data[i].meter.to.month;
        data_copy[i].meter.value = Data[i].meter.value;
        data_copy[i].prize.from.time = Data[i].prize.from.time;
        data_copy[i].prize.from.day = Data[i].prize.from.day;
        data_copy[i].prize.from.month = Data[i].prize.from.month;
        data_copy[i].prize.from.year = Data[i].prize.from.year;
        data_copy[i].prize.to.time = Data[i].prize.to.time;
        data_copy[i].prize.to.day = Data[i].prize.to.day;
        data_copy[i].prize.to.month = Data[i].prize.to.month;
        data_copy[i].prize.DK1price = Data[i].prize.DK1price;
        data_copy[i].prize.DK2price = Data[i].prize.DK2price;
    }
    return data_copy;
}