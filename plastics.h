
plastic_records *create_plastic_records(personal_gene_list *ptr_to_new_personal_gene_counts){
    plastic_records *new_plastic_records;
    int i;

    new_plastic_records= (plastic_records *)malloc(sizeof(plastic_records));
    if ( new_plastic_records == NULL ){
        printf("No memory left new_plastic_records\n");
        exit(EXIT_FAILURE);
    }
    for(i=0;i<genes_per_person;i++){
        if(ptr_to_new_personal_gene_counts->indi_gene_array[i][1]<0){
            new_plastic_records->plastic_recs[i]=-1;
        }
        else {
             new_plastic_records->plastic_recs[i]=1;
        }
    }

    return new_plastic_records;
}

/*create new personal gene counts by multiplying the last gene counts with the personal interaction matrix.Put the new gene counts
on the head of the list of personal new_gene_counts_list*/
void create_new_gene_counts(personal_records *personal_record,int generation){
    int i,j,b;
    float a;
    personal_gene_list *ptr_to_new_personal_gene_counts;

    ptr_to_new_personal_gene_counts= (personal_gene_list *)malloc(sizeof(personal_gene_list));
    if ( ptr_to_new_personal_gene_counts == NULL ){
        printf("No memory left ptr_to_new_personal_gene_counts\n");
        exit(EXIT_FAILURE);
    }

    /*place the new_counts at the head of the new_gene_counts*/
    ptr_to_new_personal_gene_counts->next=personal_record->ptr_to_new_genes_count;
    personal_record->ptr_to_new_genes_count=ptr_to_new_personal_gene_counts;

    /*if it is the first generation there are no new_gene_counts, thus we have to create them from the original gene counts*/
    if (generation==0){
        for (i=0;i<genes_per_person;i++){
            for(j=0;j<genes_per_person;j++){
                a=personal_record->gene_dependancies->gene_inter_matrix[i][j];
                b=personal_record->ptr_to_genes_count->indi_gene_array[j][1];
                ptr_to_new_personal_gene_counts->indi_gene_array[i][0]=i;
                ptr_to_new_personal_gene_counts->indi_gene_array[i][1]+=(a*b);
              }
        }
    }
    /*Now we have some new_gene_counts so the next generation is produced using the last generations gene_counts*/
    else{
        for (i=0;i<genes_per_person;i++){
            for(j=0;j<genes_per_person;j++){
                a=personal_record->gene_dependancies->gene_inter_matrix[i][j];
                b=personal_record->ptr_to_new_genes_count->next->indi_gene_array[j][1];
                ptr_to_new_personal_gene_counts->indi_gene_array[i][0]=i;
                ptr_to_new_personal_gene_counts->indi_gene_array[i][1]+=(a*b);
            }
        }
    }
    ptr_to_new_personal_gene_counts->personal_plastic_records=create_plastic_records(ptr_to_new_personal_gene_counts);
}

/*create new generations by calling create_new_gene_counts num_of_gens times for everyone on the population*/
void aging(int num_of_gens){
    int i,j;
    population_list *temp=plist_head;
    for(i=0;i<num_of_gens;i++){
       /*"Advance the whole population*/
        while(temp!=NULL){
            for(j=0;j<group_persons;j++){
                create_new_gene_counts(temp->groups->personal_record[j],i);
            }
            temp=temp->next;
        }
        temp=plist_head;
    }
}

/*check each individual for plasticity of genes by comparing each new_genes_count record with all the others personal gene_counts*/
/*Mono sta atoma pou den einai idi plastika*/
int check_plasticity(personal_gene_list *personal_recs){
    personal_gene_list *temp1=personal_recs;
    personal_gene_list *temp2=personal_recs->next;
    int i;/*plastic_flag=0*/
    if (temp1==NULL){
        printf("No new gene counts. Will exit now\n");
        exit(EXIT_FAILURE);
    }
    /*actual checking takes place here.For everyone, for every generation check*/
    while(temp1!=NULL){
        printf("den mpainw pote sto while?\n");
        while(temp2!=NULL){
            for(i=0;i<genes_per_person;i++){
                if(temp1->personal_plastic_records->plastic_recs[i]!=temp2->personal_plastic_records->plastic_recs[i]){
                    printf("Not plastic yet\n");
                    return 0;
                }
            }
            temp2=temp2->next;
        }
        temp1=temp1->next;
    }

    return 1;
}

/*wrapper function to call check_plasticity for scaning each on the population for plasticity*/
void general_plasticity(){
    int j;
    population_list *temp=plist_head;
    while(temp!=NULL){
        for(j=0;j<group_persons;j++){
            /* For everyone for every generation passed */
            if(!temp->groups->personal_record[j]->ptr_to_new_genes_count->personal_plastic_records->isplastic){
                printf("Already plastic\n");
            }
            else{
                if (check_plasticity(temp->groups->personal_record[j]->ptr_to_new_genes_count)){
                    printf("MPika check plasticity\n");
                    temp->groups->personal_record[j]->ptr_to_new_genes_count->personal_plastic_records->isplastic=1;
                }
            }
        }
        temp=temp->next;
    }
}

int check_pop_plastic(){
    population_list *temp=plist_head;
    int j;
    while(temp!=NULL){
        for(j=0;j<group_persons;j++){
            if(temp->groups->personal_record[j]->ptr_to_new_genes_count->personal_plastic_records->isplastic!=true){
                 printf("Whole population NOT mature\n");
                 return -1;
            }
        }
    }
    printf("Whole population mature\n");
    return 1;
}
