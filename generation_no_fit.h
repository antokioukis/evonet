void create_mutations(float new_dependancies[genes_per_person][genes_per_person]){
    int num_of_mutations,sign_mutation,thesi_mutation[2];
    int i;
    float final_mutation,mutation;
    const gsl_rng_type * T;
    gsl_rng * r;
    /*float u;*/

    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc (T);
    
    num_of_mutations=gsl_ran_poisson (r, rate_of_mutation);
    /*printf("Arithmos Mutations: %d \n", num_of_mutations); */

    for (i=0;i<num_of_mutations;i++){

        sign_mutation=rand()%2;
        thesi_mutation[0]=rand()%genes_per_person;
        thesi_mutation[1]=rand()%genes_per_person;

     /*   printf("Mutations stis theseis %d %d\n",thesi_mutation[0],thesi_mutation[1] );*/

        mutation=random_normal_distrubution(0,sqrt(10));

        if(sign_mutation){
            final_mutation=mutation;
        }
        else{
            final_mutation=-1*mutation;
        }
     /*   printf("Old %f \n",new_dependancies[thesi_mutation[0]][thesi_mutation[1]]);*/
        new_dependancies[thesi_mutation[0]][thesi_mutation[1]]=final_mutation;
     /*   printf("New %f \n",new_dependancies[thesi_mutation[0]][thesi_mutation[1]]);*/
    }
}

/*
void create_mutations(float new_dependancies[genes_per_person][genes_per_person]){
    int num_of_mutations,sign_mutation,thesi_mutation;
    int i;
    float final_mutation,mutation;
    const gsl_rng_type * T;
    gsl_rng * r;
    float u;

    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc (T);
    
    num_of_mutations=gsl_ran_poisson (r, rate_of_mutation);
    printf("Arithmos Mutations: %d \n", num_of_mutations);

    for (i=0;i<num_of_mutations;i++){

        1 gia mutation sto R2
        0 gia mutation sto R1
        R1_or_R2_mutated=rand()%2;

        thesi_mutation=rand()%genes_per_person;
        printf("Mutations stis theseis %d\n",thesi_mutation);

        if(R1_or_R2_mutated){
            new_dependancies[]=
        }
        else{

        }
        printf("Old %f \n",new_dependancies[thesi_mutation[0]][thesi_mutation[1]]);
        new_dependancies[thesi_mutation[0]][thesi_mutation[1]]=final_mutation;
        printf("New %f \n",new_dependancies[thesi_mutation[0]][thesi_mutation[1]]);
    }
}
*/

R1_R2_auxiliary *choose_random_father_dependencies_combined_R1R2_swapping(int num_of_gen){
    int id_patera1,id_patera2;
    int genes_from_first_parent;
    int i,j;
    int group_counter1,person_counter1,group_counter2,person_counter2;
    group *temp1=generation_array[num_of_gen-1]->groups_list;
    group *temp2=generation_array[num_of_gen-1]->groups_list;
   /* printf("random PLUS combinations\n"); */

    R1_R2_auxiliary *new_auxiliary;
    new_auxiliary = (R1_R2_auxiliary*)calloc(1, sizeof(R1_R2_auxiliary));

    id_patera1=rand()%(curr_num_of_groups*persons_per_group);
    id_patera2=rand()%(curr_num_of_groups*persons_per_group);


    group_counter1=id_patera1/persons_per_group;
    person_counter1=id_patera1%persons_per_group;
    /*printf("Group Counter1 %d person_counter1 %d \n",group_counter1,person_counter1); */
    group_counter2=id_patera2/persons_per_group;
    person_counter2=id_patera2%persons_per_group; 


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
    for(i=0;i<genes_per_person;i++){
        printf("R1:%d R2: %d\n", new_auxiliary->R1[i],new_auxiliary->R2[i]);
    }

    printf("\n");
    printf("New dependancies\n");
  */  for(i=0;i<genes_per_person;i++){
        for(j=0;j<genes_per_person;j++){
            /*new_person->gene_interactions[i][j]=random_normal_distrubution(0,sqrt(10));*/
            new_auxiliary->dependancies[i][j]=create_gene_interactions(new_auxiliary->R1[i],new_auxiliary->R2[j]);
          /*  printf("%f ",create_gene_interactions(new_auxiliary->R1[i],new_auxiliary->R2[j]));
            extract_person(R1[i],R2[j]);*/
        }
   /*     printf("\n"); */
    }

 /*
    for (i = 0; i < genes_per_person; i++){
        for(j=0;j<genes_per_person;j++){
            printf("%d ",new_auxiliary->dependancies[i][j]);
        }
        printf("\n");
    }
*/
    /*create_mutations(new_dependancies);*/
    return new_auxiliary;
}

