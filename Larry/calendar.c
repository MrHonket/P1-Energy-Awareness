#include <stdio.h>
#include <stdlib.h>
#include "global.h"


/* Funktion prototypes */

int hours_between (dato d1, dato d2);
int days_between(dato from, dato to);
int months_between(dato d1, dato d2);
int days_in_month(dato d);

dato next_hour(dato d);
dato next_day(dato d);
int leapYear(int);
void prnt_date(dato);





/* int main(void) {

  dato first_date = {{0, 0}, 28, Februar, 2002},
       last_date  = {{0, 0}, 30, Februar, 2002},
       current_date;

    printf("dage mlm\n");
    prnt_date(first_date);
    prnt_date(last_date);
    printf("---- %d\n",hours_between(first_date,last_date));
}  */

/* Returns next hour, adjusts day,month,year acordingly */
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
void prnt_date(dato d){
  printf("%2i-%2i-%4i kl %2d\n",  d.day, d.month, d.year, d.time.hour);
}

