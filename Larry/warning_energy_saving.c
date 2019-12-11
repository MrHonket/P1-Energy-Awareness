/* Mathias(Niller) */
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "database_module.h"
#define KWH 1000
#define NMB_OF_ELEMENTS 24
double warning_consumption(double price, double consumption,double median_consumption);
/* double warning_energy_saving() 
   user_history median data
   time data hvor får vi det fra?*/

int main(void){
  double price_treshold = 200;
  double median_consumption=0.5;
  int timeframe;
  data *data_array;
  dato from={{00, 00}, 15, Januar, 2018};
  dato to= {{24, 00}, 15, Januar, 2018};
  printf("hello and welcome to the gokkeslaet\n");
  printf("enter timeframe, median consumption and price threshold: ");
   scanf("%d %lf %lf",&timeframe, &median_consumption, &price_treshold);
  data_array =get_price_for_timeinterval_in_area(from, to, Dk1);
  if(data_array[timeframe].prize.DK1price>=price_treshold)
  {
    printf("your consumption is %.2lf percent off the median consumption\n",warning_consumption(data_array[timeframe].prize.DK1price,
    data_array[timeframe-1].meter.value,median_consumption));
  }
  else if (data_array[timeframe].prize.DK1price>=price_treshold)
  {
    printf("your consumption is %.2lf percent off the  median consumption\n",warning_consumption(data_array[timeframe].prize.DK2price,
    data_array[timeframe-1].meter.value,median_consumption));
  }
else
{
printf("Price is lower than threshold no worries\n");
}
    return EXIT_SUCCESS;
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
