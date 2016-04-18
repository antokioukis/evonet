#include "structs.h"
#include "initiators.h"
#include "plastics.h"
#include "generations.h"


void fill_generation_table(int population,int num_of_generations,int fitness_flag){
    int i;
    for (i=0;i<num_of_generations;i++){
        if(i==0){
            if(debug_mode) printf("Creating First Generation\n");
            generation_array[i]=add_population(population);
            //mature_pop(generation_array[i]);
        }
        else{
            //printf("going to generate new generation %d \n",i);
            generation_array[i]=create_new_generation(population,fitness_flag);
            //printf("going to mature gen %d\n",i);
           // mature_pop(generation_array[i]);
        }
        printf("Generation %d Mature\n",i);
    }
}

/*Print everything*/
void print_dump(population_list *plist_head){
    population_list *temp=plist_head;
    int group_num=0;
    int i,j,k,l,u;
    while(temp!=NULL){
        printf("Sto group %d\n", group_num);
        group_num++;
        for(i=0;i<group_persons;i++){
            printf("Gia to atomo me id %d\n",temp->groups->personal_record[i]->personal_id);
//            for (j=0;j<genes_per_person;j++){
//                printf("Gene No %d ",temp->groups->personal_record[i]->ptr_to_genes_count->indi_gene_array[j][0]);
//                printf("Gene Count %d ",temp->groups->personal_record[i]->ptr_to_genes_count->indi_gene_array[j][1]);
//                printf("R1 of Gene %s ", temp->groups->personal_record[i]->ptr_to_personal_r1->personal_gene_r1[j]);
//                printf("Balance of R1 %d ", temp->groups->personal_record[i]->ptr_to_personal_r1->balance[j]);
//                printf("R2 of Gene %s ", temp->groups->personal_record[i]->ptr_to_personal_r2->personal_gene_r2[j]);
//                printf("Balance of R2 %d ",temp->groups->personal_record[i]->ptr_to_personal_r2->balance[j]);
//                printf("Gene (On or Off)=%d",temp->groups->personal_record[i]->ptr_to_plastics->discrete_plastic[j]);
//                printf("\n");
//            }

            printf("Pinakas Gene Dependencies Sigkekrimenou Atomou\n");
            for (k=0;k<genes_per_person;k++){
                for (l=0;l<genes_per_person;l++){
                    printf(" %f ",temp->groups->personal_record[i]->gene_dependancies->gene_inter_matrix[k][l]);
                }
                printf("\n");
            }
            printf("\n");
        }
        temp=temp->next;
    }
}


int main(){
    srand (time(NULL));
    fill_generation_table(10,num_of_max_generations,0);
    //print_dump(generation_array[0]);

  //  print_dump(generation_array[1]);
    //print_dump(glist_head->pop_list);
    //mature_pop(glist_head->pop_list);
//    temp=glist_head;
//    while(temp!=NULL){
//        //print_dump(temp->pop_list);
//        printf("asdasad");
//        temp=temp->next;
//    }
    //temp=glist_head;

//    for(i=0;i<num_of_generations;i++){
//        print_dump(temp->pop_list);
//        temp=temp->next;
//    }
    //num_of_immatures();
    //num_of_matures();
    /*delete_population(100);
    printf("Ekana delete 100 apo tous mature kai mou emeinan:\n");num_of_matures(); */
    return 0;
}

