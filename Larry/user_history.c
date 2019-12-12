
/*
_____

Basil
_____

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
#include "database_module.h"
#include "calctime.h"

double calc_mean(double dataset[], int number_of_elements);
double calc_median(double dataset[], int number_of_elements);
int cmpfunc(const void *a, const void *b);

/*Denne main skal hedde user_history og have inputparametre User og Data (indeholder en value-array)*/
int main(void) {
    user User; /*Indeholder indstillinger og brugervalg, User.choice*/
    data *Data; /*Indeholder data for både meter-data og elpris*/
    int i = 0;

    /*Lav en array ud fra data og baseret på, om dataen er fra meter eller pris. Det er denne, der skal regnes på.
      Funktioner fra datamodulet*/
    /*User.choice.meter & price skal lige defineres i global.c & global.h*/
    if (User.choice.lookup_type == Meter) {
        /*Initialiserer number_of_elements, samt den array, der skal bruges. Lav om til egen funktion.*/
        int number_of_elements = calctime(Data.meterdata.to, Data.meterdata.from);/*Finder antal timer*/
        double dataset[number_of_elements];
        /*Assigner arrayelementer fra Data og en for-løkke*/
        for (i = 0; i <= number_of_elements; i++) {
            dataset[i] = Data->meterdata->value[i];
        }
    } else
    if (User.choice.lookup_type == Price) {
        /*Initialiserer number_of_elements, samt den array, der skal bruges. Lav om til egen funktion.*/
        int number_of_elements = calctime(Data.pricedata.to, Data.pricedata.from);/*Finder antal timer*/
        double dataset[number_of_elements];
        /*Assigner arrayelementer vha Data og en for-løkke*/
        for (i = 0; i <= number_of_elements; i++) {
            dataset[i] = Data->pricedata->value[i];
        }
    }

    if (User.choice.mean_or_median == mean) {
        return calc_mean(dataset, number_of_elements);
    } else
    if (User.choice.mean_or_median == median) {
        return calc_median(dataset, number_of_elements);
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
    qsort(dataset, number_of_elements, sizeof(double), cmpfunc);

    /*Returnerer median*/
    return dataset[number_of_elements/2];
}

/*qsort*/
int cmpfunc(const void *a, const void *b) {
   return (*(double*)a - *(double*)b);
}
