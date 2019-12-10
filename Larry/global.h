#ifndef GLOBAL_H
#define GLOBAL_H

/*Universelle imports*/
#include <stdio.h>
#include <stdlib.h>

/*Symbolske konstanter*/
#define FALSE       0
#define TRUE        1
#define SUCCESS     2
#define HOURS_PR_YEAR (365*24)

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
    typedef enum {ErrorTest,UserHistory,InfoEnergySaving,UpdateSettings,
              SystemInformation,WarningEnergySaving,MachineActivation,
              ConsumptionCheck,FutureData}choice_function;
    /*settings valg: settings*/
    typedef struct{int id;char residence[5];char language[5];}settings;
    /*aktive valg: choice*/
    typedef struct{int function;}choice;
/*user structet*/
typedef struct{
    settings settings;
    choice choice;
    user_type type;
}user;

/*De forskellige fejltyper. Bruges med error_message*/
typedef enum{ErrorConfirmationPassiveModule,ErrorChoiceDoesntExist,
             ErrorInfoStrNotFound,ErrorUserType}error_types;
/*debugging Prototypes*/
int debug_print(user user_choice, data user_data,int run_or_not);
char* translate(int choice_of_function);
int error_message(int error);

#endif //GLOBAL_H

