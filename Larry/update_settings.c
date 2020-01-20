#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "global.h"
#include "language.h"
#include "database_module.h"

/* opdatere settings.txt fil*/
/* Daniel */

void update_settings(void);
  int test_update_scan(char userdata[]);
void update_next_activation(user *User);
settings load_settings(void);
void update_warning_energy_saving(void);
void update_machine_activation(void);

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

/*Skal sætte den næste dato for automatisk aktivering ind i settings.txt filen*/
/*Husk at sørg for next_activation også bliver kørt i update_setings!*/
void update_next_activation(user *User){
    FILE *f;
    data *Data;
    //denne funktion er blot en stub for at vise hvad der skulle ske
    Data = get_price_for_timeinterval_in_area(User->choice.now,next_day(User->choice.now), Dk1);
    for(int i =1; i<23;i++){
        if(Data[i].prize.DK1price > 222){
            printf("next activation er sat til : ");
            print_date(Data[i].prize.from);
            printf("fordi prisen på el %lf er højere end din max graense på 222\ndu vil modtage en notifikation hvis du bruger mere el end medianforbruget for foregående måned\n\n ", Data[i].prize.DK1price);
            printf("prisgraense er sat til User->settings.max_price = 222kr\n\n");
            User->settings.next_activation = Data[i].prize.from;
            return;
        }
        User->settings.next_activation = next_day(User->choice.now);
    }

    

    //udregn hvornår næste aktivering skal ske.

    f = fopen("settings.txt", "r");
    //Læs de data ind som er i settings.txt og lav en streng med de data + næste aktivering
    fclose(f);

    //f = fopen("settings.txt", "w");
    //Skriv datastrengen ind i settings.txt filen.
    //fclose(f);
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

void update_warning_energy_saving(void){
    FILE *f;
    char str1[40], str2[40], str3[40];

    printf("update warning energy saving\n");
    // error_message(ErrorNotImplemented);
    scanf("%s",str1);
    //Lav en scanf som tager de input der er nødvendige for at sætte programmet op
    f = fopen("settings.txt", "r");
    fgets(str2,40, f);
    sprintf(str3,"%s\n%s",str2,str1);
    //Læs de data ind som er i settings.txt og lav en streng med de data + de førnævnte input
    fclose(f);

    f = fopen("settings.txt", "w");
        fwrite(str3, 1, sizeof(str3),f);
        fclose(f);
    
}


void update_machine_activation(void){
    FILE *f;

    error_message(ErrorNotImplemented);
    //Lav en scanf som tager de input der er nødvendige for at sætte programmet op

    f = fopen("settings.txt", "r");
    //Læs de data ind som er i settings.txt og lav en streng med de data + de førnævnte input
    fclose(f);

    //f = fopen("settings.txt", "w");
    //Skriv datastrengen ind i settings.txt filen.
    //fclose(f);
}
