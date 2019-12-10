/* Get data from file */


/* #include "structMeterdata.h"
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "global.h"


#define HOURS_PR_YEAR (365*24)
#define MAXLINEWIDTH 200
#define FILENAME_METER "MeterdataJakob.csv"
#define FILENAME_PRICE "elspot-prices_2017_hourly_dkk.csv"


/* prototyper */
int init_database_module(void);
data *get_price_for_timeinterval_in_area(dato from, dato to,  area area);
data *get_consumption_for_timeinterval_at_id(dato from, dato to, char *id);

void prompt_for_filname(char *filename);
char * import_meterdata_from_file(meterdata *meterdataArray, char *filename, char *strOUT);
char * import_pricedata_from_file(pricedata *pricedataArray, char *filename, char *strOUT);
void copy_contents_of_meterfile(FILE *f, meterdata *meterdataArray);
void copy_contents_of_pricefile(FILE *f, pricedata *pricedataArray);

meterdata create_meterdata_from_string(char *str);
pricedata create_pricedata_from_string(char *str, int priceIndex);

dato create_date_from_string (char *str);
void create_date_from_prizestring (char *date, char *hour, dato from, dato to);

meterdata mymeterdata[HOURS_PR_YEAR*3];
pricedata mypricedata[HOURS_PR_YEAR*3];



int init_database_module(void){
   
    char str[30];
    int index=0;

   import_meterdata_from_file(mymeterdata, FILENAME_METER, str);
   import_pricedata_from_file(mypricedata, FILENAME_PRICE, str);
   printf("hent pris for index: ");
    while (scanf("%d",&index)&& index != -1){
        if(index != -1){
            printf("her er prisen på index%d %f ",index, mypricedata[index].DK1price);
        }
    }

   return 0;
}



/* Public functions */

data *get_price_for_timeinterval_in_area(dato from, dato to,  area area){
   data dat[to.time.hour - from.time.hour];
   int count = to.time.hour - from.time.hour;
   int ret_index =0;
   int db_index = 0;
   
   for (ret_index=0 ; ret_index < count ; ret_index++) {
      db_index = from.day + ret_index;

      dat[ret_index].prize.from     = mypricedata[db_index].from;
      dat[ret_index].prize.to       = mypricedata[db_index].to;
      dat[ret_index].prize.DK1price = mypricedata[db_index].DK1price;
      dat[ret_index].prize.DK2price = mypricedata[db_index].DK2price;
   }

   return dat;
}

data *get_consumption_for_timeinterval_at_id(dato from, dato to, char *id){
   data dat[to.time.hour - from.time.hour];
   int count = to.time.hour - from.time.hour;
   int i =0;

   for(i=0;i<count;i++){
   dat[i].meter.from = mymeterdata[from.day+i].from;
   dat[i].meter.to = mymeterdata[from.day+i].to;
   dat[i].meter.value = mymeterdata[from.day+i].value;
}
   return dat;

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


char * import_pricedata_from_file(pricedata *pricedataArray, char *filename, char *strOUT){
   FILE *f = fopen(filename,"r");
   if(f!=NULL){
      sprintf(strOUT," %s", filename);
   }

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
       printf("%s",str);
      meterdataArray[measurementnr] = create_meterdata_from_string(str);
      measurementnr++;
   }
    
}

/*hent filindhold linie for linie og opret en kamp for hver linie
 * f: er en FILE pointer
 * kampliste: er det array som dataene kopieres over i*/
void copy_contents_of_pricefile(FILE *f, pricedata *pricedataArray){
   int pricenr=0;
   char str[MAXLINEWIDTH];
   
   while (fgets(str,MAXLINEWIDTH,f)!= NULL){
       printf("%s",str);
      pricedataArray[pricenr] = create_pricedata_from_string(str, pricenr);
      pricenr++;
   }
    
}

/* opret en meter måling med data fra string*/
/* Målepunkt id       ;Fra dato         ;Til dato         ;Mængde ;Måleenhed ;Kvalitet ;Type;
 * 571313104402686056 ;2017-01-01 00.00 ;2017-01-01 01.00 ;0,440  ;KWH       ;Målt     ;Tidsserier;
 *  */
meterdata create_meterdata_from_string(char *str){
    
   meterdata mdata;
//   char *id="test", unit[30], quality[30], type[30], dateStart[30], dateEnd[30] ;
    double value1=0.0 ,value2=0.0;
//   int converted=0;
    char *mydata_txt[8];
   
  
   const char s[2] = ";";
   char *token;
    int i = 0;
   token =strtok(str,s);
    
   while (token != NULL) {
      printf("%s\n",token);
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
    
   pricedata pdata;
    double value1=0.0 ,value2=0.0;
    char *mydata_txt[30];
    for(int i = 0 ; i<30 ;i++){
        mydata_txt[i] = " ";
    }
   
  
   const char s[2] = ";";
   char *token;
    int i = 0;
   token =strtok(str,s);
    
   while (token != NULL) {
      printf("%s\n",token);
      mydata_txt[i] = token;
      token=strtok(NULL, s);
      i++;
   }

   // create_date_from_prizestring(mydata_txt[0],  mydata_txt[1], pdata.from, pdata.to);
   pdata.from.year = pdata.from.month = pdata.from.day= priceIndex;
   pdata.to.year = pdata.to.month = pdata.to.day= priceIndex;

    if (sscanf(mydata_txt[7]," %lf,%lf " ,&value1,&value2)==2){
        pdata.DK1price = value1 + value2/100;
    }
    if (sscanf(mydata_txt[8]," %lf,%lf " ,&value1,&value2)==2){
        pdata.DK2price = value1 + value2/100;
    }
    
   return pdata;
    
}




/* create data from string */
dato create_date_from_string (char *str){
    dato mdate = {{00,00},0,0,0};
    if (sscanf(str,"%d-%d-%d %d.%d", &mdate.year, &mdate.month, &mdate.day, &mdate.time.hour, &mdate.time.minute)== 5){
   return mdate;
    }

    mdate.time.minute = 0;
    mdate.time.hour = 0;
    mdate.day    = 0;
    mdate.month  = 0;
    mdate.year   = 0;

    return mdate;
}

/* create data from pricestring */
void create_date_from_prizestring (char *date, char *hour, dato from, dato to){
    char *fromTo[2];
    const char s[2] = "-";
    char *token;
     int i = 0;
    if (sscanf(date,"%d-%d-%d ", &from.day, &from.month, &from.year)== 3){
              to.day=from.day;
              to.month = from.month;
              to.year = from.year;
             
    //       }
        }
    token =strtok(hour,s);

    while (token != NULL) {
        printf("%s\n",token);
        fromTo[i] = token;
        token=strtok(NULL, s);
        i++;
    }

    sscanf(fromTo[0], " %d", &from.time.hour);
    to.time.hour = from.time.hour +1;
    to.time.minute = from.time.minute = 0;
    
    


}
