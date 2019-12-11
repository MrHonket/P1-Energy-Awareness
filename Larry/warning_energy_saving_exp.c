/* Mathias(Niller) */
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "global.h"
//#include "database_module.h"
#define KWH 1000
#define NMB_OF_ELEMENTS 24
double warning_consumption(double price, double consumption,double median_consumption);
/* double warning_energy_saving() 
   user_history median data
   time data hvor får vi det fra?*/

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