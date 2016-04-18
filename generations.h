population_list *generation_array[num_of_max_generations];
int total_new_population=0;
int total_generations=0;

personal_gene_interaction_matrix *inherit_from_random_father_gene_dependancies(){
    personal_gene_interaction_matrix *patera_gene_dependancies;
    int id_patera,k,l;
    population_list *temp=generation_array[total_generations-1];

    id_patera=rand()%total_new_population;
  //  printf("id_patera %d \n",id_patera);

    while(id_patera>=group_persons) {
        temp=temp->next;
        if(debug_mode) printf("Megalitero proxwraw sto epomeno group: +%d\n",group_persons);
        id_patera=id_patera-group_persons;
    }

    id_patera=id_patera%group_persons;
  //  printf("Apo pinaka id %d \n",temp->groups->personal_record[id_patera]->personal_id);
    patera_gene_dependancies=temp->groups->personal_record[id_patera]->gene_dependancies;

    return patera_gene_dependancies;
}

personal_gene_interaction_matrix *create_mutations(personal_gene_interaction_matrix *base_array){
    int num_of_mutations,sign_mutation,thesi_mutation[2];
    int i;
    float final_mutation,mutation;

    personal_gene_interaction_matrix *ptr_to_gene_dependencies;
    ptr_to_gene_dependencies = (personal_gene_interaction_matrix *)malloc(sizeof(personal_gene_interaction_matrix));

    ptr_to_gene_dependencies=base_array;

    if(ptr_to_gene_dependencies==NULL){
        printf("Not enough memory for new personal_gene_interaction_matrix\n");
        exit(EXIT_FAILURE);
    }

    num_of_mutations=rand()%4;

    if(debug_mode)printf("Arithmos Mutations: %d \n", num_of_mutations);

    for (i=0;i<num_of_mutations;i++){

        sign_mutation=rand()%2;
        thesi_mutation[0]=rand()%genes_per_person;
        thesi_mutation[1]=rand()%genes_per_person;

       if(debug_mode) printf("Mutations stis theseis %d %d\n",thesi_mutation[0],thesi_mutation[1] );

        mutation=random_normal_distrubution(0,sqrt(10));

        if(sign_mutation){
            final_mutation=mutation;
        }
        else{
            final_mutation=-1*mutation;
        }
        ptr_to_gene_dependencies->gene_inter_matrix[thesi_mutation[0]][thesi_mutation[1]]=final_mutation;
    }
    return ptr_to_gene_dependencies;
}

/*create personal records for each individual. (no new_gene_count since there is no aging when they are "born")*/
personal_records *gen_create_personal_records(int personal_id){
    int k,l;
    personal_records *ptr_to_personal_records;
    ptr_to_personal_records = (personal_records *)malloc(sizeof(personal_records));
    if ( ptr_to_personal_records == NULL ){
        printf("No memory left ptr_to_personal_records on create_personal_records\n");
        exit(EXIT_FAILURE);
    }

        /*fill the ptr_personal_records fields*/
        ptr_to_personal_records->personal_id=personal_id;
        ptr_to_personal_records->ptr_to_genes_count=initialize_personal_gene_count();
        //printf("ready to inherit\n");
        ptr_to_personal_records->gene_dependancies=inherit_from_random_father_gene_dependancies();
        ptr_to_personal_records->gene_dependancies=create_mutations(ptr_to_personal_records->gene_dependancies);

        ptr_to_personal_records->ptr_to_personal_r1=initialize_r1();
        ptr_to_personal_records->ptr_to_personal_r2=initialize_r2();
        ptr_to_personal_records->ptr_personal_plastic_array=initialize_plastic_array();
        ptr_to_personal_records->ptr_to_plastics=initialize_plastics(ptr_to_personal_records->ptr_to_genes_count);
        ptr_to_personal_records->fitness=0;

        return ptr_to_personal_records;
}

/*for everyone in a group call create_personal_records to create them*/
array_of_group *gen_create_group_persons_array(int max_id){
    int i;
    array_of_group *ptr_grp_person_array;
    ptr_grp_person_array = (array_of_group *)malloc(sizeof(array_of_group));
    if ( ptr_grp_person_array == NULL ){
        printf("No memory left ptr_grp_person_array on create_group_persons_array\n");
        exit(EXIT_FAILURE);
    }

    /*fill the ptr_to_grp_person_array*/
    for (i=0;i<group_persons;i++){
        ptr_grp_person_array->personal_record[i]=gen_create_personal_records(i);
    }

    return ptr_grp_person_array;
}

/*add new population on population_list the new people always on the head of the population list*/
population_list *gen_add_population_node(population_list *plist_head,int max_id){
    int counter=0;
    population_list *temp=plist_head;
    struct population_list *new_node = (population_list*)malloc(sizeof(population_list));

    if ( new_node == NULL ){
        printf("No memory left new_node on add_population_node\n");
        exit(EXIT_FAILURE);
    }

    /*fill the new_node fields*/
    new_node->next = NULL;
    new_node->groups=gen_create_group_persons_array(max_id);

    if (temp==NULL) {plist_head=new_node;}
    else{
        while(temp->next!=NULL){
            temp=temp->next;
            counter++;
        }
        temp->next=new_node;
    }
    return plist_head;
}

/*determine how many people_groups are needed to store the new people then call add_population_node to actually add them*/
population_list *gen_add_population(int population){
    int i;
    population_list *plist_head=NULL;
    total_new_population=0;
    total_new_population=(population*group_persons)+total_new_population;     /*add to global used for delete*/
    for (i=0;i<population;i++){
        plist_head=gen_add_population_node(plist_head,i);
    }
    printf("Total New Population:%d\n",total_new_population);
    return plist_head;
}

population_list *create_new_generation(int population,int fitness_flag){
    total_generations++;
    if(fitness_flag){
        printf("fitness not implemented yet\n");
    }
    else{
        return gen_add_population(population);
    }
}
