/* FIX THIS!!! */
/*DONE sørg for at doubles indlæses selv om der ikke er komma i tallet 
    det klares ved at acceptere scanres>0 */

/* spring over hvis data_txt ikke indeholder et tal
 * se på problem med at 'æ' læses som et tal */

/* get_prize_data funktionen skal ændres til get_data_for_timeinterval */

/* lav en days in month funktion */

/* lav en hours_since_index0 funktion*/

/* sæt index0 til første index som indeholder en gyldig dato */

/*brug ovenstående til at beregne hvilket index nr_of_elements der skal returnes*/








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
#include <ctype.h>
#include "global.h"
#include "calc_time.h"

#define MAX_LINE_WIDTH 400
// #define HOURS_PR_YEAR 8765
// #define FILENAME_PRICE "/Users/saxjax/Documents/GitHub/P1-Energy-Awareness/Larry/database_module/elspot-prices_2018_hourly_dkk.csv"
#define DATE_DMY "%2d-%2d-%4d %2dÊ-Ê%2d"
#define DATE_YMD "%4d %2d %2d %2d.%2d"

pricedata mypricedata[HOURS_PR_YEAR*3];
meterdata myconsumpdata[HOURS_PR_YEAR*3];
int price_initialised = 0;
int consumption_initialised = 0;


void        init_database(void);
void        init_pricestruct(pricedata data[]);
pricedata   *init_price_array(pricedata mypricedata[]);
void        init_meterstruct(meterdata data[]);




int         copy_file_to_mypricedata(char *filename);
int         copy_file_to_myconsumpdata(char *filename);



void    print_price_index(int index);
void    print_consump_index(int index);

FILE    *check_file(char*filename);
void    prompt_for_filename(char *str);
dato    date_from_stringDMYI(char *str,int time);
dato    date_from_stringYMDH(char *date);
double  price_from_string(char *price);
double consumption_from_string(char *price);

int     get_next_hour(int hour);
int     hours_since_index(dato first_index, dato to);

void    get_db_start_end_index(int start_index,int end_index);








void init_database(void){
   
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
   
   //  printf("vi skal til at hente fil indhold\n");
    price_initialised =  copy_file_to_mypricedata(FILENAME_PRICE);
    printf("vi har hentet prisfil indhold\n");


   //  printf("hent pris for index: ");
   //  while (scanf("%d",&index)&& index != -1){
   //       if(index != -1){
   //          printf("her er prisen på index%d\n DK1:%f  DK2:%f \n",index, mypricedata[index].DK1price, mypricedata[index].DK2price);
   //       }
   //  }


    init_meterstruct(myconsumpdata);

   //  printf("vi skal til at hente fil indhold\n");
   consumption_initialised = copy_file_to_myconsumpdata(FILENAME_METER);
    printf("vi har hentet consumption-fil indhold\n");


   //  printf("hent pris for index: ");
   //  while (scanf("%d",&index)&& index != -1){
   //       if(index != -1){
   //          printf("her er forbruget på index%d\n VALUE:%f \n",index, myconsumpdata[index].value);
   //       }
   //  }


}




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
    data *tempdata;
    
    
    int i=0 , start_index = 0, end_index = 23;
    int nr_of_elements = 24;
    int db_cur_index = 0;
    

    if (price_initialised == 0 && consumption_initialised == 0){
        init_database();
    }
    /* init VARIABLES and return structure*/
    printf("dato 0 er : %d-%d-%d kl: %d:%d",mypricedata[3].from.year);
    start_index     = hours_since_index(mypricedata[3].from, from);
    end_index       = hours_since_index(from, to)+100;
    nr_of_elements  = abs(end_index-start_index);
    tempdata        = malloc(nr_of_elements*sizeof(data));
    db_cur_index    = start_index;


    for (i=0 ; i < nr_of_elements ; i++) { 
        tempdata[i].prize.from    = mypricedata[db_cur_index].from;      
        tempdata[i].prize.to      = mypricedata[db_cur_index].to;      
        tempdata[i].prize.DK1price= mypricedata[db_cur_index].DK1price;
        tempdata[i].prize.DK2price= mypricedata[db_cur_index].DK2price;

        tempdata[i].meter.from    = myconsumpdata[db_cur_index].from;      
        tempdata[i].meter.to      = myconsumpdata[db_cur_index].to;      
        tempdata[i].meter.value   = myconsumpdata[db_cur_index].value; 
        
        db_cur_index++;
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
            // printf("%s\n",token);
            token=strtok(NULL,s);
            i++;
        }
        
            
            sscanf(data_txt[1],"%dÊ-Ê",&houra);
        
        //   printf("hra:%d,hrb:%d\n",houra, hourb_int);
            mypricedata[j].from  = date_from_stringDMYI(data_txt[0],houra);
            mypricedata[j].to    = date_from_stringDMYI(data_txt[0],get_next_hour(houra));
            
            mypricedata[j].DK1price = price_from_string(data_txt[8]);
            mypricedata[j].DK2price = price_from_string(data_txt[9]);

            // print_price_index(j);
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
            // printf("%s\n",token);
            token=strtok(NULL,s);
            i++;
        }
        
      //   printf("linie:169 i=%d  j=%d\n",i,j);
        
        
        
        strcpy(myconsumpdata[j].id,data_txt[0]);
        // printf("---%s---\n",data_txt[1]);
        myconsumpdata[j].from   = date_from_stringYMDH(data_txt[1]);
        myconsumpdata[j].to     = date_from_stringYMDH(data_txt[2]);
                
        myconsumpdata[j].value = consumption_from_string(data_txt[3]);
        print_consump_index(j);
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
        printf("%s\n",filename);
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
   //  printf("b%d\n",mypricedata[20].from.year);

  return mypricedata;
}

