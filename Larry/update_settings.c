#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "global.h"

/* updatere settings.txt fil*/
/* Daniel */

void update_settings(void);
settings load_settings(void);

void update_settings(void)
{
    FILE *f;
    char userdata[40];

    printf("Please enter 'residence' - 'language' - 'user id'\n");
    printf("What's your place of residence? Enter DK1 for Jutland and Fyn or DK2 for Sealand\n");
    printf("What language would you like? Enter DK for danish or ENG for english.\n");
    printf("What is your userid? Please enter a unique number\n");
    scanf(" %[a-zA-Z0-9 -]", userdata);

    f = fopen("settings.txt", "w");
    fwrite(userdata, 1, sizeof(userdata),f);

    fclose(f);
}

settings load_settings(void){
    settings Settings;
    FILE *f;
    char scan_data[40], language[5], location[5];
    int user_id; 
    //herunder bruges unistd biblioteket til at se om der er access (File_Ok) til settings.txt. Hvis den ikke eksistere, skab settings fil.
    if(access("settings.txt",F_OK) == -1){
        update_settings();
    }

    f = fopen("settings.txt","r");
    
    fgets(scan_data,40,f);
    
    fclose(f);

    sscanf(scan_data, " %3s - %s - %d", location, language, &user_id);

    Settings.id = user_id;
    strcpy(Settings.language, language);
    strcpy(Settings.residence, location);

    printf("Settings = %d\n",Settings.id);

    return Settings;
}
