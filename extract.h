#ifndef EXTRACT_H
#define EXTRACT_H

#include <stdio.h>
#include "structs.h"

void extract_R1R2_generation(FILE *f1,FILE *f2, int num_of_gen);

void extract_discrete_generation(FILE *f, int num_of_gen);

void extract_gene_dependancies_matrix_generation(FILE* f, int num_of_gen);

void extract_gene_counts_generation(FILE *f, int num_of_gen);

void extract_fitness_generation(FILE *f, int num_of_gen);

void extract_robustness(FILE *f,population *new_population);

void* extract_neutRegion1_generation(void *auxialiary);

#endif
