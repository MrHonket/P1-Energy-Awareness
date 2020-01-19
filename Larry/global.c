/*Universelle imports*/
#include <stdio.h>
#include <stdlib.h>

/*Symbolske konstanter*/
#define FALSE         0
#define TRUE          1
#define SUCCESS       2
#define NMB_OF_ELEMENTS 24
#define HOURS_PR_YEAR (365*24)
#define KWH_TO_MWH    0.001
#define FILENAME_METER "Meterdata.csv"
#define FILENAME_PRICE "elspot-prices_2017_hourly_dkk.csv"

/*ERROR MESSAGES*/
typedef enum{
    ErrorConfirmationPassiveModule,
    ErrorChoiceDoesntExist,
    ErrorInfoStrNotFound,
    ErrorUserType,
    ErrorNotImplemented,
    ErrorUserLookupHistory,
    ErrorUserMeanMedianHistory,
    ErrorPassiveModuleFuncChoice,
    ErrorInWarningConsumption,
    ErrorLogDataNotImplemented,
    ErrorLanguageNotImplemented,
    ErrorSettingsNotCorrect,
    ErrorResidenceNotImplemented
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
        printf("Please lookup this error_message in the chosen file.\n");
    }
    else if(error == ErrorUserLookupHistory){
        printf("Error because the chosen lookup choice in user_history.c isn't implemented yet\n");
    }
    else if(error == ErrorUserMeanMedianHistory){
        printf("Error because the chosen mean_or_median choice in user_history.c is wrongly implemented\n");
    }
    else if(error == ErrorPassiveModuleFuncChoice){
        printf("Error because the automatically chosen function isnt one compatible with the passive module.\n");
    }
    else if(error == ErrorInWarningConsumption){
        printf("Error in warning_consumption function because of consumption and median_consumption isn't comparable.\n");
    }
    else if(error == ErrorLogDataNotImplemented){
        printf("Error because the log_data hasn't been implemented yet");
    }
    else if(error == ErrorLanguageNotImplemented){
        printf("Error, the chosen language is not implemented. Please update your settings.\n");
    }
    else if(error == ErrorSettingsNotCorrect){
        printf("Error, some values wasn't inputted correctly, please try again\n");
        printf("Please remember to use capital letters, the - seperator and whole numbers.\n");
    }
    else if(error == ErrorResidenceNotImplemented){
        printf("Error because the given residence from User.settings hasn't been implemented or doesn't exist\n");
        printf("This error occured in the info_energy_saving module in the info_energy_saving function.\n");
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
    Presentation,
    Exit,
    UserHistory,
    InfoEnergySaving,
    UpdateSettings,
    SavingAdvice,
    ConsumptionCheck,
    WarningEnergySaving,
    MachineActivation
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
    dato next_activation;//er ikke i settings endnu
}settings;


/*aktive valg: choice*/
typedef struct{
    choice_function function;
    int hour;
    int warning;
    mean_or_median mean_or_median;
    dato from;
    dato to;
    dato now;
    lookup_type lookup;
}choice;

/*user-structet*/
typedef struct{
    settings settings;
    choice choice;
    user_type type;
}user;

/*Enums for passive module*/
typedef enum{Failure, Success}passive_warnings;

/*Calc time funktionen!*/
/*Prototypes*/
// int calc_time(dato from, dato to);
// int calc_hours(dato test_year, month test);
int hours_between (dato d1, dato d2);
int days_between(dato from, dato to);
int months_between(dato d1, dato d2);
int days_in_month(dato d);
dato next_hour(dato d);
dato next_day(dato d);
int leapYear(int);
void print_date(dato);
/*Funktionerne er listet herunder*/
// int calc_time(dato from, dato to){
//     int days = 0, hours = 0, test_number = 0;
//     month from_month;
//     month to_month;

//     from_month = from.month;
//     to_month = to.month;
//     hours = calc_hours(to, to_month) - calc_hours(from, from_month);

//     hours += (24 * (to.day - from.day));
//     hours += (to.time.hour - from.time.hour);
   
//     if(hours < 0 || hours == 73 || hours == 25){
//         return 1;
//     }
//     else{
//         return hours;
//     } 
// }

