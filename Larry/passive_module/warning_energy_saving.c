#include <stdio.h>
#include <stdlib.h>
/* TID */
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

typedef struct{
    dato from;
    dato to;
    double price_area1;
    double price_area2;
}prices;
int main(void){
printf("hello and welcome to the gokkeslæt\n");
prices data= {2018,januar,15,{20,0},{2018,januar,15,{21,0},},219.3,222.4};

printf("gokkeslæt: %d\n",data.from.t.h);
    return EXIT_SUCCESS;
}