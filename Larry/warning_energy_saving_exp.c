/* Mathias(Niller) */
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "user_history_exp.h"
#include "database_module.h"
#define KWH 1000
#define NMB_OF_ELEMENTS 24

double warning_energy_saving(user User, data *Data); 
double warning_consumption(double price, double consumption,double median_consumption);
   /*time data hvor får vi det fra?*/

double warning_energy_saving(user User, data *Data){
    int Time_now=1;
    dato to= {{24, 00}, 15, Januar, 2018};
    double value,
           one_price,          //Indtil videre tager funktionen en price værdi og ikke et strukt af hvad jeg kan se?
           one_consumption,    //Indtil videre tager funktionen en consumption værdi og ikke et strukt af hvad jeg kan se?
           median_consumption;
    if(User.settings.residence=="DK1")
    {
        one_price= Data[Time_now].prize.DK1price;  
    }
    else if(User.settings.residence=="DK2")
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
       printf("your energy consumption is higher than normally right now.\n");
       return price_difference;
    }
    else if(consumption<=median_consumption)
    {
       printf("your consumption is not higher than normal\n");
       return FALSE;
    }
    else
    {
        printf("\nsomething went wrong...\n");
        return FALSE;
    }
}