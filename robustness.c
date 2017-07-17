#include "robustness.h"
extern int curr_num_of_groups;
extern int sensitivity;

person *deep_copy_person_robust(person *temp_robust_person,person *temp_normal_person){

    int j,m;

    temp_robust_person->periodos=temp_normal_person->periodos;
    temp_robust_person->mature=temp_normal_person->mature;
    temp_robust_person->fitness=temp_normal_person->fitness;
    temp_robust_person->id=temp_normal_person->id;

    for(j=0;j<max_genes_per_person;j++){
        temp_robust_person->gene_counts[j]=temp_normal_person->gene_counts[j];
    }

    for(j=0;j<max_genes_per_person;j++){
        temp_robust_person->vector_of_signs[j]=temp_normal_person->vector_of_signs[j];
        temp_robust_person->gene_R1[j]=temp_normal_person->gene_R1[j];
        temp_robust_person->gene_R2[j]=temp_normal_person->gene_R2[j];
    }

    for(j=0;j<max_genes_per_person;j++){
        for(m=0;m<max_genes_per_person;m++){
            temp_robust_person->gene_interactions[j][m]=temp_normal_person->gene_interactions[j][m];
        }
    }

    for(j=0;j<size_of_maturity_array;j++){
        temp_robust_person->maturity_array[j]=temp_normal_person->maturity_array[j];
    }
    return temp_robust_person;
}

person *create_specific_mutations(person *individual,int num_of_mutations,int last_bit, int other_bits,gsl_rng *r){

  /*create mutations*/
    int result=0;
    int num_of_gene_to_mutate, magic_number = 0;
    double bit_mutation;
    int to_be_mutated;
    int which_R1R2;
    int j=0;
    int koubas=0;

    /* create a generator chosen by the
    environment variable GSL_RNG_TYPE */


    /* print n random variates chosen from
    the poisson distribution with mean
         parameter mu */

    for(j=0;j<num_of_mutations;j++){
      which_R1R2=gsl_rng_uniform_int(r,2);
      /* todo genes_per_person instead of max_genes_per_person */
      num_of_gene_to_mutate=gsl_rng_uniform_int(r,genes_per_person+1);
      /* the mutation probability for the last bit is 100 less */
       bit_mutation=gsl_rng_uniform_pos(r);

      /*special case, changing the last bit changes the interaction an den to exei dwsei o xristis den mporei na allaxei auto to bit*/
      if(bit_mutation<=0.01 && last_bit){
        if(which_R1R2){
            /*no fuss an einai monos ari8mos,to ipoloipo bgainei 1, afairwntas 1, ton kaneis zigo kai den peirazeis to ipoloipo binary represantation*/
            if(individual->gene_R1[num_of_gene_to_mutate]%2){
                individual->gene_R1[num_of_gene_to_mutate]=individual->gene_R1[num_of_gene_to_mutate]-1;
            }
            /*no fuss an einai monos ari8mos,to ipoloipo bgainei 1, afairwntas 1, ton kaneis zigo kai den peirazeis to ipoloipo binary represantation*/
            else{
                individual->gene_R1[num_of_gene_to_mutate]=individual->gene_R1[num_of_gene_to_mutate]+1;
            }
        }
        else{
            if(individual->gene_R1[num_of_gene_to_mutate]%2){
                individual->gene_R1[num_of_gene_to_mutate]=individual->gene_R2[num_of_gene_to_mutate]-1;
            }
            /*no fuss an einai monos ari8mos,to ipoloipo bgainei 1, afairwntas 1, ton kaneis zigo kai den peirazeis to ipoloipo binary represantation*/
            else{
                individual->gene_R1[num_of_gene_to_mutate]=individual->gene_R2[num_of_gene_to_mutate]+1;
            }
        }
      }
        
        koubas=gsl_rng_uniform_int(r,sensitivity);

        if(which_R1R2){
          to_be_mutated=individual->gene_R1[num_of_gene_to_mutate];
          magic_number = 1 << koubas;
          result = to_be_mutated ^ magic_number;
          /*printf("palio: %d, koubas: %d, kainourio: %d\n", to_be_mutated, koubas, result);*/
          individual->gene_R1[num_of_gene_to_mutate]=result;
        }
        else{
          to_be_mutated=individual->gene_R2[num_of_gene_to_mutate];
          magic_number = 1 << koubas;
          result = to_be_mutated ^ magic_number;
          /*printf("palio: %d, koubas: %d, kainourio: %d\n", to_be_mutated, koubas, result);*/
          individual->gene_R2[num_of_gene_to_mutate]=result;
        }
    }
    return individual;
}



void check_robustness(FILE *robustOutput, population *new_population, int num_of_mutations, int last_bit, int other_bits,gsl_rng *r,FILE *rob_discrete_Output){
	person *temp_person;
	group *temp_group;
	int k,l,i,j;

    temp_group=new_population->groups_list;

    /*ri3e mutations ston matrix*/
    for(k=0;k<curr_num_of_groups;k++){ /*sarwse olo ton pli8ismo kai ri3e mutations se olous*/
        for(l=0;l<persons_per_group;l++){
            temp_person=temp_group->person_in_group[l];
            temp_person=create_specific_mutations(temp_person,num_of_mutations,last_bit,other_bits,r);

    		for(i=0;i<genes_per_person;i++){
        		for(j=0;j<genes_per_person;j++){
        			/*printf("%f\n",temp_person->gene_interactions[i][j]); */
            		temp_person->gene_interactions[i][j]=create_gene_interactions(temp_person->gene_R1[i],temp_person->gene_R2[j]);
        			/*printf("%f\n",temp_person->gene_interactions[i][j]); */

        		}
    		}

            temp_group->person_in_group[l]=temp_person;

    	}
    	if(temp_group->next!=NULL){
            temp_group=temp_group->next;
    	}
    }

    for(k=0;k<curr_num_of_groups-1;k++){
        temp_group=temp_group->prev;
    }

    new_population->groups_list=temp_group;
    /*kane mature tin genia*/
    mature_generation(new_population,0);
    /*printf("%d\n",new_population->groups_list->next->person_in_group[1]->periodos);*/
/*
    temp_group=new_population->groups_list;

    for(k=0;k<curr_num_of_groups;k++){
        for(l=0;l<persons_per_group;l++){
            for(i=0;i<genes_per_person;i++){
                for(j=0;j<genes_per_person;j++){
                    printf("%f ",temp_group->person_in_group[l]->gene_interactions[i][j]);
                }
                printf("\n");
            }
            printf("\n");

        }
        if(temp_group->next!=NULL){
                temp_group=temp_group->next;
        }
    }
*/

    /*peta ta discrete apotelesmata se robustness.txt*/
    extract_robustness(robustOutput,new_population,rob_discrete_Output);
    /*sigkrine ta discrete*/
}
