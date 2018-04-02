#include "extract.h"
#include <assert.h>

extern int curr_num_of_groups;
extern int sensitivity;
extern int **sensitivity_array;

int thesi_buffer_father=0;
int buffer_father[BUFSIZ]={0};

int calculate_open_non_net(int vector[max_genes_per_person],int key_genes){
    int i;
    int open_genes_non_network=0;
    /*for (i=0;i<max_genes_per_person;i++){
        printf("%d ",vector[i]);
    }
    printf("\n");
    */
    for (i=key_genes;i<max_genes_per_person;i++){
        if (vector[i]==1){
            open_genes_non_network++;
        }
    }
    /*printf("%d ", open_genes_non_network);*/
    return open_genes_non_network;
}

void extract_open_non_network(population *new_population,int key_genes){
    FILE *open_genes;
    int open_genes_sum;
    int i,j;
    group *temp=new_population->groups_list;
    open_genes=fopen("open_genes.txt","a");

    for(i=0;i<curr_num_of_groups;i++){
        for(j=0;j<persons_per_group;j++){
            open_genes_sum=calculate_open_non_net(temp->person_in_group[j]->vector_of_signs,key_genes);
            fprintf(open_genes, "%d ",open_genes_sum);
        }
        if(temp->next!=NULL){
            temp=temp->next;
        }
    }
    fprintf(open_genes, "\n");
    fclose(open_genes);
}

void extract_mutation_array(FILE *f,person *father1,person *father2){
    int i;
    if(father2!=NULL){
        for(i=0;i<genes_per_person;i++){
            if(father2->vector_of_signs[i]){
                /*printf("assos2\n");*/
                sensitivity_array[i][1]++;
            }
            else{
               /* printf("miden2\n"); */
                sensitivity_array[i][0]++;
            }
        }
    }

    for(i=0;i<genes_per_person;i++){
        if(father1->vector_of_signs[i]){
            /*printf("assos1\n"); */
            sensitivity_array[i][1]++;
        }
        else{
            /*printf("miden1\n");*/
            sensitivity_array[i][0]++;
        }
    }
}

void extract_father_id(FILE *f,int father_number1, int father_number2){

    if (f == NULL){
        printf("Error opening file father_output!\n");
        exit(1);
    }

    else if (thesi_buffer_father==BUFSIZ-2){
        fwrite(buffer_father, sizeof(int), sizeof(buffer_father), f);
        thesi_buffer_father=0;
    }

    if(father_number2==-1){
        buffer_father[thesi_buffer_father]=father_number1;
        thesi_buffer_father++;
    }
    else{
        buffer_father[thesi_buffer_father]=father_number1;
        buffer_father[thesi_buffer_father+1]=father_number2;
        thesi_buffer_father=thesi_buffer_father+2;
    }
}

void extract_father_fitness(int num_of_gen,int actual_num){
    int k,l;
    int num_of_mutations_carried;
    FILE *f;
    float father_fitness;
    float son_fitness;
    int mutated_from_last;
    group *temp;
    char *father_genotype;

    /* f = fopen("R1R2.txt", "a"); */
    temp=generation_array[num_of_gen]->groups_list;

    f=fopen("father_fitness.txt","a");

    for(k=0;k<curr_num_of_groups;k++){
        for(l=0;l<persons_per_group;l++){

            father_fitness=temp->person_in_group[l]->father_fitness;
            son_fitness=temp->person_in_group[l]->fitness;
            mutated_from_last=temp->person_in_group[l]->mutated_from_last_gen;
            num_of_mutations_carried=temp->person_in_group[l]->num_of_mutations_carried;
            father_genotype=temp->person_in_group[l]->father_genotype;
            /*printf("father genotype %s\n",father_genotype); */

            if (actual_num==0){
                /*fprintf(f, "%d %f %f\n",actual_num,temp->person_in_group[l]->father_fitness,temp->person_in_group[l]->fitness);*/
            }

            else if(mutated_from_last && father_fitness!=son_fitness){
                fprintf(f, "%d %f %f %d %s\n",actual_num,father_fitness,son_fitness,num_of_mutations_carried,father_genotype);
            }
        }

        if(temp->next!=NULL){
                temp=temp->next;
        }

    }
    fclose(f);
    return;
}


void* extract_neutRegion1_generation(void *auxialiary){
    int i = 0, j = 0, k = 0, l = 0;
    thread_auxialiary *temp_auxialiary=auxialiary;
    group *temp = generation_array[temp_auxialiary->num_of_gen] -> groups_list;

   /* printf("num_of_gen %d,index %d\n",temp_auxialiary->num_of_gen,temp_auxialiary->index_of_gene); */

    if(temp_auxialiary->f == NULL){
        fprintf(stderr, "Error opening a file for outputing neutral regions\n");
        assert(temp_auxialiary->f != NULL);
    }

    for(k=0;k<curr_num_of_groups;k++){
        for(l=0;l<persons_per_group;l++){
	        i = temp_auxialiary->index_of_gene;
	        fprintf(temp_auxialiary->f, "%d,%d\t", k, l);
	        for(j = 0; j < neutRegionLength; ++j){
	            fprintf(temp_auxialiary->f, "%d",temp->person_in_group[l]->neutRegion1[i][j]);
	        }
            fprintf(temp_auxialiary->f, "\n");
        }

        if(temp->next!=NULL){
	       temp=temp->next;
        }
    }

    free (temp_auxialiary);
    return NULL;
}


