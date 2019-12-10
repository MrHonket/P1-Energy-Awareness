
/***
 *      ____               _  _  _              _                                    _         _       
 *     |  _ \             (_)| |( )            (_)                                  | |       | |      
 *     | |_) |  __ _  ___  _ | ||/ ___   _ __   _   ___  ___   _ __ ___    ___    __| | _   _ | |  ___ 
 *     |  _ <  / _` |/ __|| || |  / __| | '_ \ | | / __|/ _ \ | '_ ` _ \  / _ \  / _` || | | || | / _ \
 *     | |_) || (_| |\__ \| || |  \__ \ | | | || || (__|  __/ | | | | | || (_) || (_| || |_| || ||  __/
 *     |____/  \__,_||___/|_||_|  |___/ |_| |_||_| \___|\___| |_| |_| |_| \___/  \__,_| \__,_||_| \___|
 *                                                                                                     
 *                                                                                                     
 */

/*
user_history
- Inputparameter er user_choice og user_data.
- return-værdien er en double (median-return bliver lavet om til en int), enten gennemsnit eller median, baseret på user_choice
- gennemsnit udregnes ved at lægge alle værdierne sammen fra user_data og dividere med antal elementer i arrayet
- median udregnes ved først at sortere alle værdierne fra user_data, dernæst dividere antal elementer med 2, 
  hvilket giver 'i' og så tage værdien af det i'ende element i user_data.
- skal evt. hedde noget andet end user_history, eftersom den jo egentlig bare returnerer en double
*/

#include <stdio.h>
#include "global.h"

double user_history(int mean_or_median, double dataset[]);

int main(void) {
    double data[] = {1.5, 9.2, 3.4, 5.6, 2.3}; /*Midlertidig data-array ;)*/
    int choice = 0, cont = 0;
    
    do {
        printf("For mean, press 1, for median, press 2: ");
        scanf("%d", &choice);

        printf("%lf\n", user_history(choice, data)); /*choice angiver om der ønskes gennemsnit eller median
                                                     data[] er et array af structs (enten pris, forbrug eller grøn andel)*/
        
        printf("Press 1 to run again, press q to quit.");
        scanf("%d\n", &cont);

        if (cont != 1) {return 0;}

    } while (cont == 1);

    return 0;
}

double user_history(int mean_or_median, double dataset[]) {
    int i = 0, mean = 0, median = 0;

    if (mean_or_median == 1) {
        /*Udregner gennemsnit*/
        for (i = 0; i < sizeof(dataset); i++) {
            mean += dataset[i];
        }
        /*Returnerer gennemsnittet*/
        printf("%lf, %d\n", mean, i);
        return mean/i;

    } else
    if (mean_or_median == 2) {
        /*Udregner median*/
        /*Sorterer arrayet - qsort?*/
        /*Tæl antal elementer, evt. samtidig*/
        return dataset[antal_elementer/2];
    } else
    {
        /*Error*/
        return 0;
    }

}