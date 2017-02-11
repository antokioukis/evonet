#include "creators.h"
#include "extract.h"
extern int curr_num_of_groups;
extern int sensitivity;

int mutated_person=0;

/*1000 ta atoma 600=10 gonidia 30aria * 2 gia R1 R2 */
auxiliary_genotype_data *create_genotype_hash(population *new_population){
    int k,l,i,j,t;
    group *temp;
    char genotype_hash[10000][600];
    auxiliary_genotype_data *genotype_data;
    static int array_genotype_occ[10000];
    static float genotype_fitness[10000];
    int hash_position=-1;
    char str[600];
    char hash_key[600];
    int found_flag=0;

    for(k=0;k<10000;k++){
        array_genotype_occ[k]=0;
        genotype_fitness[k]=0;
    }

    genotype_data = (auxiliary_genotype_data*)calloc(1, sizeof(auxiliary_genotype_data));

    hash_key[0]='\0';
    str[0]='\0';
    
    temp=new_population->groups_list;

    for(k=0;k<curr_num_of_groups;k++){
        for(l=0;l<persons_per_group;l++){
            /*create genotype, which is also used as a hash_key*/
            for(i=0;i<genes_per_person;i++){
                sprintf(str, "%d", temp->person_in_group[l]->gene_R1[i]);
                strcat(hash_key,str);
            }
            for(j=0;j<genes_per_person;j++){
                sprintf(str, "%d", temp->person_in_group[l]->gene_R2[j]);
                strcat(hash_key,str);
            }
            /*printf("hash_key:%s\n",hash_key);*/

            /*got the key, search if genotype already encountered*/
            /*printf("hash_position %d\n",hash_position);*/
            for(t=0;t<hash_position;t++){
                if(strcmp(hash_key,genotype_hash[t])==0){
                    /*printf("brika ton gonotipo\n");*/
                    array_genotype_occ[t]++;
                    found_flag=1;
                }
            }

            if(found_flag==0){
                /*printf("den brika ton gonotipo\n");*/
                strcpy(genotype_hash[hash_position], hash_key);
                array_genotype_occ[hash_position]++;
                genotype_fitness[hash_position]=temp->person_in_group[l]->fitness;
                hash_position++;
            }

            str[0]='\0';
            hash_key[0]='\0';
            found_flag=0;

        }
        if(temp->next!=NULL){
            temp=temp->next;
        }
    }

    for(k=0;k<hash_position;k++){
        genotype_data->array_genotype_occ[k]=array_genotype_occ[k];
        genotype_data->genotype_fitness[k]=genotype_fitness[k];
    }

    return genotype_data;
}

person *deep_copy_person(person *destination,person *arrival){

  int j,m, i;

    destination->periodos=arrival->periodos;
    destination->mature=arrival->mature;
    destination->fitness=arrival->fitness;
    destination->id=arrival->id;
    destination->father_fitness=arrival->father_fitness;

    for( i = 0; i < max_genes_per_person; ++i)
      for( j = 0; j < neutRegionLength; ++j)
	destination -> neutRegion1[i][j] = arrival -> neutRegion1[i][j];
    
    
    for(j=0;j<max_genes_per_person;j++){
        destination->gene_counts[j]=arrival->gene_counts[j];
    }

    for(j=0;j<max_genes_per_person;j++){
        destination->vector_of_signs[j]=arrival->vector_of_signs[j];
        destination->gene_R1[j]=arrival->gene_R1[j];
        destination->gene_R2[j]=arrival->gene_R2[j];
    }

    for(j=0;j<max_genes_per_person;j++){
        for(m=0;m<max_genes_per_person;m++){
            destination->gene_interactions[j][m]=arrival->gene_interactions[j][m];
        }
    }

    for(j=0;j<size_of_maturity_array;j++){
        destination->maturity_array[j]=arrival->maturity_array[j];
    }

    return destination;
}


