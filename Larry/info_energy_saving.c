#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"

#define KWH_TO_MWH 0.001

double info_energy_saving(user User, data data_array[]);
int cmpfunc(const void * a, const void * b);
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

    data *tmp_data = malloc(sizeof(data) * 24);
    
    if (strcmp(User.settings.residence, "DK1") == 0)
    {   
        for (int i = 0; i < 24; i++)
        {
            tmp_data[i].prize.DK1price = data_array[i].prize.DK1price;
            tmp_data[i].meter.value = data_array[i].meter.value;
        }

        for (int i = 0; i < 24; i++)
            printf("Priser: %.2lf og forbrug: %.2lf\n", tmp_data[i].prize.DK1price, tmp_data[i].meter.value);

        current_price = tmp_data[User.choice.hour].prize.DK1price;
        current_consumption = tmp_data[User.choice.hour].meter.value;
        
        if (current_price < 0)
            printf("Prisen er pt. negativ!\n");

        /* Dette giver brugerens nuværende strømpris baseret ud fra forbruget */
        user_price_current = current_consumption * KWH_TO_MWH * current_price;

        /* Sorterer pris-array så den billigste pris ligger først */
        qsort(tmp_data, NMB_OF_ELEMENTS, sizeof(data), cmpfunc);
        cheapest_price = tmp_data[0].prize.DK1price;

        /* Dette giver brugerens strømpris baseret ud fra hvornår det er billigst at bruge strøm */
        user_price_after = current_consumption * KWH_TO_MWH * cheapest_price;
        printf("Din pris, hvis du vælger at flytte dit forbrug: %.2f DKK / KwH\n\n", user_price_after);
    }
    else if (strcmp(User.settings.residence, "DK2") == 0)
    {
        current_price = tmp_data[User.choice.hour].prize.DK2price;
        current_consumption = tmp_data[User.choice.hour].meter.value;

        if (current_price < 0)
            printf("Prisen er pt. negativ!\n");

        /* Dette giver brugerens nuværende strømpris baseret ud fra forbruget */
        user_price_current = current_consumption * KWH_TO_MWH * current_price;

        /* Sorterer pris-array så den billigste pris ligger først */
        qsort(tmp_data, NMB_OF_ELEMENTS, sizeof(data), cmpfunc);
        cheapest_price = tmp_data[0].prize.DK2price;
        printf("Den billigste pris er: %.2f / KwH\n", cheapest_price);

        /* Dette giver brugerens strømpris baseret ud fra hvornår det er billigst at bruge strøm */
        user_price_after = current_consumption * KWH_TO_MWH * cheapest_price;
        printf("Din pris, hvis du vaelger at flytte dit forbrug: %.2f DKK / KwH\n\n", user_price_after);
    }
    else
    {
        error_message(ErrorResidenceNotImplemented);
    }
    
    if (user_price_after > user_price_current)
        return user_price_after - user_price_current;
    else
        return user_price_current - user_price_after;

    free(tmp_data);
} 

/* Basic compare function */
int cmpfunc(const void * a, const void * b)
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

void overview_for_interval(user User, data data_array[])
{
    int i;
    if (strcmp(User.settings.residence, "DK1") == 0)
    {
        for (i = User.choice.from.time.hour; i <= User.choice.to.time.hour; i++)
            printf("Time [%d] - Pris: %.2f DKK / MWH\n", i, data_array[i].prize.DK1price);
    }
    else
    {
        for (i = User.choice.from.time.hour; i <= User.choice.to.time.hour; i++)
            printf("Time [%d] - Pris: %.2f DKK / MWH\n", i, data_array[i].prize.DK2price);
    }
    
    
}





