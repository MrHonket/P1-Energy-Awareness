#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "user_history.h"           
#include "update_settings.h"        
#include "info_energy_saving.h"     
#include "passive_module.h"         
#include "warning_energy_saving.h"  
#include "saving_advice.h"     
#include "machine_activation.h"               
#include "consumption_check.h" 
#include "database_module.h"     

void l_prompt_user(user *User);
void l_prompt_date(user User);
void l_user_history(user *User, data *Data);
void l_info_energy_saving(user *User,data *data_array);
  void cheapest(data data_array[], user User);
  void print_information(data return_array[], user User);
void l_update_settings(user *User);
void l_saving_advice(user *User,data *Data);
void l_consumption_check(user *User,data *Data);
void l_warning_energy_saving(user *User, data *Data);
void l_morningProcedure(user *User);
void print_warning(user *User);
void l_machine_activation(user *User, data *Data);
void set_user_timeinterval(user *User);
void set_user_date_from(user *User);
void set_user_date_to(user *User);
void set_User_choice_lookup(user *User);
void init_user(user *User);
data *get_data(user *User);




void l_prompt_user(user *User){
    if(strcmp(User->settings.language,"DK") == 0){
        printf("\n\nIndtast venligst et af de angivne heltal\n");                 
        printf("Tryk %d for at gaa ud af programmet\n",Exit);                     
        printf("Tryk %d for brugerhistorik\n",UserHistory);                       
        printf("Tryk %d for info om dine energibesparelser\n",InfoEnergySaving);  
        printf("Tryk %d for brugerindstillinger\n",UpdateSettings);               
        printf("Tryk %d for at faa nogle relevante spareraad til din situation\n",SavingAdvice);  
        printf("Tryk %d for at lave et elcheck\n",ConsumptionCheck);                   
        printf("Tryk %d for at saette det op saadan at du bliver advaret hvis prisen er hoej\n",WarningEnergySaving);
        printf("Tryk %d for at saette nogle maskiner op saa de bliver aktiveret naar strommen er billig\n",MachineActivation);
        printf("Tryk %d for at starte morgen routinen\n",MorningRoutine);
    }
    else if(strcmp(User->settings.language,"ENG") == 0){
        printf("\n\nPlease enter one of the available numbers\n");                
        printf("Enter %d to exit the program\n",Exit);                            
        printf("Enter %d for your user history\n",UserHistory);                   
        printf("Enter %d for proposals to energy savings\n",InfoEnergySaving);    
        printf("Enter %d for user settings\n",UpdateSettings);                    
        printf("Enter %d for relevant advice\n",SavingAdvice);     
        printf("Enter %d to check your power consumption\n",ConsumptionCheck);       
        printf("Enter %d to create settings for when you should receive warnings due to high prices.\n",WarningEnergySaving);
        printf("Enter %d to implement machines into your system, so they can activate when the price is low\n",MachineActivation);      
    }
    else{
        l_update_settings(User);
    }
}

void l_user_history(user *User, data *Data){
    double result;
    // int hours_to;
    
    if(strcmp(User->settings.language,"DK") == 0){

        printf("Her kan du se dit gennemsnitlige forbrug/elpris over en tidsperiode\nFra ");
        set_user_timeinterval(User);
        set_User_choice_lookup(User);

        printf("Skriv venligst \n%d for gennemsnit \n%d for medianen",Mean,Median);

        scanf(" %d",&User->choice.mean_or_median);
        Data = get_data(User);

        result = user_history(*User, Data);
        printf("%s er %lf %s for perioden\n",(User->choice.mean_or_median == Median ? "Medianen" : "Gennemsnittet"), result,
                                              (User->choice.lookup==Meter ? "KWH" : "DKK"));
        printf("fra d.");
        print_date(User->choice.from);
        printf("til d.");
        print_date(User->choice.to);

        free(Data);
    }
    else if(strcmp(User->settings.language,"ENG") == 0){
        //skriv engelsk
        l_update_settings(User);
    }
    else{
        l_update_settings(User);
    }
}
/*De forskellige choice, from hour, info, etc. skal indlægges i User structet for at holde en clean struktur*/
void l_info_energy_saving(user *User,data *Data)
{
    double info;
    int choice;

    if(strcmp(User->settings.language,"DK") == 0){
    
        printf("Velkommen til modulet energibesparelser - du har nu folgende to valgmuligheder:\n");
        printf("Tryk 1 for information om strompris for en given time og hvornår på dognet strømmen er billigst\n");
        printf("Tryk 2 for for strompris i et givent tidsrum\n");

        scanf(" %d", &choice);
        if (choice == 1 || choice == 2){
            switch(choice){
                case 1: 
                    printf("Indtast hvilken dato du onsker data fra: ");
                    set_user_timeinterval(User);
                    Data = get_data(User); //burde være User->settings.residence
                    
                    // scanf(" %d", &User->choice.hour);
                    print_information(Data, *User);
                    info = info_energy_saving(*User, Data);
                    cheapest(Data, *User);
                    printf("Din besparelse bliver: %.5f DKK\n\n", info);
                    printf("--------------------------------------------------------\n\n");
                    free(Data);
                    break;
                case 2: 
                    printf("Indtast en start og en slut dato du onsker at se priser for: \n");
                    set_user_timeinterval(User);
                    Data = get_data(User); //burde være User->settings.residence
                    // scanf(" %d %d", &User->choice.from.time.hour, &User->choice.to.time.hour);
                    overview_for_interval(*User,Data);
                    free(Data);
                    break;
            }
        }
        else{
            printf("Du tastede ikke et gyldigt tal, prøv igen\n");
        }
    }
    else if(strcmp(User->settings.language,"ENG") == 0){
        l_update_settings(User);
    }
    else{
        l_update_settings(User);
    }
}

