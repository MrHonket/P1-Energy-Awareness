#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "global.h"
#include "language.h"

/* opdatere settings.txt fil*/
/* Daniel */

void update_settings(void);
  int test_update_scan(char userdata[]);
settings load_settings(void);

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
    char test_str[60];
    char test_res[10];
    char test_lang[10];
    char test_id[10];
    int length;
    int i;

    strcpy(test_str,userdata);

    sscanf(test_str,"%s - %s - %s ",test_res,test_lang,test_id);

    length = strlen(test_res);
    for(i = 0; i < length; i++){
        if(islower(test_res[i])){
            return Failure;
        }
    }
    if(!isdigit(test_res[i-1])){
        return Failure;
    }

    length = strlen(test_lang);
    for(i = 0; i < length; i++){
        if(islower(test_lang[i])){
            return Failure;
        }
    }

    length = strlen(test_id);
    for(i = 0; i < length; i++){
        if(isalpha(test_id[i])){
            return Failure;
        }
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