void create_maturity_step(person *individual,int step){
    int i;
    unsigned int position;
    int sum=0;
    float non_descrete_res[genes_per_person];


    matrix_multiplication(individual->gene_interactions,individual->vector_of_signs,non_descrete_res);

    make_discrete(individual,non_descrete_res);

    for(i=0;i<genes_per_person;i++){
/*        printf("current sign %d stin thesi %d\n",individual->vector_of_signs[i],i);*/
        sum+=individual->vector_of_signs[i]*(pow(10,i));
/*        printf("current Sum %d\n",sum);*/
    }

/*    printf(" %d \n",sum);*/
/*    printf("position Array = %ld\n",binary_to_decimal(position));*/
    position=binary_to_decimal(sum);

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
   /* int ID;
    int periodos;*/
    for(k=0;k<num_of_groups;k++){
        for(l=0;l<persons_per_group;l++){
            if(!new_population->group_in_population[k]->person_in_group[l]->mature){
                return 0;
            }
            else {
                /*ID=new_population->group_in_population[k]->person_in_group[l]->id;
                periodos=new_population->group_in_population[k]->person_in_group[l]->periodos;
                printf("Atomo me ID %d idi mature me periodo: %d\n",ID,periodos);*/
            }
        }
    }
    /*printf("Generation Mature\n");*/
    return 1;
}


void mature_generation(population *new_population){
    /*population *temp=new_population; */
    /*int ID;*/
    int step=0;
    int k,l;

    while(!check_population_mature(new_population)){
        /*printf("Pli8ismos Oxi Plastikos. Xreiazomai kai alla maturity steps\n");*/
        for(k=0;k<num_of_groups;k++){
            for(l=0;l<persons_per_group;l++){
                if(!new_population->group_in_population[k]->person_in_group[l]->mature){
           /*         ID=new_population->group_in_population[k]->person_in_group[l]->id;*/
          /*          printf("Atomo me ID %d xreiazetai maturity step\n",ID);*/
                    create_maturity_step(new_population->group_in_population[k]->person_in_group[l],step);
                }
            }
        }
        step++;
    }
}
