person *create_person(int id){
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
            new_person->gene_interactions[i][j]=random_normal_distrubution(0,sqrt(10));
        }
    }

    return new_person;
}

group *create_group(int starting_id){
    int i;

    group *new_group;
    new_group = (group*)calloc(1, sizeof(group));

    for(i=0;i<persons_per_group;i++){
       new_group->person_in_group[i]=create_person(starting_id+i);
    }
    return new_group;
}

population *create_population(){
    int i;

    population *new_population;
    new_population = (population*)calloc(1, sizeof(population));

    for(i=0;i<num_of_groups;i++){
       new_population->group_in_population[i]=create_group(persons_per_group*i);
    }
    return new_population;
}


