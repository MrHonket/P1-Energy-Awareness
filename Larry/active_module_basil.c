/*Basil*/
//"Basils" gcc compilation
//gcc active_module_basil.c global.c language.c database_module.c passive_module.c update_settings.c info_energy_saving.c user_history.c warning_energy_saving.c system_information.c machine_activation.c future_data.c consumption_check.c debug.c

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
void log_data_use(user User);
/*main vil modtage information om det er en måler eller sig selv (Automatisk) der aktivere eller en app (Human)*/
int main(void){
/*Raller*/ //user User = { {200, "DK1", "DK"}, InfoEnergySaving, Mean, {{19, 0}, 0, Januar, 2017}, {{21, 0}, 0, Januar, 2017}, Price, Human};
/*Basil*/  user User = { {200, "DK1", "DK"}, UserHistory, Median, {{15, 0}, 0, Januar, 2017}, {{21, 0}, 0, Januar, 2017}, Price, Human};    
/*Niller*/ //user User = { {200, "DK1", "DK"}, WarningEnergySaving, Median, {{15, 0}, 0, Januar, 2017}, {{21, 0}, 0, Januar, 2017}, Meter, Automated};    
    dato dato_from = {{00, 00}, 20, Januar, 2017};
    dato dato_to = {{00, 00}, 21, Januar, 2017};                       
    data *Data;
    int confirmation;
    
    User.settings = load_settings();

    confirmation = check_for_run_module(User);

    if(confirmation){
        Data = get_price_for_timeinterval_in_area(dato_from, dato_to, Dk1);
        if (User.type == Human){
            prompt_user(User,Data);
        }
        else if(User.type == Automated){
            printf("\n\nTest funktion for at se hvornaar det passive module start\n");
            confirmation = passive_module(User,Data);
            if(confirmation){
                log_data_use(User);
                if(confirmation == MakeWarning){
                    printf("ADVARSEL TIL BRUGER! Du forbruger nu hvor prisen er hoej!\n");
                }
                else if(confirmation == NoWarning){
                    printf("Test Print for at se om funktionen virker som den skal\n");
                    printf("Aka funktionen koerte rigtigt og det blev vurderet til ingen advarsel var noedvendig\n");
                }
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

    debug_user(User);
        
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
            update_next_activation();
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
void log_data_use(user User){

}
/*Funktionen som fungere som en brugers interface*/
int prompt_user(user User, data *Data){
    double info;
    data cheapest_struct;
    
    l_prompt_user(User.settings.language,Presentation);
    l_prompt_user(User.settings.language,Exit);
    l_prompt_user(User.settings.language,UserHistory);
    l_prompt_user(User.settings.language,InfoEnergySaving);
    l_prompt_user(User.settings.language,UpdateSettings);
    l_prompt_user(User.settings.language,SystemInformation);
    l_prompt_user(User.settings.language,ConsumptionCheck);
    l_prompt_user(User.settings.language,FutureData);

    scanf(" %d", &User.choice.function);
    
    if(User.choice.function == Exit){
        return EXIT_SUCCESS;
    }
    else if(User.choice.function == UserHistory){
        info = user_history(User, Data);
        printf("%s er %lf DKK\n",(User.choice.mean_or_median == Median ? "Medianen" : "Gennemsnittet"),info);
    }
    else if(User.choice.function == UpdateSettings){
        update_settings();
        User.settings = load_settings();
    }
    else if(User.choice.function == InfoEnergySaving){
        cheapest_struct = *cheapest(Data, User);
        print_information(Data, cheapest_struct, User);
        info = info_energy_saving(User, Data);
        printf("Din besparelse bliver: %.5f DKK\n", info);
        printf("--------------------------------------------------------\n\n");
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
    else{
        error_message(ErrorChoiceDoesntExist);
    }

    return prompt_user(User,Data);
}