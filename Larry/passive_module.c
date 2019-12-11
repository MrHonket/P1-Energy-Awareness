/* switch module */
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char residence[5];
    char language[5];
    int choice_of_function;
    int user_type;
}choices;

typedef struct {
    int price;
}data;

int passive_module(choices user_choices, data user_data);
void energy_saving(choices user_choices, data user_data);
void machine_activation(choices user_choices, data user_data);

int main(void)
{
   choices user_choices;
   data user_data;

   passive_module(user_choices, user_data);

   return 0;
}

/* returns 1 for exit_succes and 0 for exit_failure */
int passive_module(choices user_choices, data user_data)
{
   if(user_choices.choice_of_function == 1)
      {
      energy_saving(user_choices, user_data);
      return 1;
      }
   else if(user_choices.choice_of_function == 2)
      {
      machine_activation(user_choices, user_data);
      return 1;  
      }
   else
      return 0;

}

