#include "creators.h"
extern int curr_num_of_groups;
person *create_mutations(person *individual,double mu,gsl_rng *r){

  /*create mutations*/
    int result=0;
    int num_of_gene_to_mutate, magic_number = 0;
    int bit_mutation,to_be_mutated;
    int which_R1R2;
    int j=0;
    int koubas=0;
    unsigned int num_of_mutations;
    int euros_kouba;

    /* print n random variates chosen from
    the poisson distribution with mean
         parameter mu */

    num_of_mutations = gsl_ran_poisson (r, mu);
    /*printf("num of mutations: %u\n",num_of_mutations);*/

    euros_kouba=99/genes_per_person;

    for(j=0;j<num_of_mutations;j++){
      which_R1R2=rand()%2;
      /* todo genes_per_person instead of max_genes_per_person */
      num_of_gene_to_mutate=rand() % genes_per_person;
      /* the mutation probability for the last bit is 100 less */
      bit_mutation=rand() % 100;
      /*special case, changing the last bit changes the interaction */
      if(bit_mutation==0){
        if(which_R1R2){
            /*no fuss an einai monos ari8mos,to ipoloipo bgainei 1, afairwntas 1, ton kaneis zigo kai den peirazeis to ipoloipo binary represantation*/
            if(individual->gene_R1[num_of_gene_to_mutate]%2){
                individual->gene_R1[num_of_gene_to_mutate]=individual->gene_R1[num_of_gene_to_mutate]-1;
            }
            /*no fuss an einai monos ari8mos,to ipoloipo bgainei 1, afairwntas 1, ton kaneis zigo kai den peirazeis to ipoloipo binary represantation*/
            else{
                individual->gene_R1[num_of_gene_to_mutate]=individual->gene_R1[num_of_gene_to_mutate]+1;
            }
        }
        else{
            if(individual->gene_R1[num_of_gene_to_mutate]%2){
                individual->gene_R1[num_of_gene_to_mutate]=individual->gene_R2[num_of_gene_to_mutate]-1;
            }
            /*no fuss an einai monos ari8mos,to ipoloipo bgainei 1, afairwntas 1, ton kaneis zigo kai den peirazeis to ipoloipo binary represantation*/
            else{
                individual->gene_R1[num_of_gene_to_mutate]=individual->gene_R2[num_of_gene_to_mutate]+1;
            }
        }
      }
      else{
        /*bres poios koubas einai */
        while(bit_mutation>koubas){
          koubas=koubas+euros_kouba;
        }
        koubas=koubas/genes_per_person;

        if(which_R1R2){
          to_be_mutated=individual->gene_R1[num_of_gene_to_mutate];
          magic_number = 1 << koubas;
          result = to_be_mutated ^ magic_number;
          /*printf("palio: %d, koubas: %d, kainourio: %d\n", to_be_mutated, koubas, result);*/
          individual->gene_R1[num_of_gene_to_mutate]=result;
        }
        else{
          to_be_mutated=individual->gene_R2[num_of_gene_to_mutate];
          magic_number = 1 << koubas;
          result = to_be_mutated ^ magic_number;
          /*printf("palio: %d, koubas: %d, kainourio: %d\n", to_be_mutated, koubas, result);*/
          individual->gene_R2[num_of_gene_to_mutate]=result;
        }

      }
    }

    return individual;
}




float create_gene_interactions(int R1,int R2){
    float interaction=0;
    float power_of_interaction=0;

    unsigned lastbitR1;
    unsigned lastbitR2;

    lastbitR1=R1%2;
    lastbitR2=R2%2;


/*
    printf("Mpika me R1 = %d , R2 = %d  \n",R1,R2);

    printf("R1 se binary=%010d \n",R1_binary);

    printf("R2 se binary=%010d \n",R2_binary);

    printf("lastbitR1=%d \n",lastbitR1);
    printf("lastbitR2=%d \n",lastbitR2);
*/
    if(lastbitR2==lastbitR1){ /*ri8misi*/
	   power_of_interaction=NumberOfSetBits(R1 & R2);
        /*printf("Interaction:%f \n",power_of_interaction);*/
        power_of_interaction = power_of_interaction / max_genes_per_person; /*kanonikopoihsh*/

        if(lastbitR1){
            interaction=power_of_interaction;
 /*           printf("Positive Interaction:%f \n",interaction); */
        }
        else {
            interaction=-power_of_interaction;
 /*           printf("Negative Interaction:%f \n",interaction); */
        }
    }
    /*printf("%f ",interaction);*/
    return interaction;
}


