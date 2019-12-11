#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"

#define KWH_TO_MWH 0.001
#define NMB_OF_ELEMENTS 24

double info_energy_saving2(meterdata forbrug_array[], pricedata priser_array[], int time_frame, user user_choice);
pricedata *cheapest(pricedata priser_array[]);
int cmpfunc(const void * a, const void * b);

int main(void)
{
    double savings;
    int tidspunkt = 18;
    pricedata cheapest_struct;
    user user_choice = {1200, "DK1", "Dansk", 2, 1};

    pricedata priser_array[NMB_OF_ELEMENTS] = {
        {
            {{00, 00}, 15, Januar, 2018}, {{01, 00}, 15, Januar, 2018}, 178, 64
        },
        {
            {{01, 00}, 15, Januar, 2018}, {{02, 00}, 15, Januar, 2018}, 178, 64
        },
        {
            {{02, 00}, 15, Januar, 2018}, {{03, 00}, 15, Januar, 2018}, 178, 56
        },
        {
            {{03, 00}, 15, Januar, 2018}, {{04, 00}, 15, Januar, 2018}, 172, 39
        },
        {
            {{04, 00}, 15, Januar, 2018}, {{05, 00}, 15, Januar, 2018}, 179, 39
        },
        {
            {{05, 00}, 15, Januar, 2018}, {{06, 00}, 15, Januar, 2018}, 185, 92
        },
        {
            {{06, 00}, 15, Januar, 2018}, {{07, 00}, 15, Januar, 2018}, 190, 46
        },
        {
            {{07, 00}, 15, Januar, 2018}, {{8, 00}, 15, Januar, 2018}, 192, 32
        },
        {
            {{8, 00}, 15, Januar, 2018}, {{9, 00}, 15, Januar, 2018}, 194, 62
        },
        {
            {{9, 00}, 15, Januar, 2018}, {{10, 00}, 15, Januar, 2018}, 191, 35
        },
        {
            {{10, 00}, 15, Januar, 2018}, {{11, 00}, 15, Januar, 2018}, 199, 9
        },
        {
            {{11, 00}, 15, Januar, 2018}, {{12, 00}, 15, Januar, 2018}, 204, 29
        },
        {
            {{12, 00}, 15, Januar, 2018}, {{13, 00}, 15, Januar, 2018}, 208, 45
        },
        {
            {{13, 00}, 15, Januar, 2018}, {{14, 00}, 15, Januar, 2018}, 213, 36
        },
        {
            {{14, 00}, 15, Januar, 2018}, {{15, 00}, 15, Januar, 2018}, 220, 49
        },
        {
            {{15, 00}, 15, Januar, 2018}, {{16, 00}, 15, Januar, 2018}, 225, 84
        },
        {
            {{16, 00}, 15, Januar, 2018}, {{17, 00}, 15, Januar, 2018}, 228, 97
        },
        {
            {{17, 00}, 15, Januar, 2018}, {{18, 00}, 15, Januar, 2018}, 229, 93
        },
        {
            {{18, 00}, 15, Januar, 2018}, {{19, 00}, 15, Januar, 2018}, 228, 82
        },
        {
            {{19, 00}, 15, Januar, 2018}, {{20, 00}, 15, Januar, 2018}, 226, 81
        },
        {
            {{20, 00}, 15, Januar, 2018}, {{21, 00}, 15, Januar, 2018}, 224, 43
        },
        {
            {{21, 00}, 15, Januar, 2018}, {{22, 00}, 15, Januar, 2018}, 222, 57
        },
        {
            {{22, 00}, 15, Januar, 2018}, {{23, 00}, 15, Januar, 2018}, 220, 42
        },
        {
            {{23, 00}, 15, Januar, 2018}, {{24, 00}, 15, Januar, 2018}, 218, 26
        }
    };
    
    meterdata meterdata_array[NMB_OF_ELEMENTS] = {
        {
            "18928", {{00, 00}, 15, Januar, 2018}, {{01, 00}, 15, Januar, 2018}, 440
        },
        {
            "18921", {{01, 00}, 15, Januar, 2018}, {{02, 00}, 15, Januar, 2018}, 450
        },
        {
            "18924", {{02, 00}, 15, Januar, 2018}, {{03, 00}, 15, Januar, 2018}, 420
        },
        {
            "18923", {{03, 00}, 15, Januar, 2018}, {{04, 00}, 15, Januar, 2018}, 440
        },
        {
            "18923", {{04, 00}, 15, Januar, 2018}, {{05, 00}, 15, Januar, 2018}, 450
        },
        {
            "18923", {{05, 00}, 15, Januar, 2018}, {{06, 00}, 15, Januar, 2018}, 420
        },
        {
            "18923", {{06, 00}, 15, Januar, 2018}, {{07, 00}, 15, Januar, 2018}, 440
        },
        {
            "18923", {{07, 00}, 15, Januar, 2018}, {{8, 00}, 15, Januar, 2018}, 450
        },
        {
            "18923", {{8, 00}, 15, Januar, 2018}, {{9, 00}, 15, Januar, 2018}, 420
        },
        {
            "18923", {{9, 00}, 15, Januar, 2018}, {{10, 00}, 15, Januar, 2018}, 430
        },
        {
            "18923", {{10, 00}, 15, Januar, 2018}, {{11, 00}, 15, Januar, 2018}, 910
        },
        {
            "18923", {{11, 00}, 15, Januar, 2018}, {{12, 00}, 15, Januar, 2018}, 150
        },
        {
            "18923", {{12, 00}, 15, Januar, 2018}, {{13, 00}, 15, Januar, 2018}, 240
        },
        {
            "18923", {{13, 00}, 15, Januar, 2018}, {{14, 00}, 15, Januar, 2018}, 530
        },
        {
            "18923", {{14, 00}, 15, Januar, 2018}, {{15, 00}, 15, Januar, 2018}, 100
        },
        {
            "18923", {{15, 00}, 15, Januar, 2018}, {{16, 00}, 15, Januar, 2018}, 70
        },
        {
            "18923", {{16, 00}, 15, Januar, 2018}, {{17, 00}, 15, Januar, 2018}, 130
        },
        {
            "18923", {{17, 00}, 15, Januar, 2018}, {{18, 00}, 15, Januar, 2018}, 640
        },
        {
            "18923", {{18, 00}, 15, Januar, 2018}, {{19, 00}, 15, Januar, 2018}, 440
        },
        {
            "18923", {{19, 00}, 15, Januar, 2018}, {{20, 00}, 15, Januar, 2018}, 180
        },
        {
            "18923", {{20, 00}, 15, Januar, 2018}, {{21, 00}, 15, Januar, 2018}, 70
        },
        {
            "18923", {{21, 00}, 15, Januar, 2018}, {{22, 00}, 15, Januar, 2018}, 990
        },
        {
            "18923", {{22, 00}, 15, Januar, 2018}, {{23, 00}, 15, Januar, 2018}, 40
        },
        {
            "18923", {{23, 00}, 15, Januar, 2018}, {{24, 00}, 15, Januar, 2018}, 40
        }
    };

    printf("\n");

    savings = info_energy_saving2(meterdata_array, priser_array, tidspunkt, user_choice);
    printf("Hvis du flytter dit forbrug, sparer du: %.1f DKK\n\n", savings);

    cheapest_struct = *cheapest(priser_array);
    printf("Dato: %d , Klokkeslæt: %d - %d , Pris Område1: %.f DKK\n", cheapest_struct.from.day,
                                    cheapest_struct.from.time.hour, cheapest_struct.to.time.hour, cheapest_struct.DK1price);
    printf("\n");
    return 0;   
}

