
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
// #define HOURS_PR_YEAR 8765
// #define FILENAME_PRICE "/Users/saxjax/Documents/GitHub/P1-Energy-Awareness/Larry/database_module/elspot-prices_2018_hourly_dkk.csv"
#define DATE_DMY "%2d-%2d-%4d %2dÊ-Ê%2d"
#define DATE_YMD "%4d %2d %2d %2d.%2d"

pricedata mypricedata[HOURS_PR_YEAR];
meterdata myconsumpdata[HOURS_PR_YEAR];


void        init(void);
pricedata   *init_datab(pricedata *mypricedata, meterdata *meter_data, production *production_data);
void        init_pricestruct(pricedata data[]);
pricedata   *init_price_array(pricedata mypricedata[]);
void        init_meterstruct(meterdata data[]);




int         copy_file_to_mypricedata(char *filename);
int         copy_file_to_myconsumpdata(char *filename);



void    print_index(int index);
FILE    *check_file(char*filename);
void    prompt_for_filename(char *str);
dato    date_from_string(char *str,int time);
double  price_from_string(char *price);
int     get_next_hour(int hour);







int main(void){
   
   int index=0;
   dato date1,date2;
   data *testdata;
   data temp;
   date1.day = date2.day =20;
   date1.month=date2.month=2;
   date1.day = date2.day =20;
   date1.year=date2.year=2017;
   date1.time.hour =10;
   date2.time.hour =23;
   date1.time.minute=date2.time.minute=0;

   //
   init_pricestruct(mypricedata);

//    printf("hent pris for index: ");
//    while (scanf("%d",&index)&& index != -1){
//          if(index != -1){
//             printf("her er prisen på index%d %f ",index, mypricedata[index].DK1price);
//          }
//    }
   
    printf("vi skal til at hente fil indhold\n");
    copy_file_to_mypricedata(FILENAME_PRICE);
    printf("vi har hentet fil indhold\n");


    printf("hent pris for index: ");
    while (scanf("%d",&index)&& index != -1){
         if(index != -1){
            printf("her er prisen på index%d\n DK1:%f  DK2:%f \n",index, mypricedata[index].DK1price, mypricedata[index].DK2price);
         }
    }


    init_meterstruct(myconsumpdata);

    printf("vi skal til at hente fil indhold\n");
    copy_file_to_mypricedata(FILENAME_METER);
    printf("vi har hentet fil indhold\n");


    printf("hent pris for index: ");
    while (scanf("%d",&index)&& index != -1){
         if(index != -1){
            printf("her er forbruget på index%d\n VALUE:%f \n",index, myconsumpdata[index].value);
         }
    }


   return 0;
}


// void init(void){ 
//     int i = 0;
//     for(i=0;i<HOURS_PR_YEAR;i++){
//        mypricedata[i].DK1price  = 00;
//        mypricedata[i].DK2price  = 00;
//        mypricedata[i].from  = date_from_string("0000 00 00 00:00",DATE_YMD);
//        mypricedata[i].to  = date_from_string("0000 00 00 00:00",DATE_YMD);
//     }
// copy_file_to_mypricedata(FILENAME_PRICE);
    
// }



void init_pricestruct(pricedata data[]){
   int i =0;
   for(i=0;i<HOURS_PR_YEAR;i++){
    data[i].DK1price=0;
    data[i].DK2price=0;
    data[i].from.year=0;
    data[i].from.month=0;
    data[i].from.day=0;
    data[i].from.time.hour=0;
    data[i].from.time.minute=0;
    data[i].to.year=0;
    data[i].to.month=0;
    data[i].to.day=0;
    data[i].to.time.hour=0;
    data[i].to.time.minute=0;
   }
}


