
/*delete people checking if the number of them exceeds the current population*/
void delete_population(population_list *plist_head,int population_to_delete){
    population_list *temp=plist_head;
    int j;

    if(total_population<=population_to_delete){
        printf("Population to be removed exceeds total_population. Will Delete all of the active population.\n");
        while (plist_head->next!=NULL){
            temp=plist_head;
            plist_head=plist_head->next;
            free(temp);
        }
        plist_head=NULL;
        return;
    }

    /*panta free bottom up gia apofigi memory leaks*/
    for(j=0;j<population_to_delete;j=j+group_persons){
        temp=plist_head;
        plist_head=plist_head->next;
        free(temp->groups->personal_record[j]->gene_dependancies);
        free(temp->groups->personal_record[j]->ptr_to_genes_count);
        free(temp->groups->personal_record[j]->ptr_personal_plastic_array);
        free(temp->groups->personal_record[j]->gene_dependancies);
        free(temp->groups->personal_record[j]->ptr_to_personal_r1);
        free(temp->groups->personal_record[j]->ptr_to_personal_r2);
        free(temp->groups);
        free(temp);
    }
}


void free_personal_records(personal_records *temp){
    free(temp->gene_dependancies);
    free(temp->ptr_to_genes_count);
    free(temp->ptr_personal_plastic_array);
    free(temp->ptr_to_personal_r1);
    free(temp->ptr_to_personal_r2);
    free(temp);
}

/*scan whole population if someone is immature tag him with negative id and free the rest of the fields*/
void remove_immatures(population_list *plist_head){
    int j=0;
    population_list *temp=plist_head;
    while(temp!=NULL){
        for(j=0;j<group_persons;j++){
            if(!temp->groups->personal_record[j]->isplastic){
                free_personal_records(temp->groups->personal_record[j]);
                temp->groups->personal_record[j]->personal_id=-1000;
            }
        }
        temp=temp->next;
    }
}
