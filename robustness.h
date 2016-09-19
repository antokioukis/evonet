person *create_specific_mutations(person *individual,int num_of_mutations,int last_bit, int other_bits){

  /*create mutations*/
    int result=0;
    gsl_rng * r;
    int num_of_gene_to_mutate, magic_number = 0;
    int bit_mutation,to_be_mutated;
    int which_R1R2;
    int j=0;
    int koubas=0;
    int euros_kouba;
    
    /* create a generator chosen by the 
    environment variable GSL_RNG_TYPE */


    /* print n random variates chosen from 
    the poisson distribution with mean 
         parameter mu */

    euros_kouba=99/genes_per_person;

    for(j=0;j<num_of_mutations;j++){
      which_R1R2=rand()%2;
      /* todo genes_per_person instead of max_genes_per_person */
      num_of_gene_to_mutate=rand() % genes_per_person;
      /* the mutation probability for the last bit is 100 less */
      bit_mutation=rand() % 100;

      /*special case, changing the last bit changes the interaction an den to exei dwsei o xristis den mporei na allaxei auto to bit*/
      if(bit_mutation==0 && last_bit){
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
      else if(other_bits){
        /*bres poios koubas einai */
        while(bit_mutation>koubas){
          koubas=koubas+euros_kouba;
        }
        koubas=koubas/genes_per_person;

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
    }
    
    return individual;
}



void check_robustness(FILE *robustOutput, int num_of_gen, int num_of_mutations, int last_bit, int other_bits){
	population *new_population;
    population *temp_population;
	person *temp_person;
	group *temp_group,*head_group;
	int k,l,i,j;
	int t;

	/*xwris na peira3w ta idi iparxonta, ftiaxnw deep copy tis genias pou me noiazei*/    
    new_population = generation_array[num_of_gen];

    /*ri3e mutations ston matrix*/
    for(k=0;k<curr_num_of_groups;k++){ /*sarwse olo ton pli8ismo kai ri3e mutations se olous*/
        for(l=0;l<persons_per_group;l++){
            temp_person=new_population->groups_list->person_in_group[l];
            temp_person=create_specific_mutations(temp_person,num_of_mutations,last_bit,other_bits);

    		for(i=0;i<genes_per_person;i++){
        		for(j=0;j<genes_per_person;j++){
        			/*printf("%f\n",temp_person->gene_interactions[i][j]); */
            		temp_person->gene_interactions[i][j]=create_gene_interactions(temp_person->gene_R1[i],temp_person->gene_R2[j]);
        			/*printf("%f\n",temp_person->gene_interactions[i][j]); */

        		}
    		}

            new_population->groups_list->person_in_group[l]=temp_person;

    	}
    	if(new_population->groups_list->next!=NULL){
            new_population->groups_list=new_population->groups_list->next;
    	}
    }

    for(k=0;k<curr_num_of_groups-1;k++){
        new_population->groups_list=new_population->groups_list->prev;
    }

    /*kane mature tin genia*/
    mature_generation(new_population);
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
    extract_robustness(robustOutput,new_population);
    /*sigkrine ta discrete*/
}