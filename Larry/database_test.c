#include "database_module.h"
#include "global.h"


int main(void){
   int i =0 ;
    
    init_database(); 
    print_consump_index(1000);
    for(i=0;i<10;i++){
    print_consump_index(i);
    print_price_index(i);
    }

return 0;

}