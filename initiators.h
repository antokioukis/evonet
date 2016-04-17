#include "R1R2.h"

population_list *generation_array[num_of_max_generations];
int total_population=0;

/*create discrete vector with elements based on the sign of the plastic records*/
void make_discrete(personal_records *personal_record, float temp[genes_per_person]){
    int i;

    for (i=0;i<genes_per_person;i++){
        if(temp[i]>0){
            personal_record->ptr_to_plastics->discrete_plastic[i]=1;
        }
        else{
            personal_record->ptr_to_plastics->discrete_plastic[i]=-1;
        }
    }

//    for(i=0;i<genes_per_person;i++){
//        printf("Apotelesma discretion %d\n",personal_record->ptr_to_plastics->discrete_plastic[i]);
//    }

}

/*initialize personal nxn interaction matrix. Where n=gene_counts. Return pointer*/
personal_gene_interaction_matrix* initialize_personal_gene_interaction_matrix(){
    int i,j;
    personal_gene_interaction_matrix *ptr_to_gene_inter_matrix;
    ptr_to_gene_inter_matrix=(personal_gene_interaction_matrix*)malloc(sizeof(personal_gene_interaction_matrix));

    if ( ptr_to_gene_inter_matrix == NULL ){
        printf("No memory left for gene_interaction_matrix on initialize_personal_gene_counts\n");
        exit(EXIT_FAILURE);
    }

    for (i=0;i<genes_per_person;i++){
        for (j=0;j<genes_per_person;j++){
          /*all values from gaussian distrubution*/
            ptr_to_gene_inter_matrix->gene_inter_matrix[i][j]=random_normal_distrubution(0,sqrt(10));
          }
    }

    return ptr_to_gene_inter_matrix;
}

/*initialize personal gene counts,and put them on nx1 return pointer to vector*/
personal_gene_count* initialize_personal_gene_count(){
    int i;
    personal_gene_count *ptr_to_indi_gene_count;
    ptr_to_indi_gene_count = (personal_gene_count *)malloc(sizeof(personal_gene_count));


    if(ptr_to_indi_gene_count==NULL){
        printf("Not enough memory for personal gene counts matrix\n");
        exit(EXIT_FAILURE);
    }
    /*first column of the array stores the number of the gene the second store the random generated gene_count*/
    /*dont need the first column*/
    for (i=0;i<genes_per_person;i++){
        ptr_to_indi_gene_count->indi_gene_array[i][0]=i;
        ptr_to_indi_gene_count->indi_gene_array[i][1]=rand()%500;
    }

    return ptr_to_indi_gene_count;
}

/*discrete values of genes when person is "born"*/
personal_plastics *initialize_plastics(personal_gene_count *gene_counts){
    personal_plastics *ptr_to_personal_plastics;
    ptr_to_personal_plastics = (personal_plastics *)malloc(sizeof(personal_plastics));
    int i;

    if ( ptr_to_personal_plastics == NULL ){
        printf("No memory left personal_plastics on create personal_plastics\n");
        exit(EXIT_FAILURE);
    }

    for(i=0;i<genes_per_person;i++){
        if (gene_counts->indi_gene_array[i]>0){
            ptr_to_personal_plastics->discrete_plastic[i]=1;
        }
        /*0 not -1 cause i want to read the whole vector later as binary*/
        else{
            ptr_to_personal_plastics->discrete_plastic[i]=0;
        }
    }
    return ptr_to_personal_plastics;
}


personal_plastic_array *initialize_plastic_array(){
    personal_plastic_array *ptr_personal_plastic_array;
    ptr_personal_plastic_array = (personal_plastic_array *)malloc(sizeof(personal_plastic_array));
    if ( ptr_personal_plastic_array == NULL ){
        printf("No memory left ptr_personal_plastic_array on initialize_plastic_array\n");
        exit(EXIT_FAILURE);
    }
    else return ptr_personal_plastic_array;
}

/*create personal records for each individual. (no new_gene_count since there is no aging when they are "born")*/
personal_records *create_personal_records(int personal_id){
    personal_records *ptr_to_personal_records;
    ptr_to_personal_records = (personal_records *)malloc(sizeof(personal_records));
    if ( ptr_to_personal_records == NULL ){
        printf("No memory left ptr_to_personal_records on create_personal_records\n");
        exit(EXIT_FAILURE);
    }

        /*fill the ptr_personal_records fields*/
        ptr_to_personal_records->personal_id=personal_id;
        ptr_to_personal_records->ptr_to_genes_count=initialize_personal_gene_count();
        ptr_to_personal_records->gene_dependancies=initialize_personal_gene_interaction_matrix();
        ptr_to_personal_records->ptr_to_personal_r1=initialize_r1();
        ptr_to_personal_records->ptr_to_personal_r2=initialize_r2();
        ptr_to_personal_records->ptr_personal_plastic_array=initialize_plastic_array();
        ptr_to_personal_records->ptr_to_plastics=initialize_plastics(ptr_to_personal_records->ptr_to_genes_count);
        ptr_to_personal_records->fitness=0;

        return ptr_to_personal_records;
}

/*for everyone in a group call create_personal_records to create them*/
array_of_group *create_group_persons_array(int max_id){
    int i;
    array_of_group *ptr_grp_person_array;
    ptr_grp_person_array = (array_of_group *)malloc(sizeof(array_of_group));
    if ( ptr_grp_person_array == NULL ){
        printf("No memory left ptr_grp_person_array on create_group_persons_array\n");
        exit(EXIT_FAILURE);
    }

    /*fill the ptr_to_grp_person_array*/
    for (i=0;i<group_persons;i++){
        ptr_grp_person_array->personal_record[i]=create_personal_records(i);
    }

    return ptr_grp_person_array;
}

/*add new population on population_list the new people always on the head of the population list*/
population_list *add_population_node(population_list *plist_head,int max_id){
    int counter=0;
    population_list *temp=plist_head;
    struct population_list *new_node = (population_list*)malloc(sizeof(population_list));

    if ( new_node == NULL ){
        printf("No memory left new_node on add_population_node\n");
        exit(EXIT_FAILURE);
    }

    /*fill the new_node fields*/
    new_node->next = NULL;
    new_node->groups=create_group_persons_array(max_id);

    if (temp==NULL) {plist_head=new_node;}
    else{
        while(temp->next!=NULL){
            temp=temp->next;
            counter++;
        }
        temp->next=new_node;
    }
    return plist_head;
}

/*determine how many people_groups are needed to store the new people then call add_population_node to actually add them*/
population_list *add_population(int population){
    int i;
    population_list *plist_head=NULL;
    total_population=(population*group_persons)+total_population;     /*add to global used for delete*/
    for (i=0;i<population;i++){
        plist_head=add_population_node(plist_head,i);
    }
    printf("Total Population: %d\n",total_population);
    return plist_head;
}

