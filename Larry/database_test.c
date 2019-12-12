#include "database_module.h"
#include "global.h"


int main(void){
    int i =0,index = 0, num_of_indexes =0 ;
    data *mydata;
    dato date1 ={{0,0},01,Marts,2017};
    dato date2 ={{0,0},02,Marts,2017};
    date1.year  =2017;
    date1.month =Januar;
    date1.day   =1;
    date1.time.hour = 0;

    date2.year  =2017;
    date2.month =December;
    date2.day   =31;
    date2.time.hour = 23;



    num_of_indexes = calc_time(date1,date2);
    
    init_database(); 
    // print_consump_index(1000);
    mydata = get_price_for_timeinterval_in_area(date1,date2,Dk1);


//     for(i=0;i<num_of_indexes;i++){
//     // print_consump_index(i);
//     // print_price_index(i);
//     index = i;
//     printf("\n\n----mydata PRIZE----\nfrom:%d-%d-%d %d:%d --- to:%d-%d-%d %d:%d\nDK1: %f\nDK2: %f \n\n",
//     mydata[index].prize.from.year,mydata[index].prize.from.month,mydata[index].prize.from.day,mydata[index].prize.from.time.hour,mydata[index].prize.from.time.minute,
//     mydata[index].prize.to.year  ,mydata[index].prize.to.month  ,mydata[index].prize.to.day  ,mydata[index].prize.to.time.hour  ,mydata[index].prize.to.time.minute,
//     mydata[index].prize.DK1price,mydata[index].prize.DK2price);
    

//     printf("----mydata METER----\nfrom:%d-%d-%d %d:%d ---to:%d-%d-%d %d:%d\nVALUE: %f\n\n\n",
//     mydata[index].meter.from.year,mydata[index].meter.from.month,mydata[index].meter.from.day,mydata[index].meter.from.time.hour,mydata[index].meter.from.time.minute,
//     mydata[index].meter.to.year  ,mydata[index].meter.to.month  ,mydata[index].meter.to.day  ,mydata[index].meter.to.time.hour  ,mydata[index].meter.to.time.minute,
//     mydata[index].meter.value);
// }


return 0;

}