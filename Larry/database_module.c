#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "global.h"


#define MAX_LINE_WIDTH 400
#define DATE_DMY "%2d-%2d-%4d %2dÊ-Ê%2d"
#define DATE_YMD "%4d %2d %2d %2d.%2d"
#define FIRST_PRICEINDEX 3
#define FIRST_CONSUMPINDEX 0
#define ELSPOT_FILE_ID "Elspot Prices in DKK/MWh"   //check om filen indeholder dette i de første linier
#define CONSUMP_FILE_ID "571313104402686056"        //check om filen indeholder dette i de første linier
#define DATARESOLUTION 1 //data inddeles i 1 timers intervaller

static pricedata mypricedata[HOURS_PR_YEAR*3];
static meterdata myconsumpdata[HOURS_PR_YEAR*3];
int price_initialised = 0;          //flag sættes hvis der er nye data tilrådighed somikke ligger i mypricedata
int consumption_initialised = 0;    //flag sættes hvis der er nye data tilrådighed somikke ligger i mypricedata


data        *get_price_for_timeinterval_in_area(dato from, dato to,  area area);// get data for time interval
void        init_database(void);
void        init_pricestruct(pricedata data[]);
pricedata   *init_price_array(pricedata mypricedata[]);
void        init_meterstruct(meterdata data[]);
pricedata   empty_pricestruct(void);
meterdata   empty_consumpstruct(void);



int         copy_file_to_mypricedata(char *filename);
int         copy_file_to_myconsumpdata(char *filename);


void print_price_index_from_array(pricedata *Data, int index);
void print_consump_index_from_array(meterdata *Data, int index);


void    print_price_index(int index);
void    print_consump_index(int index);

FILE    *check_file(char*filename);
void    prompt_for_filename(char *str);
dato    date_from_stringDMYI(char *str,int time);
dato    date_from_stringYMDH(char *date);
double  price_from_string(char *price);
double  consumption_from_string(char *price);

/* int     get_next_hour(int hour);
 */
int     hours_since_index(dato first_index, dato to);
/* int     calc_time(dato from, dato to);
int     calc_hours(dato test_year, month test); */




void init_database(void){
   
   dato date1,date2;
   date1.day = date2.day =20;
   date1.month=date2.month=2;
   date1.day = date2.day =20;
   date1.year=date2.year=2017;
   date1.time.hour =10;
   date2.time.hour =23;
   date1.time.minute=date2.time.minute=0;

   if(!price_initialised){
        init_pricestruct(mypricedata);

        price_initialised =  copy_file_to_mypricedata(FILENAME_PRICE);
   
   }

   if(!consumption_initialised){

        init_meterstruct(myconsumpdata);

        consumption_initialised = copy_file_to_myconsumpdata(FILENAME_METER);
   }

}


pricedata empty_pricestruct(void){
    pricedata data;
    data.DK1price=0;
    data.DK2price=0;
    data.from.year=0;
    data.from.month=0;
    data.from.day=0;
    data.from.time.hour=0;
    data.from.time.minute=0;
    data.to.year=0;
    data.to.month=0;
    data.to.day=0;
    data.to.time.hour=0;
    data.to.time.minute=0;

    return data;

}

