void shrink(population* new_population, int num_of_groups_for_delete){
   /* int i,j; */
    int l,k;

    for(k=0; k<num_of_groups_for_delete;k++){
        for(l=0;l<persons_per_group;l++){
            new_population->group_in_population[k]->person_in_group[l]->id=-100;
        }
        printf("Deleted %d Group\n", k);
    }
}

void expand(){


}


void create_event(int type_of_event){
	if (type_of_event==0){
		depopulate();
	}
	else repopulate();
}