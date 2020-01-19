#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"

#define KWH_TO_MWH 0.001

double info_energy_saving(user User, data data_array[]);
int cmpfunc_DK1(const void * a, const void * b);
int cmpfunc_DK2(const void * a, const void * b);
void overview_for_interval( user User, data data_array[]);

/* Funktionen returnerer besparelsen forbrugeren kan opnå hvis vedkommende flytter sit forbrug til det billigste tidspunkt 
 * Funktionen tager udgangspunkt i et 24 element-langt data-array samt et user_choice der afgører om det er DK1 eller DK2 vi kigger på */
double info_energy_saving(user User, data data_array[])
{
    double current_consumption = 0.0;
    double current_price = 0.0;
    double user_price_current = 0.0;
    double user_price_after = 0.0;
    double cheapest_price = 0.0;
    int n_elements = hours_between(User.choice.from,User.choice.to);
    
if (strcmp(User.settings.residence, "DK1") == 0)
{   
    // current_price = data_array[User.choice.hour].prize.DK1price;
    // current_consumption = data_array[User.choice.hour].meter.value;
    current_price = data_array[0].prize.DK1price;
    current_consumption = data_array[0].meter.value;
    
    if (current_price < 0)
        printf("Prisen er pt. negativ!\n");

    /* Dette giver brugerens nuværende strømpris baseret ud fra forbruget */
    user_price_current = current_consumption * KWH_TO_MWH * current_price;

    /* Sorterer pris-array så den billigste pris ligger først */
    qsort(data_array, n_elements, sizeof(data), cmpfunc_DK1);
    cheapest_price = data_array[0].prize.DK1price;

    /* Dette giver brugerens strømpris baseret ud fra hvornår det er billigst at bruge strøm */
    user_price_after = current_consumption * KWH_TO_MWH * cheapest_price;
    printf("\nDin pris, hvis du vælger at flytte dit forbrug til billigste tidspunkt: %.2f DKK\n\n", user_price_after);
}
    else if (strcmp(User.settings.residence, "DK2") == 0)
    {
        current_price = data_array[User.choice.hour].prize.DK2price;
        current_consumption = data_array[User.choice.hour].meter.value;

        if (current_price < 0)
            printf("Prisen er pt. negativ!\n");

        /* Dette giver brugerens nuværende strømpris baseret ud fra forbruget */
        user_price_current = current_consumption * KWH_TO_MWH * current_price;

        /* Sorterer pris-array så den billigste pris ligger først */
        qsort(data_array, n_elements, sizeof(data), cmpfunc_DK2);
        cheapest_price = data_array[0].prize.DK2price;
        
        /* Dette giver brugerens strømpris baseret ud fra hvornår det er billigst at bruge strøm */
        user_price_after = current_consumption * KWH_TO_MWH * cheapest_price;
        printf("\nDin pris, hvis du vaelger at flytte dit forbrug til billigste tidspunkt: %.2f DKK\n\n", user_price_after);
    }
    else
    {
        error_message(ErrorResidenceNotImplemented);
    }
    
    if (user_price_after > user_price_current)
        return user_price_after - user_price_current;
    else
        return user_price_current - user_price_after;
} 

/* Basic compare function */
int cmpfunc_DK1(const void * a, const void * b)
{
    const data *priserA = (data*)a;
    const data *priserB = (data*)b;

    if (priserA->prize.DK1price < priserB->prize.DK1price)
        return -1;
    else if (priserA->prize.DK1price > priserB->prize.DK1price)
        return +1;
    else
        return 0;
}

int cmpfunc_DK2(const void * a, const void * b)
{
    const data *priserA = (data*)a;
    const data *priserB = (data*)b;

    if (priserA->prize.DK2price < priserB->prize.DK2price)
        return -1;
    else if (priserA->prize.DK2price > priserB->prize.DK2price)
        return +1;
    else
        return 0;
}

void overview_for_interval(user User, data data_array[])
{
    int i;
    int n_elements = hours_between(User.choice.from,User.choice.to);
    if (strcmp(User.settings.residence, "DK1") == 0)
    {
        printf("Dato: %d / %d / %d\t   Område: %s\n\n", data_array->prize.from.day, data_array->prize.from.month, 
        data_array->prize.from.year, User.settings.residence);
        for (i = 0; i < n_elements; i++)
            printf("dato %d / %d Kl. %d\t|\tPris: %.2f DKK / MWH \n",data_array[i].prize.from.day,data_array[i].prize.from.month, data_array[i].prize.from.time.hour, data_array[i].prize.DK1price);
    }
    else if (strcmp(User.settings.residence, "DK2") == 0)
    {
        printf("Dato: %d / %d / %d\t   Område: %s\n\n", data_array->prize.from.day, data_array->prize.from.month, 
        data_array->prize.from.year, User.settings.residence);
        for (i = 0; i < n_elements; i++)
            printf("dato %d / %d Kl. %d\t|\tPris: %.2f DKK / MWH \n",data_array[i].prize.from.day,data_array[i].prize.from.month, data_array[i].prize.from.time.hour, data_array[i].prize.DK2price);
    }
}