// int calc_hours(dato test_year, month test){
//     int days = 0, hours = 0;
//     if(test_year.year % 4 == 0){
//         for (days = 0; test >= 1; test--)
//         {
//             if(test == 2){
//                 days += 29;
//             }
//             else if(test <= 6 && test % 2 == 0){
//                 days += 30;
//             }
//             else if(test <= 7 && test % 2 != 0){
//                 days += 31;
//             }
//             else if(test > 6 && test % 2 == 0){
//                 days += 31;
//             }
//             else if(test >= 9 && test % 2 != 0){
//                 days += 30;
//             }
//         }
//         hours = days * 24;
//         return hours;
//     }
//     else if (test_year.year % 4 != 0){
//         for (days = 0; test >= 1; test--)
//         {
//             if(test == 2){
//                 days += 28;
//             }
//             else if(test <= 6 && test % 2 == 0){
//                 days += 30;
//             }
//             else if(test <= 7 && test % 2 != 0){
//                 days += 31;
//             }
//             else if(test > 6 && test % 2 == 0){
//                 days += 31;
//             }
//             else if(test >= 9 && test % 2 != 0){
//                 days += 30;
//             }
//         }
//         hours = days * 24;
//         return hours;
//     }
//     return 0;
// }

dato next_hour(dato d){
    dato temp = d;

    if (temp.time.hour < 23) {
        temp.time.hour++ ;
    }
    else {
        temp.time.hour = 0;
        temp = next_day(temp);
        temp.time.hour = 0;
    }
    return temp;
}

/* Returns hours between two dates */
int hours_between (dato d1, dato d2){
    
    return  days_between(d1,d2)*24+ d2.time.hour - d1.time.hour;
    
}

/* Return the dato after d */
int days_between(dato from, dato to){
    dato temp = from;
    int i=0, result = 0;
    int fromMonth_daysleft, MonthsBetween;
    
    MonthsBetween = months_between(from,to);

    if(MonthsBetween == 0 && from.month == to.month){
        
        return to.day-from.day;   
    }

    if(MonthsBetween == 0 && to.month-from.month == 1){
            
        return days_in_month(from)-from.day + to.day;
    }

    else{

        fromMonth_daysleft    = days_in_month(from)-from.day;
        result = fromMonth_daysleft;
        // printf("result:%d\n",result);
        
        for(i=1;i<=MonthsBetween;i++){
            temp.month ++;
            result += days_in_month(temp);
            // printf("result:%d\n",result);

        }
        
        result += to.day;
        // printf("result:%d\n",result);
    }

    return result;

}

/* Return whole months between two dates */
int months_between(dato d1, dato d2){
    
    int delta_years = d2.year-d1.year;
    int result = 0;

    if(delta_years == 0){
        result = d2.month == d1.month ? 0 : d2.month - d1.month-1;
    }

    else if(delta_years == 1 ){
        result = December-d1.month + d2.month-1 ;
    }

    else {
        printf("for stor tidsinterval, prøv et mindre!\n");
        return -1;
    }

    return result;
}

/* returns days in month */
int days_in_month(dato d){

    switch(d.month){
    case Januar: case Marts: case Maj: case Juli: case August: case Oktober: 
      return 31;
      break;
    case April: case Juni: case September: case November: 
      return 30;
      break;
    case Februar:
      return leapYear(d.year) > 0 ? 29 : 28;
      break;
    case December:
      return 31;
      break;
    default: exit(-1);  break;
  }

}

/* Is y a leapyear */
int leapYear(int y){
  int result;

  if (y % 400 == 0) result = 1;
  else if (y % 100 == 0) result = 0;
  else if (y % 4 == 0) result = 1;
  else result = 0;

  return result;
}

/* returns next day */
dato next_day(dato d){
    dato temp = d;

     switch(d.month){
    case Januar: case Marts: case Maj: case Juli: case August: case Oktober: 
      if (d.day< 31){
          temp.day++;
      }
      else{
          temp.day=1; temp.month++;
      }
      break;
    case April: case Juni: case September: case November: 
      if (d.day< 30){
          temp.day++;
      }
      else{
          temp.day=1; temp.month++;
      }
      break;
    case Februar:
      if(d.day < leapYear(d.year) > 0 ? 29 : 28){
          temp.day++;
      }
      else {
          temp.day = 1; temp.month++;
      }
      break;
    case December:
      if(d.day<31){
          temp.day++;
      }
      else {
          temp.day =1; temp.month=1; temp.year++;
      }
      
      break;
    default: exit(-1);  break;
    
  }

  return temp;  

}

/* Print dato d */
void print_date(dato d){
  printf("%2d-%2d-%4d kl %2d\n",  d.day, d.month, d.year, d.time.hour);
}

