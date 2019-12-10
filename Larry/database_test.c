
#include "database_module.h"

#define HOURS_PR_YEAR (365*24)
#define MAXLINEWIDTH 200
#define FILENAME_METER "MeterdataJakob.csv"
#define FILENAME_PRICE "elspot-prices_2017_hourly_dkk.csv"

int main(void)
{
   dato date1 = {{20,00},2017,januar,3};
   dato date2 = {{23,00},2017,januar,3};
   data *dat;
   int a,b,c;
   init_database_module();
   // dat = get_consumption_for_timeinterval_at_id(date1,date2,"wer");

   char str[]="01-01-2017";
   sscanf(str,"%2d-%2d-%4d",&a,&b,&c);
   printf("%d %d %d", a,b,c);

   return 0;
}