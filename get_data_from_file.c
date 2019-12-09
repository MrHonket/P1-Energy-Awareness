/* Get data from file */


/* #include "structMeterdata.h"
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"


#define HOURS_PR_YEAR (365*24)
#define MAXLINEWIDTH 200
#define FILENAME_METER "MeterdataJakob.csv"
#define FILENAME_PRICE "hotspotdk.csv"



/* TID */
typedef enum {
   Man,
   Tir,
   Ons,
   Tor,
   Fre,
   Lor,
   Son
} ugedag;

typedef enum{
   januar=1,
   februar,
   marts,
   april,
   maj,
   juni,
   juli,
   august,
   september,
   oktober,
   november,
   december
}maaned;

typedef struct {
   int h;
   int m;
}time;

typedef struct{
   time   time;
   int    day;
   maaned month;
   int    year;
}dato;


/* Area */
typedef enum {
   dk1,
   dk2
}area;

const char *ugedag_txt[] = {
   "Mandag",
   "Tirsdag",
   "Onsdag",
   "Torsdag",
   "Fredag",
   "Lordag",
   "Sondag"
};

const char *maaned_txt[] = {
    "none",
   "januar",
   "februar",
   "marts",
   "april",
   "maj",
   "juni",
   "juli",
   "august",
   "september",
   "oktober",
   "november",
   "december"
};


/* METERDATA */
typedef struct {
   char  id[30];
   dato  from;
   dato  to;
   double value;
   char  unit[30];
   char  quality[30];
   char  type[30];
}meterdata;

/* PRICEDATA */


typedef struct{
   dato from;
   dato to;
   double DK1price;
   double DK2price;
}pricedata;


/* DATA */
typedef struct{
   meterdata meter;
   pricedata prize;
}data;

/* prototyper */
data get_price_for_timeinterval(dato from, dato to);
data get_consumption_for_timeinterval(dato from, dato to);
void prompt_for_filname(char *filename);
char * import_meterdata_from_file(meterdata *meterdataArray, char *filename, char *strOUT);
char * import_pricedata_from_file(pricedata *pricedataArray, char *filename, char *strOUT);
void copy_contents_of_meterfile(FILE *f, meterdata *meterdataArray);
void copy_contents_of_pricefile(FILE *f, pricedata *pricedataArray);

meterdata create_meterdata_from_string(char *str);
meterdata create_pricedata_from_string(char *str);

dato create_date_from_string (char *str);
void create_dates_from_prizestring (char *date, char *hour, dato from, dato to);





int main(void)
{
   meterdata mymeterdata[HOURS_PR_YEAR*3];
   pricedata mypricedata[HOURS_PR_YEAR];
    char str[30];

   import_meterdata_from_file(mymeterdata, FILENAME_METER, str);
   import_pricedata_from_file(mypricedata,FILENAME_PRICE, str);

   return 0;
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
      printf("filnavnet findes ikke!\n");
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
      printf("filnavnet findes ikke!\n");
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
      pricedataArray[pricenr] = create_meterdata_from_string(str);
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
meterdata create_pricedata_from_string(char *str){
    
   pricedata pdata;
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

   pdata.from = create_date_from_pricestring(mydata_txt[0]);
   pdata.to = create_date_from_pricestring(mydata_txt[0])


   pdata.from = create_date_from_string(mydata_txt[1]);
   pdata.to = create_date_from_string(mydata_txt[2]);
    if (sscanf(mydata_txt[3],"%lf,%lf",&value1,&value2)){
        pdata.value = value1 + value2/1000;
    }
  strcpy(pdata.unit ,      mydata_txt[4]);
  strcpy(pdata.quality ,   mydata_txt[5]);
  strcpy(pdata.type ,      mydata_txt[6]);
   
   return pdata;
    
}




/* create data from string */
dato create_date_from_string (char *str){
    dato mdate = {{00,00},0,0,0};
    if (sscanf(str,"%d-%d-%d %d.%d", &mdate.year, &mdate.month, &mdate.day, &mdate.time.h, &mdate.time.m)== 5){
   return mdate;
    }

    mdate.time.m = 0;
    mdate.time.h = 0;
    mdate.day    = 0;
    mdate.month  = 0;
    mdate.year   = 0;

    return mdate;
}

/* create data from string */
void create_date_from_prizestring (char *date, char *hour, dato from, dato to){
    dato mdate = {{00,00},0,0,0};
    if (sscanf(date,"%d-%d-%d", &from.day, &from.month, &from.year)== 3){
       if (sscanf(hour,"%d - %d", &from.time.h, &to.time.m)== 2){
          to.time.m = from.time.m = 0;
          to.day=from.day; 
          to.month = from.month; 
          to.year = from.year;
         
       }
    }


}
