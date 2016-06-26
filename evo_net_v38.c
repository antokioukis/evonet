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

void create_generations(int fitness,int num_of_parents,int number_of_groups_wanted,int row_swapping,
                        int min_gene_R1R2,int max_gene_R1R2,int freq,
                        int event,int event1,int event2,int event3, int event4){
    int i;
    int type_of_event;
    int num_of_groups_affected;
    for(i=0;i<max_generations;i++){
        if(i==0){
            generation_array[0]=create_population(number_of_groups_wanted,min_gene_R1R2,max_gene_R1R2);
        }
        
        else{
            /*printf("Creating Generation %d\n",i);*/

            if(fitness){
                generation_array[i]=create_gen_population_fit(i,num_of_parents,row_swapping);
            }
            else{
                generation_array[i]=create_gen_population_no_fit(i,num_of_parents,row_swapping);
            }
        }
        mature_generation(generation_array[i]);
        calculate_fitness(i);
        if(event){
            if(i==event1||i==event2||i==event3||i==event4){
                printf("type of event?(0=death of groups, 1= creation of new groups)\n");
                scanf("%d", &type_of_event);
                printf("enter number of groups affected\n");
                scanf("%d", &num_of_groups_affected);
                create_event(type_of_event,num_of_groups_affected,i,num_of_parents,fitness,row_swapping);
            }
        }
        if(i%freq==0){    
            printf("Fitness_of_Generation %d: %f (pososto) \n",i,generation_array[i]->sum_of_fitness/(curr_num_of_groups*persons_per_group));
            extract_R1R2_generation(i);
            extract_gene_dependancies_matrix_generation(i);
            extract_gene_counts_generation(i);
        }
    }
}



int main(void){
    int fitness;
    int combinations;
    int groups_wanted;
    int R1R2_swapping=0;
    int min_gene_R1R2;
    int max_gene_R1R2;
    int freq;
    int event;
    int event1=-100;
    int event2=-100;
    int event3=-100;
    int event4=-100;
    srand (time(NULL));

    /*
    1o orisma
    orisma 1 gia fitness based parent selection
    orisma 0 gia random parents
    */
    printf("Inheritance based on fitness?  (0=NO,1=YES)\n");
    scanf("%d", &fitness);

    /*
    2o orisma
    orisma 1 gia sindiasmo gonewn
    orisma 0 gia autousia gene dependancies apo 1 gonea
    */
    printf("Combinations? (0=NO,1=YES)\n");
    scanf("%d", &combinations);

    /*
    3o orisma
    number of groups wanted
    */
    printf("Groups_wanted?\n");
    scanf("%d", &groups_wanted);

    /*
    4o orisma
    0 gia R1R2 swapping
    1 gia row swapping
    */
    if (combinations){
        printf("R1R2_swapping or row_swapping? (0=R1R2_swapping,1=row_swapping)\n");
        scanf("%d", &R1R2_swapping);
    }
     /*
    5o orisma
    min_gene_R1R2
    */
    printf("min_gene_R1R2?\n");
    scanf("%d", &min_gene_R1R2);
    /*
    6o orisma
    max_gene_R1R2
    */
    printf("max_gene_R1R2\n");
    scanf("%d", &max_gene_R1R2);

    /*
    7o orisma
    frequency of extraction of data
    */
    printf("frequency of data export (every X generations export the data) \n");
    scanf("%d", &freq);

    /*
    8o orisma (9.10,11,12)
    creation of events
    */
    printf("Do you want to create an event? (0=no events, 1=yes)\n");
    scanf("%d", &event);
    if(event){
        printf("Please enter number of first event (press -1 for exit)\n");
        scanf("%d", &event1);
        if(event1>0){
            printf("Please enter number of second event (press -1 for exit)\n");
            scanf("%d", &event2);
            
            if(event2>0){
                printf("Please enter number of third event (press -1 for exit)\n");
                scanf("%d", &event3);
                
                if(event3>0){
                    printf("Please enter number of forth event (press -1 for exit)\n");
                    scanf("%d", &event4);
                }

            }
        }
    }

    create_generations(fitness,combinations,groups_wanted,R1R2_swapping,min_gene_R1R2,max_gene_R1R2,freq,event,event1,event2,event3,event4);

    return 0;
}
