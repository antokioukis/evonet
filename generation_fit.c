#include "generation_fit.h"

extern int mutated_person;
extern int curr_num_of_groups;

int num_of_diff_vector(int vector[max_genes_per_person], int optimal[max_genes_per_person], int key_genes){
    int i;
    int num=0;
    for(i=0;i<key_genes;i++){
        if (vector[i]!=optimal[i]){
            num++;
        }
    }
    return num;
}

float calculate_fitness(int num_of_gen,float lamda,int optimal,float array_of_differences[max_genes_per_person],int key_genes,int actual_gen){
    int i,j,k,m;
    int num_of_diff;
    /*int w,n,c,t;*/
    person* atomo;
    int num_of_steps;
    float personal_fitness;
   /* float distance;
    float non_descrete_res[max_genes_per_person];
    int sum=0; */
    int optimal_array[max_genes_per_person];
    int optimal_dummy;
    group* temp;
    float equilibrium_fitness_min=1;
    float equilibrium_temp_fitness;
    /*float equilibrium_distance; */
    /*se periptwsi pou o xristis dwsei ligotera apo 10 gonidia oi ipoloipes 8eseis kalibontai apo 0*/
    int thesi_max_array=0;
    FILE *equilibrium_steps;
    FILE *equilibrium_period;


    /*printf("%d\n",optimal);*/
    /*PP 20170415 lathos. Nomizw prepei na diaireis me to 10 kai oxi to max_genes_per_person*/
    optimal_dummy=optimal;
    for(i=0;i<genes_per_person;i++){
      optimal_array[i]=optimal_dummy % 10;
      assert(optimal_array[i] == 0 || optimal_array[i] == 1);
      optimal_dummy=optimal_dummy/10;
      thesi_max_array++;
    }

    for(i=thesi_max_array;i<max_genes_per_person;i++){
        optimal_array[i]=0;
    }

    /*printf("num_of_gen:%d \n",num_of_gen);*/
    temp=generation_array[num_of_gen]->groups_list;
    /*gia ka8e atomo tou pli8ismou*/
    for(i=0;i<curr_num_of_groups;i++){
        for(j=0;j<persons_per_group;j++){
        /*gia na min grafw olo auto to makrinari*/
            atomo=temp->person_in_group[j];
           /* printf("ID atomou: %d, periodos %d\n",atomo->id,atomo->periodos);*/

            /*parousiazei kikliko equilibrium*/
            if(atomo->periodos>1){
                /*printf("DING DING\n"); */
                equilibrium_period=fopen("equilibrium_period.txt", "a");
                equilibrium_steps=fopen("equilibrium_steps.txt", "a");

                fprintf(equilibrium_period, "%d\n",actual_gen);

                num_of_steps=atomo->periodos;

                for (m=0;m<size_of_maturity_array;m++){
                    atomo->maturity_array[m]=0;
                }

                /*kane pollaplisiasmous osous exeis periodo (proxwra bimata)*/
                /*NEEDS MORE TESTING , printf ka8e apotelesma pou mpainei kai bgainei apo to matrix multiplication*/
                for(k=0;k<num_of_steps;k++){

                    create_maturity_step(atomo,k,equilibrium_steps,equilibrium_period,1);
                    num_of_diff=num_of_diff_vector(temp->person_in_group[j]->vector_of_signs,optimal_array,key_genes);

                    equilibrium_temp_fitness=array_of_differences[num_of_diff];

                    if (equilibrium_temp_fitness<equilibrium_fitness_min){
                        equilibrium_fitness_min=equilibrium_temp_fitness;
                    }
                   /* equilibrium_distance=0; */
                }
		      /* average fitness for all steps needed to achieve equilibrium */
                /*distance=sum_of_personal_fitness_cycles/num_of_steps; */

		      /*TODO: determine fitness based on the minimum value of the cycle */
               /* personal_fitness=exp(-lamda*distance); */
                temp->person_in_group[j]->fitness=equilibrium_fitness_min;
                personal_fitness=equilibrium_fitness_min;
                fclose(equilibrium_steps);
                fclose(equilibrium_period);

            }
            else{
                /*distance=eucledian_distance(temp->person_in_group[j]->vector_of_signs,optimal_array);
                personal_fitness=exp(-lamda*distance); */
                num_of_diff=num_of_diff_vector(temp->person_in_group[j]->vector_of_signs,optimal_array,key_genes);

                temp->person_in_group[j]->fitness=array_of_differences[num_of_diff];
                /*printf("Personal Fitness %f\n",temp->person_in_group[j]->fitness);*/
                personal_fitness=array_of_differences[num_of_diff];
            }

            generation_array[num_of_gen]->sum_of_fitness+=personal_fitness;
            /*printf("Generation Fitness %f\n",generation_array[num_of_gen]->sum_of_fitness);*/
        }

        if(temp->next!=NULL){
            temp=temp->next;
       }
       /*printf("num_of_gen:%d \n",num_of_gen);*/
    }

    return(generation_array[num_of_gen]->sum_of_fitness);
}


