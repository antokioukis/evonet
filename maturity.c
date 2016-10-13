#include "maturity.h"
extern int curr_num_of_groups;

void create_maturity_step(person *individual,int step,FILE *steps,FILE *period, int robust_or_not){
	int i;
	float res_of_mult;
	int temp_vector[max_genes_per_person];
	int position;

    if(robust_or_not)fprintf(steps, "%d ",step);
	for(i=0;i<genes_per_person;i++){
		/*if(step==1) res_of_mult=matrix_multiplication(individual->gene_interactions,individual->gene_counts,i);
		else res_of_mult=matrix_multiplication(individual->gene_interactions,individual->vector_of_signs,i);*/
		res_of_mult=matrix_multiplication(individual->gene_interactions,individual->vector_of_signs,i);
		/*printf("mult:%f\n",res_of_mult); */

		if (res_of_mult>0) temp_vector[i]=1;
		else temp_vector[i]=0;
	}

	/*printf("new_vector\n");*/
	/*for(i=0;i<genes_per_person;i++){
		printf("%d",temp_vector[i]);
	}
	printf("\n");*/

	position=vector_to_decimal(temp_vector);
	/*printf("position %d\n",position);*/

 	if(individual->maturity_array[position]==0){
        	individual->maturity_array[position]=step;
		/*printf("More maturity steps Needed\n");*/
    }
    else{
    	individual->periodos=step-individual->maturity_array[position];
        if (robust_or_not) fprintf(period, "%d",individual->periodos);
       	individual->mature=true;
    }

	if(!individual->mature){
		for(i=0;i<genes_per_person;i++){
			individual->vector_of_signs[i]=temp_vector[i];
		}
	}
}

bool check_population_mature(population *new_population){
    int k,l;
    group *temp=new_population->groups_list;
   /* int ID;
    int periodos;*/
    for(k=0;k<curr_num_of_groups;k++){
        for(l=0;l<persons_per_group;l++){
            if(!temp->person_in_group[l]->mature){
                return false;
            }
        }
        if(temp->next!=NULL){
                temp=temp->next;
        }
    }
    /*printf("Generation Mature\n"); */
    return true;
}

void mature_generation(population *new_population,int robust_or_not){
    group *temp=new_population->groups_list;
    /*int ID; */
    int step=1;
    int k,l,i=0;

    FILE *steps_Output,*period_Output;

    steps_Output = fopen("steps.txt", "a");
    period_Output= fopen("period.txt","a");

    while(!check_population_mature(new_population)){
       /* printf("Pli8ismos Oxi wrimos. Xreiazomai kai alla maturity steps\n");*/
        for(k=0;k<curr_num_of_groups;k++){
            for(l=0;l<persons_per_group;l++){
                if(!temp->person_in_group[l]->mature){
     /*               ID=temp->person_in_group[l]->id;
                      	printf("group:%d Atomo me ID %d xreiazetai maturity step\n",k,ID);
*/       		create_maturity_step(temp->person_in_group[l],step,steps_Output,period_Output,robust_or_not);
                }
                i++;
            }
            if(temp->next!=NULL){
                temp=temp->next;
            }
        }
        step++;
        temp=new_population->groups_list;
    }

    if(robust_or_not){
        fprintf(steps_Output, "\n");
        fprintf(period_Output, "\n");
    }
        /* printf("STEPS NEEDED:%d\n",step); */
        fclose(steps_Output);
        fclose(period_Output);
}
