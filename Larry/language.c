#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"

char* l_prompt_user(char language[],int location){
    if(strcmp(language,"DK") == 0){
        switch(location){
            case Presentation       : printf("\n\nIndtast venligst et af de angivne heltal\n");                 break;
            case Exit               : printf("Tryk %d for at gaa ud af programmet\n",Exit);                     break;
            case UserHistory        : printf("Tryk %d for brugerhistorik\n",UserHistory);                       break;
            case InfoEnergySaving   : printf("Tryk %d for info om dine energibesparelser\n",InfoEnergySaving);  break;
            case UpdateSettings     : printf("Tryk %d for brugerindstillinger\n",UpdateSettings);               break;
            case SystemInformation  : printf("Tryk %d for informationer om dette system\n",SystemInformation);  break;
            case ConsumptionCheck   : printf("Tryk %d for at lave et elcheck\n",ConsumptionCheck);              break;
            case FutureData         : printf("Tryk %d for et gaet om fremtidige priser\n",FutureData);          break;
        }
    }
    else if(strcmp(language,"ENG") == 0){
        switch(location){
            case Presentation       : printf("\n\nPlease enter one of the available numbers\n");                break;
            case Exit               : printf("Enter %d to exit the program\n",Exit);                            break;
            case UserHistory        : printf("Enter %d for your user history\n",UserHistory);                   break;
            case InfoEnergySaving   : printf("Enter %d for proposals to energy savings\n",InfoEnergySaving);    break;
            case UpdateSettings     : printf("Enter %d for user settings\n",UpdateSettings);                    break;
            case SystemInformation  : printf("Enter %d for information of the system\n",SystemInformation);     break;
            case ConsumptionCheck   : printf("Enter %d to check your power consumption\n",ConsumptionCheck);    break;
            case FutureData         : printf("Enter %d to get the prices of the future\n",FutureData);          break;
        }
    }
    return 0;
}