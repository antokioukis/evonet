/*return number of immatures on whole population*/
int num_of_immatures(){
    int i=0;
    int j;
    population_list *temp=plist_head;
    /*scan whole population*/
    while(temp!=NULL){
        for(j=0;j<group_persons;j++){
            if(!temp->groups->personal_record[j]->isplastic){
                i++;
            }
        }
        temp=temp->next;
    }
    printf("Immature Pli8ismos = %d \n",i);
    return i;
}

/*return number of matures on whole population*/
int num_of_matures(){
    int i=0;
    int j;
    population_list *temp=plist_head;
    /*scan whole population*/
    while(temp!=NULL){
       for(j=0;j<group_persons;j++){
           if(!(temp->groups->personal_record[j]->personal_id==-1000)){
               i++;
           }
       }
       temp=temp->next;
    }
    printf("Mature Pli8ismos = %d \n",i);
    return i;
}
