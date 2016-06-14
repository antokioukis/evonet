void calculate_fitness(int num_of_gen){
    int i,j,k,w,n;
    person* atomo;
    int num_of_steps;
    float sum_of_personal_fitness_cycles=0;
    float personal_fitness;
    float lamda=0.5;
    float distance;
    float non_descrete_res[genes_per_person];
    int optimal[genes_per_person]={1,1};
   /* int optimal[genes_per_person]={1,1,1,1,1,1,1,1,1,1}; */

    /*gia ka8e atomo tou pli8ismou*/
    for(i=0;i<num_of_groups;i++){
        for(j=0;j<persons_per_group;j++){
        /*gia na min grafw olo auto to makrinari*/
            atomo=generation_array[num_of_gen-1]->group_in_population[i]->person_in_group[j];
            /*printf("ID atomou: %d, periodos %d\n",atomo->id,atomo->periodos);*/
          /*parousiazei kikliko equilibrium*/
            if(atomo->periodos>1){
                num_of_steps=atomo->periodos;
                /*kane pollaplisiasmous osous exeis periodo (proxwra bimata)*/
                /*NEEDS MORE TESTING , printf ka8e apotelesma pou mpainei kai bgainei apo to matrix multiplication*/
                for(k=0;k<num_of_steps;k++){

                   /* for (w=0;w<genes_per_person;w++){
                        for(n=0;n<genes_per_person;n++){
                            printf("%f ", atomo->gene_interactions[w][n]);
                        }
                        printf("\n");
                    }

                    for(w=0;w<genes_per_person;w++){
                        printf("%d ", atomo->vector_of_signs[w]);
                    } printf("\n");
                    */

                    matrix_multiplication(atomo->gene_interactions,atomo->vector_of_signs,non_descrete_res);
                    make_discrete(atomo,non_descrete_res);
                    sum_of_personal_fitness_cycles+=eucledian_distance(atomo->vector_of_signs,optimal);
                   /* printf("Sum of personal fitness cycles %f\n",sum_of_personal_fitness_cycles); */
                }
                distance=sum_of_personal_fitness_cycles/num_of_steps;
                personal_fitness=exp(-lamda*distance);
                generation_array[num_of_gen-1]->group_in_population[i]->person_in_group[j]->fitness=personal_fitness;
            }
            else{
                distance=eucledian_distance(generation_array[num_of_gen-1]->group_in_population[i]->person_in_group[j]->vector_of_signs,optimal);
                personal_fitness=exp(-lamda*distance);
                generation_array[num_of_gen-1]->group_in_population[i]->person_in_group[j]->fitness=personal_fitness;
           /* printf("Personal Fitness %f\n",generation_array[num_of_gen-1]->group_in_population[i]->person_in_group[j]->fitness); */
            }
            generation_array[num_of_gen-1]->sum_of_fitness+=personal_fitness;
            /* printf("Generation Fitness %f\n",generation_array[num_of_gen-1]->sum_of_fitness);*/
            sum_of_personal_fitness_cycles=0;
        }
    }
}


void choose_fitted_father_dependencies_no_combinations(int num_of_gen,float new_dependancies[genes_per_person][genes_per_person]){
    float fitness_array[(num_of_groups*persons_per_group)];
/*  int theseis_pinaka=num_of_groups*persons_per_group;*/
    int counter=0;
    int i,j;
    double fitness_asked=0;
    int group_counter,person_counter;

  /*  printf("Fitness No combinations\n"); */

    /*pinakas fitness einai to dianisma me ta miki analoga me to poso fitted einai*/
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

/*    printf("Fitness_array[%d]= %f \n",theseis_pinaka-1,fitness_array[theseis_pinaka-1]);*/
/*    printf("Fitness of generation = %f  \n",generation_array[num_of_gen-1]->sum_of_fitness);*/

    /*na brw to fitness pou zitaei kai apo ekei mesa na brw ton patera*/
    fitness_asked=((double)rand() / RAND_MAX)*generation_array[num_of_gen-1]->sum_of_fitness;
    /*printf("fitness_asked: %f \n",fitness_asked);*/

    counter=0;
    while(fitness_asked>fitness_array[counter]){
        counter++;
    }
   /* printf("Counter= %d\n",counter);*/

    group_counter=counter/persons_per_group;
    person_counter=counter%persons_per_group;

    for(i=0;i<genes_per_person;i++){
        for(j=0;j<genes_per_person;j++){
            new_dependancies[i][j]=generation_array[num_of_gen-1]->group_in_population[group_counter]->person_in_group[person_counter]->gene_interactions[i][j];
        }
    }

    create_mutations(new_dependancies);
}