R1_R2_auxiliary *choose_fitted_father_dependencies_no_combinations(int num_of_gen, int id,gsl_rng *r, FILE *f,FILE *d,float fitness_array[(num_of_groups*persons_per_group)]){
/*  int theseis_pinaka=num_of_groups*persons_per_group; */
    int counter1=0;
    int i,j;
    double fitness_asked1=0;
    int group_counter1,person_counter1;
    // group *temp=generation_array[num_of_gen-1]->groups_list;
    group *temp1=generation_array[num_of_gen-1]->groups_list;
    R1_R2_auxiliary *new_auxiliary;

   /* printf("Fitted fathers row_swapping\n");*/

    new_auxiliary = (R1_R2_auxiliary*)calloc(1, sizeof(R1_R2_auxiliary));

    /*na brw to fitness pou zitaei kai apo ekei mesa na brw ton patera*/
    fitness_asked1=gsl_ran_flat (r,0, generation_array[num_of_gen-1]->sum_of_fitness);
    /*fitness_asked1=((double)rand() / RAND_MAX)*generation_array[num_of_gen-1]->sum_of_fitness;*/
    /*printf("fitness_asked: %f \n",fitness_asked1);*/

    counter1=0;
    while(fitness_asked1>fitness_array[counter1]){
        counter1++;
    }

       if (extr_fat_id){
        extract_father_id(f,counter1,-1);
    /* printf("Counter2= %d\n",counter1); */
    }

    /*fprintf(stderr, "%d:%d:%d,",num_of_gen, id,  counter1);*/

      /* printf("Counter= %d\n",counter);*/


    group_counter1=counter1/persons_per_group;
    person_counter1=counter1%persons_per_group;

    for(i=0;i<group_counter1;i++){
        if(temp1->next!=NULL){
            temp1=temp1->next;
       }
    }

    new_auxiliary->father_fitness=temp1->person_in_group[person_counter1]->fitness;

    new_auxiliary->father_genotype=create_genotype(temp1->person_in_group[person_counter1]->gene_R1,temp1->person_in_group[person_counter1]->gene_R2);

    extract_mutation_array(d,temp1->person_in_group[person_counter1],NULL);

    for(i=0;i<genes_per_person;i++){
        new_auxiliary->R1[i]=temp1->person_in_group[person_counter1]->gene_R1[i];
    }

    for(i=0;i<genes_per_person;i++){
        new_auxiliary->R2[i]=temp1->person_in_group[person_counter1]->gene_R2[i];
    }

    for(i=0; i<genes_per_person; ++i)
        for(j = 0; j < neutRegionLength; ++j)
	       new_auxiliary->neutRegion1[i][j] = temp1->person_in_group[person_counter1]->neutRegion1[i][j];

    return new_auxiliary;
}

