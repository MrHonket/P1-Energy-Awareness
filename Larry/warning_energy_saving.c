/* Mathias(Niller) */
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "database_module.h"

double warning_consumption(double price, double consumption,double median_consumption);
int main(void){
  data price_array;
  double price_treshold;
  double median_consumption=0.5;
  printf("hello and welcome to the gokkeslaet\n");
  scanf("%lf %lf",&price_treshold, &median_consumption);
  pricedata data= {{20,0,15,Januar,2018},{21,0,15,Januar,2018},219.3,222.4};
  meterdata consumption= {"1234",{20,0,15,Januar,2018},{21,0,15,Januar,2018},3.3,"kwh","measured","hour"}; 
  printf("priser: %lf, %lf\n",data.DK1price,data.DK2price);
  if(data.DK1price>=price_treshold)
  {
    printf("your consumption is %.2lf percent off the usual\n",warning_consumption(data.DK1price,consumption.value,median_consumption));
  }
  else if (data.DK2price>=price_treshold)
  {
    printf("your consumption is %.2lf percent off the usual\n",warning_consumption(data.DK2price,consumption.value,median_consumption));
  }
else
{
printf("Price is lower than threshold no worries\n");
}
    return EXIT_SUCCESS;
}
double warning_consumption(double price,double consumption,double median_consumption){
double price_high, price_difference;
if(consumption>median_consumption){
  price_difference=((price*consumption)/(price*median_consumption)-1);
printf("your energy consumption is higher than normally right now.\n");
return price_difference;
}
else if(consumption<=median_consumption){
  price_difference=((price*median_consumption)/(price*consumption)-1);
printf("your consumption is not higher than normal\n");
return price_difference;
}
}