#ifndef GLOBAL_H
#define GLOBAL_H

/*Universelle imports*/
#include <stdio.h>
#include <stdlib.h>

/*Symbolske konstanter*/
/*Overordnede*/
#define FALSE       0
#define TRUE        1
/*Disse herunder kan evt. laves om til enums*/
/*Choices.usertype kan indeholde en af disse værdier*/
#define HUMAN       0
#define AUTOMATED   1
/*Choices.choice kan indeholde en af disse værdier*/
#define ERROR_TEST            0
#define USER_HISTORY          1
#define INFO_ENERGY_SAVING    2
#define UPDATE_SETTINGS       3
#define SYSTEM_INFORMATION    4
#define WARNING_ENERGY_SAVING 5
#define MACHINE_ACTIVATION    6
#define CONSUMPTION_CHECK     7
#define FUTURE_DATA           8
/*Konstanter der beskriver en fejlmeddelse i error_message*/
#define ERROR_CONFIRMATION_PASSIVE_MODULE 10
#define ERROR_CHOICE_DOESNT_EXIST         11
#define ERROR_INFO_STR_NOT_FOUND          12
#define ERROR_USER_TYPE                   13

/*VARIABLE TIL data*/
    /* tids enums og structs: ugedag, month, time, dato, ugedag_txt[],month_txt[]. */
    typedef enum {Man,Tir,Ons,Tor,Fre,Lor,Son} ugedag;
    typedef enum{januar=1,februar,marts,april,
        maj,juni,juli,august,september,
        oktober,november,december}month;
    typedef struct {int hour;int minute;}time;
    typedef struct{time time;int day;month month;int year;}dato;
    /*område struct: area */
    typedef enum {dk1,dk2}area;
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
    /*IMPLEMENTERES HVIS VI ØNSKER DET!!!*/
    /*settings valg: settings*/
    typedef struct{
        //Hvis user skal udvides med en choice og en settings struct for at abstrahere mere.
    }settings;
    /*aktive valg: choice*/
    typedef struct{
        //Hvis user skal udvides med en choice og en settings struct for at abstrahere mere.
    }choice;
/*user structet*/
typedef struct{
    int id;
    char residence[5];
    char language[5];
    int choice_of_function;
    int user_type;
}user;

/*debugging Prototypes*/
int debug_print(user user_choice, data user_data,int run_or_not);
char* translate(int choice_of_function);
int error_message(int error);

#endif //GLOBAL_H