#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"

/* updatere settings.txt fil*/
/* Daniel */

void update_settings(void);
settings load_settings(void);

int main ()
{

    update_settings();

    load_settings();

    return(0);
}

void update_settings(void)
{
    FILE *f;
    char userdata[40];

    printf("What's your place of residence? Enter DK1 for Jutland and Fyn or DK2 for Sealand - Language (DK or ENG) - User id: ");
    scanf(" %[a-zA-Z0-9 -]", userdata);

    f = fopen(" settings.txt", "w");
    fwrite(userdata, 1, sizeof(userdata),f);

    fclose(f);
}

settings load_settings(void){
    settings Settings;
    FILE *f;
    char scan_data[40], language[5], location[5];
    int user_id; 

    f = fopen(" settings.txt", "r");
    
    fgets(scan_data,40,f);
    
    fclose(f);

    sscanf(scan_data, " %3s - %s - %d", location, language, &user_id);

    Settings.id = user_id;
    strcpy(Settings.language, language);
    strcpy(Settings.residence, location);

    return Settings;
}
