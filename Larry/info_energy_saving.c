#include <stdio.h>
#include <stdlib.h>

#define NMB_OF_ELEMENTS 4

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

/* METERDATA */
typedef struct {
   int   id;
   dato  fra;
   dato  til;
   float amount;
} meterdata;


typedef struct {
    dato from;
    dato to; 
    double price_area1;
    double price_area2;
    struct priser *next;
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
            18928, {{20, 00}, 15, januar, 2018}, {{21, 00}, 15, januar, 2018}, 250.32
        },
        {
            18928, {{21, 00}, 15, januar, 2018}, {{22, 00}, 15, januar, 2018}, 203.40
        },
        {
            18928, {{22, 00}, 15, januar, 2018}, {{23, 00}, 15, januar, 2018}, 175.33
        },
        {
            18928, {{23, 00}, 15, januar, 2018}, {{24, 00}, 15, januar, 2018}, 127.30
        }
    };


    /* printf("Pris område1: %.1f Pris område2: %.1f\n", data.price_area1, data.price_area2);*/

    /*savings = info_energy_saving(meterdata_array, priser_array, 0);
    printf("Besparelse: %.1f\n", savings);*/

    cheapest_struct = *cheapest(priser_array, 0);
    printf("Dato: %d , Klokkeslæt: %d - %d , Pris Område1: %.f\n", cheapest_struct.from.day,
                                                  cheapest_struct.from.time.hour, cheapest_struct.to.time.hour, cheapest_struct.price_area1);

    return 0;
}


/* Jeg ønsker at gå ind i et array af priser og finde den billigste pris samt det tidspunkt på døgnet det gælder */
double info_energy_saving(meterdata forbrug_array[], priser priser_array[], int time_frame)
{
    int saving = 0;
    int time = 0;
    int median = 0;

    qsort(priser_array, NMB_OF_ELEMENTS, sizeof(priser), cmpfunc);
    /* printf("Median = %.1f\n", priser_array[NMB_OF_ELEMENTS/2].price_area1);
    median = priser_array[NMB_OF_ELEMENTS/2].price_area1;*/

    saving = priser_array[0].price_area1;
    return saving;
}


priser *cheapest(priser priser_array[], int time_frame)
{
    priser *cheapest;
    cheapest = (priser*)malloc(1 * sizeof(priser));

    qsort(priser_array, NMB_OF_ELEMENTS, sizeof(priser), cmpfunc);
    /* printf("Median = %.1f\n", priser_array[NMB_OF_ELEMENTS/2].price_area1);
    median = priser_array[NMB_OF_ELEMENTS/2].price_area1;*/

    cheapest->from = priser_array[time_frame].from;
    cheapest->to = priser_array[time_frame].to;
    cheapest->price_area1 = priser_array[time_frame].price_area1;
    cheapest->price_area2 = priser_array[time_frame].price_area2;

    return cheapest;
}







int cmpfunc(const void * a, const void * b)
{
    priser *priserA = (priser*)a;
    priser *priserB = (priser*)b;

    return priserB->price_area1 - priserA->price_area2;
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
