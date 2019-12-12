#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "database_module.h"

#define KWH_TO_MWH 0.001
#define NMB_OF_ELEMENTS 24

double info_energy_saving(user User, data data_array[]);
data *cheapest(data data_array[], user User);
int cmpfunc(const void * a, const void * b);
void print_information(data return_array[], data cheapest_struct, double user_price, user User);
/*
int main(void)
{
    double savings;
    //int tidspunkt = 19;
    double user_price;
    data cheapest_struct;
    data *return_array;
    dato from = {{00, 00}, 15, Januar, 2018};
    dato to = {{00, 00}, 15, Januar, 2018};
    user user_choice = { {1200, "DK1", "Dansk"}, {2, Mean, {{20, 0}, 15, Januar, 2017}, {{21, 0}, 15, Januar, 2017}}};
    
    return_array = get_price_for_timeinterval_in_area(from, to, Dk1);
    cheapest_struct = *cheapest(return_array);
    print_information(return_array, cheapest_struct, user_price, user_choice);

    savings = info_energy_saving2(return_array, user_choice);
    printf("Hvis du flytter dit forbrug til ovenstående tidspunkt, sparer du: %.5f DKK\n\n", savings);

    printf("\n");
    return 0;   
}
*/


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
        qsort(data_array, NMB_OF_ELEMENTS, sizeof(pricedata), cmpfunc);
        cheapest_price = data_array[0].prize.DK1price;

        /* Dette giver brugerens strømpris baseret ud fra hvornår det er billigst at bruge strøm */
        user_price_after = current_consumption * KWH_TO_MWH * cheapest_price;
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
        qsort(data_array, NMB_OF_ELEMENTS, sizeof(pricedata), cmpfunc);
        cheapest_price = data_array[0].prize.DK2price;

        /* Dette giver brugerens strømpris baseret ud fra hvornår det er billigst at bruge strøm */
        user_price_after = current_consumption * KWH_TO_MWH * cheapest_price;
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
    cheapest = (data*)malloc(1 * sizeof(pricedata));
    
    qsort(data_array, NMB_OF_ELEMENTS, sizeof(pricedata), cmpfunc);

    cheapest->prize.from = data_array[User.choice.from.day].prize.from;
    cheapest->prize.to = data_array[User.choice.from.day].prize.to;
    cheapest->prize.DK1price = data_array[User.choice.from.day].prize.DK1price;
    cheapest->prize.DK2price = data_array[User.choice.from.day].prize.DK2price;

    /* Informerer forbrugeren om hvorvidt det billigste tidspunkt er sent om aftenen */
    if (data_array[User.choice.from.day].prize.from.time.hour > 21)
        printf("Det billigste tidspunkt er efter kl 21 om aftenen\n");

    return cheapest;
}

/* En samlet print funktion der tager højde for om vi kigger på DK1 eller DK2 */
void print_information(data return_array[], data cheapest_struct, double user_price, user User)
{
    if (strcmp(User.settings.residence, "DK1") == 0)
    {
        user_price = return_array[User.choice.from.time.hour].meter.value * KWH_TO_MWH * return_array[User.choice.from.time.hour].prize.DK1price;
        printf("Nuværende pris: %.1f DKK\n\n", return_array[User.choice.from.time.hour].prize.DK1price); 
        printf("Nuværende forbrug: %.2f KWH\n\n", return_array[User.choice.from.time.hour].meter.value); 
        printf("Nuværende pris baseret på nuværende forbrug: %.2f DKK\n\n", user_price); 
        printf("Det billigste tidspunkt at forbruge på er: \n");
        printf("\n");
        printf("Dato: %d | Klokkeslæt: %d - %d | Pris DK1: %.f DKK\n\n", cheapest_struct.prize.from.day,
                         cheapest_struct.prize.from.time.hour, cheapest_struct.prize.to.time.hour, cheapest_struct.prize.DK1price);
    }
    else
    {
        user_price = return_array[User.choice.from.time.hour].meter.value * KWH_TO_MWH * return_array[User.choice.from.time.hour].prize.DK2price;
        printf("Nuværende pris: %.1f\n\n", return_array[User.choice.from.time.hour].prize.DK2price); 
        printf("Nuværende forbrug: %.2f\n\n", return_array[User.choice.from.time.hour].meter.value); 
        printf("Nuværende pris baseret på nuværende forbrug: %.2f DKK\n\n", user_price); 
        printf("Det billigste tidspunkt at forbruge på er: \n");
        printf("\n");
        printf("Dato: %d | Klokkeslæt: %d - %d | Pris DK2: %.f DKK\n\n", cheapest_struct.prize.from.day,
                         cheapest_struct.prize.from.time.hour, cheapest_struct.prize.to.time.hour, cheapest_struct.prize.DK2price);
    }
}

/* Basic compare function */
int cmpfunc(const void * a, const void * b)
{
    data *priserA = (data*)a;
    data *priserB = (data*)b;

    return priserA->prize.DK1price - priserB->prize.DK1price;
}

