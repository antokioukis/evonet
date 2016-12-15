#ifndef GENERATION_NO_FIT_H
#define GENERATION_NO_FIT_H
#include "extract.h"
#include "creators.h"

R1_R2_auxiliary *choose_random_father_dependencies_combined_R1R2_swapping(int num_of_gen,FILE *f);

R1_R2_auxiliary *choose_random_father_dependencies_combined_row_swapping(int num_of_gen,FILE *f);


R1_R2_auxiliary *choose_random_father_dependencies_no_combinations(int num_of_gen,FILE *f);

group *gen_create_group_no_fit(int starting_id,int num_of_gen, int num_of_parents,int row_swapping,int min_count,int max_count,double mutation_rate,
	gsl_rng *r,FILE *f);

population *create_gen_population_no_fit(int num_of_gen, int num_of_parents,int row_swapping,int min_count,int max_count,
	double mutation_rate,gsl_rng *r,FILE *f);
#endif
