#ifndef ROBUSTNESS_H
#define ROBUSTNESS_H

#include <stdio.h>
#include "creators.h"
#include "maturity.h"
#include "extract.h"


person *deep_copy_person_robust(person *temp_robust_person,person *temp_normal_person);

person *create_specific_mutations(person *individual,int num_of_mutations,int last_bit, int other_bits);

void check_robustness(FILE *robustOutput, population *new_population, int num_of_mutations, int last_bit, int other_bits);
#endif
