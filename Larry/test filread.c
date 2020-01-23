#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {DK,DM}min_enum;
typedef struct {int tal,min_enum en }min_struct;

int main(void){
    min_struct st;
    st.min_enum = DM;
    st.tal = 24;

    FILE *f;
    f = fopen("settings.txt", "w+b");
    fwrite(&st,sizeof(min_struct),1,f);
    fclose(f);

    st.min_enum = DK;
    st.tal = 234567;

    printf("%d  %d",st.min_enum,st.tal);

    }