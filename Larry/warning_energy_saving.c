/* Mathias(Niller) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "user_history.h"
#define KWH 1000
#define NMB_OF_ELEMENTS 24

double warning_energy_saving(user User, data *Data); 
double warning_consumption(double price, double consumption,double median_consumption);

double warning_energy_saving(user User, data *Data){
    int Time_now=User.choice.from.time.hour;
    double value,
           one_price,          
           one_consumption,    
           median_consumption;
    if(strcmp(User.settings.residence,"DK1") == 0)
    {
        one_price= Data[Time_now].prize.DK1price;  
    }
    else if(strcmp(User.settings.residence,"DK2") == 0)
    {
        one_price =Data[Time_now].prize.DK2price;
    }
    one_consumption = Data[Time_now].meter.value; 
    median_consumption = user_history(User, Data);

    value = warning_consumption(one_price,one_consumption,median_consumption);
    return value;  
}
double warning_consumption(double price,double consumption,double median_consumption){
    double price_difference;
    if(consumption>median_consumption)
    {
       price_difference=((price*consumption)/(price*median_consumption)-1);
       return price_difference;
    }
    else if(consumption<=median_consumption)
    {
       price_difference=((price*median_consumption)/(price*consumption)-1);
       return FALSE;
    }
    else
    {
        error_message(ErrorInWarningConsumption);
        return Failure;
    }
}
