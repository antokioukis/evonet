/*delete people checking if the number of them exceeds the current population*/
void delete_population(int population_to_delete){
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
    }

    for(j=0;j<population_to_delete;j=j+group_persons){
        temp=plist_head;
        plist_head=plist_head->next;
        free(temp->groups->personal_record[j]->gene_dependancies);
        free(temp->groups->personal_record[j]->ptr_to_genes_count);
        free(temp->groups->personal_record[j]->ptr_to_new_genes_count);
        free(temp->groups->personal_record[j]->gene_dependancies);
        free(temp->groups->personal_record[j]->ptr_to_personal_r1);
        free(temp->groups->personal_record[j]->ptr_to_personal_r2);
        free(temp->groups);
        free(temp);
    }
}
