#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "user_history.h"           
#include "update_settings.h"        
#include "info_energy_saving.h"     
#include "passive_module.h"         
#include "warning_energy_saving.h"  
#include "system_information.h"     
#include "machine_activation.h"     
#include "future_data.h"            
#include "consumption_check.h"      

void l_prompt_user(user User);
void l_user_history(user User, data *Data);
void l_info_energy_saving(user User,data *Data);
void l_update_settings(user User,data *Data);
void l_system_information(user User,data *Data);
void l_consumption_check(user User,data *Data);
void l_future_data(user User,data *Data);
void l_warning_energy_saving(user User,data *Data);
void l_machine_activation(user User,data *Data);

void l_prompt_user(user User){
    if(strcmp(User.settings.language,"DK") == 0){
        printf("\n\nIndtast venligst et af de angivne heltal\n");                 
        printf("Tryk %d for at gaa ud af programmet\n",Exit);                     
        printf("Tryk %d for brugerhistorik\n",UserHistory);                       
        printf("Tryk %d for info om dine energibesparelser\n",InfoEnergySaving);  
        printf("Tryk %d for brugerindstillinger\n",UpdateSettings);               
        printf("Tryk %d for informationer om dette system\n",SystemInformation);  
        printf("Tryk %d for at lave et elcheck\n",ConsumptionCheck);              
        printf("Tryk %d for et gaet om fremtidige priser\n",FutureData);       
    }
    else if(strcmp(User.settings.language,"ENG") == 0){
        printf("\n\nPlease enter one of the available numbers\n");                
        printf("Enter %d to exit the program\n",Exit);                            
        printf("Enter %d for your user history\n",UserHistory);                   
        printf("Enter %d for proposals to energy savings\n",InfoEnergySaving);    
        printf("Enter %d for user settings\n",UpdateSettings);                    
        printf("Enter %d for information of the system\n",SystemInformation);     
        printf("Enter %d to check your power consumption\n",ConsumptionCheck);    
        printf("Enter %d to get the prices of the future\n",FutureData);          
    }
    else{
        error_message(ErrorLanguageNotImplemented);
    }
}

void l_user_history(user User, data *Data){
    double result;
    int test = 2;
    
    if(strcmp(User.settings.language,"DK") == 0){
        printf("Her kan du se dit gennemsnitlige forbrug i aaret\nFra ");
        print_date(Data[0].prize.from);
        printf("Til ");
        print_date(Data[HOURS_PR_YEAR - test].prize.to);
        printf("Skriv venligst %d hvis du vil have det som gennemsnit eller %d hvis du vil have medianen",Mean,Median);

        scanf(" %d",&User.choice.mean_or_median);

        result = user_history(User, Data);
        printf("%s er %lf DKK for perioden\n",(User.choice.mean_or_median == Median ? "Medianen" : "Gennemsnittet"), result);
    }
    else if(strcmp(User.settings.language,"ENG") == 0){
        //skriv engelsk
        error_message(ErrorLanguageNotImplemented);
    }
    else{
        error_message(ErrorLanguageNotImplemented);
    }
    if(test){
        printf("\nBemaerk at der traekkes to fra Hours Pr Year for ikke at komme udenfor indeks OG at gennemsnit == median!\n");
    }
}

