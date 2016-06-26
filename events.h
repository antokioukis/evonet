void delete_groups(int groups_to_delete,int num_of_generation){
	int i,l;
	group *temp;
	if(groups_to_delete>curr_num_of_groups){
		printf("Delete the whole population. Ignore statement\n");
		return;
	}
	temp=generation_array[num_of_generation]->groups_list;
	while(temp->next!=NULL){
		temp=temp->next;
	}
	for(i=0;i<groups_to_delete;i++){
		if(generation_array[num_of_generation]!=0){
			for(l=0;l<persons_per_group;l++){
				generation_array[num_of_generation]->sum_of_fitness=generation_array[num_of_generation]->sum_of_fitness-temp->person_in_group[l]->fitness;
			}
		}
		temp=temp->prev;
		free(temp->next);
		temp->next=NULL;
		curr_num_of_groups--;
		/*printf("Deleted Group: %d remaining\n",curr_num_of_groups); */
	}
}

void insert_groups(int groups_to_insert,int num_of_generation,int num_of_parents,int fitness,int row_swapping){
	int i;
	group *temp=generation_array[num_of_generation]->groups_list;
	while(temp->next!=NULL){
		temp=temp->next;
	}
	for(i=0;i<groups_to_insert;i++){
		if(fitness==0){
			if(num_of_parents==0){
				temp->next=gen_create_group_no_fit(curr_num_of_groups+1,num_of_generation,0,row_swapping);
			}
			else{
				temp->next=gen_create_group_no_fit(curr_num_of_groups+1,num_of_generation,1,row_swapping);
			}

		}
		else{
			if(num_of_parents==0){
				temp->next=gen_create_group_fit(curr_num_of_groups+1,num_of_generation,0,row_swapping);
			}
			else{
				temp->next=gen_create_group_fit(curr_num_of_groups+1,num_of_generation,1,row_swapping);
			}
		}

	  	temp->next->next=NULL;
	  	temp->next->prev=temp;
	  	curr_num_of_groups++;
	 	/*printf("Created Group: %d\n",curr_num_of_groups);*/
	 	temp=temp->next;

	}

	mature_generation(generation_array[num_of_generation]);
	calculate_fitness(num_of_generation);
}

void create_event(int type_of_event,int groups_affected,int num_of_generation,int num_of_parents, int fitness, int row_swapping){
	if(type_of_event==0){
		delete_groups(groups_affected,num_of_generation);
	}
	else{
		insert_groups(groups_affected,num_of_generation,num_of_parents,fitness,row_swapping);
	}
}