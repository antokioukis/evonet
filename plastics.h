#include "counters.h"
#include "delete.h"

#define klepsimo 0

int total_gens=1;

/*Ftia3e mou pinaka. Bale -1 an to antistoixo gene_counts einai <0  kai 1 an einai >0*/
/*return ton pinaka -1 1*/
plastic_records *create_plastic_records(personal_gene_list *ptr_to_new_personal_gene_counts){
    plastic_records *new_plastic_records;
    int i;

    new_plastic_records= (plastic_records *)malloc(sizeof(plastic_records));
    if ( new_plastic_records == NULL ){
        printf("No memory left new_plastic_records\n");
        exit(EXIT_FAILURE);
    }

    for(i=0;i<genes_per_person;i++){
        if(ptr_to_new_personal_gene_counts->indi_gene_array[i][1]<0){
            new_plastic_records->plastic_recs[i]=-1;
        }
        else {
             new_plastic_records->plastic_recs[i]=1;
        }
    }

    return new_plastic_records;
}

/*create new personal gene counts by multiplying the last gene counts with the personal interaction matrix.Put the new gene counts
on the head of the list of personal new_gene_counts_list*/
void create_new_gene_counts(personal_records *personal_record){
    int i,j,b,counter=0;
    float a;

    personal_gene_list *ptr_to_new_personal_gene_counts;
    personal_gene_list *temp;

    ptr_to_new_personal_gene_counts= (personal_gene_list *)malloc(sizeof(personal_gene_list));

    if ( ptr_to_new_personal_gene_counts == NULL ){
        printf("No memory left ptr_to_new_personal_gene_counts\n");
        exit(EXIT_FAILURE);
    }
    ptr_to_new_personal_gene_counts->next=NULL;
        /*if it is the first generation there are no new_gene_counts, thus we have to create them from the original gene counts*/
    if (total_gens==1){
        for (i=0;i<genes_per_person;i++){
            for(j=0;j<genes_per_person;j++){
                a=personal_record->gene_dependancies->gene_inter_matrix[i][j];
                b=personal_record->ptr_to_genes_count->indi_gene_array[j][1];
                ptr_to_new_personal_gene_counts->indi_gene_array[i][0]=i;
                ptr_to_new_personal_gene_counts->indi_gene_array[i][1]+=(a*b);
              }
        }
        personal_record->ptr_to_new_genes_count=ptr_to_new_personal_gene_counts;
    }
    /*Now we have some new_gene_counts so the next generation is produced using the last generations gene_counts*/
    else{
        temp=personal_record->ptr_to_new_genes_count;
        while(temp->next!=NULL){
            temp=temp->next;
            counter++;
        }
        for (i=0;i<genes_per_person;i++){
            for(j=0;j<genes_per_person;j++){
                a=personal_record->gene_dependancies->gene_inter_matrix[i][j];
                b=temp->indi_gene_array[j][1];
                ptr_to_new_personal_gene_counts->indi_gene_array[i][0]=i;
                ptr_to_new_personal_gene_counts->indi_gene_array[i][1]+=(a*b);
            }
        }

        temp->next=ptr_to_new_personal_gene_counts;
    }

     ptr_to_new_personal_gene_counts->personal_plastic_records=create_plastic_records(ptr_to_new_personal_gene_counts);
}

/*check each individual for plasticity of genes by comparing each new_genes_count record with all the others personal gene_counts*/
/*Mono sta atoma pou den einai idi plastika*/
bool check_plasticity(personal_records *personal_records){
    personal_gene_list *temp1=personal_records->ptr_to_new_genes_count;
    personal_gene_list *temp2=personal_records->ptr_to_new_genes_count->next;
    int i;
    int counter=0;

    while(temp2!=NULL){
        for(i=0;i<genes_per_person;i++){

            if(temp1->personal_plastic_records->plastic_recs[i]!=temp2->personal_plastic_records->plastic_recs[i]){
                break;
            }
            else counter++;
        }

        if (counter+klepsimo>=genes_per_person) {return true;}
        else counter=0;

        temp2=temp2->next;
    }
    return false;
}

/*check if whole population is plastic*/
int check_pop_plastic(){
    population_list *temp=plist_head;
    int j;
    while(temp!=NULL){
        for(j=0;j<group_persons;j++){

            if(!temp->groups->personal_record[j]->isplastic){
                 return 0;
            }

        }
        temp=temp->next;
    }
    return 1;
}


void mature_pop(){
    population_list *temp=plist_head;
    int i;

    while(!check_pop_plastic()){
        while(temp!=NULL){
            for(i=0;i<group_persons;i++){

                if(!(temp->groups->personal_record[i]->isplastic)){
                    create_new_gene_counts(temp->groups->personal_record[i]);
                    if(check_plasticity(temp->groups->personal_record[i])){
                        temp->groups->personal_record[i]->isplastic=1;
                    }
                }

            }
            temp=temp->next;
        }
        temp=plist_head;

        if((total_gens%100==0)||(total_gens%50==0)){printf("Generation %d\n",total_gens);}
        if (total_gens>200) {remove_immatures(); return;}
        total_gens++;
    }
}
