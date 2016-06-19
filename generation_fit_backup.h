void calculate_fitness(int num_of_gen){
    int i,j,k;
    /*int w,n;*/
    person* atomo;
    int num_of_steps;
    float sum_of_personal_fitness_cycles=0;
    float personal_fitness;
    float lamda=0.5;
    float distance;
    float non_descrete_res[genes_per_person];
    int optimal[genes_per_person]={1,1}; 
    /*int optimal[genes_per_person]={1,1,1,1,1,1,1,1,1,1};*/
    group* temp;

    generation_array[num_of_gen-1]->sum_of_fitness=0;
    temp=generation_array[num_of_gen-1]->groups_list;
    /*gia ka8e atomo tou pli8ismou*/
    for(i=0;i<curr_num_of_groups;i++){
        for(j=0;j<persons_per_group;j++){
        /*gia na min grafw olo auto to makrinari*/
            atomo=temp->person_in_group[j];
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
                temp->person_in_group[j]->fitness=personal_fitness;
            }
            else{
                distance=eucledian_distance(temp->person_in_group[j]->vector_of_signs,optimal);
                personal_fitness=exp(-lamda*distance);
                temp->person_in_group[j]->fitness=personal_fitness;
                /*printf("Personal Fitness %f\n",temp->person_in_group[j]->fitness);*/
            }
            generation_array[num_of_gen-1]->sum_of_fitness+=personal_fitness;
           /* printf("Generation Fitness %f\n",generation_array[num_of_gen-1]->sum_of_fitness); */
            sum_of_personal_fitness_cycles=0;
        }
        if(temp->next!=NULL){
            temp=temp->next;
       }
    }
}


void choose_fitted_father_dependencies_no_combinations(int num_of_gen,float new_dependancies[genes_per_person][genes_per_person]){
    float fitness_array[(curr_num_of_groups*persons_per_group)];
/*  int theseis_pinaka=num_of_groups*persons_per_group;*/
    int counter=0;
    int i,j;
    double fitness_asked=0;
    int group_counter,person_counter;
    group *temp=generation_array[num_of_gen-1]->groups_list;

  /*  printf("Fitness No combinations\n"); */

    /*pinakas fitness einai to dianisma me ta miki analoga me to poso fitted einai*/
    for(i=0;i<curr_num_of_groups;i++){
        for(j=0;j<persons_per_group;j++){
            if(i==0&&j==0){
                fitness_array[counter]=temp->person_in_group[j]->fitness;
            }
            else{
                fitness_array[counter]=fitness_array[counter-1]+temp->person_in_group[j]->fitness;
            }
            counter++;
        }
        if(temp->next!=NULL){
            temp=temp->next;
       }
    }

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

    for(i=0;i<group_counter;i++){
        temp=temp->next;
    }


    for(i=0;i<genes_per_person;i++){
        for(j=0;j<genes_per_person;j++){
            new_dependancies[i][j]=temp->person_in_group[person_counter]->gene_interactions[i][j];
        }
    }

    create_mutations(new_dependancies);
}