meterdata empty_consumpstruct(void){
    meterdata data;
    data.value=0;
    data.from.year=0;
    data.from.month=0;
    data.from.day=0;
    data.from.time.hour=0;
    data.from.time.minute=0;
    data.to.year=0;
    data.to.month=0;
    data.to.day=0;
    data.to.time.hour=0;
    data.to.time.minute=0;

    return data;
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
    
    int first_data_index = FIRST_PRICEINDEX;
    int i=0 , start_index = 0, end_index = 23;
    int nr_of_elements = 24;
    int db_cur_index = 0;
    

    if (price_initialised == 0 || consumption_initialised == 0){
        init_database();
    }
    /* init VARIABLES and return structure*/
    // printf("dato 0 er : %d-%d-%d kl: %d:%d\n",mypricedata[first_data_index].from.year, mypricedata[first_data_index].from.month,mypricedata[first_data_index].from.day,mypricedata[first_data_index].from.time.hour,mypricedata[first_data_index].from.time.minute);
    start_index     = hours_since_index(mypricedata[first_data_index].from, from);
    end_index       = hours_since_index(mypricedata[first_data_index].from, to);
    nr_of_elements  = abs(end_index-start_index)+1;
    tempdata        = malloc(nr_of_elements*sizeof(data));
    db_cur_index    = start_index;


    for (i=0 ; i < nr_of_elements ; i++) { 
        tempdata[i].prize.from    = mypricedata[db_cur_index+FIRST_PRICEINDEX].from;    
        tempdata[i].prize.to      = mypricedata[db_cur_index+FIRST_PRICEINDEX].to;   
        tempdata[i].prize.DK1price= mypricedata[db_cur_index+FIRST_PRICEINDEX].DK1price;
        tempdata[i].prize.DK2price= mypricedata[db_cur_index+FIRST_PRICEINDEX].DK2price;

        tempdata[i].meter.from    = myconsumpdata[db_cur_index+FIRST_CONSUMPINDEX].from;      
        tempdata[i].meter.to      = myconsumpdata[db_cur_index+FIRST_CONSUMPINDEX].to;      
        tempdata[i].meter.value   = myconsumpdata[db_cur_index+FIRST_CONSUMPINDEX].value; 
        
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
    int data_recognised = 0;
    int i=0,j=0;
    char str[MAX_LINE_WIDTH];
    const char s[2] = ";";
    char *token;
    char *data_txt[30];

    FILE *f = check_file(filename);

    for(i=0;i<30;i++){
        data_txt[i] = " ";
    }

    j=0;

    while (fgets(str,MAX_LINE_WIDTH,f)!=NULL){
        int   houra;
        token = strtok(str,s);
        

        if(data_recognised == 0 && strstr(token,ELSPOT_FILE_ID)!=0){
            data_recognised = 1;
        }

        if(data_recognised == 1){

            i=0;
            while(token !=NULL){
                data_txt[i] = token;
                /* printf("%s\n",token); */
                token=strtok(NULL,s);
                i++;
            }
                
            sscanf(data_txt[1],"%dÊ-Ê",&houra);
        
            mypricedata[j].from  = date_from_stringDMYI(data_txt[0],houra);
            mypricedata[j].to    = next_hour(mypricedata[j].from);
            
            mypricedata[j].DK1price = price_from_string(data_txt[8]);
            mypricedata[j].DK2price = price_from_string(data_txt[9]);

            j++;
        } 
         
    }
   
    

    fclose(f);

    if (data_recognised == 1){
        price_initialised = 1;
        printf("sucessful import af %d antal pris data!\n\n",j-FIRST_PRICEINDEX);
        return SUCCESS;
          
    } 

    printf("\nIngen prisdata blev indlæst , det tyder på at filen: %s har en forkert formatering!\n\n",filename);
    return EXIT_FAILURE; 
   
}



/* Målepunkt id;Fra dato;Til dato;Mængde;Måleenhed;Kvalitet;Type;
571313104402686056;2017-01-01 00.00;2017-01-01 01.00;0,440;KWH;Målt;Tidsserier;
571313104402686056;2017-01-01 01.00;2017-01-01 02.00;0,450;KWH;Målt;Tidsserier; 
*/
int copy_file_to_myconsumpdata(char *filename){
    int data_recognised = 0;
    int i=0,j=0, k=0;
    dato tempfrom, tempto;
    int dist = 0;
    char str[MAX_LINE_WIDTH];
    const char s[2] = ";";
    char *token;
    char *data_txt[30];

    FILE *f = check_file(filename);

    for(i=0;i<30;i++){
        data_txt[i] = " ";
    }

    j=0;

    while (fgets(str,MAX_LINE_WIDTH,f)!=NULL){
        
        token = strtok(str,s);

        i=0;

        if(data_recognised == 0 && strcmp(token,CONSUMP_FILE_ID)==0){
            data_recognised = 1;
        }

        if(data_recognised == 1){

            while(token !=NULL){
                data_txt[i] = token;
            /*  printf("%s\n",token); */
                token=strtok(NULL,s);
                i++;
            }
            
            /* printf("linie:169 i=%d  j=%d\n",i,j); */
            tempfrom = date_from_stringYMDH(data_txt[1]);
            tempto   = date_from_stringYMDH(data_txt[2]);

            if(hours_between(tempfrom,tempto)==DATARESOLUTION ){      
                strcpy(myconsumpdata[j].id,data_txt[0]);
                /* printf("---%s---\n",data_txt[1]); */
                myconsumpdata[j].from   = date_from_stringYMDH(data_txt[1]);
                myconsumpdata[j].to     = date_from_stringYMDH(data_txt[2]);
                myconsumpdata[j].value = consumption_from_string(data_txt[3]);

                if(j>1 &&( dist = hours_between(myconsumpdata[j-1].from,myconsumpdata[j].from))>DATARESOLUTION){
                    //dist--;//flyttet til for loopet
            
                /*  printf("lappet hul i data :");
                    print_date(myconsumpdata[j].from);
                    printf("      afstand mlm datoer = %d \n", dist); */
                    k = 0;
                    
                    for(k=0; k<dist-1; k++){
                        myconsumpdata[j+k] = empty_consumpstruct();
                    }
                    /* printf("%d tomme datafelter tilføjet fra index %d til index %d\n",dist,j,j+k);
                    printf("index %5d : på dato: %d-%d-%d kl%d dist %d\n",j-1,myconsumpdata[j-1].from.year, myconsumpdata[j-1].from.month, myconsumpdata[j-1].from.day,myconsumpdata[j-1].from.time.hour, dist);
                */
                    j += dist;
                    strcpy(myconsumpdata[j].id,data_txt[0]);
                    myconsumpdata[j].from   = date_from_stringYMDH(data_txt[1]);
                    myconsumpdata[j].to     = date_from_stringYMDH(data_txt[2]);
                    myconsumpdata[j].value = consumption_from_string(data_txt[3]);

                    printf("      %5d : på dato: %d-%d-%d kl%d dist %d\n\n",j,myconsumpdata[j].from.year, myconsumpdata[j].from.month, myconsumpdata[j].from.day,myconsumpdata[j].from.time.hour, dist);

                }
                j++;
            }
        }
    }

    fclose(f);

    if (data_recognised == 1){
         consumption_initialised = 1;
         printf("sucessful import af %d antal forbrugs data!\n\n",j-FIRST_PRICEINDEX);
        return SUCCESS;      
    }

    printf("\nIngen prisdata blev indlæst , det tyder på at filen har en forkert formatering!\n\n");
    return EXIT_FAILURE;
    
}



FILE *check_file(char*filename){
    FILE *f = fopen(filename,"r");
    while (f==NULL){
        char newfilename[MAX_LINE_WIDTH];
        printf("filnavnet %s findes ikke!\nindtast sti til ny fil\n",filename);
        prompt_for_filename(newfilename);
        f=fopen(newfilename,"r");
    }
    return f;

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
         /*  printf("did not convert string  -\"%s\"- and int --%d-- to date\n",date , time);  */
    }
    return ret_date;
    
}


