#ifndef EVENTS_H
#define EVENTS_H


#include <stdio.h>
#include "generation_no_fit.h"
#include "generation_fit.h"
#include "maturity.h"

void delete_groups(int groups_to_delete,int num_of_generation);

void insert_groups(int groups_to_insert,float lamda,int num_of_generation,int num_of_parents,int fitness,int row_swapping,int min_count,int max_count,double mutation_rate,gsl_rng *r);

#endif
