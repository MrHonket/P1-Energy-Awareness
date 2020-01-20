//Activation har vurderet at prisen er høj lige nu , derfor uundersøges om der er et stort forbrug.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "user_history.h"
#define KWH 1000
#define NMB_OF_ELEMENTS 24

double warning_energy_saving(user User, data *Data); 
double warning_consumption(double consumption,double median_consumption);

double warning_energy_saving(user User, data *Data){
    int Now_index = hours_between(User.choice.from, User.choice.now);
    double value,
        //    one_price,          
           one_consumption,    
           median_consumption;
    // if(strcmp(User.settings.residence,"DK1") == 0)
    // {
    //     one_price= Data[Now_index].prize.DK1price;  
    // }
    // else if(strcmp(User.settings.residence,"DK2") == 0)
    // {
    //     one_price =Data[Now_index].prize.DK2price;
    // }
    one_consumption = Data[Now_index].meter.value; 
    median_consumption = user_history(User, Data);

    value = warning_consumption(/*one_price*/one_consumption,median_consumption);
    return value;  
}
double warning_consumption(double consumption,double median_consumption){// returnerer hvis forbruget er større end median forbruget  et forbrug ellers false, du bruger ikke mere end gennemsnit
    double consumption_difference;
    if(consumption>median_consumption)
    {
       consumption_difference=((consumption)/(median_consumption)-1);
       return consumption_difference;
    }
    else if(consumption<=median_consumption)
    {
    //    consumption_difference=((price*median_consumption)/(price*consumption)-1);
       return FALSE;
    }
    else
    {
        error_message(ErrorInWarningConsumption);
        return Failure;
    }
}
