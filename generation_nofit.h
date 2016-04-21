void create_mutations(float new_dependancies[genes_per_person][genes_per_person]){
    int num_of_mutations,sign_mutation,thesi_mutation[2];
    int i;
    float final_mutation,mutation;

    /*POISSON TO BE IMPLEMENTED*/
    num_of_mutations=rand()%4;

  //  printf("Arithmos Mutations: %d \n", num_of_mutations);

    for (i=0;i<num_of_mutations;i++){

        sign_mutation=rand()%2;
        thesi_mutation[0]=rand()%genes_per_person;
        thesi_mutation[1]=rand()%genes_per_person;

     //   printf("Mutations stis theseis %d %d\n",thesi_mutation[0],thesi_mutation[1] );

        mutation=random_normal_distrubution(0,sqrt(10));

        if(sign_mutation){
            final_mutation=mutation;
        }
        else{
            final_mutation=-1*mutation;
        }
     //   printf("Old %f \n",new_dependancies[thesi_mutation[0]][thesi_mutation[1]]);
        new_dependancies[thesi_mutation[0]][thesi_mutation[1]]=final_mutation;
     //   printf("New %f \n",new_dependancies[thesi_mutation[0]][thesi_mutation[1]]);
    }
}

void choose_random_father_dependencies(int num_of_gen,float new_dependancies[genes_per_person][genes_per_person]){
    int group_counter=0;
    int person_counter=0;
    int id_patera,i,j;

    id_patera=rand()%(num_of_groups*persons_per_group);

    group_counter=id_patera/persons_per_group;
    person_counter=id_patera%persons_per_group;
//    printf("Group_of_father %d Person_on_group %d \n",group_counter,person_counter);


    for(i=0;i<genes_per_person;i++){
        for(j=0;j<genes_per_person;j++){
            new_dependancies[i][j]=generation_array[num_of_gen-1]->group_in_population[group_counter]->person_in_group[person_counter]->gene_interactions[i][j];
        }
    }
    create_mutations(new_dependancies);
}

person *gen_create_person_nofit(int id,int num_of_gen){
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
    choose_random_father_dependencies(num_of_gen,new_person->gene_interactions);
//    printf("Created Inheritance\n");
//    for(i=0;i<genes_per_person;i++){
//        for(j=0;j<genes_per_person;j++){
//            printf(" %f ", new_person->gene_interactions[i][j]);
//        }printf("\n");
//    }

    return new_person;
}

group *gen_create_group_nofit(int starting_id,int num_of_gen){
    int i;

    group *new_group;
    new_group = (group*)calloc(1, sizeof(group));

    for(i=0;i<persons_per_group;i++){
       // printf("Creating Atomo %d\n",i);
        new_group->person_in_group[i]=gen_create_person_nofit(starting_id+i,num_of_gen);
        //printf("Atomo created %d\n",i);
    }
    return new_group;
}

population *create_gen_population_nofit(int num_of_gen){
    int i;

    population *new_population;
    new_population = (population*)calloc(1, sizeof(population));

    for(i=0;i<num_of_groups;i++){
       // printf("Creating Group %d\n",i);
        new_population->group_in_population[i]=gen_create_group_nofit(persons_per_group*i,num_of_gen);
     //   printf("Group created %d\n",i);
    }
   // printf("Generation Created\n");
    return new_population;
}

//population *gen_create_with_fiteness(){
//    return create_gen_population_fit();
//}



