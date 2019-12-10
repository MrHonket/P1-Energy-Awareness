#include <stdio.h>
#include <stdlib.h>

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

double info_energy_saving(meterdata forbrug_array[], priser priser_array[], int time_frame);
priser *cheapest(priser priser_array[], int time_frame);
int cmpfunc(const void * a, const void * b);


int main(void)
{
    double savings;
    priser cheapest_struct;

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

    savings = info_energy_saving(meterdata_array, priser_array, 0);
    printf("Hvis du flytter dit forbrug, sparer du: %.1f DKK\n\n", savings);

    cheapest_struct = *cheapest(priser_array, 0);
    printf("Dato: %d , Klokkeslæt: %d - %d , Pris Område1: %.f DKK\n", cheapest_struct.from.day,
                                    cheapest_struct.from.time.hour, cheapest_struct.to.time.hour, cheapest_struct.price_area1);

    printf("\n");
    return 0;   
}

/* Jeg ønsker at gå ind i et array af priser og finde den billigste pris samt det tidspunkt på døgnet det gælder */
double info_energy_saving(meterdata forbrug_array[], priser priser_array[], int time_frame)
{
    double current_consumption;
    double current_price;
    double user_price_current;
    double user_price_after;
    double cheapest_price;

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

    /* Informerer forbrugren om hvorvidt det billigste tidspunkt er sent om aftenen */
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


 /* printf("Gokkeslæt fra: %d.%d\n", data.from.time.hour, data.from.time.min);
    printf("Dato fra: %d\n", data.from.day);
    printf("Måned: %s\n", maaned_txt[data.from.month]);
    printf("Årstal: %d\n", data.from.year);

    printf("\n");
    printf("Gokkeslæt til: %d.%d\n", data.to.time.hour, data.to.time.min);
    printf("Dato til: %d\n", data.to.day);
    printf("Måned: %s\n", maaned_txt[data.to.month]);
    printf("Årstal: %d\n", data.to.year);


    printf("\n");
    printf("Mængde: %.1f\n", info.amount);
*/


/* Structs
priser data = 
    {
        {{20, 00}, 15, januar, 2018}, {{21, 00}, 15, januar, 2018}, 196.34, 34.50
    };
    
    meterdata info =
    {
        18928, {{20, 00}, 15, januar, 2018}, {{20, 00}, 15, januar, 2018}, 127.3
    };
 */
