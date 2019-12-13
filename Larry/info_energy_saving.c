#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"

#define NMB_OF_ELEMENTS 24

double info_energy_saving(user User, data data_array[]);
data *cheapest(data data_array[], user User);
int sort_for_best_price(const void * a, const void * b);
void print_information(data return_array[], data cheapest_struct, user User);

/* Funktionen returnerer besparelsen forbrugeren kan opnå hvis vedkommende flytter sit forbrug til det billigste tidspunkt 
 * Funktionen tager udgangspunkt i et 24 element-langt data-array samt et user_choice der afgører om det er DK1 eller DK2 vi kigger på */
double info_energy_saving(user User, data data_array[])
{
    double current_consumption = 0.0;
    double current_price = 0.0;
    double user_price_current = 0.0;
    double user_price_after = 0.0;
    double cheapest_price = 0.0;
    
    if (strcmp(User.settings.residence, "DK1") == 0)
    {   
        current_price = data_array[User.choice.from.time.hour].prize.DK1price;
        current_consumption = data_array[User.choice.from.time.hour].meter.value;
        
        if (current_price < 0)
            printf("Prisen er pt. negativ!\n");

        /* Dette giver brugerens nuværende strømpris baseret ud fra forbruget */
        user_price_current = current_consumption * KWH_TO_MWH * current_price;

        /* Sorterer pris-array så den billigste pris ligger først */
        qsort(data_array, NMB_OF_ELEMENTS, sizeof(data), sort_for_best_price);
        cheapest_price = data_array[0].prize.DK1price;

        /* Dette giver brugerens strømpris baseret ud fra hvornår det er billigst at bruge strøm */
        user_price_after = current_consumption * KWH_TO_MWH * cheapest_price;
        printf("Din pris, hvis du vaelger at flytte dit forbrug: %.2f DKK\n\n", user_price_after);
    }
    else 
    {
        current_price = data_array[User.choice.from.time.hour].prize.DK2price;
        current_consumption = data_array[User.choice.from.time.hour].meter.value;

        if (current_price < 0)
            printf("Prisen er pt. negativ!\n");

        /* Dette giver brugerens nuværende strømpris baseret ud fra forbruget */
        user_price_current = current_consumption * KWH_TO_MWH * current_price;

        /* Sorterer pris-array så den billigste pris ligger først */
        qsort(data_array, NMB_OF_ELEMENTS, sizeof(data), sort_for_best_price);
        cheapest_price = data_array[0].prize.DK2price;
        printf("Den billigste pris er: %.2f\n", cheapest_price);

        /* Dette giver brugerens strømpris baseret ud fra hvornår det er billigst at bruge strøm */
        user_price_after = current_consumption * KWH_TO_MWH * cheapest_price;
        printf("Din pris, hvis du vaelger at flytte dit forbrug: %.2f DKK\n\n", user_price_after);
    }

    if (user_price_after > user_price_current)
        return user_price_after - user_price_current;
    else
        return user_price_current - user_price_after;
} 

/* Funktionen returnerer en data-struct således vi kan se, hvornår på dagen det er billigst at forbruge strøm */
data *cheapest(data data_array[], user User)
{
    data *cheapest;
    cheapest = (data*)malloc(1 * sizeof(data));
    
    qsort(data_array, NMB_OF_ELEMENTS, sizeof(data), sort_for_best_price);

    cheapest->prize.from = data_array[0].prize.from;
    cheapest->prize.to = data_array[0].prize.to;
    cheapest->prize.DK1price = data_array[0].prize.DK1price;
    cheapest->prize.DK2price = data_array[0].prize.DK2price;

    printf("Det billigste tidspunkt at forbruge din strom vil vaere: \n--------------------------------------------------------\n");

    if (strcmp(User.settings.residence, "DK1") == 0)
        printf("Dato: %d | Klokkeslaet: %d - %d | Pris DK1: %.2f DKK |\n\n", cheapest->prize.from.day,
                         cheapest->prize.from.time.hour, cheapest->prize.to.time.hour, cheapest->prize.DK1price);
    else       
        printf("Dato: %d | Klokkeslaet: %d - %d | Pris DK2: %.2lf DKK |\n\n", cheapest->prize.from.day,
                         cheapest->prize.from.time.hour, cheapest->prize.to.time.hour, cheapest->prize.DK2price);
    return cheapest;
}

/* En samlet print funktion der tager højde for om vi kigger på DK1 eller DK2 */
void print_information(data return_array[], data cheapest_struct, user User)
{
    printf("Tidspunkt valgt af bruger: kl.%d\n\n", User.choice.from.time.hour);
    double user_price;
    if (strcmp(User.settings.residence, "DK1") == 0)
    {
        user_price = return_array[User.choice.from.time.hour].meter.value * KWH_TO_MWH * return_array[User.choice.from.time.hour].prize.DK1price;
        printf("Nuvaerende pris: %.2f DKK\n\n", return_array[User.choice.from.time.hour].prize.DK1price); 
        printf("Nuvaerende forbrug: %.2f KWH \n\n", return_array[User.choice.from.time.hour].meter.value); 
        printf("Nuvaerende pris baseret på nuvaerende forbrug: %.2f DKK\n\n", user_price); 
    }
    else
    {
        user_price = return_array[User.choice.from.time.hour].meter.value * KWH_TO_MWH * return_array[User.choice.from.time.hour].prize.DK2price;
        printf("Nuvaerende pris: %.2f\n\n", return_array[User.choice.from.time.hour].prize.DK2price); 
        printf("Nuvaerende forbrug: %.2f\n\n", return_array[User.choice.from.time.hour].meter.value); 
        printf("Nuvaerende pris baseret paa nuvaerende forbrug: %.2f DKK\n\n", user_price); 
    }
}

/* Basic compare function */
int sort_for_best_price(const void * a, const void * b)
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
