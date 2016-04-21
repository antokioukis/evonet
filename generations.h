float *choose_random_father_dependencies(int num_of_gen){
    int group_counter=0;
    int person_counter=0;
    int id_patera;
    id_patera=rand()%num_of_groups*persons_per_group;
    while(id_patera>persons_per_group){
        group_counter++;
        id_patera=id_patera-persons_per_group;
        printf("Id patera megalitero apo persons_per_group\n");
    }
    while(id_patera>generation_array[num_of_gen-1]->group_in_population[group_counter]->person_in_group[person_counter]){
        person_counter++;
    }
    return generation_array[num_of_gen-1]->group_in_population[group_counter]->person_in_group[person_counter]->gene_interactions;
}


person *gen_create_person_nofit(int id,int num_of_gen){
    int i,j;

    person *new_person;
    new_person = (person*)calloc(1, sizeof(person));

    new_person->id=id;


    for(i=0;i<genes_per_person;i++){
        new_person->gene_counts[i]=(int)random_normal_distrubution(100,sqrt(100));
    }

    for(i=0;i<genes_per_person;i++){
        new_person->vector_of_signs[i]=1;
    }

    for(i=0;i<genes_per_person;i++){
        for(j=0;j<genes_per_person;j++){
            new_person->gene_interactions[i][j]=choose_random_father_dependencies(num_of_gen);
        }
    }

    return new_person;
}

group *gen_create_group_nofit(int starting_id,int num_of_gen){
    int i;

    group *new_group;
    new_group = (group*)calloc(1, sizeof(group));

    for(i=0;i<persons_per_group;i++){
       new_group->person_in_group[i]=gen_create_person_nofit(starting_id+i,num_of_gen);
    }
    return new_group;
}

population *create_gen_population_nofit(int num_of_gen){
    int i;

    population *new_population;
    new_population = (population*)calloc(1, sizeof(population));

    for(i=0;i<num_of_groups;i++){
       new_population->group_in_population[i]=gen_create_group_nofit(persons_per_group*i,num_of_gen);
    }
    return new_population;
}

//population *gen_create_with_fiteness(){
//    return create_gen_population_fit();
//}