/* Funktionen ser på hvornår på dagen det er billigst at forbruge strømog printer det ud */
void cheapest(data data_array[], user User)
{
    data *cheapest;
    int n_elements = hours_between(User.choice.from,User.choice.to)+1;
    cheapest = (data*)malloc(1 * sizeof(data));
    
    if (strcmp(User.settings.residence, "DK1") == 0){
        qsort(data_array, n_elements, sizeof(data), cmpfunc_DK1);
        cheapest->prize.from = data_array[0].prize.from;
        cheapest->prize.to = data_array[0].prize.to;
        cheapest->prize.DK1price = data_array[0].prize.DK1price;
    }
    else if (strcmp(User.settings.residence, "DK2") == 0){
        qsort(data_array, n_elements, sizeof(data), cmpfunc_DK2);
        cheapest->prize.from = data_array[0].prize.from;
        cheapest->prize.to = data_array[0].prize.to;
        cheapest->prize.DK2price = data_array[0].prize.DK2price;
    }
    printf("Det billigste tidspunkt at forbruge din strøm vil være: \n--------------------------------------------------------\n");

    if (strcmp(User.settings.residence, "DK1") == 0){    
        printf("Dato: %d / %d / %d | Klokkeslaet: %d - %d | Pris DK1: %.2f DKK / MwH |\n\n", cheapest->prize.from.day, 
        cheapest->prize.from.month, cheapest->prize.from.year, cheapest->prize.from.time.hour, cheapest->prize.to.time.hour, cheapest->prize.DK1price);
    }
    else if (strcmp(User.settings.residence, "DK2") == 0){
        printf("Dato: %d / %d / %d | Klokkeslaet: %d - %d | Pris DK2: %.2lf DKK / MwH |\n\n", cheapest->prize.from.day, 
        cheapest->prize.from.month, cheapest->prize.from.year, cheapest->prize.from.time.hour, cheapest->prize.to.time.hour, cheapest->prize.DK2price);
    }
    free(cheapest);
}

/* En samlet print funktion der tager højde for om vi kigger på DK1 eller DK2 */
void print_information(data return_array[], user User)
{   
    printf("\n");
    printf("--------------------------------------------------------\n");
    printf("Tidspunkt valgt af bruger: kl.%d og %d timer frem \n\n", User.choice.from.time.hour, hours_between(User.choice.from,User.choice.to));
    print_date(User.choice.from);
    double user_price;
    if (strcmp(User.settings.residence, "DK1") == 0){
        user_price = return_array[0].meter.value * KWH_TO_MWH * return_array[0].prize.DK1price;
        printf("Timens pris: %.2f DKK / MWH\n\n", return_array[0].prize.DK1price); 
        printf("Nuvaerende forbrug: %.2f KWH \n\n", return_array[0].meter.value); 
        printf("Pris baseret paa nuvaerende forbrug: %.2f DKK / H\n\n", user_price); 
    }
    else if (strcmp(User.settings.residence, "DK2") == 0){
        user_price = return_array[0].meter.value * KWH_TO_MWH * return_array[0].prize.DK2price;
        printf("Timens pris: %.2f DKK\n\n", return_array[0].prize.DK2price); 
        printf("Nuvaerende forbrug: %.2f / KwH\n\n", return_array[0].meter.value); 
        printf("Pris baseret paa nuvaerende forbrug: %.2f DKK / H\n\n", user_price); 
    }
}