/*Create personal records, return pointer to person */
person *create_person(int id,int min_gene_R1R2, int max_gene_R1R2,int min_count,int max_count){
    int i,j;

    person *new_person;
    new_person = (person*)calloc(1, sizeof(person));

    new_person->id=id;
    new_person->mature=0;
   /* printf("Sto atomo me id: %d \n",new_person->id); */

    for(i=0;i<genes_per_person;i++){
        new_person->vector_of_signs[i]=0;
        if(i%2==0)
        new_person->vector_of_signs[i]=1;  /* first generation so gene_counts always positive on the vector -> 1 */
    }

    for (i=0;i<genes_per_person;i++){
        new_person->gene_R1[i]=rand_interval(min_gene_R1R2,max_gene_R1R2);
        new_person->gene_R2[i]=rand_interval(min_gene_R1R2,max_gene_R1R2);

        new_person->gene_counts[i]=rand_interval(min_count,max_count);
    }

    for(i=0;i<genes_per_person;i++){
        for(j=0;j<genes_per_person;j++){
            /*new_person->gene_interactions[i][j]=random_normal_distrubution(0,sqrt(10));*/
            new_person->gene_interactions[i][j]=create_gene_interactions(new_person->gene_R1[i],new_person->gene_R2[j]);
           /* printf("%d ",new_person->gene_interactions[i][j]); */
        }
     /*   printf("\n"); */
    }
   /* printf("Created Person: %d\n", new_person->id);
    for (i=0;i<genes_per_person;i++){
        printf("katw gene_counts[%d]: %d \n",i,new_person->gene_counts[i]);
    } */

    return new_person;
}

/*return pointer to new group. New group is array of pointers to persons.*/
group *create_group(int group_num,int min_gene_R1R2, int max_gene_R1R2,int min_count,int max_count){
    int i;
    /*int j;*/
    group *new_group;
    new_group = (group*)calloc(1, sizeof(group));
    new_group->group_number=group_num;
    for(i=0;i<persons_per_group;i++){
        new_group->person_in_group[i]=create_person(i,min_gene_R1R2,max_gene_R1R2,min_count,max_count); /*create pointer to person, save on the groups array , argument is the personal id */

        /*for (j=0;j<genes_per_person;j++){
            printf("panw vector_of_signs[%d]: %d \n",j,new_group->person_in_group[i]->vector_of_signs[j]);
        }*/

    }
    return new_group;
    curr_num_of_groups++;
}



/*return pointer to new population. New population is array of pointers to groups.*/
population *create_population(int groups_wanted, int min_gene_R1R2, int max_gene_R1R2,int min_count,int max_count,int robust_or_not){
    int i;
    /*int k,j;*/
    group *temp;

    population *new_population;
    new_population = (population*)calloc(1, sizeof(population));

    temp=NULL;
    for(i=0;i<groups_wanted;i++){
        if(i==0){
           /* printf("Head on the group_list of the generation 0\n"); */
            new_population->groups_list=create_group(i,min_gene_R1R2,max_gene_R1R2,min_count,max_count); /*create pointer to group_list, save on the population array*/
            new_population->groups_list->next=NULL;
            new_population->groups_list->prev=NULL;
        }
        else{
            temp=new_population->groups_list;
            while(temp->next!=NULL){
                temp=temp->next;
            }
            temp->next=create_group(i,min_gene_R1R2,max_gene_R1R2,min_count,max_count);
            temp->next->next=NULL;
            temp->next->prev=temp;

        }
       /* printf("Created Group: %d\n",curr_num_of_groups); */
        if(robust_or_not)curr_num_of_groups++;
    }
/*
    temp=new_population->groups_list;
    for(i=0;i<groups_wanted;i++){
        printf("Group Num:%d\n",i);
        for(j=0;j<persons_per_group;j++){
            for(k=0;k<genes_per_person;k++){
            printf("gene vector[%d]: %d\n",k, temp->person_in_group[j]->vector_of_signs[k]);
            }
        }
        temp=temp->next;
    }
  */
    return new_population;
}
