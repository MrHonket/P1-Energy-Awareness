#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "language.h"

/* opdatere settings.txt fil*/
/* Daniel */

void update_settings(void);
  int test_update_scan(char userdata[]);
settings load_settings(void);
void update_next_activation(void);

void update_settings(void)
{
    FILE *f;
    char userdata[40];

    scanf(" %[a-zA-Z0-9 -]", userdata);

    if(test_update_scan(userdata)){

        f = fopen("settings.txt", "w");
        fwrite(userdata, 1, sizeof(userdata),f);

        fclose(f);
    }
    else{
        error_message(ErrorSettingsNotCorrect);
        update_settings();
    }
}

int test_update_scan(char userdata[]){
    char test_res[10];
    char test_lang[10];
    int test_id;

    sscanf(userdata,"%s - %s - %d ",test_res,test_lang,&test_id);

    printf("%s %s %d\n",test_res,test_lang,test_id);

    if(strcmp(test_res,"%[A-Z0-9]") < 0){
        return Failure;
    }
    if(strcmp(test_lang,"%[A-Z]") < 0){
        return Failure;
    }
    if(test_id <= 0){
        return Failure;
    }

    return 1;
}

settings load_settings(void){
    settings Settings;
    FILE *f;
    char scan_data[40], language[5], location[5];
    int user_id; 
    
    f = fopen("settings.txt","r");
    
    fgets(scan_data,40,f);
    
    fclose(f);

    sscanf(scan_data, " %s - %s - %d", location, language, &user_id);

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