void extract_R1R2_generation(FILE *f1,FILE *f2, int num_of_gen){
    int k,l,i;

    group *temp;

    /* f = fopen("R1R2.txt", "a"); */
    temp=generation_array[num_of_gen]->groups_list;

    if (f1 == NULL){
        printf("Error opening file r1!\n");
        exit(1);
    }

    if (f2 == NULL){
        printf("Error opening file r2!\n");
        exit(1);
    }

    for(k=0;k<curr_num_of_groups;k++){
        for(l=0;l<persons_per_group;l++){
            for(i=0;i<genes_per_person;i++){
                fprintf(f1, "%d \n",temp->person_in_group[l]->gene_R1[i]);
            }
            for(i=0;i<genes_per_person;i++){
                fprintf(f2, "%d \n",temp->person_in_group[l]->gene_R2[i]);
            }
        }

        if(temp->next!=NULL){
                temp=temp->next;
        }

    }

    return;
}

void extract_discrete_generation(FILE *f, int num_of_gen){
    int k,l,i;
    group *temp;

    /* f = fopen("R1R2.txt", "a"); */
    temp=generation_array[num_of_gen]->groups_list;

    if (f == NULL)
    {
        printf("Error opening file discrete\n");
        exit(1);
    }

    for(k=0;k<curr_num_of_groups;k++){
        for(l=0;l<persons_per_group;l++){
            for(i=0;i<genes_per_person;i++){
        /*      printf("current sign %d stin thesi %d\n",individual->vector_of_signs[i],i); */
                fprintf(f,"%d",temp->person_in_group[l]->vector_of_signs[i]);
            }
            fprintf(f, "\n");
        }

        if(temp->next!=NULL){
                temp=temp->next;
        }

    }

    return;
}

void extract_gene_dependancies_matrix_generation(FILE* f, int num_of_gen){
    int k,l,i,j;

    group *temp;

    temp=generation_array[num_of_gen]->groups_list;

    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    for(k=0;k<curr_num_of_groups;k++){
        for(l=0;l<persons_per_group;l++){
            for(i=0;i<genes_per_person;i++){
                for(j=0;j<genes_per_person;j++){
                    fprintf(f, "%8.5f ",temp->person_in_group[l]->gene_interactions[i][j]);
                }
                /*fprintf(f, "\n");*/
            }
            fprintf(f, "\n");

        }
        if(temp->next!=NULL){
                temp=temp->next;
        }
    }
    return;
}

void extract_gene_counts_generation(FILE *f, int num_of_gen){
    int k,l,i;

    group *temp;

    temp=generation_array[num_of_gen]->groups_list;

    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for(k=0;k<curr_num_of_groups;k++){
        for(l=0;l<persons_per_group;l++){
            for(i=0;i<genes_per_person;i++){
                fprintf(f, "%d \n",temp->person_in_group[l]->gene_counts[i]);
            }
        }
        if(temp->next!=NULL){
                temp=temp->next;
        }
    }
    return;
}

void extract_fitness_generation(FILE *f, int num_of_gen, float mutation_rate){

    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(f, "%d %d %d %f %f\n", num_of_gen,curr_num_of_groups*persons_per_group,genes_per_person,generation_array[num_of_gen]->sum_of_fitness/(curr_num_of_groups*persons_per_group),mutation_rate);
}


void extract_robustness(FILE *f,population *new_population,FILE *d){
    group* temp;
    int k,l,i,j;

    temp=new_population->groups_list;

    if (f == NULL)
    {
        printf("Error opening file robust\n");
        exit(1);
    }

    if (d == NULL)
    {
        printf("Error opening file discrete\n");
        exit(1);
    }

    for(k=0;k<curr_num_of_groups;k++){
        for(l=0;l<persons_per_group;l++){
            for(i=0;i<genes_per_person;i++){
        /*      printf("current sign %d stin thesi %d\n",individual->vector_of_signs[i],i); */
                /*fprintf(f,"%d",temp->person_in_group[l]->vector_of_signs[i]); */ /*antwnis 1/7/17*/
                for(j=0;j<genes_per_person;j++){
                    fprintf(f, "%8.5f ",temp->person_in_group[l]->gene_interactions[i][j]);
                }
                fprintf(d,"%d",temp->person_in_group[l]->vector_of_signs[i]);
            }
            fprintf(d, "\n");
            fprintf(f, "\n");
        }

        if(temp->next!=NULL){
                temp=temp->next;
        }

    }

    return;
}

void extract_genotype_occ(FILE *f,auxiliary_genotype_data* genotype_data){
    int position=0;
    FILE *d=fopen("genotype_fit.txt","a");

    if (f == NULL)
    {
        printf("Error opening file genotype\n");
        exit(1);
    }

    while(position<10000-1){
        if (genotype_data->array_genotype_occ[position]!=0){
            fprintf(f,"%d ",genotype_data->array_genotype_occ[position]);
            /*printf("%f ",genotype_data->genotype_fitness[position]);*/
            fprintf(d,"%f ",genotype_data->genotype_fitness[position]);
        }

        position++;
    }
    fprintf(f, "\n");
    fprintf(d, "\n");
    fclose(d);

}
