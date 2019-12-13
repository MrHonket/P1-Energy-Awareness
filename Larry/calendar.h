#ifndef CALENDAR_H
#define CALENDAR_H

#include <stdio.h>
#include <stdlib.h>
#include "global.h"


/* Funktion prototypes */

int hours_between (dato d1, dato d2);
int days_between(dato from, dato to);
int months_between(dato d1, dato d2);
int days_in_month(dato d);
dato next_hour(dato d);
dato next_day(dato d);
void prnt_date(dato);

#endif