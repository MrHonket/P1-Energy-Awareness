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
void print_information(data return_array[], data cheapest_struct, user User);
void dialog_with_user(data data_array[], user User, double info, data cheapest_struct);

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
        qsort(data_array, NMB_OF_ELEMENTS, sizeof(data), cmpfunc);
        cheapest_price = data_array[0].prize.DK1price;

        /* Dette giver brugerens strømpris baseret ud fra hvornår det er billigst at bruge strøm */
        user_price_after = current_consumption * KWH_TO_MWH * cheapest_price;
        printf("Din pris, hvis du vælger at flytte dit forbrug: %.2f DKK\n\n", user_price_after);
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
        qsort(data_array, NMB_OF_ELEMENTS, sizeof(data), cmpfunc);
        cheapest_price = data_array[0].prize.DK2price;
        printf("Den billigste pris er: %.2f\n", cheapest_price);

        /* Dette giver brugerens strømpris baseret ud fra hvornår det er billigst at bruge strøm */
        user_price_after = current_consumption * KWH_TO_MWH * cheapest_price;
        printf("Din pris, hvis du vælger at flytte dit forbrug: %.2f DKK\n\n", user_price_after);
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
    
    qsort(data_array, NMB_OF_ELEMENTS, sizeof(data), cmpfunc);

    cheapest->prize.from = data_array[0].prize.from;
    cheapest->prize.to = data_array[0].prize.to;
    cheapest->prize.DK1price = data_array[0].prize.DK1price;
    cheapest->prize.DK2price = data_array[0].prize.DK2price;

    printf("Det billigste tidspunkt at forbruge din strøm vil være: \n--------------------------------------------------------\n");

    if (strcmp(User.settings.residence, "DK1") == 0)
        printf("Dato: %d | Klokkeslæt: %d - %d | Pris DK1: %.2f DKK |\n\n", cheapest->prize.from.day,
                         cheapest->prize.from.time.hour, cheapest->prize.to.time.hour, cheapest->prize.DK1price);
    else       
        printf("Dato: %d | Klokkeslæt: %d - %d | Pris DK2: %.2lf DKK |\n\n", cheapest->prize.from.day,
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
        printf("Nuværende pris: %.2f DKK\n\n", return_array[User.choice.from.time.hour].prize.DK1price); 
        printf("Nuværende forbrug: %.2f KWH \n\n", return_array[User.choice.from.time.hour].meter.value); 
        printf("Nuværende pris baseret på nuværende forbrug: %.2f DKK\n\n", user_price); 
    }
    else
    {
        user_price = return_array[User.choice.from.time.hour].meter.value * KWH_TO_MWH * return_array[User.choice.from.time.hour].prize.DK2price;
        printf("Nuværende pris: %.2f\n\n", return_array[User.choice.from.time.hour].prize.DK2price); 
        printf("Nuværende forbrug: %.2f\n\n", return_array[User.choice.from.time.hour].meter.value); 
        printf("Nuværende pris baseret på nuværende forbrug: %.2f DKK\n\n", user_price); 
    }
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


void dialog_with_user(data data_array[], user User, double info, data cheapest_struct)
{
    int choice;
    printf("Velkommen ti modulet energibesparelser! Du har nu to valgmuligheder:\n");
    printf("1. Informér mig om hvad strømmen koster for en given time og hvornår på døgnet det er billigst\n");
    printf("2. Fortæl mig hvad strømmen koster i et givent tidsrum\n");

    scanf(" %d", &choice);

    switch(choice){
        case 1: 
            print_information(data_array, cheapest_struct, User);
            info = info_energy_saving(User, data_array);
            cheapest_struct = *cheapest(data_array, User);
            printf("Din besparelse bliver: %.5f DKK\n", info);
            printf("--------------------------------------------------------\n\n");
            break;
    }
}







