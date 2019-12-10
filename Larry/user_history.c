/*
user_history
- Inputparameter er user_choice og user_data.
- return-værdien er en double (median-return bliver lavet om til en int), enten gennemsnit eller median, baseret på user_choice
- gennemsnit udregnes ved at lægge alle værdierne sammen fra user_data og dividere med strlen
- median udregnes ved først at sortere alle værdierne fra user_data, dernæst dividere strlen med 2, 
  hvilket giver 'i' og så tage værdien af det i'ende element i user_data.



*/

#include <stdio.h>
#include "global.h"

double user_history(int mean_or_median, double dataset[]);

int main(void) {
    double data[] = {1.5, 9.2, 3.4, 5.6, 2.3};
    int choice = 0, cont = 0;
    
    do {
        printf("For median, press 1, for mean, press 2: ");
        scanf("%d", &choice);

        printf("%lf", user_history(choice, data)); /*choice angiver om der ønskes gennemsnit eller median
                                                     data[] er et array af structs (enten pris, forbrug eller grøn andel)*/
        
        printf("Press 1 to run again, press q to quit.");
        scanf("%d\n", &cont);

    } while (cont != 'q');

    return 0;
}

double user_history(int mean_or_median, double dataset[]) {
    int i = 0,
        mean = 0,
        median = 0;

    for (i = 0; i <= 5; i++) {
        printf("%lf\n", dataset[i]);
    }

    if (mean != 0) {
        /*Udregner gennemsnit*/
        for (i = 0; i < 6; i++) {
            mean += dataset[i];
        }
        /*Returnerer gennemsnittet*/
        return mean/i;

    } else
    if (median != 0) {
        /*Udregner median*/
        /*Sorterer funktion - qsort?*/
        /*Tæl antal elementer, evt. samtidig*/
        return median;
    } else
    {
        /*Error*/
        return 0;
    }

}