void choose_fitted_father_dependencies_combined(int num_of_gen,float new_dependancies[genes_per_person][genes_per_person]){
    float fitness_array[(num_of_groups*persons_per_group)];
/*  int theseis_pinaka=num_of_groups*persons_per_group;*/
    int counter1=0;
    int counter2=0;
    int i,j;
    double fitness_asked1=0;
    double fitness_asked2=0;
    int group_counter1,person_counter1,group_counter2,person_counter2;
    int genes_from_first_parent;
    int genes_from_second_parent;

   /* printf("Fitness PLUS combinations\n"); */

    /*pinakas fitness einai to dianisma me ta miki analoga me to poso fitted einai*/
    for(i=0;i<num_of_groups;i++){
        for(j=0;j<persons_per_group;j++){
            if(i==0&&j==0){
                fitness_array[counter1]=generation_array[num_of_gen-1]->group_in_population[i]->person_in_group[j]->fitness;
            }
            else{
                fitness_array[counter1]=fitness_array[counter1-1]+generation_array[num_of_gen-1]->group_in_population[i]->person_in_group[j]->fitness;
            }
            counter1++;
        }
    }

/*    printf("Fitness_array[%d]= %f \n",theseis_pinaka-1,fitness_array[theseis_pinaka-1]);*/
/*    printf("Fitness of generation = %f  \n",generation_array[num_of_gen-1]->sum_of_fitness);*/

    /*na brw to fitness pou zitaei kai apo ekei mesa na brw ton patera*/
    fitness_asked1=((double)rand() / RAND_MAX)*generation_array[num_of_gen-1]->sum_of_fitness;
    /*printf("fitness_asked: %f \n",fitness_asked);*/

    fitness_asked2=((double)rand() / RAND_MAX)*generation_array[num_of_gen-1]->sum_of_fitness;

    counter1=0;
    while(fitness_asked1>fitness_array[counter1]){
        counter1++;
    }

    counter2=0;
    while(fitness_asked2>fitness_array[counter2]){
        counter2++;
    }
   /* printf("Counter= %d\n",counter);*/

    group_counter1=counter1/persons_per_group;
    person_counter1=counter1%persons_per_group;

    group_counter2=counter2/persons_per_group;
    person_counter2=counter2%persons_per_group;

    genes_from_first_parent=rand()%genes_per_person;
    genes_from_second_parent=genes_per_person-genes_from_first_parent;


    /*panw aristero tetartimorio ston pinaka gene_dependancies*/
    for(i=0;i<genes_per_person;i++){
        for(j=0;j<genes_from_first_parent;j++){
            new_dependancies[i][j]=generation_array[num_of_gen-1]->group_in_population[group_counter1]->person_in_group[person_counter1]->gene_interactions[i][j];
        }
    }

 /*   printf("Apo ton prwto parent pira %d\n", genes_from_first_parent); */


 /*   printf("Panw aristero tetartimorio");
    for(i=0;i<genes_per_person;i++){
        for(j=0;j<genes_from_first_parent;j++){
            printf(" %f ",new_dependancies[i][j]);
        }
        printf("\n");
    }

*/

    /* katw de3io tetartimorio*/
    for(i=genes_from_first_parent;i<genes_per_person;i++){
        for(j=genes_from_first_parent;j<genes_per_person;j++){
            new_dependancies[i][j]=generation_array[num_of_gen-1]->group_in_population[group_counter2]->person_in_group[person_counter2]->gene_interactions[i][j];
        }
    }

   /* printf("Apo ton deutero parent pira %d\n", genes_from_second_parent); */

    /*katw aristero tetartimorio r1_second + r2_first*/
    for(i=genes_from_first_parent;i<genes_per_person;i++){
        for(j=0;j<genes_from_first_parent;j++){
            new_dependancies[i][j]=create_gene_interactions(
                                    generation_array[num_of_gen-1]->group_in_population[group_counter2]->person_in_group[person_counter2]->gene_R1[i],
                                    generation_array[num_of_gen-1]->group_in_population[group_counter1]->person_in_group[person_counter1]->gene_R2[j]);
        }
    }

    /*panw de3io tetartimorio r1_first + r2_second*/
    for(i=0;i<genes_per_person;i++){
        for(j=genes_from_first_parent;j<genes_per_person;j++){
            new_dependancies[i][j]=create_gene_interactions(
                                        generation_array[num_of_gen-1]->group_in_population[group_counter2]->person_in_group[person_counter2]->gene_R2[i],
                                        generation_array[num_of_gen-1]->group_in_population[group_counter1]->person_in_group[person_counter1]->gene_R1[j]
                                    );
        }
    }

    for(i=0;i<genes_per_person;i++){
        for(j=0;j<genes_per_person;j++){
            printf(" %f ",new_dependancies[i][j]);
        }
        printf("\n");
    }

   /* create_mutations(new_dependancies); */
}


