
/*return number of immatures on whole population*/
int num_of_immatures(population_list *plist_head){
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
int num_of_matures(population_list *plist_head){
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

/*used to calculate if current discrete genes are the same with the first evolutionary step*/
int distance_to_first_gen(){
    int i;
    int res=1;
    for(i=1;i<genes_per_person;i++){
        res=concatenate(res,1);
    }
    res=binary_to_decimal(res);
    //printf("Res %d \n",res);
    return res;
}