dato date_from_stringYMDH(char *date){
    dato ret_date = {{0,0},0,0,0};
    if(sscanf(date,"%4d-%2d-%2d %d.%d",&ret_date.year, &ret_date.month, &ret_date.day, &ret_date.time.hour, &ret_date.time.minute)<4){
        printf("did not convert string  -\"%s\"-   to date\n",date); 
    }
    return ret_date;
}


double price_from_string(char *price){
   double value1=0,value2=0;
   int scanres=0;
   
   if ((scanres = sscanf(price," %lf,%lf " ,&value1,&value2))>0){
      return  value1 + value2/100;
   }
   
   /* printf("did not convert string  -\"%s\"-   to doubles %lf %lf to number\n",price ,value1,value2); */
   return -1000;
}


double consumption_from_string(char *consump){
    double value1=0,value2=0;
    int scanres=0;
    
    if ((scanres = sscanf(consump," %lf,%lf " ,&value1,&value2))>0){//evt %3f
        return  value1 + value2/1000;
    }
    
   /* printf("did not convert string -\"%s\"-   to doubles %lf %lf to number\n",price ,value1,value2); */
    return -1000;
}



void print_price_index_from_array(pricedata *Data, int index){
   printf("from: %d-%d-%d %d:%d\nto  : %d-%d-%d %d:%d\n DK1: %f\nDK2: %f \n\n",
   Data[index].from.year,Data[index].from.month,Data[index].from.day,Data[index].from.time.hour,Data[index].from.time.minute,
   Data[index].to.year  ,Data[index].to.month  ,Data[index].to.day  ,Data[index].to.time.hour  ,Data[index].to.time.minute,
   Data[index].DK1price,Data[index].DK2price);
    
}

void print_consump_index_from_array(meterdata *Data, int index){
   printf("from: %d-%d-%d %d:%d\nto  : %d-%d-%d %d:%d\n VALUE: %f\n\n",
   Data[index].from.year,Data[index].from.month,Data[index].from.day,Data[index].from.time.hour,Data[index].from.time.minute,
   Data[index].to.year  ,Data[index].to.month  ,Data[index].to.day  ,Data[index].to.time.hour  ,Data[index].to.time.minute,
   Data[index].value);
    
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


// int get_next_hour(int hour){
//     return hour < 23 ? hour+1 : 0;
// }

int hours_since_index(dato first_index, dato to){
   /*  printf("calc_time returnerer: %d",calc_time(first_index,to)); */
   return hours_between(first_index,to);    
}




