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
/* double warning_energy_saving() */
int main(void){
  double price_treshold = 200;
  double median_consumption=0.5;
  int timeframe=12;
  printf("hello and welcome to the gokkeslaet\n");
  printf("enter timeframe, median consumption and price threshold: ");
  /* mean_price=user_history(mean.data); */
  scanf("%d %lf %lf",&timeframe, &median_consumption, &price_treshold);
  pricedata price_array[NMB_OF_ELEMENTS] = {
        {
            {{00, 00}, 15, Januar, 2018}, {{01, 00}, 15, Januar, 2018}, 178, 64
        },
        {
            {{01, 00}, 15, Januar, 2018}, {{02, 00}, 15, Januar, 2018}, 178, 64
        },
        {
            {{02, 00}, 15, Januar, 2018}, {{03, 00}, 15, Januar, 2018}, 178, 56
        },
        {
            {{03, 00}, 15, Januar, 2018}, {{04, 00}, 15, Januar, 2018}, 172, 39
        },
        {
            {{04, 00}, 15, Januar, 2018}, {{05, 00}, 15, Januar, 2018}, 179, 39
        },
        {
            {{05, 00}, 15, Januar, 2018}, {{06, 00}, 15, Januar, 2018}, 185, 92
        },
        {
            {{06, 00}, 15, Januar, 2018}, {{07, 00}, 15, Januar, 2018}, 190, 46
        },
        {
            {{07, 00}, 15, Januar, 2018}, {{8, 00}, 15, Januar, 2018}, 192, 32
        },
        {
            {{8, 00}, 15, Januar, 2018}, {{9, 00}, 15, Januar, 2018}, 194, 62
        },
        {
            {{9, 00}, 15, Januar, 2018}, {{10, 00}, 15, Januar, 2018}, 191, 35
        },
        {
            {{10, 00}, 15, Januar, 2018}, {{11, 00}, 15, Januar, 2018}, 199, 9
        },
        {
            {{11, 00}, 15, Januar, 2018}, {{12, 00}, 15, Januar, 2018}, 204, 29
        },
        {
            {{12, 00}, 15, Januar, 2018}, {{13, 00}, 15, Januar, 2018}, 208, 45
        },
        {
            {{13, 00}, 15, Januar, 2018}, {{14, 00}, 15, Januar, 2018}, 213, 36
        },
        {
            {{14, 00}, 15, Januar, 2018}, {{15, 00}, 15, Januar, 2018}, 220, 49
        },
        {
            {{15, 00}, 15, Januar, 2018}, {{16, 00}, 15, Januar, 2018}, 225, 84
        },
        {
            {{16, 00}, 15, Januar, 2018}, {{17, 00}, 15, Januar, 2018}, 228, 97
        },
        {
            {{17, 00}, 15, Januar, 2018}, {{18, 00}, 15, Januar, 2018}, 229, 93
        },
        {
            {{18, 00}, 15, Januar, 2018}, {{19, 00}, 15, Januar, 2018}, 228, 82
        },
        {
            {{19, 00}, 15, Januar, 2018}, {{20, 00}, 15, Januar, 2018}, 226, 81
        },
        {
            {{20, 00}, 15, Januar, 2018}, {{21, 00}, 15, Januar, 2018}, 224, 43
        },
        {
            {{21, 00}, 15, Januar, 2018}, {{22, 00}, 15, Januar, 2018}, 222, 57
        },
        {
            {{22, 00}, 15, Januar, 2018}, {{23, 00}, 15, Januar, 2018}, 220, 42
        },
        {
            {{23, 00}, 15, Januar, 2018}, {{24, 00}, 15, Januar, 2018}, 218, 26
        }
    };
    
  meterdata meterdata_array[NMB_OF_ELEMENTS] = {
        {
            "18928", {{00, 00}, 15, Januar, 2018}, {{01, 00}, 15, Januar, 2018}, 440
        },
        {
            "18921", {{01, 00}, 15, Januar, 2018}, {{02, 00}, 15, Januar, 2018}, 450
        },
        {
            "18924", {{02, 00}, 15, Januar, 2018}, {{03, 00}, 15, Januar, 2018}, 420
        },
        {
            "18923", {{03, 00}, 15, Januar, 2018}, {{04, 00}, 15, Januar, 2018}, 440
        },
        {
            "18923", {{04, 00}, 15, Januar, 2018}, {{05, 00}, 15, Januar, 2018}, 450
        },
        {
            "18923", {{05, 00}, 15, Januar, 2018}, {{06, 00}, 15, Januar, 2018}, 420
        },
        {
            "18923", {{06, 00}, 15, Januar, 2018}, {{07, 00}, 15, Januar, 2018}, 440
        },
        {
            "18923", {{07, 00}, 15, Januar, 2018}, {{8, 00}, 15, Januar, 2018}, 450
        },
        {
            "18923", {{8, 00}, 15, Januar, 2018}, {{9, 00}, 15, Januar, 2018}, 420
        },
        {
            "18923", {{9, 00}, 15, Januar, 2018}, {{10, 00}, 15, Januar, 2018}, 430
        },
        {
            "18923", {{10, 00}, 15, Januar, 2018}, {{11, 00}, 15, Januar, 2018}, 910
        },
        {
            "18923", {{11, 00}, 15, Januar, 2018}, {{12, 00}, 15, Januar, 2018}, 150
        },
        {
            "18923", {{12, 00}, 15, Januar, 2018}, {{13, 00}, 15, Januar, 2018}, 240
        },
        {
            "18923", {{13, 00}, 15, Januar, 2018}, {{14, 00}, 15, Januar, 2018}, 530
        },
        {
            "18923", {{14, 00}, 15, Januar, 2018}, {{15, 00}, 15, Januar, 2018}, 100
        },
        {
            "18923", {{15, 00}, 15, Januar, 2018}, {{16, 00}, 15, Januar, 2018}, 70
        },
        {
            "18923", {{16, 00}, 15, Januar, 2018}, {{17, 00}, 15, Januar, 2018}, 130
        },
        {
            "18923", {{17, 00}, 15, Januar, 2018}, {{18, 00}, 15, Januar, 2018}, 640
        },
        {
            "18923", {{18, 00}, 15, Januar, 2018}, {{19, 00}, 15, Januar, 2018}, 440
        },
        {
            "18923", {{19, 00}, 15, Januar, 2018}, {{20, 00}, 15, Januar, 2018}, 180
        },
        {
            "18923", {{20, 00}, 15, Januar, 2018}, {{21, 00}, 15, Januar, 2018}, 70
        },
        {
            "18923", {{21, 00}, 15, Januar, 2018}, {{22, 00}, 15, Januar, 2018}, 990
        },
        {
            "18923", {{22, 00}, 15, Januar, 2018}, {{23, 00}, 15, Januar, 2018}, 40
        },
        {
            "18923", {{23, 00}, 15, Januar, 2018}, {{24, 00}, 15, Januar, 2018}, 40
        }
    };
  if(price_array[timeframe].DK1price>=price_treshold)
  {
    printf("your consumption is %.2lf percent off the usual\n",warning_consumption(price_array[timeframe].DK1price,
    meterdata_array[timeframe-1].value,median_consumption));
  }
  else if (price_array[timeframe].DK2price>=price_treshold)
  {
    printf("your consumption is %.2lf percent off the usual\n",warning_consumption(price_array[timeframe].DK2price,
    meterdata_array[timeframe-1].value,median_consumption));
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
