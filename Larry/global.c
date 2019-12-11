/*Universelle imports*/
#include <stdio.h>
#include <stdlib.h>

/*Symbolske konstanter*/
#define FALSE       0
#define TRUE        1
#define SUCCESS     2
#define HOURS_PR_YEAR 8765

/*ERROR MESSAGES*/
typedef enum{
    ErrorConfirmationPassiveModule,
    ErrorChoiceDoesntExist,
    ErrorInfoStrNotFound,
    ErrorUserType,
    ErrorNotImplemented
}error_types;

int error_message(int error){
    if(error == ErrorConfirmationPassiveModule){
        printf("Error at confirmation from the Passive Module\n");
    }
    else if(error == ErrorChoiceDoesntExist){
        printf("Error because the given function choice doesnt exist\n");
    }
    else if(error == ErrorInfoStrNotFound){
        printf("Error because info_str wasn't correctly given from function\n");
    }
    else if(error == ErrorUserType){
        printf("Error because the given user type was neither Human nor Automated\n");
    }
    else if(error == ErrorNotImplemented){
        printf("Error because a function in choice_function hasn't been implemented yet\n");
        printf("Please lookup this error_message in one of the .c files.\n");
    }
    else{
        printf("Error because the error_message nr. %d in error_types hasn't been implemented yet\n",error);
    }

    return 0;
}

/*DATA VARIABLE*/

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
   Januar=1,
   Februar,
   Marts,
   April,
   Maj,
   Juni,
   Juli,
   August,
   September,
   Oktober,
   November,
   December
}month;

typedef struct {
   int hour;
   int minute;
}time; /*Behøves vel ikke at gemme minuttal...*/

typedef struct{
   time   time;
   int    day;
   month month;
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

const char *month_txt[] = {
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
/* Målepunkt id   ;Fra dato        ;Til dato        ;Mængde;Måleenhed;Kvalitet;Type;
571313104402686056;2017-01-01 00.00;2017-01-01 01.00;0,440 ;KWH      ;Målt    ;Tidsserier; */

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
/* Elspot Prices in DKK/MWh;;;;;;;;;;;;;;;;;;
 *Data was last updated 31-12-2018;;;;;;;;;;;;;;;;;;
 *        ;Hours  ; SYS   ; SE1   ;SE2   ;SE3   ;SE4   ;FI    ;DK1   ;DK2   ;Oslo  ;Kr.sand;Bergen;Molde ;Tr.heim;Tromsø;EE    ;LV    ;LT
01-01-2017;00 - 01; 191,05; 178,64;178,64;178,64;178,64;178,64;155,82;155,82;211,13;211,13 ;211,13;178,64;178,64 ;178,64;178,64;178,64;178,64 */

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

/* ENERGY PORDUCTION DATA */
/* HourUTC;HourDK;PriceArea;GrossCon;NetCon;LocalPowerProd;OffshoreWindPower;OnshoreWindPower;CentralProd;ElectricBoilerCon;SolarPowerProd;ExchangeContinent;ExchangeGreatBelt;ExchangeNordicCountries
 * 2019-11-28 22:00;2019-11-28 23:00;DK2;1419.942879;;199.253645;386.969134968152;385.377565031848;334.512434;42.47308;0.0;532.125;-55.0;-363.2949
 gros          : Sum of the consumption incl. transmission loss
 net           : Sum of the consumption excl. transmission loss
 localPowerprod: Sum of production from local Combined Heat and Power units (CHP)
 offshoreWind  : Electricity production from offshore wind power
 onshoreWind   : Electricity production from onshore wind power
 centralProd   : Sum of production from central power Plants, Central power Plants are eg Skærbækværket, Studstrupværket and Herningværket
 electricBoilerCon   : Consumption of electric boilers in the district heating systems
 solarProd     :Production is to some extent estimated
 
 extra
- Exchange of electricity towards continental EuropeA positive exchange is import of electricity, while a negative is export.
Both DK1 and DK2 are only connected to Germany until 2019, where DK1 also will be connected the the Netherlands through the COBRA connection.

-Exchange of electricity over the Great Belt connection between DK1 and DK2
-Exchange of electricity towards Norway and Sweden.  A positive exchange is import of electricity, while a negative is export.
DK1 are connected to both Norway and Sweden, DK2 only to Sweden
 */

typedef struct{
   dato from;
   dato to;
   area area;
   double gros; 
   double net;  
   double localPowerprod;
   double offshoreWind;
   double onshoreWind;   
   double centralProd;
   double electricBoilerCon;
   double solarProd;

}production;

typedef enum {
    Human,
    Automated
}user_type;

typedef enum {
    ErrorTest,
    UserHistory,
    InfoEnergySaving,
    UpdateSettings,
    SystemInformation,
    WarningEnergySaving,
    MachineActivation,
    ConsumptionCheck,
    FutureData
}choice_function;

typedef enum {
    Mean = 1,
    Median
}mean_or_median;

typedef enum {
    Meter,
    Price,
    Green
} lookup_type;

/*settings valg: settings*/
typedef struct{
    int id;
    char residence[5];
    char language[5];
}settings;


/*aktive valg: choice*/
typedef struct{
    int function;
    mean_or_median mean_or_median;
    dato from;
    dato to;
    lookup_type lookup;
}choice;

/*user-structet*/
typedef struct{
    settings settings;
    choice choice;
    user_type type;
}user;