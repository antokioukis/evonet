#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include "structs.h"
#include "mathss.h"
#include "creators.h"
#include "maturity.h"
#include "generation_no_fit.h"
#include "generation_fit.h"
#include "events.h"
#include "extract.h"

void print_dump(int num_of_generation){
    int i,j,k,l;
    group *temp=generation_array[num_of_generation]->groups_list;
    while(temp!=NULL){
        printf("Number of group: %d\n",i);
        for(j=0;j<persons_per_group;j++){
            printf("Id atomou: %d\n",temp->person_in_group[j]->id);
            printf("Fitness atomou: %f\n",temp->person_in_group[j]->fitness);
            printf("Gene dependancies matrix:\n");
            for(l=0;l<genes_per_person;l++){
                for(k=0;k<genes_per_person;k++){
                    printf("%f ",temp->person_in_group[j]->gene_interactions[l][k]);
                }
                printf("\n");
            }
            printf("R1-R2 atomou\n");
            for(l=0;l<genes_per_person;l++){
                printf("R1 %d R2 %d\n",temp->person_in_group[j]->gene_R1[l],temp->person_in_group[j]->gene_R2[l]);
            }
            for(l=0;l<genes_per_person;l++){
                printf("Gene Counts %d\n",temp->person_in_group[j]->gene_counts[l]);
            }
            printf("\n");
        }
        i++;
        temp=temp->next;
    }
}

void create_generations(int fitness,int num_of_parents,int number_of_groups_wanted){
    int i;
    for(i=0;i<max_generations;i++){
        if(i==0){
            generation_array[0]=create_population(number_of_groups_wanted);
        }
        
        else{
            printf("Creating Generation %d\n",i);
            if(fitness){
                generation_array[i]=create_gen_population_fit(i,num_of_parents);
            }
            else{
                generation_array[i]=create_gen_population_no_fit(i,num_of_parents);
            }
        }
            mature_generation(generation_array[i]);
            calculate_fitness(i);
             printf("Fitness_of_Generation %d: %f (pososto) \n",i,generation_array[i]->sum_of_fitness/(curr_num_of_groups*persons_per_group));
            extract_gene_dependancies_matrix_generation(i);
    }
}



int main(void){
    srand (time(NULL));
    /*
    1o orisma
    orisma 1 gia fitness based parent selection
    orisma 2 gia random parents
    */
    /*
    2o orisma
    orisma 1 gia sindiasmo gonewn
    orisma 0 gia autousia gene dependancies apo 1 gonea
    */
    /*3o orisma
    number of groups wanted
    */
    create_generations(1,1,5);
    /*extract_generation(generation_array[1]);*/

    return 0;
}
