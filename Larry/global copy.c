
/*Universelle imports*/
#include <stdio.h>
#include <stdlib.h>
#include "global.h"


const char* area_txt[] = {"DK1","DK2"};
const char* language_txt[] = {"","","","","","","","","","","","","DK","ENG"};
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


int hours_between (dato d1, dato d2);
int days_between(dato from, dato to);
int months_between(dato d1, dato d2);
int days_in_month(dato d);
dato next_hour(dato d);
dato next_day(dato d);
int leapYear(int);
void print_date(dato);
void clear_input_buffer();
void wait_for_keypress();
/*Funktionerne er listet herunder*/


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

void clear_input_buffer(){
    while (getchar() != '\n');
}

void wait_for_keypress(){
    char c;
    printf("tryk en tast!");
    while (scanf(" %c",&c)==0)
    {
        /* code */
    }
}