void l_update_settings(user *User){
    //skriv variable hvis nogen
    if(strcmp(User->settings.language,"DK") == 0){
        printf("Skriv venligst paa formen: 'bosted' - 'sprog' - 'bruger id'\n");
        printf("Hvor bor du? Skriv DK1 for Jylland og Fyn eller DK2 for Sjælland\n");
        printf("Hvilket sprog oensker du? Skriv DK for dansk eller ENG for engelsk.\n");
        printf("Hvad er dit brugerid? Skriv venligst et unikt nummer\n");
        update_settings();
        User->settings = load_settings();
    }
    else if(strcmp(User->settings.language,"ENG") == 0){
        printf("Please enter 'residence' - 'language' - 'user id'\n");
        printf("What's your place of residence? Enter DK1 for Jutland and Fyn or DK2 for Sealand\n");
        printf("What language would you like? Enter DK for danish or ENG for english.\n");
        printf("What is your userid? Please enter a unique number\n");
        update_settings();
        User->settings = load_settings();
    }
    else{
        error_message(ErrorLanguageNotImplemented);
        strcpy(User->settings.language,"ENG");
        l_update_settings(User);
    }
}

void l_saving_advice(user *User, data *Data){
    //skriv variable
    
    if(strcmp(User->settings.language,"DK") == 0){
        //skriv dansk
        error_message(ErrorLanguageNotImplemented);
        saving_advice(*User,Data);
    }
    else if(strcmp(User->settings.language,"ENG") == 0){
        //skriv engelsk
        error_message(ErrorLanguageNotImplemented);
        saving_advice(*User,Data);
    }
    else{
        l_update_settings(User);
    }
}

void l_consumption_check(user *User, data *Data){
    //skriv variable
    
    if(strcmp(User->settings.language,"DK") == 0){
        //skriv dansk
        error_message(ErrorLanguageNotImplemented);
        consumption_check(*User,Data);
    }
    else if(strcmp(User->settings.language,"ENG") == 0){
        //skriv engelsk
        error_message(ErrorLanguageNotImplemented);
        consumption_check(*User,Data);
    }
    else{
        l_update_settings(User);
    }
}

void l_warning_energy_saving(user *User, data *Data){
    //skriv variable
    
    if(strcmp(User->settings.language,"DK") == 0){
        // error_message(ErrorLanguageNotImplemented);
        printf("hvor meget må strøm koste pr MWH før du modtager en advarsel?\n");
        update_warning_energy_saving();
    }
    else if(strcmp(User->settings.language,"ENG") == 0){
        //skriv engelsk
        error_message(ErrorLanguageNotImplemented);
        update_warning_energy_saving();
    }
    else{
        l_update_settings(User);
    }
}


void l_morningProcedure(user *User){
    data *Data;
    double info, median_consump, mean_price, consumed_price=0;
    printf("---------------------------------------------------------------------------------------------------\n\n");  
    printf("MORGEN RUTINE!\n\n");
    printf("---------------------------------------------------------------------------------------------------\n\n");  
    set_user_timeinterval(User);
    Data = get_data(User); //burde være User->settings.residence
    printf("---------------------------------------------------------------------------------------------------\n\n");
    printf("DIT STRØMOVERBLIK\n");
    
    print_information(Data, *User);
    overview_for_interval(*User,Data);
    info = info_energy_saving(*User, Data);
    cheapest(Data, *User);  
    printf("Din besparelse bliver: %.5f DKK\n", info);
    printf("---------------------------------------------------------------------------------------------------\n\n");  
    free(Data);
    printf("MIDDEL PRISER OG FORBRUG FOR DENNE MÅNED\n\n");
    printf("---------------------------------------------------------------------------------------------------\n");
    User->choice.from.day = 1;
    User->choice.from.time.hour = 0;
    User->choice.to = User->choice.from;
    User->choice.to.day = days_in_month(User->choice.to);
    User->choice.lookup = Meter;
    User->choice.mean_or_median = Median;
    print_date(User->choice.from);
    print_date(User->choice.to);
    Data = get_data(User);
    median_consump = user_history(*User,Data);
    printf("\ndit median forbrug i den %d. måned er %.2fKw / H \n\n", User->choice.from.month,median_consump);
    User->choice.lookup = Price;
    User->choice.mean_or_median = Mean;
    mean_price = user_history(*User,Data);
    printf("gennemsnits prisen i den %d. måned er %.2fDKK / MWH \n", User->choice.from.month,mean_price);
    free(Data);

    User->choice.from = User->choice.to = User->choice.now;
    User->choice.from.month = 1;
    User->choice.from.day = 1;
    User->choice.from.time.hour = 1;
    User->choice.from.time.minute = 0;

    Data = get_data(User);
    for(int i = 0; i <= hours_between(User->choice.from,User->choice.to);i++){
        consumed_price += Data[i].meter.value * Data[i].prize.DK1price * KWH_TO_MWH;
    }
    printf("--------------------------------------------------------\n\n");
    printf("I dette år har du brugt strøm  for %.2fDKK \n\n", consumed_price);
    printf("--------------------------------------------------------\n");
    free(Data);
    printf("tryk en tast");
    char c;
    while (scanf(" %c",&c)==0)
    {
        /* code */
    }
    

    

    
}


