
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

double calc_mean(double dataset[], int number_of_elements);
int sort_array_for_median(const void *a, const void *b);

double user_history(user User, data *Data) {
    int i = 0;
    int number_of_elements = 0;
    double *pointer_to_dataset;
    /*Lav en array ud fra Data-structen og baseret på, om dataen er fra meter eller pris. Det er denne, der skal regnes på.*/
    if (User.choice.lookup == Meter) {
        /*Initialiserer number_of_elements, samt den array, der skal bruges. Lav om til egen funktion.*/
        number_of_elements = hours_between(User.choice.from, User.choice.to)+1;/*Finder antal timer*/
        double *dataset = malloc(sizeof(double)*number_of_elements);

        /*Assigner arrayelementer fra Data og en for-løkke*/
        for (i = 0; i < number_of_elements; i++) {
            dataset[i] = Data[i].meter.value;
        }

        /*Sorterer dataset*/
        qsort(dataset, number_of_elements, sizeof(double), sort_array_for_median);

        pointer_to_dataset = dataset;//brug dataset istedet for pointer_til_dataset
    } 
    else if (User.choice.lookup == Price) {
        /*Initialiserer number_of_elements, samt den array, der skal bruges. Lav om til egen funktion.*/
        number_of_elements = hours_between(User.choice.from, User.choice.to)+1;/*Finder antal timer*/
        double *dataset = malloc(sizeof(double)*number_of_elements);

        /*Assigner arrayelementer vha Data og en for-løkke*/
        for (i = 0; i < number_of_elements; i++) {
            dataset[i] = Data[i].prize.DK1price; /*Gør de to DK1priser til en valutastruct og user-setting*/
        }

        /*Sorterer dataset*/
        qsort(dataset, number_of_elements, sizeof(double), sort_array_for_median);
        pointer_to_dataset = dataset;//brug dataset istedet for pointer_til_dataset
    } else {
        error_message(ErrorUserLookupHistory);
        return 0;
    }

    if (User.choice.mean_or_median == Mean) {
        return(calc_mean(pointer_to_dataset, number_of_elements));
    } else
    if (User.choice.mean_or_median == Median) {
        int n = number_of_elements/2;
        
        return pointer_to_dataset[n];
    } else {
        error_message(ErrorUserMeanMedianHistory);
        return 0;
    }

    free(pointer_to_dataset);//dette skal frees et andet sted
}

double calc_mean(double dataset[], int number_of_elements) {
    int i = 0;
    double d_i;
    double mean = 0;
    /*Addere alle værdier i datasættet*/
    for (i = 0; i < number_of_elements; i++) {
        mean += dataset[i];
    }
    
    /*Returnerer gennemsnittet*/
    return (mean/number_of_elements);//(mean/number_of_elements)
}

/*qsort*/
int sort_array_for_median(const void *a, const void *b) {
    if (*(double*)a < *(double*)b) {
        return -1;
    }
    else if (*(double*)a > *(double*)b) {
        return 1;
    } else
        return 0;
}
