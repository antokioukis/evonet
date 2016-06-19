void extract_generation(population *new_population){
    int k,l,i;
    FILE *f;
    group *temp;

	f = fopen("extract.txt", "a");
    temp=new_population->groups_list;

    if (f == NULL)
	{
    	printf("Error opening file!(is extract.txt present on directory?)\n");
    	exit(1);
	}

    for(k=0;k<curr_num_of_groups;k++){
        for(l=0;l<persons_per_group;l++){
        	for(i=0;i<genes_per_person;i++){
        		fprintf(f, "%d %d \n",temp->person_in_group[l]->gene_R1[i],temp->person_in_group[l]->gene_R2[i]);
        	}
        }
        if(temp->next!=NULL){
                temp=temp->next;
        }
    }
    return;
}