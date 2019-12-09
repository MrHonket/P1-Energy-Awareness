/* Get data from file */


/* #include "structMeterdata.h"
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXLINEWIDTH 200
#define FILENAME "meterdata.csv"


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
   januar,
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
}klokkeslet;

typedef struct{
   int  y;
   maaned m;
   int    d;
   klokkeslet t;
}dato;

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
   int   maaler_id;
   dato  fra;
   dato  til;
   float maengde;
   char  *enhed; 
   char  *kvalitet;
   char  *type;
}meterdata;

/* prototyper */
void prompt_for_filname(char *filename){

char * get_meterdata_from_file(meterdata *meterdataArray, char *filename, char *strOUT);
void copy_contents_of_file(FILE *f, meterdata *meterdataArray);
meterdata create_meterdata_from_string(char *str);

dato create_date_from_string (char *str){




/* get meter data from csv file
 * meterdataarray: her læses dataene ud som strings
 * filename: filnavn på datafil som skal indlæses
 * strOUT: navn på den fil der blev indlæst, den kan være ændret hvis brugeren giver en ny sti */
char * get_meterdata_from_file(meterdata *meterdataArray, char *filename, char *strOUT){
    
   FILE *f = fopen(filename,"r");
   if(f!=NULL){
      sprintf(strOUT," %s", filename);
   }

   if(f==NULL){
      char newfile[MAXLINEWIDTH];
      printf("filnavnet findes ikke!\n");
      prompt_for_filename(newfile);
      get_meterdata_from_file(meterdataArray, newfile, strOUT);
   }

   else {
   
   copy_contents_of_file(f, meterdataArray);
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
void copy_contents_of_file(FILE *f, meterdata *meterdataArray){
   int measurementnr=0;
   char str[MAXLINEWIDTH];
   
   while (fgets(str,MAXLINEWIDTH,f)!= NULL){
      
      meterdataArray[measurementnr] = create_meterdata_from_string(str);
      measurementnr++;
   }
    
}

/* opret en meter måling med data fra string*/
/* Målepunkt id       ;Fra dato         ;Til dato         ;Mængde ;Måleenhed ;Kvalitet ;Type;
 * 571313104402686056 ;2017-01-01 00.00 ;2017-01-01 01.00 ;0,440  ;KWH       ;Målt     ;Tidsserier;
 *  */
meterdata create_meterdata_from_string(char *str){
    
   meterdata mdata;
   char id[30], unit[30], quality[30], type[30], dateStart[30], dateEnd[30] ;
   float value=0.0;
   int converted=0;
   
   converted = sscanf(str, "%s ; %s ; %s ; %lf ; %s ; %s ; %s",id, dateStart, dateEnd, &value, unit, quality, type);
   if(converted == 7 ){
   strcpy(mdata.maaler_id , id);
   mdata.fra = create_date_from_string(dateStart);
   mdata.til = create_date_from_string(dateStart);
   mdata.maengde = value;
   strcpy(mdata.enhed , id);
   strcpy(mdata.kvalitet , id);
   strcpy(mdata.type , id);
   }
   
   return mdata;
    
}


/* create data from string */
dato create_date_from_string (char *str){
   dato mdate;
   sscanf(str,"%d%d%d%d%d", mdate.y, mdate.m, mdate.d, mdate.t.h, mdate.t.m);
   return mdate;
}