person *create_mutations(person *foreigner,double mu, gsl_rng *r){

  /*create mutations*/
    int result=0;
    int num_of_gene_to_mutate, magic_number = 0;
    double bit_mutation;
    int to_be_mutated;
    int which_R1R2;
    int j=0;
    int koubas=0;
    unsigned int num_of_mutations = 0, num_of_neutral_mutations = 0;
    person *individual = NULL; 
    
    /* print n random variates chosen from
    the poisson distribution with mean
         parameter mu */

    num_of_mutations = gsl_ran_poisson (r, mu);
    
    num_of_neutral_mutations = gsl_ran_poisson(r, 0.005); /*mu * neutRegionLength / sensitivity);*/

    /*fprintf(stderr, "mutations: %d, mu: %f\n", num_of_mutations, mu);*/

    
    
    /*printf("num of mutations: %u, neutral: %u\n",num_of_mutations, num_of_neutral_mutations); */

    /*koubas=gsl_rng_uniform(r);

   / euros_kouba=99/sensitivity;
*/
    /*deep copy foreigner se temp*/
    individual = (person*)calloc(1, sizeof(person));
    individual=deep_copy_person(individual,foreigner);
    free(foreigner);

    if (num_of_mutations>0) mutated_person=1; else mutated_person=0;

    for( j = 0; j < num_of_neutral_mutations; ++j){
	/* choose a gene to mutate */
	   int agene = gsl_rng_uniform_int(r, max_genes_per_person);
	/* choose a position */
	
	
		
	   if(apos > neutRegionLength-1)
	       break;
	   
	   if( mutatedSites[agene][apos] == 1 ){
	       ++apos;
	       --j;
	       continue;
	   }
	   else{
	    total_mutations++;
	    individual -> neutRegion1[agene][apos] = 1;
	    mutatedSites[agene][apos] = 1;
	    ++apos;
	   }
	
    }
    

    for(j=0;j<num_of_mutations;j++){
      /*girnaei apo 0- (n-1) edw to n einai 2*/
      which_R1R2=gsl_rng_uniform_int(r,2);
      /*printf("%d\n",which_R1R2);*/

      /* todo genes_per_person instead of max_genes_per_person */
      num_of_gene_to_mutate=gsl_rng_uniform_int(r,genes_per_person+1);
      /*printf("%d\n",num_of_gene_to_mutate);*/

      /* the mutation probability for the last bit is 100 less */
      bit_mutation=gsl_rng_uniform_pos(r);

      /*special case, changing the last bit changes the interaction */
      if(bit_mutation<=0.2){
       /* printf("bit:mutation %f\n",bit_mutation); */
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
            if(individual->gene_R2[num_of_gene_to_mutate]%2){
                individual->gene_R2[num_of_gene_to_mutate]=individual->gene_R2[num_of_gene_to_mutate]-1;
            }
            /*no fuss an einai monos ari8mos,to ipoloipo bgainei 1, afairwntas 1, ton kaneis zigo kai den peirazeis to ipoloipo binary represantation*/
            else{
                individual->gene_R2[num_of_gene_to_mutate]=individual->gene_R2[num_of_gene_to_mutate]+1;
            }
        }
      }
      else{
        /*bres poios koubas einai */
        koubas=gsl_rng_uniform_int(r,sensitivity);

        if(which_R1R2){
          to_be_mutated=individual->gene_R1[num_of_gene_to_mutate];
          magic_number = 1 << koubas;
          result = to_be_mutated ^ magic_number;
          /*printf("palio: %d, koubas: %d, kainourio: %d\n", to_be_mutated, koubas, result);  */
          individual->gene_R1[num_of_gene_to_mutate]=result;
         /* printf("kainourio: %d\n", individual->gene_R1[num_of_gene_to_mutate]); */
        }
        else{
          to_be_mutated=individual->gene_R2[num_of_gene_to_mutate];
          magic_number = 1 << koubas;
          result = to_be_mutated ^ magic_number;
          /*printf("palio: %d, koubas: %d, kainourio: %d\n", to_be_mutated, koubas, result); */
          individual->gene_R2[num_of_gene_to_mutate]=result;
          /*printf("kainourio: %d\n", individual->gene_R2[num_of_gene_to_mutate]); */
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
person *create_person(int id,int min_gene_R1R2, int max_gene_R1R2,int min_count,int max_count,int R1R2_matrix[max_genes_per_person][1]){
    int i,j;

    person *new_person;
    new_person = (person*)calloc(1, sizeof(person));

    new_person->id=id;
    new_person->mature=0;
   /* printf("Sto atomo me id: %d \n",new_person->id); */

    /* I create a new neutral region linked with the person. 
       If there is recombination, probably this is not correct 
    */
    for( i = 0; i < genes_per_person; ++i)
      for( j = 0; j < neutRegionLength; ++j)
	new_person -> neutRegion1[i][j] = 0;

    for (i=0;i<genes_per_person;i++){
        if(R1R2_matrix ==0){
            new_person->gene_R1[i]=rand_interval(min_gene_R1R2,max_gene_R1R2);
            new_person->gene_R2[i]=rand_interval(min_gene_R1R2,max_gene_R1R2);
        }
        else{
            new_person->gene_R1[i]=R1R2_matrix[i][0];
            new_person->gene_R2[i]=R1R2_matrix[i+10][0];
            /*printf("%d ",new_person->gene_R1[i]);
            printf("%d ",new_person->gene_R1[i]); */
        }
        /*printf("\n");*/
        new_person->gene_counts[i]=rand_interval(min_count,max_count);
    }

    for(i=0;i<genes_per_person;i++){
        if (new_person->gene_counts[i]>0){
            new_person->vector_of_signs[i]=1;  /* first generation so gene_counts always positive on the vector -> 1 */
        }
        else{
            new_person->vector_of_signs[i]=0;
        }
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
group *create_group(int group_num,int min_gene_R1R2, int max_gene_R1R2,int min_count,int max_count,int R1R2_matrix[persons_per_group*max_genes_per_person][1]){
    int i,j;
    int matrix_person[max_genes_per_person][1];
    group *new_group;

    new_group = (group*)calloc(1, sizeof(group));
    new_group->group_number=group_num;

    for(i=0;i<persons_per_group;i++){

        for(j=0;j<genes_per_person;j++){
            if(R1R2_matrix[0][0]!=0){
                matrix_person[j][0]=R1R2_matrix[(i*genes_per_person)+j][0];
               /* printf("%d",matrix_person[j][0]); */
            }
            else{
                 matrix_person[j][0]=0;
            }
            /*printf("\n"); */
        }


        new_group->person_in_group[i]=create_person(i,min_gene_R1R2,max_gene_R1R2,min_count,max_count,matrix_person); /*create pointer to person, save on the groups array , argument is the personal id */

        /*for (j=0;j<genes_per_person;j++){
            printf("panw vector_of_signs[%d]: %d \n",j,new_group->person_in_group[i]->vector_of_signs[j]);
        }*/

    }
    return new_group;
}

/*ean iparxei to start in 
molis exei teleiwsei h dimiourgia tou pli8ismou pigaine se ka8e ena atomo kai gemise to me auta pou sou leei to arxeio, genotype einai R1 [Is]
kai R2[Is]
while((ch = getc(fp)) != EOF)
    {
    }

    if ch is \n proxwra sto epomeno atomo
*/

/*return pointer to new population. New population is array of pointers to groups.*/
population *create_population(int groups_wanted, int min_gene_R1R2, int max_gene_R1R2,int min_count,int max_count,int robust_or_not,FILE *start_in){
    int i,j,k;
    char *line=NULL;
    size_t len = 0;
    size_t read;
    const char tokenizer[2]=" ";
    char *token;
    int thesi_r1r2_input=0;

    /*int k,j;*/
    group *temp;
    int R1R2_matrix_group[persons_per_group*max_genes_per_person*2][1];

    int R1R2_matrix_total[num_of_groups*persons_per_group*max_genes_per_person*2][1];

    population *new_population;
    new_population = (population*)calloc(1, sizeof(population));
    line=0;
    temp=NULL;


        while ((read = getline(&line, &len, start_in)) != -1) {
            token = strtok(line, tokenizer);
            R1R2_matrix_total[thesi_r1r2_input][0]=atoi(token);
            thesi_r1r2_input++;
            while( token != NULL ) {        
              /*printf( " %s\n", token );*/
              R1R2_matrix_total[thesi_r1r2_input][0]=atoi(token);
              /*printf("%d\n",R1R2_matrix_total[thesi_r1r2_input][1]);*/
              token = strtok(NULL, tokenizer);
              thesi_r1r2_input++;
            }
        }


    for(i=0;i<groups_wanted;i++){

        for(k=0;k<persons_per_group*max_genes_per_person*2;k++){
            R1R2_matrix_group[k][0]=R1R2_matrix_total[j][0];
        }

        j=j+(persons_per_group*max_genes_per_person*2);
        /*printf("%d\n",j);*/

        if(i==0){
           /* printf("Head on the group_list of the generation 0\n"); */
            new_population->groups_list=create_group(i,min_gene_R1R2,max_gene_R1R2,min_count,max_count,R1R2_matrix_group); /*create pointer to group_list, save on the population array*/
            new_population->groups_list->next=NULL;
            new_population->groups_list->prev=NULL;
        }
        else{
            temp=new_population->groups_list;
            while(temp->next!=NULL){
                temp=temp->next;
            }
            temp->next=create_group(i,min_gene_R1R2,max_gene_R1R2,min_count,max_count,R1R2_matrix_group);
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
