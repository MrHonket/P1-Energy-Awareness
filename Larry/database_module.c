/* Jakob */

/* Get data from file */



/* #include "structMeterdata.h"
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "global.h"


#define MAXLINEWIDTH 200
// #define FILENAME_METER "MeterdataJakob.csv"
#define FILENAME_PRICE "elspot-prices_2017_hourly_dkk.csv"


/* prototyper */
void init_database(void);
data *get_price_for_timeinterval_in_area(dato from, dato to,  area area);
data *get_consumption_for_timeinterval_at_id(dato from, dato to, char *id);


void init_pricestruct(pricedata *data);
void init_meterstruct(meterdata *data);
void init_datastruct(data *data);


void prompt_for_filname(char *filename);
char * import_meterdata_from_file(meterdata *meterdataArray, char *filename, char *strOUT);
char * import_pricedata_from_file(pricedata pricedataArray[], char *filename, char *strOUT);
void copy_contents_of_meterfile(FILE *f, meterdata *meterdataArray);
void copy_contents_of_pricefile(FILE *f, pricedata prices[]);

meterdata create_meterdata_from_string(char *str);
pricedata create_pricedata_from_string(char *str, int priceIndex);
 pricedata create_pricedata_from_hardstring(char *str);


dato create_date_from_string (char *str);
void create_date_from_prizestring (char *date, char *hour, dato from, dato to);


meterdata mymeterdata[HOURS_PR_YEAR];
pricedata mypricedata[HOURS_PR_YEAR];


/* UDKOMMENTERET FOR AT KUNNE BRUGES I ANDRE PROGRAMMER!!!!
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

   

    
    

  

   
   // init_database();
   // init_database();
   init_pricestruct(mypricedata);

   

   printf("hent pris for index: ");
   while (scanf("%d",&index)&& index != -1){
         if(index != -1){
            printf("her er prisen på index%d %f ",index, mypricedata[index].DK1price);
         }
   }
   
   testdata = get_price_for_timeinterval_in_area(date1, date2, Dk1) ;

   for(index = 0;index<24;index++){
      printf("\n%lf %d %d\n", testdata[index].meter.value,testdata[index].meter.from.time.hour,testdata[index].meter.to.time.hour );
   }

  
   // import_meterdata_from_file(mymeterdata, FILENAME_METER, str);
   // import_pricedata_from_file(mypricedata, FILENAME_PRICE, );

   //   temp = testdata[10];
     

   return 0;
}
*/




/* inits */
void init_database(void){
   char str[30];
    int i = 0;

    
   init_pricestruct(mypricedata);
      //   init_meterstruct(mymeterdata);
        
   import_pricedata_from_file(mypricedata, FILENAME_PRICE, str);
   // import_meterdata_from_file(mymeterdata, FILENAME_METER, str);

}

void init_pricestruct(pricedata data[]){
   int i =0;
   for(i=0;i<HOURS_PR_YEAR;i++){
    data[i].DK1price=2999;
    data[i].DK2price=3999;
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

void init_meterstruct(meterdata *data){
   data->value = 0;
   data->from.year=0;
   data->from.month=0;
   data->from.day=0;
   data->from.time.hour=0;
   data->from.time.minute=0;
   data->to.year=0;
   data->to.month=0;
   data->to.day=0;
   data->to.time.hour=0;
   data->to.time.minute=0;
    
}

void init_datastruct(data *data){
    init_pricestruct(&data->prize);
    init_meterstruct(&data->meter);
}






/* Public functions */

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
      tempdata[i].prize.from.year=year;
      tempdata[i].prize.from.month = month;
      tempdata[i].prize.from.day = day;
      tempdata[i].prize.from.time.hour =hour1+i;
      tempdata[i].prize.from.time.minute =00;
      tempdata[i].prize.to.year=year;
      tempdata[i].prize.to.month = month;
      tempdata[i].prize.to.day = day;
      tempdata[i].prize.to.time.hour =hour2+i;
      tempdata[i].prize.to.time.minute =00;

      tempdata[i].prize.DK1price=rand()%150;
      tempdata[i].prize.DK2price=rand()%150;

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

      tempdata[i].meter.value= rand()%500;
      
      // tempdata[i].prize.from     = mypricedata[db_index].from;
      // tempdata[i].prize.to       = mypricedata[db_index].to;
      // tempdata[i].prize.DK1price = mypricedata[db_index].DK1price;
      // tempdata[i].prize.DK2price = mypricedata[db_index].DK2price;
      db_index++;
   }

   return tempdata;
}

