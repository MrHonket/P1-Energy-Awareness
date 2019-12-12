/* Mathias(Niller) */
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "global.h"
//#include "database_module.h"
#define KWH 1000
#define NMB_OF_ELEMENTS 24

double warning_energy_saving(user User, data *Data); 
double warning_consumption(double price, double consumption,double median_consumption);
   /*user_history median data
   time data hvor får vi det fra?*/

double warning_energy_saving(user User, data *Data){
    double value,
           one_price,          //Indtil videre tager funktionen en price værdi og ikke et strukt af hvad jeg kan se?
           one_consumption,    //Indtil videre tager funktionen en consumption værdi og ikke et strukt af hvad jeg kan se?
           median_consumption;

    /*Mock data*/
    one_price = 10.5; //Skal findes i Data.prize.DK1/2price men kan IKKE tilgås sådan grundet det er en pointer til et struct.
    one_consumption = 5; //Skal findes i Data.meter.unit el. value men kan IKKE tilgås sådan grundet det er en pointer til et struct.
    median_consumption = Median; //= user_history hvor User.choice.mean_or_median = Median før User sendes i funktionen.
    /*Endmock*/

    value = warning_consumption(one_price,one_consumption,median_consumption);

    return value;
}

double warning_consumption(double price,double consumption,double median_consumption){
    double price_difference;
    consumption/=KWH;
    if(consumption>median_consumption){
    price_difference=((price*consumption)/(price*median_consumption)-1);
    printf("your energy consumption is higher than normally right now.\n");
    return price_difference;
    }
    else if(consumption<=median_consumption)
    {
    price_difference=((price*median_consumption)/(price*consumption)-1);
    printf("your consumption is not higher than normal\n");
    return price_difference;
    }
    else 
    return FALSE;
}