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
    int i=0;
    int j=0;
    group *temp=generation_array[num_of_generation]->groups_list;
    while(temp!=NULL){
        printf("Number of group: %d\n",i);
        for(j=0;j<persons_per_group;j++){
            printf("Id atomou: %d\n",temp->person_in_group[j]->id);
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
            if(fitness) printf("Fitness_of_Generation %d: %f \n",i,generation_array[i]->sum_of_fitness);
    }
}



int main(void){
    int i;
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
    create_generations(1,1,10);
    extract_generation(generation_array[1]);

/*    calculate_fitness(1);
    printf("fitness of 0 %f\n",generation_array[0]->sum_of_fitness);

    create_event(0,3,0);
    calculate_fitness(1);
    printf("fitness of 0 %f\n",generation_array[0]->sum_of_fitness);

    generation_array[1]=create_gen_population_fit(1,1);
    mature_generation(generation_array[1]);
    calculate_fitness(2);
    printf("fitness of 1 %f\n",generation_array[1]->sum_of_fitness);

    generation_array[2]=create_gen_population_fit(2,1);
    mature_generation(generation_array[2]);
    calculate_fitness(3);
    printf("fitness of 2 %f\n",generation_array[2]->sum_of_fitness);

    create_event(1,3,2);
    calculate_fitness(3);
    printf("fitness of 2 %f\n",generation_array[2]->sum_of_fitness);

*/
    
    return 0;
}