void l_info_energy_saving(user User,data *Data)
{
    double info;
    data cheapest_struct;
    int choice;
    int from_hour;
    int to_hour;
    int hour_choice;

    if(strcmp(User.settings.language,"DK") == 0){
    
        printf("Velkommen til modulet energibesparelser - du har nu følgende to valgmuligheder:\n");
        printf("Tryk 1 for information om strømpris for en given time og hvornår på døgnet strømmen er billigst\n");
        printf("Tryk 2 for for strømpris i et givent tidsrum\n");

        scanf(" %d", &choice);

        switch(choice){
            case 1: 
                printf("Indtast hvilken time du ønsker data fra: ");
                scanf(" %d", &hour_choice);
                print_information(Data, cheapest_struct, User, hour_choice);
                info = info_energy_saving(User, Data, hour_choice);
                cheapest_struct = *cheapest(Data, User);
                printf("Din besparelse bliver: %.5f DKK\n", info);
                printf("--------------------------------------------------------\n\n");
                break;
            case 2: 
                printf("Indtast en start time og en slut time du ønsker at se priser for: \n");
                scanf(" %d %d", &from_hour, &to_hour);
                overview_for_interval(Data, User, from_hour, to_hour);
                break;
        }
    }
    else if(strcmp(User.settings.language,"ENG") == 0){
        printf("Sorry, English not implemented for module, use danish (DK).\n");
    }
    else{
        error_message(ErrorLanguageNotImplemented);
    }
}

void l_update_settings(user User, data *Data){
    //skriv variable hvis nogen
    
    if(strcmp(User.settings.language,"DK") == 0){
        printf("Skriv venligst paa formen: 'bosted' - 'sprog' - 'bruger id'\n");
        printf("Hvor bor du? Skriv DK1 for Jylland og Fyn eller DK2 for Sjælland\n");
        printf("Hvilket sprog oensker du? Skriv DK for dansk eller ENG for engelsk.\n");
        printf("Hvad er dit brugerid? Skriv venligst et unikt nummer\n");
        update_settings();
    }
    else if(strcmp(User.settings.language,"ENG") == 0){
        printf("Please enter 'residence' - 'language' - 'user id'\n");
        printf("What's your place of residence? Enter DK1 for Jutland and Fyn or DK2 for Sealand\n");
        printf("What language would you like? Enter DK for danish or ENG for english.\n");
        printf("What is your userid? Please enter a unique number\n");
        update_settings();
    }
    else{
        error_message(ErrorLanguageNotImplemented);
    }
}

void l_system_information(user User, data *Data){
    //skriv variable
    
    if(strcmp(User.settings.language,"DK") == 0){
        //skriv dansk
        error_message(ErrorLanguageNotImplemented);
    }
    else if(strcmp(User.settings.language,"ENG") == 0){
        //skriv engelsk
        error_message(ErrorLanguageNotImplemented);
    }
    else{
        error_message(ErrorLanguageNotImplemented);
    }
}

void l_consumption_check(user User, data *Data){
    //skriv variable
    
    if(strcmp(User.settings.language,"DK") == 0){
        //skriv dansk
        error_message(ErrorLanguageNotImplemented);
    }
    else if(strcmp(User.settings.language,"ENG") == 0){
        //skriv engelsk
        error_message(ErrorLanguageNotImplemented);
    }
    else{
        error_message(ErrorLanguageNotImplemented);
    }
}

void l_future_data(user User, data *Data){
    //skriv variable
    
    if(strcmp(User.settings.language,"DK") == 0){
        //skriv dansk
        error_message(ErrorLanguageNotImplemented);
    }
    else if(strcmp(User.settings.language,"ENG") == 0){
        //skriv engelsk
        error_message(ErrorLanguageNotImplemented);
    }
    else{
        error_message(ErrorLanguageNotImplemented);
    }
}

void l_warning_energy_saving(user User,data *Data){
    //skriv variable
    
    if(strcmp(User.settings.language,"DK") == 0){
        //skriv dansk
        error_message(ErrorLanguageNotImplemented);
    }
    else if(strcmp(User.settings.language,"ENG") == 0){
        //skriv engelsk
        error_message(ErrorLanguageNotImplemented);
    }
    else{
        error_message(ErrorLanguageNotImplemented);
    }
}

void l_machine_activation(user User,data *Data){
    //skriv variable
    
    if(strcmp(User.settings.language,"DK") == 0){
        //skriv dansk
        error_message(ErrorLanguageNotImplemented);
    }
    else if(strcmp(User.settings.language,"ENG") == 0){
        //skriv engelsk
        error_message(ErrorLanguageNotImplemented);
    }
    else{
        error_message(ErrorLanguageNotImplemented);
    }
}