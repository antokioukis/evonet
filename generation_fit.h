void calculate_fitness(int num_of_gen,float lamda){
    int i,j,k,c,t;
    /*int w,n;*/
    person* atomo;
    int num_of_steps;
    float sum_of_personal_fitness_cycles=0;
    float personal_fitness;
    float distance;
    float non_descrete_res[max_genes_per_person];
    int sum=0;
   /* int optimal[max_genes_per_person]={1,1,1,1}; */
    int optimal[max_genes_per_person]={1,1,1,1,1,1,1,1,1,1};
    group* temp;

    /*printf("num_of_gen:%d \n",num_of_gen);*/
    temp=generation_array[num_of_gen]->groups_list;
    /*gia ka8e atomo tou pli8ismou*/
    for(i=0;i<curr_num_of_groups;i++){
        for(j=0;j<persons_per_group;j++){
        /*gia na min grafw olo auto to makrinari*/
            atomo=temp->person_in_group[j];
           /* printf("ID atomou: %d, periodos %d\n",atomo->id,atomo->periodos);*/
            /*parousiazei kikliko equilibrium*/
            if(atomo->periodos>1){
                num_of_steps=atomo->periodos;
                /*kane pollaplisiasmous osous exeis periodo (proxwra bimata)*/
                /*NEEDS MORE TESTING , printf ka8e apotelesma pou mpainei kai bgainei apo to matrix multiplication*/
                for(k=0;k<num_of_steps;k++){

                   /* for (w=0;w<max_genes_per_person;w++){
                        for(n=0;n<max_genes_per_person;n++){
                            printf("%f ", atomo->gene_interactions[w][n]);
                        }
                        printf("\n");
                    }

                    for(w=0;w<max_genes_per_person;w++){
                        printf("%d ", atomo->vector_of_signs[w]);
                    } printf("\n");
                    */

                    for (c = 0; c < genes_per_person; c++) {
                        for (t = 0; k < genes_per_person; t++) {
                            sum = sum + atomo->gene_interactions[c][t]*atomo->vector_of_signs[t];
                        }
                        non_descrete_res[c] = sum;
                        sum = 0;
                    }

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
               /* printf("Personal Fitness %f\n",temp->person_in_group[j]->fitness); */
            }
            generation_array[num_of_gen]->sum_of_fitness+=personal_fitness;
           /* printf("Generation Fitness %f\n",generation_array[num_of_gen-1]->sum_of_fitness); */
            sum_of_personal_fitness_cycles=0;
        }
        if(temp->next!=NULL){
            temp=temp->next;
       }
    }
}


R1_R2_auxiliary *choose_fitted_father_dependencies_no_combinations(int num_of_gen){
    float fitness_array[(num_of_groups*persons_per_group)];
/*  int theseis_pinaka=num_of_groups*persons_per_group; */
    int counter=0;
    int i,j;
    double fitness_asked=0;
    int group_counter,person_counter;
    group *temp=generation_array[num_of_gen-1]->groups_list;
    R1_R2_auxiliary *new_auxiliary;

  /*  printf("Fitted fathers no_combinations\n"); */
    new_auxiliary = (R1_R2_auxiliary*)calloc(1, sizeof(R1_R2_auxiliary));


    /*pinakas fitness einai to dianisma me ta miki analoga me to poso fitted einai*/
    for(i=0;i<curr_num_of_groups;i++){
        for(j=0;j<persons_per_group;j++){
            if(i==0&&j==0){
                fitness_array[counter]=temp->person_in_group[j]->fitness;
            }
            else{
                fitness_array[counter]=fitness_array[counter-1]+temp->person_in_group[j]->fitness;
            }
           /* printf("Atomiko FItness: %f \n",temp->person_in_group[j]->fitness);*/
          /*  printf("Fitness_array[%d]:%f \n",counter,fitness_array[counter]);*/
            counter++;
        }
        if(temp->next!=NULL){
            temp=temp->next;
       }
    }
    

/*    printf("Fitness_array[%d]= %f \n",theseis_pinaka-1,fitness_array[theseis_pinaka-1]);*/
/*    printf("Fitness of generation = %f  \n",generation_array[num_of_gen-1]->sum_of_fitness);*/

    /*na brw to fitness pou zitaei kai apo ekei mesa na brw ton patera*/
    fitness_asked=((double)rand() / RAND_MAX)*generation_array[num_of_gen-1]->sum_of_fitness;
  /*  printf("fitness1_asked: %f \n",fitness_asked1); */

    counter=0;
    while(fitness_asked>fitness_array[counter]){
        counter++;
    }

   /* printf("Counter2= %d\n",counter1); */

    group_counter=counter/persons_per_group;
    person_counter=counter%persons_per_group;

    for(i=0;i<group_counter;i++){
        if(temp->next!=NULL){
            temp=temp->next;
       }
    }

   /* printf("ID patera %d ID patera %d \n",generation_array[num_of_gen-1]->group_in_population[group_counter1]->person_in_group[person_counter1]->id,generation_array[num_of_gen-1]->group_in_population[group_counter2]->person_in_group[person_counter2]->id);
*/

    for(i=0;i<genes_per_person;i++){
        new_auxiliary->R1[i]=temp->person_in_group[person_counter]->gene_R1[i];
    }

    for(i=0;i<genes_per_person;i++){
        new_auxiliary->R2[i]=temp->person_in_group[person_counter]->gene_R2[i];
    }
    /*
    printf("Pira apo prwto patera %d gonidia\n", genes_from_first_parent);
    for(i=0;i<max_genes_per_person;i++){
        printf("R1:%d R2: %d\n", new_auxiliary->R1[i],new_auxiliary->R2[i]);
    }

*/
 /*
    for (i = 0; i < max_genes_per_person; i++){
        for(j=0;j<max_genes_per_person;j++){
            printf("%d ",new_auxiliary->dependancies[i][j]);
        }
        printf("\n");
    }
*/
    return new_auxiliary;
}

R1_R2_auxiliary *choose_fitted_father_dependencies_combined_R1R2_swapping(int num_of_gen){
    float fitness_array[(num_of_groups*persons_per_group)];
/*  int theseis_pinaka=num_of_groups*persons_per_group; */
    int counter=0;
    int genes_from_first_parent;
    int counter1=0;
    int counter2=0;
    int i,j;
    double fitness_asked1=0;
    double fitness_asked2=0;
    int group_counter1,person_counter1,group_counter2,person_counter2;
    group *temp;
    group *temp1;
    group *temp2;
    R1_R2_auxiliary *new_auxiliary;


    /*printf("Fitted fathers R1R2_swapping\n");*/

    temp=generation_array[num_of_gen-1]->groups_list;
    temp1=generation_array[num_of_gen-1]->groups_list;
    temp2=generation_array[num_of_gen-1]->groups_list;
   
    new_auxiliary = (R1_R2_auxiliary*)calloc(1, sizeof(R1_R2_auxiliary));


    /*pinakas fitness einai to dianisma me ta miki analoga me to poso fitted einai*/
    for(i=0;i<curr_num_of_groups;i++){
        for(j=0;j<persons_per_group;j++){
            if(i==0&&j==0){
                fitness_array[counter]=temp->person_in_group[j]->fitness;
            }
            else{
                fitness_array[counter]=fitness_array[counter-1]+temp->person_in_group[j]->fitness;
            }
           /* printf("Atomiko FItness: %f \n",temp->person_in_group[j]->fitness);*/
          /*  printf("Fitness_array[%d]:%f \n",counter,fitness_array[counter]);*/
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
  /*  printf("fitness1_asked: %f \n",fitness_asked1); */

    fitness_asked2=((double)rand() / RAND_MAX)*generation_array[num_of_gen-1]->sum_of_fitness;
   /* printf("fitness2_asked: %f \n",fitness_asked2); */

    counter1=0;
    while(fitness_asked1>fitness_array[counter1]){
        counter1++;
    }
   /* printf("Counter1= %d\n",counter1); */

    counter2=0;
    while(fitness_asked2>fitness_array[counter2]){
        counter2++;
    }

   /* printf("Counter2= %d\n",counter1); */

    group_counter1=counter1/persons_per_group;
    person_counter1=counter1%persons_per_group;
    /*printf("Group Counter1 %d person_counter1 %d \n",group_counter1,person_counter1); */
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
            new_auxiliary->R1[i]=temp1->person_in_group[person_counter1]->gene_R1[i];
        }
        else{
            new_auxiliary->R1[i]=temp2->person_in_group[person_counter2]->gene_R1[i];
        }
    }

    for(i=0;i<genes_per_person;i++){
        if(i<genes_from_first_parent){
            new_auxiliary->R2[i]=temp2->person_in_group[person_counter2]->gene_R2[i];
        }
        else{
            new_auxiliary->R2[i]=temp1->person_in_group[person_counter1]->gene_R2[i];
        }
    }
    /*
    printf("Pira apo prwto patera %d gonidia\n", genes_from_first_parent);
    for(i=0;i<max_genes_per_person;i++){
        printf("R1:%d R2: %d\n", new_auxiliary->R1[i],new_auxiliary->R2[i]);
    }
    */
    return new_auxiliary;
}

R1_R2_auxiliary* choose_fitted_father_dependencies_combined_row_swapping(int num_of_gen){
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
    R1_R2_auxiliary *new_auxiliary;
    
   /* printf("Fitted fathers row_swapping\n");*/

    new_auxiliary = (R1_R2_auxiliary*)calloc(1, sizeof(R1_R2_auxiliary));

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

    for(i=0;i<genes_per_person;i++){
        which_parent=rand()%2;
        /*row_swapping*/
        if(which_parent==0){
            for(j=0;j<genes_per_person;j++){
                new_auxiliary->R1[j]=temp1->person_in_group[person_counter1]->gene_R1[j];
            }
        }
        else{
            for(j=0;j<genes_per_person;j++){
                new_auxiliary->R1[j]=temp1->person_in_group[person_counter2]->gene_R1[j];
            }
        }
    }

    for(i=0;i<genes_per_person;i++){
        which_parent=rand()%2;
        /*row_swapping*/
        if(which_parent==0){
            for(j=0;j<genes_per_person;j++){
                new_auxiliary->R2[j]=temp1->person_in_group[person_counter1]->gene_R2[j];
            }
        }
        else{
            for(j=0;j<genes_per_person;j++){
                new_auxiliary->R1[j]=temp1->person_in_group[person_counter1]->gene_R2[j];
            }
        }
    }
    
    return new_auxiliary;

   /* printf("ID patera %d ID patera %d \n",generation_array[num_of_gen-1]->group_in_population[group_counter1]->person_in_group[person_counter1]->id,generation_array[num_of_gen-1]->group_in_population[group_counter2]->person_in_group[person_counter2]->id);
*/
}


person *gen_create_person_fit(int id,int num_of_gen, int num_of_parents,int row_swapping,int min_count,int max_count,double mutation_rate){
    int i,j;
    /*int j;*/
    R1_R2_auxiliary *auxiliary;
    person *new_person;
    new_person = (person*)calloc(1, sizeof(person));

    new_person->id=id;

    for (i=0;i<genes_per_person;i++){
        new_person->gene_counts[i]=rand_interval(min_count,max_count);
    }

    for(i=0;i<genes_per_person;i++){
        new_person->vector_of_signs[i]=1;
    }

/*    printf("Creating Inheritance\n");*/
    if(num_of_parents){
        if(row_swapping){
            auxiliary=choose_fitted_father_dependencies_combined_row_swapping(num_of_gen);
        }
        else{
            auxiliary=choose_fitted_father_dependencies_combined_R1R2_swapping(num_of_gen);
        }
       /* printf("Atomo %d\n",id); */
    }
    else{
        auxiliary=choose_fitted_father_dependencies_no_combinations(num_of_gen);
    }

    /*printf("Created Person\n");*/
    for(i=0;i<genes_per_person;i++){
        new_person->gene_R1[i]=auxiliary->R1[i];
        new_person->gene_R2[i]=auxiliary->R2[i];
       /* printf("R1: %d R2: %d \n",new_person->gene_R1[i],new_person->gene_R2[i]); */
    
    }/*
    printf("\n");
    for (i = 0; i < max_genes_per_person; i++){
        for(j=0;j<max_genes_per_person;j++){
            printf("%f ",new_person->gene_interactions[i][j]);
        }
        printf("\n");
    }
*/
    new_person=create_mutations(new_person,mutation_rate);

    for(i=0;i<genes_per_person;i++){
        for(j=0;j<genes_per_person;j++){
            /*new_person->gene_interactions[i][j]=random_normal_distrubution(0,sqrt(10));*/
            new_person->gene_interactions[i][j]=create_gene_interactions(new_person->gene_R1[i],new_person->gene_R2[j]);
          /*  printf("%f ",create_gene_interactions(new_auxiliary->R1[i],new_auxiliary->R2[j]));
            extract_person(R1[i],R2[j]);*/
            /*if (new_person->gene_interactions[i][j]<0) printf("Arnitiko gene interaction %f\n",new_person->gene_interactions[i][j]);
            */
        }
   /*     printf("\n"); */
    }

    free(auxiliary);

    return new_person;
}

group *gen_create_group_fit(int starting_id,int num_of_gen, int num_of_parents,int row_swapping,int min_count,int max_count,double mutation_rate){
    int i;

    group *new_group;
    new_group = (group*)calloc(1, sizeof(group));
/*printf("Group:%d \n",starting_id);*/
    for(i=0;i<persons_per_group;i++){
      /*  printf("Creating Atomo %d\n",i); */
        new_group->person_in_group[i]=gen_create_person_fit(i,num_of_gen, num_of_parents,row_swapping,min_count,max_count,mutation_rate);
        /*printf("Atomo created %d\n",i);*/
    }
    return new_group;
}


population *create_gen_population_fit(int num_of_gen, int num_of_parents,int row_swapping,int min_count,int max_count,double mutation_rate){
    int i;
    group *temp;

    population *new_population;
    new_population = (population*)calloc(1, sizeof(population));

    for(i=0;i<curr_num_of_groups;i++){
        if(i==0){
            /*printf("Head on the group_list of the generation 0");*/       
            new_population->groups_list=gen_create_group_fit(i,num_of_gen,num_of_parents,row_swapping,min_count,max_count,mutation_rate); /*create pointer to group_list, save on the population array*/
            new_population->groups_list->next=NULL;
            new_population->groups_list->prev=NULL;
        }
        else{
            temp=new_population->groups_list;
            while(temp->next!=NULL){
                temp=temp->next;
            }
            temp->next=gen_create_group_fit(i,num_of_gen,num_of_parents,row_swapping,min_count,max_count,mutation_rate);
            temp->next->next=NULL;
            temp->next->prev=temp;
        }
    }
    /*printf("Generation Created\n");*/
    return new_population;
}