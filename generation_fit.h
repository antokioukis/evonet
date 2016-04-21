void calculate_fitness(int num_of_gen){
    int i,j;
    float personal_fitness;
    float lamda=0.5;
    float distance;
    int optimal[genes_per_person]={1,1,1,1,1,1,1,1,1,1};

    for(i=0;i<num_of_groups;i++){
        for(j=0;j<persons_per_group;j++){
            distance=eucledian_distance(generation_array[num_of_gen-1]->group_in_population[i]->person_in_group[j]->vector_of_signs,optimal);
            personal_fitness=exp(-lamda*distance);

            generation_array[num_of_gen-1]->group_in_population[i]->person_in_group[j]->fitness=personal_fitness;
           // printf("Personal Fitness %f\n",generation_array[num_of_gen-1]->group_in_population[i]->person_in_group[j]->fitness);

            generation_array[num_of_gen-1]->sum_of_fitness+=personal_fitness;
            //printf("Generation Fitness %f\n",generation_array[num_of_gen-1]->sum_of_fitness);
        }
    }
}


void choose_fitted_father_dependencies(int num_of_gen,float new_dependancies[genes_per_person][genes_per_person]){
    float fitness_array[(num_of_groups*persons_per_group)];
 //   int theseis_pinaka=num_of_groups*persons_per_group;
    int counter=0;
    int i,j;
    double fitness_asked=0;
    int group_counter,person_counter;

    for(i=0;i<num_of_groups;i++){
        for(j=0;j<persons_per_group;j++){
            if(i==0&&j==0){
                fitness_array[counter]=generation_array[num_of_gen-1]->group_in_population[i]->person_in_group[j]->fitness;
            }
            else{
                fitness_array[counter]=fitness_array[counter-1]+generation_array[num_of_gen-1]->group_in_population[i]->person_in_group[j]->fitness;
            }
            counter++;
        }
    }

//    printf("Fitness_array[%d]= %f \n",theseis_pinaka-1,fitness_array[theseis_pinaka-1]);
//    printf("Fitness of generation = %f  \n",generation_array[num_of_gen-1]->sum_of_fitness);

    //na brw to fitness pou zitaei kai apo ekei mesa na brw ton patera
    fitness_asked=((double)rand() / RAND_MAX)*generation_array[num_of_gen-1]->sum_of_fitness;
    //printf("fitness_asked: %f \n",fitness_asked);

    counter=0;
    while(fitness_asked>fitness_array[counter]){
        counter++;
    }
   // printf("Counter= %d\n",counter);

    group_counter=counter/persons_per_group;
    person_counter=counter%persons_per_group;

    for(i=0;i<genes_per_person;i++){
        for(j=0;j<genes_per_person;j++){
            new_dependancies[i][j]=generation_array[num_of_gen-1]->group_in_population[group_counter]->person_in_group[person_counter]->gene_interactions[i][j];
        }
    }

    create_mutations(new_dependancies);
}


person *gen_create_person_fit(int id,int num_of_gen){
    int i;
    //int j;

    person *new_person;
    new_person = (person*)calloc(1, sizeof(person));

    new_person->id=id;


    for(i=0;i<genes_per_person;i++){
        new_person->gene_counts[i]=(int)random_normal_distrubution(100,sqrt(100));
    }

    for(i=0;i<genes_per_person;i++){
        new_person->vector_of_signs[i]=1;
    }

//    printf("Creating Inheritance\n");
    choose_fitted_father_dependencies(num_of_gen,new_person->gene_interactions);
//    printf("Created Inheritance\n");
//    for(i=0;i<genes_per_person;i++){
//        for(j=0;j<genes_per_person;j++){
//            printf(" %f ", new_person->gene_interactions[i][j]);
//        }printf("\n");
//    }

    return new_person;
}

group *gen_create_group_fit(int starting_id,int num_of_gen){
    int i;

    group *new_group;
    new_group = (group*)calloc(1, sizeof(group));

    for(i=0;i<persons_per_group;i++){
       // printf("Creating Atomo %d\n",i);
        new_group->person_in_group[i]=gen_create_person_fit(starting_id+i,num_of_gen);
        //printf("Atomo created %d\n",i);
    }
    return new_group;
}


population *create_gen_population_fit(int num_of_gen){
    int i;

    population *new_population;
    new_population = (population*)calloc(1, sizeof(population));

    calculate_fitness(num_of_gen);

    for(i=0;i<num_of_groups;i++){
       // printf("Creating Group %d\n",i);
        new_population->group_in_population[i]=gen_create_group_fit(persons_per_group*i,num_of_gen);
     //   printf("Group created %d\n",i);
    }
   // printf("Generation Created\n");
    return new_population;
}