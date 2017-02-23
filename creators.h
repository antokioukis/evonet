#ifndef CREATORS_H
#define CREATORS_H


#include "mathss.h"

char *create_genotype(int R1[max_genes_per_person],int R2[max_genes_per_person]);

person *deep_copy_person(person *destination,person *arrival);

person *create_mutations(person *individual,double mu,gsl_rng *r);

float create_gene_interactions(int R1,int R2);

person *create_person(int id,int min_gene_R1R2, int max_gene_R1R2,int min_count,int max_count,int R1R2_matrix[max_genes_per_person][1]);

/*return pointer to new group. New group is array of pointers to persons.*/
group *create_group(int group_num,int min_gene_R1R2, int max_gene_R1R2,int min_count,int max_count,int R1R2_matrix[persons_per_group*max_genes_per_person][1]);

/*return pointer to new population. New population is array of pointers to groups.*/
population *create_population(int groups_wanted, int min_gene_R1R2, int max_gene_R1R2,int min_count,int max_count,int robust_or_not,FILE *start_in);

person *create_mutations(person *foreigner,double mu,gsl_rng *r);

auxiliary_genotype_data *create_genotype_hash(population *new_population);
#endif
