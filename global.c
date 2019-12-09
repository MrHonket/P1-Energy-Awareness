
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
   int  fra;
   int  til;
   float maengde;
   char  *enhed; 
   char  *kvalitet;
   char  *type;
}meterdata;


const char* tekst{
   "overskrift",
   "KWh"



};