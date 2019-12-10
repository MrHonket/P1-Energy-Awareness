#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "global.h"
/* #include "database_module.h" */

double warning_energy_saving(double price, double consumption,double median_consumption);
int main(void){
  double price_treshold;
  double median_consumption=0.5;
  printf("hello and welcome to the gokkeslaet\n");
  scanf("%lf %lf",&price_treshold, &median_consumption);
  pricedata data= {{20,0,15,januar,2018},{21,0,15,januar,2018},219.3,222.4};
  meterdata consumption= {"1234",{20,0,15,januar,2018},{21,0,15,januar,2018},3.3,"kwh","measured","hour"}; 
  printf("gokkeslaet: %d\n",data.from.time.hour);   
  printf("slut gokker: %d\n",data.to.time.hour);
  printf("dato: %d. %s %d\n",data.from.day,month_txt[data.from.month],data.from.year); 
  printf("priser: %lf, %lf\n",data.DK1price,data.DK2price);
  printf("Forbrug i perioden: %lf\n",consumption.value);
  if(data.DK1price<=price_treshold)
  {
    printf("you are paying %.2lf percent more than usual",warning_energy_saving(data.DK1price,consumption.value,median_consumption));
  }
  else if (data.DK2price<=price_treshold)
  {
    printf("you are paying %.2lf percent more than usual",warning_energy_saving(data.DK2price,consumption.value,median_consumption));
  }

printf("Forbrug i perioden: %lf\n",consumption.value);
if(data.DK1price<=price_treshold|| data.DK2price<=price_treshold){
printf("the price difference is: %.2lf",warning_energy_saving(data.DK2price,consumption.value,median_consumption));
}
else{
printf("Price is lower than threshold no worries\n");
}
    return EXIT_SUCCESS;
}
double warning_energy_saving(double price,double consumption,double median_consumption){
double price_high, price_difference;
if(consumption>median_consumption){
price_difference=(price*consumption)-(price*median_consumption);
printf("your energy consumption is higher than normally right now.\n");
return price_difference;
}
printf("Price Difference %.2lf",price_difference);
return price_difference;
}