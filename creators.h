#ifndef CREATORS_H
#define CREATORS_H


#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include "mathss.h"

person *create_mutations(person *individual,double mu);

float create_gene_interactions(int R1,int R2);

/*return pointer to new group. New group is array of pointers to persons.*/
group *create_group(int group_num,int min_gene_R1R2, int max_gene_R1R2,int min_count,int max_count);

/*return pointer to new population. New population is array of pointers to groups.*/
population *create_population(int groups_wanted, int min_gene_R1R2, int max_gene_R1R2,int min_count,int max_count,int robust_or_not);
#endif
