#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "global.h"
#include "language.h"
#include "database_module.h"
#include "debug.h"

/* opdatere settings.txt fil*/
/* Daniel */

void update_settings(user *User);
void load_settings(user *User);
//   int test_update_scan(char userdata[]);
void update_Language(user *User);
void update_Area(user *User);
void update_Id(user *User);


void update_next_activation(user *User);

void update_warning_energy_saving(void);
void update_machine_activation(void);

void update_settings(user *User)
{
    FILE *f;
    // debug_user(User);
    if(User->choice.function == UpdateSettings){
    update_Language(User);
    // debug_user(User);
    update_Area(User);
    // debug_user(User);
    update_Id(User);
    debug_user(User);
    }
    
    f = fopen("settings.txt", "w+b");
    // if (
        rewind(f);
        fwrite(&User->settings.id,sizeof(int),1,f);
        // fwrite(&User->settings.language,sizeof(int),1,f);
        // // fwrite(&User->settings.next_activation,sizeof(dato),1,f);
        // fwrite(&User->settings.residence,sizeof(int),1,f);
    fclose(f);
    
}
void load_settings(user *User){
    FILE *f;
    f = fopen("settings.txt","r+b");
    if (f!=NULL){
        rewind(f);
        fread(&User->settings.id,sizeof(int),1,f);
        // fread(&User->settings.language,sizeof(int),1,f);
        // // fread(&User->settings.next_activation,sizeof(dato),1,f);
        // fread(&User->settings.residence,sizeof(int),1,f);
        fclose(f);
    }
    else{
        error_message(ErrorSettingsNotLoaded);
        User->choice.function = UpdateSettings;
        update_settings(User);
    }
}


void update_Language(user *User){
    char str[5];
    int scanres;
    l_update_Language(User);
    clear_input_buffer();

    scanres = scanf(" %s",str);
    
    if (scanres==1){
        if(strcmp(str,"ENG")==0||strcmp(str,"Eng")==0||strcmp(str,"eng")==0||strcmp(str,"ENg")==0){
            User->settings.language = ENG;
            return;
        }
        else if(strcmp(str,"DK")==0||strcmp(str,"Dk")==0||strcmp(str,"dK")==0||strcmp(str,"dk")==0){
            User->settings.language = DK;
            return;
        }
         
    }

        error_message(ErrorLanguageNotImplemented);
        update_Language(User);      
}

void update_Area(user *User){
    char str[5];
    int scanres;
    l_update_Area(User);
    clear_input_buffer();

    scanres = scanf(" %s",str);
    if (scanres==1){
        if(strcmp(str,"dk1")==0||strcmp(str,"DK1")==0||strcmp(str,"Dk1")==0||strcmp(str,"dK1")==0){
            User->settings.residence = Dk1;
            return;
        }
        else if(strcmp(str,"dk2")==0||strcmp(str,"DK2")==0||strcmp(str,"Dk2")==0||strcmp(str,"dK2")==0){
            User->settings.residence = Dk2;
            return;
        }
    }
   
    error_message(ErrorResidenceNotImplemented);
    update_Area(User);  
    
}

void update_Id(user *User){
    int id;
    int scanres;
    l_update_Id(User);
    clear_input_buffer();

    scanres = scanf(" %d",&id);
    if (scanres==1){
        User->settings.id = id;
        return;
    }
    
    error_message(ErrorUserIdNotAccepted);
    update_Id(User);  
    
}




// int test_update_scan(char userdata[]){
//     char test_str[60];
//     char test_res[10];
//     char test_lang[10];
//     char test_id[10];
//     int length;
//     int i;

//     strcpy(test_str,userdata);

//     sscanf(test_str,"%s - %s - %s ",test_res,test_lang,test_id);

//     length = strlen(test_res);
//     for(i = 0; i < length; i++){
//         if(islower(test_res[i])){
//             return Failure;
//         }
//     }
//     if(!isdigit(test_res[i-1])){
//         return Failure;
//     }

//     length = strlen(test_lang);
//     for(i = 0; i < length; i++){
//         if(islower(test_lang[i])){
//             return Failure;
//         }
//     }

//     length = strlen(test_id);
//     for(i = 0; i < length; i++){
//         if(isalpha(test_id[i])){
//             return Failure;
//         }
//     }

//     return 1;
// }

/*Skal sætte den næste dato for automatisk aktivering ind i settings.txt filen*/
/*Husk at sørg for next_activation også bliver kørt i update_setings!*/
void update_next_activation(user *User){
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
            update_settings(User);
            return;
        }
        User->settings.next_activation = next_day(User->choice.now);
        update_settings(User);
    }
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
