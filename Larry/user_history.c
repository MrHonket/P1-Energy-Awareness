
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
- Inputparameter er User (en user-struct) og Data (et datasæt)
    - User.choice.mean_or_median afgør om det skal findes gennemsnit eller median, samt om det skal findes for meterdata
      eller for elpris.
    - Data indeholder tid, der bruges til at finde antal elementer (svarer til antal timer, der regnes på), 

- return-værdien er en double (gennemsnit eller median)

- gennemsnit udregnes ved at lægge alle værdierne sammen fra user_data og dividere med antal elementer i arrayet
- median udregnes ved først at sortere alle værdierne fra user_data, dernæst dividere antal elementer med 2, 
  hvilket giver 'i' og så tage værdien af det i'ende element i user_data.
*/

#include <stdio.h>
#include <stdlib.h>
#include "global.h"

#define MEAN 1
#define MEDIAN 2

double mean(double dataset[], int number_of_elements);
double median(double dataset[], int number_of_elements);
int cmpfunc (const void * a, const void * b);

/*Denne main skal hedde user_history og have inputparametre User og Data*/
int main(void) {
    user User; /*Indeholder indstillinger*/
    data Data[]; /*Indeholder data for både meter-data og elpris*/
    double dataset[];
    /*Initialiserer antal elementer vha Data-arrayen*/
    int number_of_elements = Data.to - Data.from; /*Skal specificeres yderligere. f.eks. er det fra meter eller pris, osv. 
                                                    Vi skal ende med at have et timeantal, så man kunne evt starte med at sige
                                                    at for hver dag er der 24 timer, osv.
                                                    Brug evt. time.h?*/
    

    /*Lav en array ud fra data og baseret på, om dataen er fra meter eller pris. Det er denne, der skal regnes på*/
    if (User.choice_of_function.meter) {
        /*Læg meter[].value i array dataset[]*/
    } else
    if (User.choice_of_function.price) {
        /*Læg i pris[].value i array dataset[]*/
    }

        if (User.choice_of_function.mean_or_median == MEAN) {
            return mean(dataset, number_of_elements);
        } else
        if (User.choice_of_function.mean_or_median == MEDIAN) {
            return median(dataset, number_of_elements);
        }
}

double mean(double dataset[], int number_of_elements) {
    int i = 0;
    double mean = 0;

    /*Udregner gennemsnit*/
    for (i = 0; i < number_of_elements; i++) {
        mean += dataset[i];
    }

    /*Returnerer gennemsnittet*/
    return (mean/i);
}

double median(double dataset[], int number_of_elements) {
    /*Udregner median*/
    qsort(dataset, number_of_elements, sizeof(double), cmpfunc);

    /*Returnerer median*/
    return dataset[number_of_elements/2];
}

/*qsort*/
int cmpfunc (const void * a, const void * b) {
   return ( *(double*)a - *(double*)b );
}
