#include <stdlib.h>
#include <stdio.h>
#include "global.h"

int calc_time(dato from, dato to);
int calc_hours(dato test_year, month test);

/* int main(void){
    dato fr = {{00, 00}, 1, 2 , 2017};
    dato t = {{00, 00}, 1, 6, 2017};
    int hos = 0;

    hos = calc_time(fr, t);

    printf("ola %d \n", hos);

    return 0;
} */

int calc_time(dato from, dato to){
    int days = 0, hours = 0;
    month from_month;
    month to_month;


    from_month = from.month;
    to_month = to.month;

    printf("test %d\n", from_month);
    printf("test %d\n", to_month);

    hours = calc_hours(to, to_month) - calc_hours(from, from_month);
   
    return hours; 

}

int calc_hours(dato test_year, month test){
    int days = 0, hours = 0;
    if(test_year.year % 4 == 0){
        for (days = 0; test >= 1; test--)
        {
            if(test == 2){
                days += 29;
            }
            else if(test <= 6 && test % 2 == 0){
                days += 30;
            }
            else if(test <= 7 && test % 2 != 0){
                days += 31;
            }
            else if(test > 6 && test % 2 == 0){
                days += 31;
            }
            else if(test >= 9 && test % 2 != 0){
                days += 30;
            }
        }
        hours = days * 24;
        return hours;
    }
    else if (test_year.year % 4 != 0){
        for (days = 0; test >= 1; test--)
        {
            if(test == 2){
                days += 28;
            }
            else if(test <= 6 && test % 2 == 0){
                days += 30;
            }
            else if(test <= 7 && test % 2 != 0){
                days += 31;
            }
            else if(test > 6 && test % 2 == 0){
                days += 31;
            }
            else if(test >= 9 && test % 2 != 0){
                days += 30;
            }
        }
        hours = days * 24;
        return hours;
        
    }
    return 0;

}
