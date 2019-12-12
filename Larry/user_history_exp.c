
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

double calc_mean(double dataset[], int number_of_elements);
double calc_median(double dataset[], int number_of_elements);
int sort_array_for_median(const void *a, const void *b);

/*Denne main skal hedde user_history og have inputparametre User og Data (indeholder en value-array)*/
double user_history(user User, data *Data) {
    int i = 0;
    int number_of_elements = 0;
    double *pointer_to_dataset;
    /*Lav en array ud fra Data-structen og baseret på, om dataen er fra meter eller pris. Det er denne, der skal regnes på.*/
    /*User.choice.meter & price skal lige defineres i global.c & global.h*/
    if (User.choice.lookup == Meter) {
        /*Initialiserer number_of_elements, samt den array, der skal bruges. Lav om til egen funktion.*/
        number_of_elements = calc_time(Data->meter.from, Data->meter.to);/*Finder antal timer*/
        double *dataset = malloc(sizeof(double)*number_of_elements);

        /*Assigner arrayelementer fra Data og en for-løkke*/
        for (i = 0; i < number_of_elements; i++) {
            dataset[i] = Data[i].meter.value;
            printf("%lf\n", Data[i].meter.value);
        }
        /*printf("Usorteret:\n");
        for (i = 0; i < number_of_elements; i++) {
            printf("%lf\n", dataset[i]);
        }*/

        /*Sorterer dataset*/
        qsort(dataset, number_of_elements, sizeof(double), sort_array_for_median);

        /*
        printf("Sorteret:\n");
        for (i = 0; i < number_of_elements; i++) {
            printf("%lf\n", dataset[i]);
        }
        */
        pointer_to_dataset = dataset;
        //printf("heeeey heeey baby (hoo) (ha)\n");
    } else
    if (User.choice.lookup == Price) {
        /*Initialiserer number_of_elements, samt den array, der skal bruges. Lav om til egen funktion.*/
        number_of_elements = calc_time(Data->prize.from, Data->prize.to);/*Finder antal timer*/
        double *dataset = malloc(sizeof(double)*number_of_elements);

        /*Assigner arrayelementer vha Data og en for-løkke*/
        for (i = 0; i < number_of_elements; i++) {
            dataset[i] = Data[i].prize.DK1price; /*Gør de to DK1priser til en valutastruct og user-setting*/
        }
        /*printf("Usorteret:\n");
        for (i = 0; i < number_of_elements; i++) {
            printf("%lf\n", dataset[i]);
        }*/

        /*Sorterer dataset*/
        //printf("Sorteret: ");
        qsort(dataset, number_of_elements, sizeof(double), sort_array_for_median);
        /*for (i = 0; i < number_of_elements; i++) {
            printf("%lf\n", dataset[i]);
        }*/
        pointer_to_dataset = dataset;
        //printf("heeeey heeey baby (hoo) (ha)\n");
    } else {
        //Error
        //error_message() 
        return 0;
    }

    if (User.choice.mean_or_median == Mean) {
        /*return calc_mean(dataset, number_of_elements);*/
        //printf("\nMean:  %lf", calc_mean(pointer_to_dataset, number_of_elements));
        return(calc_mean(pointer_to_dataset, number_of_elements));
    } else
    if (User.choice.mean_or_median == Median) {
        /*return calc_median(dataset, number_of_elements);*/
        //printf("\nMedian:  %lf", calc_median(pointer_to_dataset, number_of_elements));
        return(calc_median(pointer_to_dataset, number_of_elements));
    } else {
        /*Error*/
        return 0;
    }

    free(pointer_to_dataset);
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
    /*int j = 0;
    printf("\nInde i medianfunktionen:");
    for (j = 0; j < number_of_elements; j++) {
        printf("\n%lf", dataset[j]);
    }*/

    /*Returnerer median*/
    return dataset[number_of_elements/2];
}

/*qsort*/
int sort_array_for_median(const void *a, const void *b) {
    //printf("Hey gurl it's been a long time lets catch up :)");
    //return (*(double*)a - *(double*)b);

    if (*(double*)a < *(double*)b) {
        return -1;
    }
    else if (*(double*)a > *(double*)b) {
        return 1;
    } else
        return 0;
}