void init_meterstruct(meterdata data[]){
   int i =0;
   for(i=0;i<HOURS_PR_YEAR;i++){
    data[i].value=2999;
    data[i].from.year=0;
    data[i].from.month=0;
    data[i].from.day=0;
    data[i].from.time.hour=0;
    data[i].from.time.minute=0;
    data[i].to.year=0;
    data[i].to.month=0;
    data[i].to.day=0;
    data[i].to.time.hour=0;
    data[i].to.time.minute=0;
   }
}




data *get_price_for_timeinterval_in_area(dato from, dato to,  area area){
   int interval = 24 ;
   int year=2018,month=02,day=10,hour1=0,hour2=1;
   double dk1=135,dk2=156;
   // abs(to.time.hour - from.time.hour);
   data *tempdata;
   int i =0;
   int db_index = from.day;
   tempdata = malloc(interval*sizeof(data));
   
   for (i=0 ; i < interval ; i++) { 
      tempdata[i].prize.from    = mypricedata[i].from;
      
      tempdata[i].prize.to      = mypricedata[i].to;
      
      tempdata[i].prize.DK1price=mypricedata[i].DK1price;
      tempdata[i].prize.DK2price=mypricedata[i].DK2price;

      tempdata[i].meter.from.year=year;
      tempdata[i].meter.from.month = month;
      tempdata[i].meter.from.day = day;
      tempdata[i].meter.from.time.hour =hour1+i;
      tempdata[i].meter.from.time.minute =00;
      tempdata[i].meter.to.year=year;
      tempdata[i].meter.to.month = month;
      tempdata[i].meter.to.day = day;
      tempdata[i].meter.to.time.hour =hour2+i;
      tempdata[i].meter.to.time.minute =00;

      tempdata[i].meter.value= rand()%100 /53.2;
      
      // tempdata[i].prize.from     = mypricedata[db_index].from;
      // tempdata[i].prize.to       = mypricedata[db_index].to;
      // tempdata[i].prize.DK1price = mypricedata[db_index].DK1price;
      // tempdata[i].prize.DK2price = mypricedata[db_index].DK2price;
      db_index++;
   }

   return tempdata;
}





/* Elspot Prices in DKK/MWh;;;;;;;;;;;;;;;;;;
Data was last updated 31-12-2018;;;;;;;;;;;;;;;;;;
;Hours;SYS;SE1;SE2;SE3;SE4;FI;DK1;DK2;Oslo;Kr.sand;Bergen;Molde;Tr.heim;Tromsø;EE;LV;LT
01-01-2017;00 - 01;191,05;178,64;178,64;178,64;178,64;178,64;155,82;155,82;211,13;211,13;211,13;178,64;178,64;178,64;178,64;178,64;178,64
01-01-2017;01 - 02;190,38;178,64;178,64;178,64;178,64;178,64;155,37;155,37;209,42;209,42;209,42;178,64;178,64;178,64;178,64;178,64;178,64
*/
int copy_file_to_mypricedata(char *filename){
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

    j=0;

    while (fgets(str,MAX_LINE_WIDTH,f)!=NULL){
        char  hourb[7];
        int   houra,hourb_int;
        token = strtok(str,s);
        i=0;
        while(token !=NULL){
            data_txt[i] = token;
            printf("%s\n",token);
            token=strtok(NULL,s);
            i++;
        }
        
        printf("linie:169 i=%d  j=%d\n",i,j);
        
        sscanf(data_txt[1],"%dÊ-Ê",&houra);
        // sscanf(data_txt[1],"%*d %*3c %s",hourb);
        // sscanf((data_txt[1]+5),"%d",&hourb_int);

        
        printf("hra:%d,hrb:%d\n",houra, hourb_int);
        mypricedata[j].from  = date_from_string(data_txt[0],houra);
        mypricedata[j].to    = date_from_string(data_txt[0],get_next_hour(houra));
        
        mypricedata[j].DK1price = price_from_string(data_txt[8]);
        mypricedata[j].DK2price = price_from_string(data_txt[9]);

        print_index(j);
        j++;
    }
    /* ;%2dÊ-Ê%2d;%*d,%*d;%*d;%*d;%*d;196;196;162,28;196;196;196;196;196;196;196;196;196;196
 */    




    fclose(f);
    return SUCCESS;
}


