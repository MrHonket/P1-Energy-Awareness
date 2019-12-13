#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "language.h"

/* opdatere settings.txt fil*/
/* Daniel */

void update_settings(void);
settings load_settings(void);
void update_next_activation(void);

void update_settings(void)
{
    FILE *f;
    char userdata[40];

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

    f = fopen("settings.txt","r");
    
    fgets(scan_data,40,f);
    
    fclose(f);

    sscanf(scan_data, " %3s - %s - %d", location, language, &user_id);

    Settings.id = user_id;
    strcpy(Settings.language, language);
    strcpy(Settings.residence, location);

    return Settings;
}
/*Skal sætte den næste dato for automatisk aktivering ind i settings.txt filen*/
/*Husk at sørg for next_activation også bliver kørt i update_setings!*/
void update_next_activation(void){
    data *Data;
}