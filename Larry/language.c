#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "info_energy_saving.h"

void l_info_energy_saving(user User,data data_array[]);

void l_prompt_user(char language[]){
    if(strcmp(language,"DK") == 0){
        printf("\n\nIndtast venligst et af de angivne heltal\n");                 
        printf("Tryk %d for at gaa ud af programmet\n",Exit);                     
        printf("Tryk %d for brugerhistorik\n",UserHistory);                       
        printf("Tryk %d for info om dine energibesparelser\n",InfoEnergySaving);  
        printf("Tryk %d for brugerindstillinger\n",UpdateSettings);               
        printf("Tryk %d for informationer om dette system\n",SystemInformation);  
        printf("Tryk %d for at lave et elcheck\n",ConsumptionCheck);              
        printf("Tryk %d for et gaet om fremtidige priser\n",FutureData);       
    }
    else if(strcmp(language,"ENG") == 0){
        printf("\n\nPlease enter one of the available numbers\n");                
        printf("Enter %d to exit the program\n",Exit);                            
        printf("Enter %d for your user history\n",UserHistory);                   
        printf("Enter %d for proposals to energy savings\n",InfoEnergySaving);    
        printf("Enter %d for user settings\n",UpdateSettings);                    
        printf("Enter %d for information of the system\n",SystemInformation);     
        printf("Enter %d to check your power consumption\n",ConsumptionCheck);    
        printf("Enter %d to get the prices of the future\n",FutureData);          
    }
}

void l_info_energy_saving(user User,data data_array[])
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
                print_information(data_array, cheapest_struct, User, hour_choice);
                info = info_energy_saving(User, data_array, hour_choice);
                cheapest_struct = *cheapest(data_array, User);
                printf("Din besparelse bliver: %.5f DKK\n", info);
                printf("--------------------------------------------------------\n\n");
                break;
            case 2: 
                printf("Indtast en start time og en slut time du ønsker at se priser for: \n");
                scanf(" %d %d", &from_hour, &to_hour);
                overview_for_interval(data_array, User, from_hour, to_hour);
                break;
        }
    }
    else if(strcmp(User.settings.language,"ENG") == 0){
        printf("Sorry, English not implemented for module, use danish (DK).\n");
    }
    else{
        printf("Sorry, Language not implemented for module.\n");
    }
}