data *get_consumption_for_timeinterval_at_id(dato from, dato to, char *id){
   int interval = abs(to.time.hour - from.time.hour);
   data *tempdata;
   int i =0;
   int db_index = from.day;
   tempdata = malloc(interval*sizeof(data));

   for(i=0;i<interval;i++){
       int db_index = from.day + i;

       tempdata[i].meter.from = mymeterdata[db_index].from;
       tempdata[i].meter.to = mymeterdata[db_index].to;
       tempdata[i].meter.value = mymeterdata[db_index].value;
   }
   return tempdata;

}


 pricedata create_pricedata_from_hardstring(char *str){
   int year,month,day,hour1,hour2;
   double dk1,dk2;
   pricedata temp;

   // str = "2017 01 01 00 00 130.30 155.33";
   sscanf(str,"%4d %2d %2d %2d %2d %lf %lf",&year,&month,&day,&hour1,&hour2,&dk1,&dk2);
   temp.from.year=year;
   temp.from.month = month;
   temp.from.day = day;
   temp.from.time.hour =hour1;
   temp.from.time.minute =00;
   temp.to.year=year;
   temp.to.month = month;
   temp.to.day = day;
   temp.to.time.hour =hour2;
   temp.to.time.minute =00;

   temp.DK1price=dk1;
   temp.DK2price=dk2;

   return temp;


}









/* get meter data from csv file
 * meterdataarray: her læses dataene ud som strings
 * filename: filnavn på datafil som skal indlæses
 * strOUT: navn på den fil der blev indlæst, den kan være ændret hvis brugeren giver en ny sti */
char * import_meterdata_from_file(meterdata *meterdataArray, char *filename, char *strOUT){
    
   FILE *f = fopen(filename,"r");
   if(f!=NULL){
      sprintf(strOUT," %s", filename);
   }

   if(f==NULL){
      char newfile[MAXLINEWIDTH];
      printf("filnavnet findes ikke!\nindtast sti til meterdata: ");
      prompt_for_filname(newfile);
      import_meterdata_from_file(meterdataArray, newfile, strOUT);
   }

   else {
   
   copy_contents_of_meterfile(f, meterdataArray);
   fclose(f);
   }
   printf("%s\n",filename);
   
   return strOUT;
}


char * import_pricedata_from_file(pricedata pricedataArray[], char *filename, char *strOUT){
   printf("%s",filename);
   FILE *f = fopen(filename,"r");
   // if(f!=NULL){
      
   //    sprintf(strOUT," %s", filename);
   // }

   if(f==NULL){
      char newfile[MAXLINEWIDTH];
      printf("filnavnet findes ikke!\nnindtast sti til prisdata: ");
      prompt_for_filname(newfile);
      import_pricedata_from_file(pricedataArray, newfile, strOUT);
   }

   else {
   
   copy_contents_of_pricefile(f, pricedataArray);
   fclose(f);
   }
   printf("%s\n",filename);
   
   return strOUT;

}



/* bed om filnavn, bruges hvis FILNAVN ikke findes i samme folder som a.out  */
void prompt_for_filname(char *filename){
   printf("skriv filnavn:");
   scanf(" %s",filename);
}


/*hent filindhold linie for linie og opret en kamp for hver linie
 * f: er en FILE pointer
 * kampliste: er det array som dataene kopieres over i*/
void copy_contents_of_meterfile(FILE *f, meterdata *meterdataArray){
   int measurementnr=0;
   char str[MAXLINEWIDTH];
   
   while (fgets(str,MAXLINEWIDTH,f)!= NULL){
   //       printf("%s",str);
      meterdataArray[measurementnr] = create_meterdata_from_string(str);
      measurementnr++;
   }
    
}

/*hent filindhold linie for linie og opret en kamp for hver linie
 * f: er en FILE pointer
 * kampliste: er det array som dataene kopieres over i*/
void copy_contents_of_pricefile(FILE *f, pricedata prices[]){
   int pricenr=0;
   char str[MAXLINEWIDTH];
   
   while (fgets(str,MAXLINEWIDTH,f)!= NULL){
   //       printf("%s",str);
      prices[pricenr] = create_pricedata_from_string(str, pricenr);
      pricenr++;
   }
    
}

/* opret en meter måling med data fra string*/
/* Målepunkt id       ;Fra dato         ;Til dato         ;Mængde ;Måleenhed ;Kvalitet ;Type;
 * 571313104402686056 ;2017-01-01 00.00 ;2017-01-01 01.00 ;0,440  ;KWH       ;Målt     ;Tidsserier;
 *  */