R1_R2_auxiliary *choose_fitted_father_dependencies_combined_R1R2_swapping(int num_of_gen,gsl_rng *r,FILE *f,FILE *d, float fitness_array[(num_of_groups*persons_per_group)]){
/*  int theseis_pinaka=num_of_groups*persons_per_group; */
    int genes_from_first_parent;
    int counter1=0;
    int counter2=0;
    int i,k;
    // int j;
    double fitness_asked1=0;
    double fitness_asked2=0;
    int group_counter1,person_counter1,group_counter2,person_counter2;
    // group *temp;
    group *temp1;
    group *temp2;
    R1_R2_auxiliary *new_auxiliary;


    /*printf("Fitted fathers R1R2_swapping\n");*/
    temp1=generation_array[num_of_gen-1]->groups_list;
    temp2=generation_array[num_of_gen-1]->groups_list;

    new_auxiliary = (R1_R2_auxiliary*)calloc(1, sizeof(R1_R2_auxiliary));

    /*na brw to fitness pou zitaei kai apo ekei mesa na brw ton patera*/
    fitness_asked1=gsl_ran_flat (r,0, generation_array[num_of_gen-1]->sum_of_fitness);
  /*  printf("fitness1_asked: %f \n",fitness_asked1); */

    fitness_asked2=gsl_ran_flat (r,0, generation_array[num_of_gen-1]->sum_of_fitness);
   /* printf("fitness2_asked: %f \n",fitness_asked2); */

    counter1=0;
    while(fitness_asked1>fitness_array[counter1]){
        counter1++;
    }
   /* printf("Counter1= %d\n",counter1); */

    counter2=0;
    while(fitness_asked2>fitness_array[counter2]){
        counter2++;
    }

    if (extr_fat_id){
        extract_father_id(f,counter1,counter2);
    /* printf("Counter2= %d\n",counter1); */
    }

    group_counter1=counter1/persons_per_group;
    person_counter1=counter1%persons_per_group;
    /*printf("Group Counter1 %d person_counter1 %d \n",group_counter1,person_counter1); */
    group_counter2=counter2/persons_per_group;
    person_counter2=counter2%persons_per_group;


    for(i=0;i<group_counter1;i++){
        if(temp1->next!=NULL){
            temp1=temp1->next;
        }
    }

    for(i=0;i<group_counter2;i++){
        if(temp2->next!=NULL){
            temp2=temp2->next;
       }
    }

    extract_mutation_array(d,temp1->person_in_group[person_counter1],temp2->person_in_group[person_counter2]);

   /* printf("ID patera %d ID patera %d \n",generation_array[num_of_gen-1]->group_in_population[group_counter1]->person_in_group[person_counter1]->id,generation_array[num_of_gen-1]->group_in_population[group_counter2]->person_in_group[person_counter2]->id);
*/
    genes_from_first_parent=gsl_rng_uniform_int(r,genes_per_person);

    for(i=0;i<genes_per_person;i++){
        if(i<genes_from_first_parent){
            new_auxiliary->R1[i]=temp1->person_in_group[person_counter1]->gene_R1[i];
            new_auxiliary->R2[i]=temp1->person_in_group[person_counter1]->gene_R2[i];
            /*NEW CODE*/
            for(k=0;k<neutRegionLength;k++){
                new_auxiliary->neutRegion1[i][k]=temp1->person_in_group[person_counter1]->neutRegion1[i][k];
            }
        }

        else{
            new_auxiliary->R1[i]=temp2->person_in_group[person_counter2]->gene_R1[i];
            new_auxiliary->R2[i]=temp2->person_in_group[person_counter2]->gene_R2[i];
            /*NEW CODE*/
            for(k=0;k<neutRegionLength;k++){
                    new_auxiliary->neutRegion1[i][k]=temp2->person_in_group[person_counter2]->neutRegion1[i][k];
            }
            /*++++++*/
        }

    }

    return new_auxiliary;
}

