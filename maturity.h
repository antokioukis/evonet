population *active_population;

void create_maturity_step(person *individual,int step){
    int i,k,c;
    unsigned int position;
    int sum=0;
    float non_descrete_res[max_genes_per_person]={0,0,0,0,0,0,0,0,0,0};

    for (c = 0; c < genes_per_person; c++) {
        for (k = 0; k < genes_per_person; k++) {
            sum = sum + individual->gene_interactions[c][k]*individual->vector_of_signs[k];
        }

        non_descrete_res[c] = sum;
        sum = 0;
    }

    make_discrete(individual,non_descrete_res);

    for(i=0;i<max_genes_per_person;i++){
      /*  printf("current sign %d stin thesi %d\n",individual->vector_of_signs[i],i); */
        sum+=individual->vector_of_signs[i]*(pow(10,i));
      /*  printf("current Sum %d\n",sum);*/
    }

   /* printf(" %d \n",sum);  */
    position=binary_to_decimal(sum);
   /* printf("position Array = %ld\n",binary_to_decimal(position)); */

    if(individual->maturity_array[position]==0){
        individual->maturity_array[position]=step;
    }
    else{
        individual->periodos=step-individual->maturity_array[position];
        individual->mature=true;
    }
}

int check_population_mature(population *new_population){
    int k,l;
    group *temp=new_population->groups_list;
   /* int ID;
    int periodos;*/
    for(k=0;k<curr_num_of_groups;k++){
        for(l=0;l<persons_per_group;l++){
            if(!temp->person_in_group[l]->mature){
                return 0;
            }
        }
        if(temp->next!=NULL){
                temp=temp->next;
        }
    }
   /* printf("Generation Mature\n"); */ 
    return 1;
}

void mature_generation(population *new_population){
    group *temp=new_population->groups_list;
    /*int ID; */
    int step=0;
    int k,l;

    while(!check_population_mature(new_population)){
      /*  printf("Pli8ismos Oxi wrimos. Xreiazomai kai alla maturity steps\n"); */
        for(k=0;k<curr_num_of_groups;k++){
            for(l=0;l<persons_per_group;l++){
                if(!temp->person_in_group[l]->mature){
     /*               ID=temp->person_in_group[l]->id;
                    printf("group:%d Atomo me ID %d xreiazetai maturity step\n",k,ID);
       */             create_maturity_step(temp->person_in_group[l],step);
                }
            }
            if(temp->next!=NULL){
                temp=temp->next;
            }
        }
        step++;
        temp=new_population->groups_list;
    }
}