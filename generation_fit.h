#ifndef GENERATION_FIT_H
#define GENERATION_FIT_H

#include <assert.h>
#include <stdio.h>
#include "creators.h"

void calculate_fitness(int num_of_gen,float lamda);


R1_R2_auxiliary *choose_fitted_father_dependencies_no_combinations(int num_of_gen);

R1_R2_auxiliary *choose_fitted_father_dependencies_combined_R1R2_swapping(int num_of_gen);

R1_R2_auxiliary* choose_fitted_father_dependencies_combined_row_swapping(int num_of_gen);


person *gen_create_person_fit(int id,int num_of_gen, int num_of_parents,int row_swapping,int min_count,int max_count,double mutation_rate);

group *gen_create_group_fit(int starting_id,int num_of_gen, int num_of_parents,int row_swapping,int min_count,int max_count,double mutation_rate);


population *create_gen_population_fit(int num_of_gen, int num_of_parents,int row_swapping,int min_count,int max_count,double mutation_rate);
#endif
