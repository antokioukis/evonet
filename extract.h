#ifndef EXTRACT_H
#define EXTRACT_H

#include <stdio.h>
#include "structs.h"

int calculate_open_non_net(int vector[max_genes_per_person],int key_genes);

void extract_open_non_network(population *new_population,int key_genes);

void extract_R1R2_generation(FILE *f1,FILE *f2, int num_of_gen);

void extract_discrete_generation(FILE *f, int num_of_gen);

void extract_gene_dependancies_matrix_generation(FILE* f, int num_of_gen);

void extract_gene_counts_generation(FILE *f, int num_of_gen);

void extract_fitness_generation(FILE *f, float generation_fitness);

void extract_robustness(FILE *f,population *new_population,FILE *d);

void* extract_neutRegion1_generation(void *auxialiary);

void extract_father(FILE *f,int father_number1, int father_number2);

void extract_father_fitness(int num_of_gen,int actual_num);

void extract_genotype_occ(FILE *f,auxiliary_genotype_data *genotype_data);

#endif