person *gen_create_person_fit(int id,int num_of_gen, int num_of_parents){
    int i;
    /*int j;*/

    person *new_person;
    new_person = (person*)calloc(1, sizeof(person));

    new_person->id=id;


    for(i=0;i<genes_per_person;i++){
        new_person->gene_counts[i]=(int)random_normal_distrubution(100,sqrt(100));
    }

    for(i=0;i<genes_per_person;i++){
        new_person->vector_of_signs[i]=1;
    }

/*    printf("Creating Inheritance\n");*/
    if(num_of_parents){
        choose_fitted_father_dependencies_combined(num_of_gen,new_person->gene_interactions);
    }
/*
    printf("Created Inheritance\n");
    for(i=0;i<genes_per_person;i++){
        for(j=0;j<genes_per_person;j++){
            printf(" %f ", new_person->gene_interactions[i][j]);
        }printf("\n");
    }
*/

    else {
        choose_fitted_father_dependencies_no_combinations(num_of_gen,new_person->gene_interactions);
    }


    return new_person;
}

group *gen_create_group_fit(int starting_id,int num_of_gen, int num_of_parents){
    int i;

    group *new_group;
    new_group = (group*)calloc(1, sizeof(group));

    for(i=0;i<persons_per_group;i++){
       /* printf("Creating Atomo %d\n",i);*/
        new_group->person_in_group[i]=gen_create_person_fit(starting_id+i,num_of_gen, num_of_parents);
        /*printf("Atomo created %d\n",i);*/
    }
    return new_group;
}


population *create_gen_population_fit(int num_of_gen, int num_of_parents){
    int i;

    population *new_population;
    new_population = (population*)calloc(1, sizeof(population));

    calculate_fitness(num_of_gen);

    for(i=0;i<num_of_groups;i++){
       /* printf("Creating Group %d\n",i);*/
        new_population->group_in_population[i]=gen_create_group_fit(persons_per_group*i,num_of_gen, num_of_parents);
     /*   printf("Group created %d\n",i);*/
    }
   /* printf("Generation Created\n");*/
    return new_population;
}