/* Målepunkt id;Fra dato;Til dato;Mængde;Måleenhed;Kvalitet;Type;
571313104402686056;2017-01-01 00.00;2017-01-01 01.00;0,440;KWH;Målt;Tidsserier;
571313104402686056;2017-01-01 01.00;2017-01-01 02.00;0,450;KWH;Målt;Tidsserier; 
*/
int copy_file_to_myconsumpdata(char *filename){
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

    j=0;

    while (fgets(str,MAX_LINE_WIDTH,f)!=NULL){
        char  hourb[7];
        int   houra,hourb_int;
        token = strtok(str,s);

        i=0;
        while(token !=NULL){
            data_txt[i] = token;
            printf("%s\n",token);
            token=strtok(NULL,s);
            i++;
        }
        
        printf("linie:169 i=%d  j=%d\n",i,j);
        
        
        // sscanf(data_txt[1],"%*d %*3c %s",hourb);
        // sscanf((data_txt[1]+5),"%d",&hourb_int);
        strcpy(myconsumpdata[j],data_txt[0]);
        
        printf("hra:%d,hrb:%d\n",houra, hourb_int);
        mypricedata[j].from  = date_from_string(data_txt[0],houra);
        mypricedata[j].to    = date_from_string(data_txt[0],get_next_hour(houra));
        
        mypricedata[j].DK1price = price_from_string(data_txt[8]);
        mypricedata[j].DK2price = price_from_string(data_txt[9]);

        print_index(j);
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













pricedata *init_datab(pricedata *mypricedata, meterdata *meter_data, production *production_data){
    int i = 0;
    mypricedata = malloc((HOURS_PR_YEAR+50)*sizeof(pricedata));    
    for(i=0;i<HOURS_PR_YEAR;i++){
        mypricedata[i] = *init_price_array(mypricedata);
    }
    printf("b%d\n",mypricedata[20].from.year);

  return mypricedata;
}

pricedata *init_price_array(pricedata mypricedata[]){
    int i = 0;
    pricedata *temp;
    temp = malloc(sizeof(pricedata));
    
    temp->DK1price  = 00;
    temp->DK2price =00;
    temp->from      = date_from_string("0000-00-00", 0);
    temp->to        = date_from_string("0000-00-00",0); 
    temp->from.year =  00;
   return temp; 
}

/* Helper functions */

void prompt_for_filename(char *str){
    printf("skriv filnavn:");
    scanf(" %s",str);
}


dato date_from_string(char *date, int time){
    dato ret_date;
    sscanf(date,"%2d-%2d-%4d",&ret_date.year, &ret_date.month, &ret_date.day);
    ret_date.time.hour = time;
    ret_date.time.minute =0;
    return ret_date;
}


double price_from_string(char *price){
    double value1=0,value2=0;
    int scanres=0;
    
    if ((scanres = sscanf(price," %lf,%lf " ,&value1,&value2))>1){
        return  value1 + value2/100;
    }
    
    printf("could not convert %lf %lf to number\n",value1,value2);
    return -1000;
}




void print_index(int index){
    printf("from: %d-%d-%d %d:%d\nto  : %d-%d-%d %d:%d\n DK1: %f\nDK2: %f \n\n",
    mypricedata[index].from.year,mypricedata[index].from.month,mypricedata[index].from.day,mypricedata[index].from.time.hour,mypricedata[index].from.time.minute,
    mypricedata[index].to.year  ,mypricedata[index].to.month  ,mypricedata[index].to.day  ,mypricedata[index].to.time.hour  ,mypricedata[index].to.time.minute,
    mypricedata[index].DK1price,mypricedata[index].DK2price);
    
}


int get_next_hour(int hour){
    return hour < 23 ? hour+1 : 0;
}