R1_R2_auxiliary* choose_fitted_father_dependencies_combined_row_swapping(int num_of_gen,gsl_rng *r,FILE *f,FILE *d, float fitness_array[(num_of_groups*persons_per_group)]){
/*  int theseis_pinaka=num_of_groups*persons_per_group;
    int counter=0; */
    int counter1=0;
    int counter2=0;
    int i,j;
    double fitness_asked1=0;
    double fitness_asked2=0;
    int group_counter1,person_counter1,group_counter2,person_counter2;
    int which_parent;

    int k;

    // group *temp=generation_array[num_of_gen-1]->groups_list;
    group *temp1=generation_array[num_of_gen-1]->groups_list;
    group *temp2=generation_array[num_of_gen-1]->groups_list;
    R1_R2_auxiliary *new_auxiliary;

   /* printf("Fitted fathers row_swapping\n");*/

    new_auxiliary = (R1_R2_auxiliary*)calloc(1, sizeof(R1_R2_auxiliary));

    /*na brw to fitness pou zitaei kai apo ekei mesa na brw ton patera*/
    fitness_asked1=gsl_ran_flat (r,0, generation_array[num_of_gen-1]->sum_of_fitness);
    /*printf("fitness_asked: %f \n",fitness_asked);*/

    fitness_asked2=gsl_ran_flat (r,0, generation_array[num_of_gen-1]->sum_of_fitness);

    counter1=0;
    while(fitness_asked1>fitness_array[counter1]){
        counter1++;
    }

    counter2=0;
    while(fitness_asked2>fitness_array[counter2]){
        counter2++;
    }


    if (extr_fat_id){
        extract_father_id(f,counter1,counter2);
    /* printf("Counter2= %d\n",counter1); */
    }

    group_counter1=counter1/persons_per_group;
    person_counter1=counter1%persons_per_group;

    group_counter2=counter2/persons_per_group;
    person_counter2=counter2%persons_per_group;


    for(i=0;i<group_counter1;i++){
        if(temp1->next!=NULL){
            temp1=temp1->next;
       }
    }

    for(i=0;i<group_counter2;i++){
        if(temp2->next!=NULL){
            temp2=temp2->next;
       }
    }

    extract_mutation_array(d,temp1->person_in_group[person_counter1],temp2->person_in_group[person_counter2]);

    for(i=0;i<genes_per_person;i++){
        which_parent=gsl_rng_uniform_int(r,2);
        /*row_swapping*/
        if(which_parent==0){
            /*printf("Apo prwto theseis+euros:%d thesi_neutral:%d euros:%d\n",thesi_neutral+euros,thesi_neutral,euros);*/
            for(j=0;j<genes_per_person;j++){
                new_auxiliary->R1[j]=temp1->person_in_group[person_counter1]->gene_R1[j];
                /*NEW CODE*/
                for(k=0;k<neutRegionLength;k++){
                    new_auxiliary->neutRegion1[i][k]=temp1->person_in_group[person_counter1]->neutRegion1[i][k];
                }
            }
        }
        else{
            /*printf("Apo deutero theseis+euros:%d thesi_neutral:%d euros:%d\n",thesi_neutral+euros,thesi_neutral,euros);*/
            for(j=0;j<genes_per_person;j++){
                new_auxiliary->R1[j]=temp2->person_in_group[person_counter2]->gene_R1[j];
                /*NEW CODE*/
                for(k=0;k<neutRegionLength;k++){
                    new_auxiliary->neutRegion1[i][k]=temp2->person_in_group[person_counter1]->neutRegion1[i][k];
                }
            }
        }
    }

    for(i=0;i<genes_per_person;i++){
        which_parent=gsl_rng_uniform_int(r,2);
        /*row_swapping*/
        if(which_parent==0){
            for(j=0;j<genes_per_person;j++){
                new_auxiliary->R2[j]=temp1->person_in_group[person_counter1]->gene_R2[j];
            }
        }
        else{
            for(j=0;j<genes_per_person;j++){
                new_auxiliary->R2[j]=temp2->person_in_group[person_counter2]->gene_R2[j];
            }
        }
    }

    return new_auxiliary;

   /* printf("ID patera %d ID patera %d \n",generation_array[num_of_gen-1]->group_in_population[group_counter1]->person_in_group[person_counter1]->id,generation_array[num_of_gen-1]->group_in_population[group_counter2]->person_in_group[person_counter2]->id);
*/
}


