#include "initiators.h"
#include "plastics.h"

/*Print everything*/
void print_dump(){
    population_list *temp=plist_head;
    int i/*,j,k,l,u*/;
    while(temp!=NULL){
        /*printf("Gia to group me max id %d\n",temp->max_id); */
        for(i=0;i<group_persons;i++){
            printf("Gia to atomo me id %d\n",temp->groups->personal_record[i]->personal_id);
/*            for (j=0;j<genes_per_person;j++){
                printf("Gene No %d ",temp->groups->personal_record[i]->ptr_to_genes_count->indi_gene_array[j][0]);
                printf("Gene Count %d ",temp->groups->personal_record[i]->ptr_to_genes_count->indi_gene_array[j][1]);
                printf("R1 of Gene %s ", temp->groups->personal_record[i]->ptr_to_personal_r1->personal_gene_r1[j]);
                printf("Balance of R1 %d ", temp->groups->personal_record[i]->ptr_to_personal_r1->balance[j]);
                printf("R2 of Gene %s ", temp->groups->personal_record[i]->ptr_to_personal_r2->personal_gene_r2[j]);
                printf("Balance of R2 %d ",temp->groups->personal_record[i]->ptr_to_personal_r2->balance[j]);
*/              printf("\n");
            }
 /*           for (j=0;j<genes_per_person;j++){
                while(temp->groups->personal_record[i]->ptr_to_new_genes_count!=NULL){
                    for(u=0;u<genes_per_person;u++){
                            printf("New Gene No %d ",temp->groups->personal_record[i]->ptr_to_new_genes_count->indi_gene_array[u][0]);
                            printf("New Gene Count %d ",temp->groups->personal_record[i]->ptr_to_new_genes_count->indi_gene_array[u][1]);
                            printf("S of gene count %d",temp->groups->personal_record[i]->ptr_to_new_genes_count->personal_plastic_records->plastic_recs[u]);
                            printf("\n");
                    }
                    temp->groups->personal_record[i]->ptr_to_new_genes_count=temp->groups->personal_record[i]->ptr_to_new_genes_count->next;
                }
            }
            printf("Pinakas Dependencies Sigkekrimenou Atomou\n");
            for (k=0;k<genes_per_person;k++){
                for (l=0;l<genes_per_person;l++){
                    printf(" %f ",temp->groups->personal_record[i]->gene_dependancies->gene_inter_matrix[k][l]);
                }
                printf("\n");
            }*/
            printf("\n");
        }
        temp=temp->next;
    }
/*}*/

int main(){
    srand (time(NULL));

    add_population(500);
    mature_pop();
    num_of_immatures();
    num_of_matures();
    delete_population(100);
    printf("Ekana delete 100 apo tous mature kai mou emeinan:\n");num_of_matures();
    return 0;
}
