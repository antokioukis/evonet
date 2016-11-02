#ifndef GENERATION_NO_FIT_H
#define GENERATION_NO_FIT_H

#include "creators.h"

R1_R2_auxiliary *choose_random_father_dependencies_combined_R1R2_swapping(int num_of_gen);

R1_R2_auxiliary *choose_random_father_dependencies_combined_row_swapping(int num_of_gen);


R1_R2_auxiliary *choose_random_father_dependencies_no_combinations(int num_of_gen);

group *gen_create_group_no_fit(int starting_id,int num_of_gen, int num_of_parents,int row_swapping,int min_count,int max_count,double mutation_rate,gsl_rng *r);

population *create_gen_population_no_fit(int num_of_gen, int num_of_parents,int row_swapping,int min_count,int max_count,double mutation_rate,gsl_rng *r);
#endif
