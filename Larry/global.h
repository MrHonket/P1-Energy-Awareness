#ifndef GLOBAL_H
#define GLOBAL_H

/*Universelle imports*/
#include <stdio.h>
#include <stdlib.h>

/*Symbolske konstanter*/
#define FALSE         0
#define TRUE          1
#define SUCCESS       2
#define HOURS_PR_YEAR 8765*20
#define KWH_TO_MWH    0.001
#define FILENAME_METER "Meterdata.csv"
#define FILENAME_PRICE "elspot-prices_2017_hourly_dkk.csv"


/*FEJLSØGNING*/
/*For inklusion af fejlsøgning i program, lav en ny Error... i error_types.
 *Kald derefter error_message(Error...) på stedet i koden.*/
typedef enum{ErrorConfirmationPassiveModule,ErrorChoiceDoesntExist,
             ErrorInfoStrNotFound,ErrorUserType,ErrorNotImplemented,
             ErrorUserLookupHistory,ErrorUserMeanMedianHistory,
             ErrorPassiveModuleFuncChoice,ErrorInWarningConsumption}error_types;
int error_message(int error);

/*VARIABLE TIL data*/
    /* tids enums og structs: ugedag, month, time, dato, ugedag_txt[],month_txt[].*/
    typedef enum {Man,Tir,Ons,Tor,Fre,Lor,Son} ugedag;
    typedef enum{Januar=1,Februar,Marts,April,
        Maj,Juni,Juli,August,September,
        Oktober,November,December}month;
    typedef struct {int hour;int minute;}time;
    typedef struct{time time;int day;month month;int year;}dato;
    /*område struct: area */
    typedef enum {Dk1,Dk2}area;
    /*prisdata struct: pricedata*/
    typedef struct{dato from;dato to;double DK1price;double DK2price;}pricedata;
    /*forbrugsdata struct: meterdata*/
    typedef struct {char id[30];dato from;dato to;double value;
                    char unit[30];char quality[30];char type[30];}meterdata;
    /*productionsdata struct: production*/
    typedef struct{dato from;dato to;area area;double gros;double net;double localPowerprod;
                double offshoreWind;double onshoreWind;double centralProd;double electricBoilerCon;
                double solarProd;}production;
/* data structet */
typedef struct{
   meterdata meter;
   pricedata prize;
}data;

/*Tid omdannet til tekst prototypes: ugedag_txt[], month_txt[]*/
const char *ugedag_txt;
const char *month_txt;

/*VARIABLE TIL user*/
    /*symbolske konstanter for brugertypen og valg af funktion*/
    typedef enum {Human,Automated}user_type;
    typedef enum {Presentation,Exit,UserHistory,InfoEnergySaving,UpdateSettings,
              SystemInformation,ConsumptionCheck,FutureData,WarningEnergySaving,
              MachineActivation}choice_function;
    typedef enum {Mean = 1,Median}mean_or_median;
    typedef enum {Meter,Price,Green}lookup_type;
    /*settings valg: settings*/
    typedef struct{int id;char residence[5];char language[5];dato next_activation;}settings;
    /*aktive valg: choice*/
    typedef struct{int function; mean_or_median mean_or_median;
                   dato from;dato to;lookup_type lookup;}choice;
    
/*user structet*/
typedef struct{
    settings settings;
    choice choice;
    user_type type;
}user;

/*Enums for passive module*/
typedef enum{Failure,Success}passive_warnings;

/*Calc time prototypes*/
int calc_time(dato from, dato to);
int calc_hours(dato test_year, month test);
int hours_between (dato d1, dato d2);
int days_between(dato from, dato to);
int months_between(dato d1, dato d2);
int days_in_month(dato d);
dato next_hour(dato d);
dato next_day(dato d);
int leapYear(int);
void prnt_date(dato);

#endif //GLOBAL_H