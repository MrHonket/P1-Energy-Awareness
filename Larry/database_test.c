#include "database_module2.h"


int main(void){
    meterdata *m_data = {0};
    pricedata *p_data;
    production *prod_data ={0};
    int i = 0;
    

    init();
    // p_data = init_datab(p_data,m_data,prod_data); 


    printf("%d\n",date_from_string("2017 02 30 12:22").year);
    
    for(i=0;i<10;i++){
    print_index(i);
    }


}