void new_choose_fitted_father_dependencies_combined(int num_of_gen,float new_dependancies[genes_per_person][genes_per_person]){
    float fitness_array[(num_of_groups*persons_per_group)];
/*  int theseis_pinaka=num_of_groups*persons_per_group; */
    int counter=0;
    int genes_from_first_parent;
    int counter1=0;
    int counter2=0;
    int gene_R1[genes_per_person];
    int gene_R2[genes_per_person];
    int i,j;
    double fitness_asked1=0;
    double fitness_asked2=0;
    int group_counter1,person_counter1,group_counter2,person_counter2;
    group *temp=generation_array[num_of_gen-1]->groups_list;
    group *temp1=generation_array[num_of_gen-1]->groups_list;
    group *temp2=generation_array[num_of_gen-1]->groups_list;
   /* printf("Fitness PLUS combinations\n"); */

    /*pinakas fitness einai to dianisma me ta miki analoga me to poso fitted einai*/
    for(i=0;i<curr_num_of_groups;i++){
        for(j=0;j<persons_per_group;j++){
            if(i==0&&j==0){
                fitness_array[counter]=temp->person_in_group[j]->fitness;
            }
            else{
                fitness_array[counter]=fitness_array[counter-1]+temp->person_in_group[j]->fitness;
            }
            counter++;
        }
        if(temp->next!=NULL){
            temp=temp->next;
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


    for(i=0;i<group_counter1;i++){
        if(temp1->next!=NULL){
            temp1=temp1->next;
       }
    }

    for(i=0;i<group_counter2;i++){
        if(temp2->next!=NULL){
            temp2=temp2->next;
       }
    }

   /* printf("ID patera %d ID patera %d \n",generation_array[num_of_gen-1]->group_in_population[group_counter1]->person_in_group[person_counter1]->id,generation_array[num_of_gen-1]->group_in_population[group_counter2]->person_in_group[person_counter2]->id);
*/
    genes_from_first_parent=rand()%genes_per_person;

    for(i=0;i<genes_per_person;i++){
        if(i<genes_from_first_parent){
            gene_R1[i]=temp1->person_in_group[person_counter1]->gene_R1[i];
        }
        else{
            gene_R1[i]=temp2->person_in_group[person_counter2]->gene_R1[i];
        }
    }

    for(i=0;i<genes_per_person;i++){
        if(i<genes_from_first_parent){
            gene_R2[i]=temp2->person_in_group[person_counter2]->gene_R2[i];
        }
        else{
            gene_R2[i]=temp1->person_in_group[person_counter1]->gene_R2[i];
        }
    }

    for(i=0;i<genes_per_person;i++){
        for(j=0;j<genes_per_person;j++){
            /*new_person->gene_interactions[i][j]=random_normal_distrubution(0,sqrt(10));*/
            new_dependancies[i][j]=create_gene_interactions(gene_R1[i],gene_R2[j]);
        }
    }
    create_mutations(new_dependancies);

}

void choose_fitted_father_dependencies_combined(int num_of_gen,float new_dependancies[genes_per_person][genes_per_person]){
    float fitness_array[(num_of_groups*persons_per_group)];
/*  int theseis_pinaka=num_of_groups*persons_per_group; */
    int counter=0;
    int counter1=0;
    int counter2=0;
    int i,j;
    double fitness_asked1=0;
    double fitness_asked2=0;
    int group_counter1,person_counter1,group_counter2,person_counter2;
    int which_parent;
    group *temp=generation_array[num_of_gen-1]->groups_list;
    group *temp1=generation_array[num_of_gen-1]->groups_list;
    group *temp2=generation_array[num_of_gen-1]->groups_list;
   /* printf("Fitness PLUS combinations\n"); */

    /*pinakas fitness einai to dianisma me ta miki analoga me to poso fitted einai*/
    for(i=0;i<curr_num_of_groups;i++){
        for(j=0;j<persons_per_group;j++){
            if(i==0&&j==0){
                fitness_array[counter]=temp->person_in_group[j]->fitness;
            }
            else{
                fitness_array[counter]=fitness_array[counter-1]+temp->person_in_group[j]->fitness;
            }
            counter++;
        }
        if(temp->next!=NULL){
            temp=temp->next;
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


    for(i=0;i<group_counter1;i++){
        if(temp1->next!=NULL){
            temp1=temp1->next;
       }
    }

    for(i=0;i<group_counter2;i++){
        if(temp2->next!=NULL){
            temp2=temp2->next;
       }
    }

   /* printf("ID patera %d ID patera %d \n",generation_array[num_of_gen-1]->group_in_population[group_counter1]->person_in_group[person_counter1]->id,generation_array[num_of_gen-1]->group_in_population[group_counter2]->person_in_group[person_counter2]->id);
*/
    for(i=0;i<genes_per_person;i++){
        which_parent=rand()%2;
        /*row_swapping*/
        if(which_parent==0){
            for(j=0;j<genes_per_person;j++){
                new_dependancies[i][j]=temp1->person_in_group[person_counter1]->gene_interactions[i][j];
            }
        }
        else{
            for(j=0;j<genes_per_person;j++){
                new_dependancies[i][j]=temp2->person_in_group[person_counter2]->gene_interactions[i][j];
            }
        }
    }

    create_mutations(new_dependancies);
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
        new_choose_fitted_father_dependencies_combined(num_of_gen,new_person->gene_interactions);
    }
    else {
        choose_fitted_father_dependencies_no_combinations(num_of_gen,new_person->gene_interactions);
    }
    printf("R1:%d R2:%d",new_person->gene_R1[0],new_person->gene_R2[0]);
    printf("Created Person\n");
    return new_person;
}

group *gen_create_group_fit(int starting_id,int num_of_gen, int num_of_parents){
    int i;

    group *new_group;
    new_group = (group*)calloc(1, sizeof(group));

    for(i=0;i<persons_per_group;i++){
      /*  printf("Creating Atomo %d\n",i); */
        new_group->person_in_group[i]=gen_create_person_fit(i,num_of_gen, num_of_parents);
        /*printf("Atomo created %d\n",i);*/
    }
    return new_group;
}


population *create_gen_population_fit(int num_of_gen, int num_of_parents){
    int i;
    group *temp;

    population *new_population;
    new_population = (population*)calloc(1, sizeof(population));


    calculate_fitness(num_of_gen);

    for(i=0;i<curr_num_of_groups;i++){
        if(i==0){
            /*printf("Head on the group_list of the generation 0");*/       
            new_population->groups_list=gen_create_group_fit(i,num_of_gen,num_of_parents); /*create pointer to group_list, save on the population array*/
            new_population->groups_list->next=NULL;
            new_population->groups_list->prev=NULL;
        }
        else{
            temp=new_population->groups_list;
            while(temp->next!=NULL){
                temp=temp->next;
            }
            temp->next=gen_create_group_fit(i,num_of_gen,num_of_parents);
            temp->next->next=NULL;
            temp->next->prev=temp;
        }
    }
    /*printf("Generation Created\n");*/
    return new_population;
}