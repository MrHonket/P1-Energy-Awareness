
/* *get_price_for_time_interval */
/* *get_consumption_for_timeinterval */

/* init_datab */
/* init_pricestruct */
/* init_meterstruct */
/* init_datastruct */


/* import_pricedata_from_file */
/* import_meterdata_from_file */


/* prompt for filename */
/* check_if_file_exists */

/* create_price_struct_from_string */
/* create meterstruct from string */
/*Universelle imports*/


#include <stdio.h>
#include <string.h>
#include "global.h"

#define MAX_LINE_WIDTH 400
#define HOURS_PR_YEAR (365*24)
#define FILENAME_PRICE "/Users/saxjax/Documents/GitHub/P1-Energy-Awareness/Larry/database_module/elspot-prices_2018_hourly_dkk.csv"
#define DATE_DMY "%2d-%2d-%4d %2dÊ-Ê%2d"
#define DATE_YMD "%4d %2d %2d %2d.%2d"

pricedata price_data[HOURS_PR_YEAR];


void init(void);
pricedata *init_datab(pricedata *price_data, meterdata *meter_data, production *production_data);
pricedata *init_price_array(pricedata price_data[]);

int copy_file_to_price_data(char *filename);



void print_index(int index);
FILE *check_file(char*filename);
void prompt_for_filename(char *str);
dato date_from_string(char *str,char *type);




void init(void){ 
    int i = 0;
    for(i=0;i<HOURS_PR_YEAR;i++){
       price_data[i].DK1price  = 00;
       price_data[i].DK2price  = 00;
       price_data[i].from  = date_from_string("0000 00 00 00:00",DATE_YMD);
       price_data[i].to  = date_from_string("0000 00 00 00:00",DATE_YMD);
    }
copy_file_to_price_data(FILENAME_PRICE);
    
}

int copy_file_to_price_data(char *filename){
    int i=0,j=0;
    char str[MAX_LINE_WIDTH];
    double value1=0,value2=0;
    const char s[2] = ";";
    char *token;
    char *data_txt[30];

    FILE *f = check_file(filename);
    for(i=0;i<30;i++){
        data_txt[i] = " ";
    }
    i=j=0;

    while (fgets(str,MAX_LINE_WIDTH,f)!=NULL){
        pricedata temp;
        token = strtok(str,s);
        while(token !=NULL){
            data_txt[i] = token;
            printf("%s\n",token);
            token=strtok(NULL,s);
            i++;
        }
        

        price_data[j].from = date_from_string(data_txt[0],DATE_DMY);
        price_data[j].to    = date_from_string(data_txt[0],DATE_DMY);



        /* sscanf(data_txt[0],"%2d-%2d-%4d",&price_data[j].from.day, &price_data[j].from.month, &price_data[j].from.year);
        printf("\n\n\n");
        
        sscanf(data_txt[1],"%2dÊ-Ê%2d", &price_data[j].from.time.hour,&price_data[j].to.time.hour);
        printf("%2d-%2d-%4d;%2d-----\n",price_data[j].from.day, price_data[j].from.month, price_data[j].from.year, price_data[j].from.time.hour);
         */

        print_index(i);
        j++;
    }
/* ;%2dÊ-Ê%2d;%*d,%*d;%*d;%*d;%*d;196;196;162,28;196;196;196;196;196;196;196;196;196;196
 */    



    




    fclose(f);
    return SUCCESS;
}

FILE *check_file(char*filename){
    FILE *f = fopen(filename,"r");
    if(f!=NULL){
        // sprintf(strOUT,"%s",filename);
    }

    if(f!=NULL){
        printf("%s",filename);
        return f;
    }

    else{ 
        char newfile[MAX_LINE_WIDTH];
        printf("filnavnet findes ikke!\nindtast sti til fil med priser: ");
        prompt_for_filename(newfile);
        check_file(newfile);
    }
    return 0;
}













pricedata *init_datab(pricedata *price_data, meterdata *meter_data, production *production_data){
    int i = 0;
    price_data = malloc((HOURS_PR_YEAR+50)*sizeof(pricedata));    
    for(i=0;i<HOURS_PR_YEAR;i++){
        price_data[i] = *init_price_array(price_data);
    }
    printf("b%d\n",price_data[20].from.year);

  return price_data;
}

pricedata *init_price_array(pricedata price_data[]){
    int i = 0;
    pricedata *temp;
    temp = malloc(sizeof(pricedata));
    
    temp->DK1price  = 00;
    temp->DK2price =00;
    temp->from      = date_from_string("0000-00-00 00.00", DATE_YMD);
    temp->to        = date_from_string("0000-00-00 00.00",DATE_YMD); 
    temp->from.year =  00;
   return temp; 
}

/* Helper functions */

void prompt_for_filename(char *str){
    printf("skriv filnavn:");
    scanf(" %s",str);
}


dato date_from_string(char *str,char *type){
    dato ret_date;
    sscanf(str,type,&ret_date.year, &ret_date.month, &ret_date.day, &ret_date.time.hour, &ret_date.time.minute);
    return ret_date;
}




void print_index(int index){
    printf("from: %d-%d-%d %d:%d\nto  : %d-%d-%d %d:%d\n DK1: %f\nDK2: %f ",
    price_data[index].from.year,price_data[index].from.month,price_data[index].from.day,price_data[index].from.time.hour,price_data[index].from.time.minute,
    price_data[index].to.year  ,price_data[index].to.month  ,price_data[index].to.day  ,price_data[index].to.time.hour  ,price_data[index].to.time.minute,
    price_data[index].DK1price,price_data[index].DK2price);
    
}

