#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_math.h>

#include "structs.h"
#include "mathss.h"
#include "creators.h"
#include "maturity.h"
#include "generation_nofit.h"
#include "generation_fit.h"

void print_dump(population *new_population){
    int i,j;
    int l,k;

    for(k=0;k<num_of_groups;k++){
        for(l=0;l<persons_per_group;l++){

            printf("ID Atomou %d\n",new_population->group_in_population[k]->person_in_group[l]->id);
            printf("Maturity Atomou %d\n",new_population->group_in_population[k]->person_in_group[l]->mature);
            printf("Fitness Atomou %f\n",new_population->group_in_population[k]->person_in_group[l]->fitness);

            printf("Gene Counts\n");
            for(i=1;i<genes_per_person;i++){
                printf(" %d ",new_population->group_in_population[k]->person_in_group[l]->gene_counts[i]);
            }printf("\n");

            printf("Vector of Signs\n");
            for(i=1;i<genes_per_person;i++){
                printf(" %d ",new_population->group_in_population[k]->person_in_group[l]->vector_of_signs[i]);
            }printf("\n");

            printf("Pinakas Dependancies\n");
            for(i=0;i<genes_per_person;i++){
                for(j=0;j<genes_per_person;j++){
                    printf(" %f ",new_population->group_in_population[k]->person_in_group[l]->gene_interactions[i][j]);
                }printf("\n");
            }

        }
    }
}

void create_generations(int fitness){
    int i;
    for(i=0;i<max_generations;i++){
        if(i==0){
            generation_array[i]=create_population();
        }
        else{
            printf("Creating Generation %d\n",i);
            if(fitness){
                generation_array[i]=create_gen_population_fit(i);
                printf("Fitness_of_Generation %d: %f \n",i-1,generation_array[i-1]->sum_of_fitness);
            }
            else{
                generation_array[i]=create_gen_population_nofit(i);
            }
        }
        mature_generation(generation_array[i]);
        printf("Generation %d Mature\n",i);
    }
}

int main(void){
    srand (time(NULL));
    /*
    orisma 1 gia inheritance based on fitness
    orisma 0 gia random inheritance
    */
    create_generations(1);
    return 1;
}