R1_R2_auxiliary *choose_random_father_dependencies_combined_row_swapping(int num_of_gen){
    int group_counter1=0;
    int person_counter1=0;
    int id_patera1,i,j;

    int group_counter2=0;
    int person_counter2=0;
    int id_patera2;

    R1_R2_auxiliary *new_auxiliary;
    group *temp2,*temp1;

    int which_parent;

    new_auxiliary = (R1_R2_auxiliary*)calloc(1, sizeof(R1_R2_auxiliary));

    temp1=generation_array[num_of_gen-1]->groups_list;
    temp2=generation_array[num_of_gen-1]->groups_list;
    /*printf("No fitness PLUS combined");*/

    id_patera1=rand()%(curr_num_of_groups*persons_per_group);
    id_patera2=rand()%(curr_num_of_groups*persons_per_group);


    group_counter1=id_patera1/persons_per_group;
    person_counter1=id_patera1%persons_per_group;
/*    printf("Group_of_father %d Person_on_group %d \n",group_counter,person_counter); */

    group_counter2=id_patera2/persons_per_group;
    person_counter2=id_patera2%persons_per_group;

    for(i=0;i<group_counter1;i++){
        temp1=temp1->next;
    }

    for(i=0;i<group_counter2;i++){
        temp2=temp2->next;
    }

    for(i=0;i<genes_per_person;i++){
        which_parent=rand()%2;
        /*row_swapping*/
        if(which_parent==0){
            for(j=0;j<genes_per_person;j++){
                new_auxiliary->dependancies[i][j]=temp1->person_in_group[person_counter1]->gene_interactions[i][j];
            }
        }
        else{
            for(j=0;j<genes_per_person;j++){
                new_auxiliary->dependancies[i][j]=temp2->person_in_group[person_counter2]->gene_interactions[i][j];
            }
        }
    }
    
    return new_auxiliary;
    /*create_mutations(new_dependancies); */
}


R1_R2_auxiliary *choose_random_father_dependencies_no_combinations(int num_of_gen){
    int group_counter=0;
    int person_counter=0;
    int id_patera,i,j;
    R1_R2_auxiliary *new_auxiliary;


    group *temp=generation_array[num_of_gen-1]->groups_list;
    new_auxiliary = (R1_R2_auxiliary*)calloc(1, sizeof(R1_R2_auxiliary));

    id_patera=rand()%(curr_num_of_groups*persons_per_group);
    /*printf("ID_patera:%d \n",id_patera); */

    group_counter=id_patera/persons_per_group;
    person_counter=id_patera%persons_per_group;
    /*printf("Group_of_father %d Person_on_group %d \n",group_counter,person_counter); */
    for(i=0;i<group_counter;i++){
        temp=temp->next;
    }

    for(i=0;i<genes_per_person;i++){
        new_auxiliary->R1[i]=temp->person_in_group[person_counter]->gene_R1[i];
    }

    for(i=0;i<genes_per_person;i++){
        new_auxiliary->R2[i]=temp->person_in_group[person_counter]->gene_R2[i];
    }

    for(i=0;i<genes_per_person;i++){
        for(j=0;j<genes_per_person;j++){
            new_auxiliary->dependancies[i][j]=temp->person_in_group[person_counter]->gene_interactions[i][j];
        }
    }



    /*create_mutations(new_dependancies);*/
    return new_auxiliary;
}


person *gen_create_person_no_fit(int id,int num_of_gen, int num_of_parents){
    int i;
    int j;
    R1_R2_auxiliary *auxiliary;
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
        /*auxiliary=choose_random_father_dependencies_combined_row_swapping(num_of_gen);*/
        auxiliary=choose_random_father_dependencies_combined_R1R2_swapping(num_of_gen);
    }
    else{
        auxiliary=choose_random_father_dependencies_no_combinations(num_of_gen);
    }

    for(i=0;i<genes_per_person;i++){
        new_person->gene_R1[i]=auxiliary->R1[i];
        new_person->gene_R2[i]=auxiliary->R2[i];
        for(j=0;j<genes_per_person;j++){
            new_person->gene_interactions[i][j]=auxiliary->dependancies[i][j];
        }
       /* printf("R1: %d R2: %d \n",new_person->gene_R1[i],new_person->gene_R2[i]); */
    
    }/*
    printf("\n");
    for (i = 0; i < genes_per_person; i++){
        for(j=0;j<genes_per_person;j++){
            printf("%f ",new_person->gene_interactions[i][j]);
        }
        printf("\n");
    }
*/
    return new_person;
}

group *gen_create_group_no_fit(int starting_id,int num_of_gen, int num_of_parents){
    int i;

    group *new_group;
    new_group = (group*)calloc(1, sizeof(group));

    for(i=0;i<persons_per_group;i++){
       /* printf("Creating Atomo %d\n",i);*/
        new_group->person_in_group[i]=gen_create_person_no_fit(i,num_of_gen, num_of_parents);
        /*printf("Atomo created %d\n",i);*/
    }
    return new_group;
}

population *create_gen_population_no_fit(int num_of_gen, int num_of_parents){
    int i;
    group *temp;

    population *new_population;
    new_population = (population*)calloc(1, sizeof(population));

    for(i=0;i<curr_num_of_groups;i++){
        if(i==0){
            /*printf("Head on the group_list of the generation 0"); */           
            new_population->groups_list=gen_create_group_no_fit(i,num_of_gen,num_of_parents); /*create pointer to group_list, save on the population array*/
            new_population->groups_list->next=NULL;
            new_population->groups_list->prev=NULL;
        }
        else{
            temp=new_population->groups_list;
            while(temp->next!=NULL){
                temp=temp->next;
            }
            temp->next=gen_create_group_no_fit(i,num_of_gen,num_of_parents);
            temp->next->next=NULL;
            temp->next->prev=temp;
        }
    }
    printf("Generation Created\n");
    return new_population;
}