person *gen_create_person_fit(int id,int num_of_gen, int num_of_parents,int row_swapping,int min_count,int max_count,
    double mutation_rate,gsl_rng *r,float recomb_rate,FILE *f,FILE *d,float fitness_array[(num_of_groups*persons_per_group)]){
    /*float fitness_array[(num_of_groups*persons_per_group)];*/
    int i,j;
    float recomb_chance;
    /*int j;*/
    R1_R2_auxiliary *auxiliary;
    person *new_person;

    new_person = (person*)calloc(1, sizeof(person));

    new_person->id=id;

    for (i=0;i<genes_per_person;i++){
        new_person->gene_counts[i]=rand_interval(min_count,max_count);
    }

    /*for(i=0;i<genes_per_person;i++){
        new_person->vector_of_signs[i]=1;
    }*/

    recomb_chance=gsl_ran_flat(r,0,1);

    /*    printf("Fitness_array[%d]= %f \n",theseis_pinaka-1,fitness_array[theseis_pinaka-1]);*/
/*    printf("Fitness of generation = %f  \n",generation_array[num_of_gen-1]->sum_of_fitness);*/

    if(num_of_parents && recomb_chance<=recomb_rate){
       /* printf("diplos\n"); */
        if(row_swapping){
            auxiliary=choose_fitted_father_dependencies_combined_row_swapping(num_of_gen,r,f,d,fitness_array);
        }
        else{
	       auxiliary=choose_fitted_father_dependencies_combined_R1R2_swapping(num_of_gen,r,f,d,fitness_array);
        }
       /* printf("Atomo %d\n",id); */
    }
    else{
      auxiliary=choose_fitted_father_dependencies_no_combinations(num_of_gen, id,r,f,d,fitness_array);
    }

    /*printf("Created Person\n");*/
    for(i=0;i<genes_per_person;i++){
        new_person->gene_R1[i]=auxiliary->R1[i];
        new_person->gene_R2[i]=auxiliary->R2[i];

    }

    /*printf("my genotype: %s\n",new_person->genotype);*/
    /*printf("my FATHER's genotype: %s\n",new_person->father_genotype);*/


    for(i=0; i<genes_per_person; ++i){
        for(j = 0; j < neutRegionLength; ++j){
	       new_person-> neutRegion1[i][j] = auxiliary-> neutRegion1[i][j];
        }
    }


    for(i=0; i<genes_per_person; ++i){
        for(j = 0; j < neutRegionLength; ++j){
	       if( new_person-> neutRegion1[i][j] == 1 ){
             /*   printf("i=%d j=%d\n",i,j); */
	           mutatedSites[i][j] = 1;
	        }
        }
    }

    new_person->mutated_from_last_gen=0;
    new_person->father_fitness=auxiliary->father_fitness;
    new_person->father_genotype=auxiliary->father_genotype;
    /*printf("father genotype %s\n",new_person->father_genotype);*/

    for(i=0;i<genes_per_person;i++){
        new_person->vector_of_signs[i]=1;
    }

    free(auxiliary);

    return new_person;
}

group *gen_create_group_fit(int starting_id,int num_of_gen, int num_of_parents,int row_swapping,int min_count,int max_count,
    double mutation_rate,gsl_rng *r,float recomb_rate,FILE *f,FILE *d,float fitness_array[(num_of_groups*persons_per_group)]){
    int i;

    group *new_group;
    new_group = (group*)calloc(1, sizeof(group));
/*printf("Group:%d \n",starting_id);*/
    for(i=0;i<persons_per_group;i++){
      /*  printf("Creating Atomo %d\n",i); */
        new_group->person_in_group[i]=gen_create_person_fit(i,num_of_gen, num_of_parents,row_swapping,min_count,max_count,mutation_rate,r,recomb_rate,f,d,fitness_array);
        /*printf("Atomo created %d\n",i);*/
    }
    return new_group;
}