meterdata create_meterdata_from_string(char *str){
    
   meterdata mdata;
    init_meterstruct(&mdata);
    
   //   char *id="test", unit[30], quality[30], type[30], dateStart[30], dateEnd[30] ;
    double value1=0.0 ,value2=0.0;
   //   int converted=0;
    char *mydata_txt[8];
   
  
   const char s[2] = ";";
   char *token;
    int i = 0;
   token =strtok(str,s);
    
   while (token != NULL) {
   //      printf("%s\n",token);
      mydata_txt[i] = token;
      token=strtok(NULL, s);
      i++;
   }

   strcpy(mdata.id , mydata_txt[0]);
   mdata.from = create_date_from_string(mydata_txt[1]);
   mdata.to = create_date_from_string(mydata_txt[2]);
    if (sscanf(mydata_txt[3],"%lf,%lf",&value1,&value2)){
        mdata.value = value1 + value2/1000;
    }
  strcpy(mdata.unit ,      mydata_txt[4]);
  strcpy(mdata.quality ,   mydata_txt[5]);
  strcpy(mdata.type ,      mydata_txt[6]);
   
   return mdata;
    
}


/* opret en pris med data fra string*/
/* Elspot Prices in DKK/MWh;;;;;;;;;;;;;;;;;;
Data was last updated 31-12-2018;;;;;;;;;;;;;;;;;;
;Hours;SYS;SE1;SE2;SE3;SE4;FI;DK1;DK2;Oslo;Kr.sand;Bergen;Molde;Tr.heim;Tromsø;EE;LV;LT
01-01-2017;00 - 01;191,05;178,64;178,64;178,64;178,64;178,64;155,82;155,82;211,13;211,13;211,13;178,64;178,64;178,64;178,64;178,64;178,64
 *  */
pricedata create_pricedata_from_string(char *str, int priceIndex){
    
   pricedata *pdata;
   init_pricestruct(pdata);

   double value1=0.0 ,value2=0.0;
   char *mydata_txt[30];
   const char s[2] = ";";
   char *token;
   int i = 0;


   for( i = 0 ; i<30 ;i++){
      mydata_txt[i] = " ";
   }
   
   sscanf(str,"%2d-%2d-%4d;%2d - %2d",&pdata->from.day, &pdata->from.month, &pdata->from.year, &pdata->from.time.hour, &pdata->to.time.hour);

   // create_date_from_prizestring(mydata_txt[0],  mydata_txt[1], pdata.from, pdata.to);
   // pdata.from.year = pdata.from.month = pdata.from.day= priceIndex;
   pdata->to.year  = pdata->from.year ;
   pdata->to.month = pdata->from.month;
   pdata->to.day   = pdata->from.day;

      token =strtok(str,s);
      
      while (token != NULL) {
         printf("%s\n",token);
         // mydata_txt[i] = token;
         token=strtok(NULL, s);
         i++;
      }

    pdata->to.time.hour = pdata->from.time.hour+1;
    
    if (sscanf(mydata_txt[7]," %lf,%lf " ,&value1,&value2)==2){
        pdata->DK1price = value1 + value2/100;
    }
    
    
    if (sscanf(mydata_txt[8]," %lf,%lf " ,&value1,&value2)==2){
        pdata->DK2price = value1 + value2/100;
    }
    else{
        printf("kunne ikke læse dk1pris for :\n %s\n",str);
        
    }

    
   return *pdata;
    
}




/* create data from string */
dato create_date_from_string (char *str){
    dato mdate = {{00,00},0,0,0};
    if (sscanf(str,"%4d-%2d-%2d %2d.%2d", &mdate.year, &mdate.month, &mdate.day, &mdate.time.hour, &mdate.time.minute)== 5){
   return mdate;
    }

    mdate.time.minute = 0;
    mdate.time.hour = 0;
    mdate.day    = 0;
    mdate.month  = 0;
    mdate.year   = 0;

    return mdate;
}

dato date_from_string(char *date, int time){
    dato ret_date;
    sscanf(date,"%2d-%2d-%4d",&ret_date.year, &ret_date.month, &ret_date.day);
    ret_date.time.hour = time;
    ret_date.time.minute =0;
    return ret_date;
}

/* create data from pricestring */
//void create_date_from_prizestring (char *date, char *hour, dato from, dato to){
//    char *fromTo[2];
//    const char s[2] = "-";
//    char *token;
//     int i = 0;
//    if (sscanf(date,"%d-%d-%d ", &from.day, &from.month, &from.year)== 3){
//              to.day=from.day;
//              to.month = from.month;
//              to.year = from.year;
//
//    //       }
//        }
//    token =strtok(hour,s);
//
//    while (token != NULL) {
//        printf("%s\n",token);
//        fromTo[i] = token;
//        token=strtok(NULL, s);
//        i++;
//    }
//
//    sscanf(fromTo[0], " %d", &from.time.hour);
//    to.time.hour = from.time.hour +1;
//    to.time.minute = from.time.minute = 0;
//
//
//
//
//}


