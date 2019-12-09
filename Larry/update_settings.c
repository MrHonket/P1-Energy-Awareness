#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void update_settings(void);

int main ()
{

    update_settings();

  
    return(0);
}

void update_settings(void)
{
    FILE *f;
    char location[20];

    printf("What's the location of your house? Enter DK1 for Jutland and Fyn or DK2 for Sealand: ");
    scanf(" %3s", location);

    f = fopen(" settings.txt", "w");
    fwrite(location, 1, sizeof(location),f);

    fclose(f);
}