/* Funktionen returnerer besparelsen forbrugeren kan opnå hvis vedkommende flytter sit forbrug til det billigste tidspunkt 
 * Funktionen tager udgangspunkt i et 24 element-langt dat-array der samt et user_choice der afgører om det er DK1 eller DK2 vi kigger på */
double info_energy_saving2(meterdata forbrug_array[], pricedata priser_array[], int time_frame, user user_choice)
{
    double current_consumption = 0.0;
    double current_price = 0.0;
    double user_price_current = 0.0;
    double user_price_after = 0.0;
    double cheapest_price = 0.0;
    
    if (strcmp(user_choice.residence, "DK1") == 0)
    {   
        current_price = priser_array[time_frame].DK1price;
        printf("Nuværende pris: %.1f\n\n", current_price);
        current_consumption = forbrug_array[time_frame].value;
        printf("Nuværende forbrug: %.1f\n\n", current_consumption);

        if (current_price < 0)
            printf("Prisen er pt. negativ!\n");

        /* Dette giver brugerens nuværende strømpris baseret ud fra forbruget */
        user_price_current = current_consumption * KWH_TO_MWH * current_price;
        printf("Nuværende pris baseret på nuværende forbrug: %.1f DKK\n", user_price_current);

        /* Sorterer pris-array så den billigste pris ligger først */
        qsort(priser_array, NMB_OF_ELEMENTS, sizeof(pricedata), cmpfunc);
        cheapest_price = priser_array[0].DK1price;

        /* Dette giver brugerens strømpris baseret ud fra hvornår det er billigst at bruge strøm */
        user_price_after = current_consumption * KWH_TO_MWH * cheapest_price;
        printf("Den billigste pris for forbrugeren baseret på nuværende forbrug: %.1f DKK\n", user_price_after);
    }
    else 
    {
        current_price = priser_array[time_frame].DK2price;
        printf("Nuværende pris: %.1f\n\n", current_price);
        current_consumption = forbrug_array[time_frame].value;
        printf("Nuværende forbrug: %.1f\n\n", current_consumption);

        if (current_price < 0)
            printf("Prisen er pt. negativ!\n");

        /* Dette giver brugerens nuværende strømpris baseret ud fra forbruget */
        user_price_current = current_consumption * KWH_TO_MWH * current_price;
        printf("Nuværende pris baseret på nuværende forbrug: %.1f DKK\n", user_price_current);

        /* Sorterer pris-array så den billigste pris ligger først */
        qsort(priser_array, NMB_OF_ELEMENTS, sizeof(pricedata), cmpfunc);
        cheapest_price = priser_array[0].DK2price;

        /* Dette giver brugerens strømpris baseret ud fra hvornår det er billigst at bruge strøm */
        user_price_after = current_consumption * KWH_TO_MWH * cheapest_price;
        printf("Den billigste pris for forbrugeren baseret på nuværende forbrug: %.1f DKK\n", user_price_after);
    }

    if (user_price_after > user_price_current)
        return user_price_after - user_price_current;
    else
        return user_price_current - user_price_after;
} 

pricedata *cheapest(pricedata priser_array[])
{
    pricedata *cheapest;
    cheapest = (pricedata*)malloc(1 * sizeof(pricedata));

    qsort(priser_array, NMB_OF_ELEMENTS, sizeof(pricedata), cmpfunc);

    cheapest->from = priser_array[0].from;
    cheapest->to = priser_array[0].to;
    cheapest->DK1price = priser_array[0].DK1price;
    cheapest->DK2price = priser_array[0].DK2price;

    /* Informerer forbrugeren om hvorvidt det billigste tidspunkt er sent om aftenen */
    if (priser_array[0].from.time.hour > 21)
        printf("Det billigste tidspunkt er efter kl 21 om aftenen\n");

    return cheapest;
}

int cmpfunc(const void * a, const void * b)
{
    pricedata *priserA = (pricedata*)a;
    pricedata *priserB = (pricedata*)b;

    return priserA->DK1price - priserB->DK1price;
}

