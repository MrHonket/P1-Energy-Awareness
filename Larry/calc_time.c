#include <stdlib.h>
#include <stdio.h>
#include "global.h"

/* int calc_time(dato from, dato to);

int main(void){
    dato fr = {{0,0},Januar,1,2017}; 
    dato t = {{0,0},Februar,1,2017};
    int hos = 0;

    hos = calc_time(fr, t);

    printf("ola %d \n", hos);

    return 0;
} */

int calc_time(dato from, dato to){
    int days = 0, hours = 0;
    int local_month;

    local_month = from.month;


    if(from.year % 4 == 0){
        while(local_month >= 1){
            if(local_month == 2){
                days += 29;
                local_month--;
            }
            else if(local_month <= 6 && local_month % 2 == 0){
                days += 30;
                local_month--;
            }
            else if(local_month <= 7 && local_month % 2 != 0){
                days += 31;
                local_month--;
            }
            else if(local_month > 6 && local_month % 2 == 0){
                days += 31;
                local_month--;
            }
            else if(local_month >= 9 && local_month % 2 != 0){
                days += 30;
                local_month--;
            }
        }
        hours = days * 24;
        return hours;
    }
    else if (from.year % 4 != 0){
        while(local_month >= 1){
            if(local_month == 2){
                days += 28;
                local_month--;
            }
            else if(local_month <= 6 && local_month % 2 == 0){
                days += 30;
                local_month--;
            }
            else if(local_month <= 7 && local_month % 2 != 0){
                days += 31;
                local_month--;
            }
            else if(local_month > 6 && local_month % 2 == 0){
                days += 31;
                local_month--;
            }
            else if(local_month >= 9 && local_month % 2 != 0){
                days += 30;
                local_month--;
            }
        }
        hours = days * 24;
        return hours;
        
    }
    return 0;

}
