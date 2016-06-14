void shrink(population* new_population, int num_of_groups_for_delete){
   /* int i,j; */
    int l,k;

    if(max_population<(num_of_groups_for_delete*persons_per_group)){
    	printf("Whole population would be deleted, not accepting\n");
    	return;
    }

    printf("Arxiko fitness %f\n",new_population->sum_of_fitness);

    for(k=0; k<num_of_groups_for_delete;k++){
        for(l=0;l<persons_per_group;l++){
            new_population->group_in_population[k]->person_in_group[l]->id=-100;
            new_population->sum_of_fitness=(new_population->sum_of_fitness)-(new_population->group_in_population[k]->person_in_group[l]->fitness);
            new_population->group_in_population[k]->person_in_group[l]->fitness=0;
        }

        printf("Deleted %d Group\n", k);
    }
    printf("Teliko fitness %f\n",new_population->sum_of_fitness);
}
/*
void expand(population* new_population,int num_of_groups_for_add){
	int k,l;
	for(k=0;k<num_of_groups_for_add;k++){	
		new_population->group_in_population[k]=gen_create_group_fit(persons_per_group*k,2,1);
		for(l=0;l<persons_per_group;l++){
			new_population->sum_of_fitness=(new_population->sum_of_fitness)+(new_population->group_in_population[k]->person_in_group[l]->fitness);
		}
		printf("Added %d Group\n", k);
	}
	printf("Teliko fitness %f\n",new_population->sum_of_fitness);
}
*/

void create_event(population* new_population, int type_of_event,int num_of_groups_affected){
	if (type_of_event==0){
		shrink(new_population,num_of_groups_affected);
	}
	/*else expand(new_population,num_of_groups_affected); */
}