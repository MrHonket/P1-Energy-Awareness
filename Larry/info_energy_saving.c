#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NMB_OF_ELEMENTS 4
#define KWH_TO_MWH 0.001

/* TID */
typedef enum {Man, Tir, Ons, Tor, Fre, Lor, Son} ugedag;
typedef enum{januar,februar, marts, april, maj, juni, juli, august, september, oktober, november, december} maaned;

typedef struct {
   int hour;
   int min;   
} klokkeslet;

typedef struct{
   klokkeslet time;
   int  day;
   maaned month;
   int  year;
} dato;

const char *ugedag_txt[] = {
   "Mandag",
   "Tirsdag",
   "Onsdag",
   "Torsdag",
   "Fredag",
   "Lordag",
   "Sondag"
};

const char *maaned_txt[] = {
   "januar",
   "februar",
   "marts",
   "april",
   "maj",
   "juni",
   "juli",
   "august",
   "september",
   "oktober",
   "november",
   "december"
};

/* METERDATA - amount målt i KWH */
typedef struct {
   int   id;
   dato  fra;
   dato  til;
   float amount;
} meterdata;

/* PRISER - målt ud fra DKK/MWH */
typedef struct {
    dato from;
    dato to; 
    double price_area1;
    double price_area2;
} priser;

typedef struct{
    int id;
    char residence[5];
    char language[5];
    int choice_of_function;
    int user_type;
} user;


double info_energy_saving(meterdata forbrug_array[], priser priser_array[], int time_frame);
double info_energy_saving2(meterdata forbrug_array[], priser priser_array[], int time_frame, user user_choice);
priser *cheapest(priser priser_array[], int time_frame);
int cmpfunc(const void * a, const void * b);


int main(void)
{
    double savings;
    double savings2;
    priser cheapest_struct;
    user user_choice = {1200, "DK1", "Dansk", 2, 1};

    priser priser_array[4] = {
        {
            {{20, 00}, 15, januar, 2018}, {{21, 00}, 15, januar, 2018}, 199.34, 89.50
        },
        {
            {{21, 00}, 15, januar, 2018}, {{22, 00}, 15, januar, 2018}, 178.34, 80.50
        },
        {
            {{22, 00}, 15, januar, 2018}, {{23, 00}, 15, januar, 2018}, 165.34, 75.50
        },
        {
            {{23, 00}, 15, januar, 2018}, {{24, 00}, 15, januar, 2018}, 100.34, 53.50
        }
    };
    
    meterdata meterdata_array[4] = {
        {
            18928, {{20, 00}, 15, januar, 2018}, {{21, 00}, 15, januar, 2018}, 440
        },
        {
            18921, {{21, 00}, 15, januar, 2018}, {{22, 00}, 15, januar, 2018}, 303
        },
        {
            18924, {{22, 00}, 15, januar, 2018}, {{23, 00}, 15, januar, 2018}, 275
        },
        {
            18923, {{23, 00}, 15, januar, 2018}, {{24, 00}, 15, januar, 2018}, 127
        }
    };

    printf("\n");
    /* printf("Pris område1: %.1f Pris område2: %.1f\n", data.price_area1, data.price_area2);*/

    /* savings = info_energy_saving(meterdata_array, priser_array, 0);
    printf("Hvis du flytter dit forbrug, sparer du: %.1f DKK\n\n", savings);*/

    savings2 = info_energy_saving2(meterdata_array, priser_array, 0, user_choice);
    printf("Hvis du flytter dit forbrug, sparer du: %.1f DKK\n\n", savings2);

    cheapest_struct = *cheapest(priser_array, 0);
    printf("Dato: %d , Klokkeslæt: %d - %d , Pris Område1: %.f DKK\n", cheapest_struct.from.day,
                                    cheapest_struct.from.time.hour, cheapest_struct.to.time.hour, cheapest_struct.price_area1);

    printf("\n");
    return 0;   
}

/* Funktionen returnerer besparelsen forbrugeren kan opnå hvis vedkommende flytter sit forbrug til det billigste tidspunkt 
 * Funktionen tager udgangspunkt i et 24 element-langt dat-array der samt et user_choice der afgører om det er DK1 eller DK2 vi kigger på */
double info_energy_saving2(meterdata forbrug_array[], priser priser_array[], int time_frame, user user_choice)
{
    double current_consumption = 0.0;
    double current_price = 0.0;
    double user_price_current = 0.0;
    double user_price_after = 0.0;
    double cheapest_price = 0.0;
    
    if (strcmp(user_choice.residence, "DK1") == 0)
    {   
        current_price = priser_array[time_frame].price_area1;
        current_consumption = forbrug_array[time_frame].amount;

        if (current_price < 0)
            printf("Prisen er pt. negativ!\n");

        /* Dette giver brugerens nuværende strømpris baseret ud fra forbruget */
        user_price_current = current_consumption * KWH_TO_MWH * current_price;
        printf("Nuværende pris baseret på nuværende forbrug: %.1f DKK\n", user_price_current);

        /* Sorterer pris-array så den billigste pris ligger først */
        qsort(priser_array, NMB_OF_ELEMENTS, sizeof(priser), cmpfunc);
        cheapest_price = priser_array[0].price_area1;

        /* Dette giver brugerens strømpris baseret ud fra hvornår det er billigst at bruge strøm */
        user_price_after = current_consumption * KWH_TO_MWH * cheapest_price;
        printf("Den billigste pris for forbrugeren baseret på nuværende forbrug: %.1f DKK\n", user_price_after);
    }
    else 
    {
        current_price = priser_array[time_frame].price_area2;
        current_consumption = forbrug_array[time_frame].amount;

        if (current_price < 0)
            printf("Prisen er pt. negativ!\n");

        /* Dette giver brugerens nuværende strømpris baseret ud fra forbruget */
        user_price_current = current_consumption * KWH_TO_MWH * current_price;
        printf("Nuværende pris baseret på nuværende forbrug: %.1f DKK\n", user_price_current);

        /* Sorterer pris-array så den billigste pris ligger først */
        qsort(priser_array, NMB_OF_ELEMENTS, sizeof(priser), cmpfunc);
        cheapest_price = priser_array[0].price_area2;

        /* Dette giver brugerens strømpris baseret ud fra hvornår det er billigst at bruge strøm */
        user_price_after = current_consumption * KWH_TO_MWH * cheapest_price;
        printf("Den billigste pris for forbrugeren baseret på nuværende forbrug: %.1f DKK\n", user_price_after);
    }

    if (user_price_after > user_price_current)
        return user_price_after - user_price_current;
    else
        return user_price_current - user_price_after;
} 

priser *cheapest(priser priser_array[], int time_frame)
{
    priser *cheapest;
    cheapest = (priser*)malloc(1 * sizeof(priser));

    qsort(priser_array, NMB_OF_ELEMENTS, sizeof(priser), cmpfunc);

    cheapest->from = priser_array[0].from;
    cheapest->to = priser_array[0].to;
    cheapest->price_area1 = priser_array[0].price_area1;
    cheapest->price_area2 = priser_array[0].price_area2;

    /* Informerer forbrugeren om hvorvidt det billigste tidspunkt er sent om aftenen */
    if (priser_array[0].from.time.hour > 21)
        printf("Det billigste tidspunkt er efter kl 21 om aftenen\n");

    return cheapest;
}


int cmpfunc(const void * a, const void * b)
{
    priser *priserA = (priser*)a;
    priser *priserB = (priser*)b;

    return priserA->price_area1 - priserB->price_area1;
}