void print_warning(user *User){
    
    if(strcmp(User->settings.language,"DK") == 0){
        if(User->choice.warning){
        printf("ADVARSEL TIL BRUGER! Du forbruger nu hvor prisen er hoej!\n");
    }
    else if(User->choice.warning == FALSE){
        printf("Test Print for at se om funktionen virker som den skal\n");
        printf("Aka funktionen koerte rigtigt og det blev vurderet til ingen advarsel var noedvendig\n");
    }
    }
    else if(strcmp(User->settings.language,"ENG") == 0){
        //skriv engelsk
        error_message(ErrorLanguageNotImplemented);
    }
    else{
        l_update_settings(User);
    }
}

void l_machine_activation(user *User, data *Data){
    //skriv variable
    
    if(strcmp(User->settings.language,"DK") == 0){
        error_message(ErrorLanguageNotImplemented);
        update_machine_activation();
    }
    else if(strcmp(User->settings.language,"ENG") == 0){
        //skriv engelsk
        error_message(ErrorLanguageNotImplemented);
        update_machine_activation();
    }
    else{
        l_update_settings(User);
    }
}


void set_user_timeinterval(user *User){
    char str[3];
    printf("(-)for at bruge bruge den nuværende dato og 24 timer frem,  (.) for at skrive ind manuelt:");
                    
    scanf(" %s", str);
    if(strcmp(str,"-")==0){
        User->choice.from = User->choice.now;
        User->choice.to = next_day(User->choice.from);
    }
    else {
        set_user_date_from(User);
        set_user_date_to(User);
    }
    
    print_date(User->choice.from);
    print_date(User->choice.to);
    User->choice.hour = hours_between(User->choice.from,User->choice.to)+1;

}

void set_user_date_from(user *User){
    int d, m, y, h;
    printf("indstil from dato skriv DD MM YYYY H\n");
    scanf("%d %d %d %d",&d,&m,&y,&h);
    User->choice.from.day = d;
    User->choice.from.month = m;
    User->choice.from.year = y;
    User->choice.from.time.hour = h;
    User->choice.from.time.minute = 0;
    print_date(User->choice.from);
    
}

void set_user_date_to(user *User){
    int d, m, y, h;
    printf("indstil to dato skriv DD MM YYYY H\n");
    scanf("%d %d %d %d",&d,&m,&y,&h);
    
    User->choice.to.day = d;
    User->choice.to.month = m;
    User->choice.to.year = y;
    User->choice.to.time.hour = h;
    User->choice.to.time.minute = 0;
    print_date(User->choice.to);

}

void set_User_choice_lookup(user *User){
    char  str[3];
    printf("hvad vil du gerne regne på?\nForbrug(f)\nElpris(e)\n: ");
    scanf(" %s", str);
    if (strcmp(str,"e")==0){
        User->choice.lookup = Price;
    }
    else if (strcmp(str,"f")==0){
        User->choice.lookup = Meter;
    }
    else {
        error_message(ErrorUserLookupHistory);
        printf("det lykkedes ikke at sætte user.choice.lookup så den er defaulted til Forbrug");
        User->choice.lookup = Meter;
    }
}

void init_user(user *User){
    User->choice.from = date_from_stringDMYI("0-0-0" ,0);
    User->choice.to = date_from_stringDMYI("0-0-0" ,0);
    User->choice.now = date_from_stringDMYI("0-0-0" ,0);
    User->settings.next_activation = date_from_stringDMYI("1-1-2017", 0);

}


data *get_data(user *User){
    return get_price_for_timeinterval_in_area(User->choice.from,User->choice.to, Dk1);
}

