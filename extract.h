void extract_R1R2_generation(FILE *f, int num_of_gen){
    int k,l,i;
    
    group *temp;

    /* f = fopen("R1R2.txt", "a"); */
    temp=generation_array[num_of_gen]->groups_list;

    if (f == NULL)
    {
        printf("Error opening file r1r2!\n");
        exit(1);
    }

    fprintf(f, "Generation %d: Population: %d Number of Genes: %d\n", num_of_gen,curr_num_of_groups*persons_per_group,genes_per_person);

    for(k=0;k<curr_num_of_groups;k++){
        for(l=0;l<persons_per_group;l++){
            for(i=0;i<genes_per_person;i++){
                fprintf(f, "%d \n",temp->person_in_group[l]->gene_R1[i]);
            }
            for(i=0;i<genes_per_person;i++){
                fprintf(f, "%d \n",temp->person_in_group[l]->gene_R2[i]);
            }
        }

        if(temp->next!=NULL){
                temp=temp->next;
        }

    }

    return;
}

void extract_gene_dependancies_matrix_generation(FILE* f, int num_of_gen){
    int k,l,i,j;
    
    group *temp;

    
    temp=generation_array[num_of_gen]->groups_list;

    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(f, "\n");
    fprintf(f, "Generation %d: Population: %d Number of Genes: %d\n", num_of_gen,curr_num_of_groups*persons_per_group,genes_per_person);
    for(k=0;k<curr_num_of_groups;k++){
        for(l=0;l<persons_per_group;l++){
            for(i=0;i<genes_per_person;i++){
                for(j=0;j<genes_per_person;j++){
                    fprintf(f, "%f ",temp->person_in_group[l]->gene_interactions[i][j]);
                }
                fprintf(f, "\n");
            }
            fprintf(f, "\n");

        }
        if(temp->next!=NULL){
                temp=temp->next;
        }
    }
    return;
}

void extract_gene_counts_generation(FILE *f, int num_of_gen){
    int k,l,i;
    
    group *temp;
    
    temp=generation_array[num_of_gen]->groups_list;

    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(f, "Generation %d: Population: %d Number of Genes: %d\n", num_of_gen,curr_num_of_groups*persons_per_group,genes_per_person);
    for(k=0;k<curr_num_of_groups;k++){
        for(l=0;l<persons_per_group;l++){
            for(i=0;i<genes_per_person;i++){
                fprintf(f, "%d \n",temp->person_in_group[l]->gene_counts[i]);
            }
        }
        if(temp->next!=NULL){
                temp=temp->next;
        }
    }
    return;
}

void extract_fitness_generation(FILE *f, int num_of_gen){

    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(f, "Generation %d: Population: %d Number of Genes: %d Fitness of Generation: %f\n", num_of_gen,curr_num_of_groups*persons_per_group,genes_per_person,generation_array[num_of_gen]->sum_of_fitness/(curr_num_of_groups*persons_per_group));
}
