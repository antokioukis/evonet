#ifndef GENERATION_NO_FIT_H
#define GENERATION_NO_FIT_H
#include "extract.h"
#include "creators.h"

R1_R2_auxiliary *choose_random_father_dependencies_combined_R1R2_swapping(int num_of_gen,FILE *f,FILE *d);

R1_R2_auxiliary *choose_random_father_dependencies_combined_row_swapping(int num_of_gen,FILE *f,FILE *d);


R1_R2_auxiliary *choose_random_father_dependencies_no_combinations(int num_of_gen,FILE *f,FILE *d);

person *gen_create_person_no_fit(int id,int num_of_gen, int num_of_parents,int row_swapping,int min_count,int max_count,
                    double mutation_rate,gsl_rng *r,int recomb_rate,FILE *f,FILE *d);

group *gen_create_group_no_fit(int starting_id,int num_of_gen, int num_of_parents,int row_swapping,int min_count,int max_count,double mutation_rate,
	gsl_rng *r,int recomb_rate,FILE *f,FILE *d);

population *create_gen_population_no_fit(int num_of_gen, int num_of_parents,int row_swapping,int min_count,int max_count,
	double mutation_rate,gsl_rng *r,int recomb_rate,FILE *f,FILE *d);

void extract_father_id(FILE *f,int father_number1, int father_number2);

void extract_mutation_array(FILE *f,person *father1,person *father2);


#endif