pricedata *init_price_array(pricedata mypricedata[]){
    int i = 0;
    pricedata *temp;
    temp = malloc(sizeof(pricedata));
    
    temp->DK1price  = 00;
    temp->DK2price =00;
    temp->from      = date_from_stringDMYI("0000-00-00", 0);
    temp->to        = date_from_stringDMYI("0000-00-00",0); 
    temp->from.year =  00;
   return temp; 
}

/* Helper functions */

void prompt_for_filename(char *str){
    printf("skriv filnavn:");
    scanf(" %s",str);
}


dato date_from_stringDMYI(char *date, int time){
    dato ret_date ={{0,0},0,0,0};
    if(sscanf(date,"%2d-%2d-%4d",&ret_date.day, &ret_date.month, &ret_date.year)==3){
    ret_date.time.hour = time;
    ret_date.time.minute =0;
    }
    else {
          printf("error tried to convert string %s and int %d to date\n",date , time); 
    }
    return ret_date;
    
}


dato date_from_stringYMDH(char *date){
    dato ret_date = {{0,0},0,0,0};
    if(sscanf(date,"%4d-%2d-%2d %d.%d",&ret_date.year, &ret_date.month, &ret_date.day, &ret_date.time.hour, &ret_date.time.minute)<4){
        printf("error tried to convert string %s to date\n",date); 
    }
    return ret_date;
}

double price_from_string(char *price){
   double value1=0,value2=0;
   int scanres=0;
   
   if ((scanres = sscanf(price," %lf,%lf " ,&value1,&value2))>0){
      return  value1 + value2/100;
   }
   
   printf("error tried to convert string %s to doubles %lf %lf to number\n",price ,value1,value2);
   return -1000;
}

double consumption_from_string(char *price){
    double value1=0,value2=0;
    int scanres=0;
    
    if ((scanres = sscanf(price," %lf,%lf " ,&value1,&value2))>0){
        return  value1 + value2/1000;
    }
    
   printf("error tried to convert string %s to doubles %lf %lf to number\n",price ,value1,value2);
    return -1000;
}





void print_price_index(int index){
   printf("from: %d-%d-%d %d:%d\nto  : %d-%d-%d %d:%d\n DK1: %f\nDK2: %f \n\n",
   mypricedata[index].from.year,mypricedata[index].from.month,mypricedata[index].from.day,mypricedata[index].from.time.hour,mypricedata[index].from.time.minute,
   mypricedata[index].to.year  ,mypricedata[index].to.month  ,mypricedata[index].to.day  ,mypricedata[index].to.time.hour  ,mypricedata[index].to.time.minute,
   mypricedata[index].DK1price,mypricedata[index].DK2price);
    
}

void print_consump_index(int index){
   printf("from: %d-%d-%d %d:%d\nto  : %d-%d-%d %d:%d\n VALUE: %f\n\n",
   myconsumpdata[index].from.year,myconsumpdata[index].from.month,myconsumpdata[index].from.day,myconsumpdata[index].from.time.hour,myconsumpdata[index].from.time.minute,
   myconsumpdata[index].to.year  ,myconsumpdata[index].to.month  ,myconsumpdata[index].to.day  ,myconsumpdata[index].to.time.hour  ,myconsumpdata[index].to.time.minute,
   myconsumpdata[index].value);
    
}


int get_next_hour(int hour){
    return hour < 23 ? hour+1 : 0;
}

int hours_since_index(dato first_index, dato to){
    return 100;
    //calc_time(first_index,to);
}

void    get_db_start_end_index(int start_index,int end_index){
    
}


