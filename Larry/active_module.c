//"Rigtige" gcc compilation
//gcc active_module.c global.c language.c database_module.c passive_module.c update_settings.c info_energy_saving.c user_history.c warning_energy_saving.c saving_advice.c  machine_activation.c consumption_check.c debug.c

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
#include "saving_advice.h"     //Implemented som error_message!
#include "machine_activation.h"     //Implemented som error_message!
#include "consumption_check.h"      //Implemented som error_message!
#include "debug.h"                  //implementeret og brugbart!


/*Dette er prototyper i programmet.*/
int check_for_run_module(user *User);
int prompt_user(user *User,data *Data);
    data* copy_data(user User,data *Data);
void log_data_use(data Output);

/*main vil modtage information om det er en måler eller sig selv (Automatisk) der aktivere eller en app (Human)
main vil også modtage hvilken dato main er kaldt og sætte den pågældende dato som User.choice.now blot med årstal 2017
kald main på følgende måde:
./larry human $( date +%m-%d-%H)
*/
int main(int arg_c, char *arg_v[]){
    user User;
    init_user(&User);
    if(arg_c >= 2){
        if(strcmp(arg_v[1], "Automated") == 0) {
            
            User.type = Automated ;
            User.choice.mean_or_median = Median;
            User.choice.lookup = Meter;
            User.choice.function = WarningEnergySaving;
        }
        else {
            User.type = Human;
            User.choice.mean_or_median = Median;
            User.choice.lookup = Meter;
            User.choice.function = MorningRoutine;
        }
        if(arg_c >=3){
            User.choice.now.year = 2017;
            sscanf(arg_v[2],"%d-%d-%d",&User.choice.now.month,&User.choice.now.day,&User.choice.now.time.hour);
            User.choice.now.time.minute = 0;
            print_date(User.choice.now);
            User.choice.from = date_from_stringDMYI("1-1-2017", 0);
            User.choice.to = date_from_stringDMYI("31-12-2017", 23); 
            printf("User choise from, to, now set to\n"); 
            print_date(User.choice.from);
            print_date(User.choice.to);
            print_date(User.choice.now);

        }
    }
    else {
            User.type = Human;
            User.choice.now = date_from_stringDMYI("1-5-2017", 13);
            User.choice.lookup = Meter;
            User.choice.from = date_from_stringDMYI("1-1-2017", 0);
            User.choice.to = date_from_stringDMYI("31-12-2017", 23);
            printf("User choise from, to, now set to\n"); 
            print_date(User.choice.from);
            print_date(User.choice.to);
            print_date(User.choice.now);       
        }

           
    data *Data;
    data Output; //Dette vil være et struct som evt. kunne returneres i passiv_modulet til brug i log_data.
    int confirmation;

    if(access("settings.txt",F_OK) == 0){
        User.settings = load_settings();
    }
    else{
        //viser et view til brugeren hvor de kan skrive deres data DK1 osv

        l_update_settings(&User);
        debug_user(User);
    }
    //checker skal jeg køre eller ej, hvis "bruger" så kør altid, hvis det er en maskine , returnerer den true hvis der i settings er givet besked om at en maskine må køre på et bestemt tidspunkt
    //timenow er altid sat til 
    confirmation = check_for_run_module(&User);

    if(confirmation){
        Data = get_price_for_timeinterval_in_area(User.choice.from, User.choice.to, Dk1);//et års data tilbage i tid
        if (User.type == Human){
            prompt_user(&User,Data);
        }
        else if(User.type == Automated){
            confirmation = passive_module(&User,Data); //returnerer en int 
            if(confirmation){                         
                log_data_use(Output);  //tom stub               
            }
            else{
                error_message(ErrorConfirmationPassiveModule);
            }
        }
        else{
            error_message(ErrorUserType);
        }
        update_next_activation(&User);         //update next activation vil tage settings og planlægge næste aktivering.
    }
    else{
        //her ville vi oprette en linie i log
        //don't run, evt. log_data_use(User); alt efter hvordan den implementeres.
    }

    
    /*Test funktioner der skal slettes til sidst*/
    User.settings = load_settings();
    debug_user(User);
    
    
    return EXIT_SUCCESS;
    
}

/*Checker for om der skal aktiveresSætter næste automatiske aktivering
 *Hvis aktivatitionen sker automatisk skal den vurdere om next activation stemmer overens med nuværende tidspunkt
 *Ellers hvis aktivationen sker af et menneske skal den bare gå videre.
 *Hvis den er automatisk og vurderes til at aktivere nu skal den hurtigt udregne næste gang den vurdere at aktivere hele programmet.
 *Hvis den er automatisk men vurderes til ikke at aktivere nu, så skal den returnere main(Automated) efter X antal tid(1 time?)*/
int check_for_run_module(user *User){
    if(User->type == Automated){
        int Now_index = hours_between(User->choice.from,User->choice.now);
        
        if(User->settings.next_activation.year < 1 || User->settings.next_activation.year > 2100){
            User->settings.next_activation = next_hour(User->choice.now);
            update_next_activation(User);
        }
            printf("next activation: ");
            print_date(User->settings.next_activation );
        int next_activation_index = hours_between(User->choice.from,User->settings.next_activation);
        
        // dato time_now = User->settings.next_activation;/*rigtig tid skal hentes fra time library*/
        if(next_activation_index == Now_index){
            update_next_activation(User);
            return TRUE;
        }
        else if(next_activation_index < Now_index){//denne sammenligning er ugyldig, lav en funktion som 
            update_next_activation(User);// denne funktion burde ændre
            check_for_run_module(User);
        }
        else{
            //pause for 1 times tid for at simulere måler
            //return main(Automated) (når det er muligt)
            return 0;
        }
    }
    else if(User->type == Human){
        return 1;
    }
    else{
        error_message(ErrorUserType);
        
    }
    return EXIT_FAILURE;
}
/*Funktion der logger brugen af programmet og måden de data der måtte komme derigennem.*/
/*Disse data vil være relevante at vise i funktionen system_information.c når den implementeres*/
void log_data_use(data Output){
    error_message(ErrorLogDataNotImplemented);
}
/*Funktionen som fungere som en brugers interface
 Kunne overvejes at lægges ind i language.c istedet for.*/
int prompt_user(user *User, data *Data){
    l_prompt_user(User);
    scanf(" %d", &User->choice.function);
    
    data *data_copy;
    data_copy = copy_data(*User,Data); //her har vi mulighed for at udvide copy_data til at bruge data fra user settings

    if(User->choice.function == Exit){
        return EXIT_SUCCESS;
    }
    else if(User->choice.function == UserHistory){
        l_user_history(User,data_copy);
    }
    else if(User->choice.function == UpdateSettings){
        l_update_settings(User);
    }
    else if(User->choice.function == InfoEnergySaving){
        l_info_energy_saving(User,data_copy);
    }
    else if(User->choice.function == ConsumptionCheck){
        l_consumption_check(User, data_copy);
    }
    else if(User->choice.function == SavingAdvice){
        l_saving_advice(User, data_copy);
    }
    else if(User->choice.function == WarningEnergySaving){
        l_warning_energy_saving(User,data_copy);
    }
    else if(User->choice.function == MachineActivation){
        l_machine_activation(User,data_copy);
    }
    else if(User->choice.function == MorningRoutine){
        l_morningProcedure(User);    
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