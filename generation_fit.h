#ifndef GENERATION_FIT_H
#define GENERATION_FIT_H

#include <assert.h>
#include <stdio.h>
#include "extract.h"
#include "creators.h"

void calculate_fitness(int num_of_gen,float lamda);

R1_R2_auxiliary *choose_fitted_father_dependencies_no_combinations(int num_of_gen, int id,FILE *f);

R1_R2_auxiliary *choose_fitted_father_dependencies_combined_R1R2_swapping(int num_of_gen,FILE *f);

R1_R2_auxiliary* choose_fitted_father_dependencies_combined_row_swapping(int num_of_gen,FILE *f);


person *gen_create_person_fit(int id,int num_of_gen, int num_of_parents,int row_swapping,int min_count,int max_count,double mutation_rate,gsl_rng *r,FILE *f);

group *gen_create_group_fit(int starting_id,int num_of_gen, int num_of_parents,int row_swapping,int min_count,int max_count,double mutation_rate,gsl_rng *r,FILE *f);


population *create_gen_population_fit(int num_of_gen, int num_of_parents,int row_swapping,int min_count,int max_count,double mutation_rate,gsl_rng *r,FILE *f);

void mutate_population(population *pop, double mu, gsl_rng *r);

void create_mutation_vector(int num_of_gen, int agene);

void extract_father(FILE *f,int father_number1, int father_number2);

#endif
