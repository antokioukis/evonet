#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#include "structs.h"
#include "mathss.h"
#include "creators.h"
#include "maturity.h"
#include "generation_nofit.h"
#include "generation_fit.h"
#include "deletes.h"

clock_t begin, end;
double time_spent;

void print_dump(population *new_population){
    int i,j;
    int l,k;

    for(k=0;k<num_of_groups;k++){
        for(l=0;l<persons_per_group;l++){
            if(new_population->group_in_population[k]->person_in_group[l]->id!=-100){
                printf("ID Atomou %d\n",new_population->group_in_population[k]->person_in_group[l]->id);
    /*            printf("Maturity Atomou %d\n",new_population->group_in_population[k]->person_in_group[l]->mature);
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
         */   }
        }
    }
}

void create_generations(int fitness,int num_of_parents){
    int i;
    for(i=0;i<max_generations;i++){
        if(i==0){
            printf("Creating Generation 0\n");
            generation_array[i]=create_population();
            printf("Fitness_of_Generation 0: Not calculated \n");
        }
        else{
            printf("Creating Generation %d\n",i);
            if(fitness){
                generation_array[i]=create_gen_population_fit(i,num_of_parents);
                printf("Fitness_of_Generation %d: %f \n",i,generation_array[i-1]->sum_of_fitness);
            }
            else{
                generation_array[i]=create_gen_population_nofit(i,num_of_parents);
            }
        }
        if(fitness==0){
            mature_generation(generation_array[i]);
        }
        else{
            threaded_mature_generation(generation_array[i]);
        }
        printf("Generation %d Mature\n",i);
    }
}

int main(void){
  /*  begin = clock(); */

    srand (time(NULL));
    /*
    1o orisma
    orisma 1 gia inheritance based on fitness
    orisma 0 gia random inheritance
    */
    /*
    2o orisma
    orisma 1 gia sindiasmo gonewn
    orisma 0 gia autousia gene dependancies apo 1 gonea
    */

    create_generations(1,1);

 /*   end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time spent %f:\n",time_spent);
*/
/*
    print_dump(generation_array[0]);
    delete_population(generation_array[0],2);
    print_dump(generation_array[0]);
    create_new_population(generation_array[0],1);
    print_dump(generation_array[0]);

*/
    return 1;
}
