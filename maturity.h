#ifndef MATURITY_H
#define MATURITY_H

#include <stdio.h>
#include "mathss.h"

void create_maturity_step(person *individual,int step,FILE *steps,FILE *period, int robust_or_not);

bool check_population_mature(population *new_population);

void mature_generation(population *new_population,int robust_or_not);
#endif