population *create_gen_population_fit(int num_of_gen, int num_of_parents,int row_swapping,int min_count,int max_count,
                                        double mutation_rate,gsl_rng *r,float recomb_rate,FILE *f,FILE *d){
    int i,counter,j;
    group *temp;
    float fitness_array[(num_of_groups*persons_per_group)];

    group *temp2=generation_array[num_of_gen-1]->groups_list;

    population *new_population = (population*)calloc(1, sizeof(population));

    /* printf("apos: %d, total mutations: %d\n", apos, total_mutations); */

    apos = 0;
    total_mutations = 0;

    /* printf("1. mutation vector............\n"); */
    /* for( i = 0; i < neutRegionLength; ++i) */
    /*   printf("%d", mutatedSites[0][i]); */
    /* printf("\n"); */

    counter=0;
    /*pinakas fitness einai to dianisma me ta miki analoga me to poso fitted einai*/
    for(i=0;i<curr_num_of_groups;i++){
        for(j=0;j<persons_per_group;j++){
            if(i==0 && j==0){
                fitness_array[counter]=temp2->person_in_group[j]->fitness;
            }
            else{
                fitness_array[counter]=fitness_array[counter-1]+temp2->person_in_group[j]->fitness;
            }
            counter++;
        }
 /*       if(temp2->next!=NULL){*/
        temp2=temp2->next;

    }




    for(i=0;i<curr_num_of_groups;i++){
        if(i==0){
            /*printf("Head on the group_list of the generation 0");*/
            new_population->groups_list=gen_create_group_fit(i,num_of_gen,num_of_parents,row_swapping,min_count,max_count,mutation_rate,r,recomb_rate,f,d,fitness_array); /*create pointer to group_list, save on the population array*/
            new_population->groups_list->next=NULL;
            new_population->groups_list->prev=NULL;
        }
        else{
            temp=new_population->groups_list;
            while(temp->next!=NULL){
                temp=temp->next;
            }
            temp->next=gen_create_group_fit(i,num_of_gen,num_of_parents,row_swapping,min_count,max_count,mutation_rate,r,recomb_rate,f,d,fitness_array);
            temp->next->next=NULL;
            temp->next->prev=temp;
        }
    }
    /*gia to extract_fathers_id*/
    fprintf(f, "\n");

    /* create_mutation_vector(num_of_gen-1, 0); */
    /*printf("Generation Created\n");*/


    /* printf("\n2. mutation vector............\n"); */
    /* for( i = 0; i < neutRegionLength; ++i) */
    /*   printf("%d", mutatedSites[0][i]); */
    /* printf("\n"); */


    return new_population;
}

void mutate_population(population *pop, double mu, gsl_rng *r, int generation_number){
    int i = 0, j = 0;
    int k=0;
    int l=0;
    group *group = pop -> groups_list;

    for( i = 0; i < curr_num_of_groups; ++i){
        assert(group != NULL);
        for( j = 0; j < persons_per_group; ++j ){
            group -> person_in_group[j] = create_mutations(group->person_in_group[j], mu,  r);

            for(l=0;l<genes_per_person;l++){
                for(k=0;k<genes_per_person;k++){
                    group -> person_in_group[j]->gene_interactions[l][k]=create_gene_interactions(group -> person_in_group[j]->gene_R1[l],group -> person_in_group[j]->gene_R2[k]);
                }
            }


            if (mutated_person==1){
                group -> person_in_group[j]->mutated_from_last_gen=1;
                /*printf("eimai metallagmenos se sxesi me ton patera mou\n");*/
            }
            else{
                mutated_person=0;
                group -> person_in_group[j]->mutated_from_last_gen=0;
            }
        }
        group = group->next;
    }
}


void create_mutation_vector(int num_of_gen, int agene){

    int i=0, j=0, k=0, breakflag = 0;
    group *temp; /*=generation_array[num_of_gen-1]->groups_list; */
    /*printf("mpika agene: %d \n",agene); */
    for(k = 0; k < neutRegionLength; ++k){
        breakflag = 0;
        temp=generation_array[num_of_gen]->groups_list;
        assert( temp != NULL);
        /*mutatedSites[agene][k] = 0;*/
        for( i =0; i < curr_num_of_groups; ++i){
	        for(j = 0; j < persons_per_group; ++j){
	            if( temp->person_in_group[j]->neutRegion1[agene][k] == 1 ){
                  /*  printf("pote sto if? agene %d \n",agene); */
		            mutatedSites[agene][k] = 1;
		            breakflag = 1;
		            break;
		        }
	        }
            if(breakflag){
                breakflag = 0;
	           break;
	        }
	    temp = temp -> next;
	   }
    }
}
