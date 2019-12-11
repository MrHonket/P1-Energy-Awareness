
/*                                                                                                          *
 *      ____               _  _  _                 _                                       _         _      * 
 *     |  _ \             (_)| |( )               (_)                                     | |       | |     * 
 *     | |_) |  __ _  ___  _ | ||/ ___      _ __   _   ___  ___      _ __ ___    ___    __| | _   _ | |     *
 *     |  _ <  / _` |/ __|| || |  / __|    | '_ \ | | / __|/ _ \    | '_ ` _ \  / _ \  / _` || | | || |     *
 *     | |_) || (_| |\__ \| || |  \__ \    | | | || || (__|  __/    | | | | | || (_) || (_| || |_| || |     *
 *     |____/  \__,_||___/|_||_|  |___/    |_| |_||_| \___|\___|    |_| |_| |_| \___/  \__,_| \__,_||_|     *
 *                                                                                                          *
 *                                                                                                          *
user_history
- Inputparameter er user_choice (er det en median eller gennemsnit, der ønskes) og user_data (ideelt en array af værdier) og antal
  elementer i arrayet.
- return-værdien er en double (median-return bliver lavet om til en int), enten gennemsnit eller median, baseret på user_choice
- gennemsnit udregnes ved at lægge alle værdierne sammen fra user_data og dividere med antal elementer i arrayet
- median udregnes ved først at sortere alle værdierne fra user_data, dernæst dividere antal elementer med 2, 
  hvilket giver 'i' og så tage værdien af det i'ende element i user_data.
*/

#include <stdio.h>
#include <stdlib.h>
#include "global.h"

double user_history(int mean_or_median, double dataset[], int number_of_elements);
int cmpfunc (const void * a, const void * b);

int main(void) {
    /*Mock-data)*/
    double data[] = {1.5, 9.2, 3.4, 5.6, 2.3};
    int choice1 = 1, choice2 = 2, n = 5;

        printf("Mean: %lf\nMedian: %lf", user_history(choice1, data, n), user_history(choice2, data, n)); 
        /*choice angiver om der ønskes gennemsnit eller median 
          data[] er et array af structs (enten pris, forbrug eller grøn andel)*/

    return 0;
}

double user_history(int mean_or_median, double dataset[], int number_of_elements) {
    int i = 0;
    double mean = 0;

    if (mean_or_median == 1) {
        /*Udregner gennemsnit*/
        for (i = 0; i < number_of_elements; i++) {
            mean += dataset[i];
        }
        /*Returnerer gennemsnittet*/
        printf("%lf, %d\n", mean, i);
        return (mean/i);

    } else
    if (mean_or_median == 2) {
        /*Udregner median*/
        qsort(dataset, number_of_elements, sizeof(double), cmpfunc);

        /*Returnerer median*/
        return dataset[number_of_elements/2];
    } else
    {
        /*Error*/
        return 0;
    }

}

int cmpfunc (const void * a, const void * b) {
   return ( *(double*)a - *(double*)b );
}