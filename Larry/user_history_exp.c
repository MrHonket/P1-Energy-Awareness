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
- Inputparameter er User (en user-struct) og Data (en struct, der indeholder en value-array)
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

double calc_mean(double dataset[], int number_of_elements);
double calc_median(double dataset[], int number_of_elements);
int cmpdatamedian(const void *a, const void *b);

/*Denne main skal hedde user_history og have inputparametre User og Data (indeholder en value-array)*/
int user_history(user User, data *Data) {
    /*Lav en array ud fra data og baseret på, om dataen er fra meter eller pris. Det er denne, der skal regnes på.
      Funktioner fra datamodulet*/
    if (User.choice.lookup == Meter) {
        int number_of_elements = HOURS_PR_YEAR;//Skal indeholde Data->meter->to *Data.meter.from;/*Erstat med Jakobs calctime, der finder antal timer*/
        meterdata dataset[number_of_elements];
        //dataset = Data->meter;  Her skal data_settet sættes lige den korrekte delmængde af *Data
    } else
    if (User.choice.lookup == Price) {
        int number_of_elements = HOURS_PR_YEAR;//Skal indeholde Data->meter->to *Data.meter.from;/*Erstat med Jakobs calctime, der finder antal timer*/
        pricedata dataset[number_of_elements];
        //dataset = Data->prize; Her skal data_settet sættes lige den korrekte delmængde af *Data
    }

    if (User.choice.mean_or_median == Mean) {
        return 0; //calc_mean(dataset, number_of_elements); Dette skal returneres når det andet virker
    } else
    if (User.choice.mean_or_median == Median) {
        return 0; //calc_median(dataset, number_of_elements); Dette skal returneres når det andet virker
    }
}

/*dataset[] laves til data *array */
double calc_mean(double dataset[], int number_of_elements) {
    int i = 0;
    double mean = 0;

    /*Udregner gennemsnit*/
    for (i = 0; i < number_of_elements; i++) {
        mean += dataset[i];
    }

    /*Returnerer gennemsnittet*/
    return (mean/i);
}

double calc_median(double dataset[], int number_of_elements) {
    /*Udregner median*/
    qsort(dataset, number_of_elements, sizeof(double), cmpdatamedian);

    /*Returnerer median*/
    return dataset[number_of_elements/2];
}

/*qsort*/
int cmpdatamedian(const void *a, const void *b) {
   return (*(double*)a - *(double*)b);
}
