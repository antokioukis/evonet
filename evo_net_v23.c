#include "initiators.h"
#include "plastics.h"
#include "delete.h"

/*
step 1: create array of floats nxn where n is genes per person (done but problem with srand doesnt create distinct random values FIXED)
step 2: create array of genes per person (done rand works creates different sets of random values)
step 3: create pointers to each of the above mentioned data structures (done)
step 4: create person arrays each entry must have pointer to step 1 and step 2 (done)
step 5: create population hash-table with pointers to each group_persons(done)
step 6: check for errors in each malloc (done)
step 7: create the kill functions, you will specify how many people must die and will get removed. Printed before and after
step 8: create the personal matrixes R1 ,R2 (done)
step 9: figure out on each gene R1 and R2 balance (ipologizetai swsta to balance alla otan to pernaw mesa stous pinakes mou emfanizei mono to teleutaio.
    paizei na exw kanei malakia me to print. ) (DOne)
step 10: check matrix multiplication working correctly
step 11: ta orismata pou pairnw gia create new gne counts einai kala?
step 12: na mpoun oi free (done)
step 13: na mpoun comments giati kapoia stigmi 8a to xaseis kai mesa stis sinartiseis gia na mporw na to diabasw meta(Done)
step 14: na mpoun oi dikleides asfaleies se oles tis malloc min skasei kati kai psaxnomai (done)
step 15: na kanw print ola ta balance oolwn twn gonidiwn
*/

/*Logic of program
    Create array named population which points to each each group of persons. In order for the program to be scalable each bucket contains N persons
    Each bucket points to an array where all the people from that group have 2 pointers: 1 pointer to their personal gene counts and 1 pointer to their
    personal gene interactions

                min<id<max           personal_id
    population-------------->bucket---------------->personal reconds

    Basically population is a hash table
*/

/*Print everything*/
void print_dump(){
    population_list *temp=plist_head;
    int i,j,k,l,u;
    while(temp!=NULL){
        printf("Gia to group me max id %d\n",temp->max_id);
        for(i=0;i<group_persons;i++){
            printf("Gia to atomo me id %d\n",temp->groups->personal_record[i]->personal_id);
            for (j=0;j<genes_per_person;j++){
                printf("Gene No %d ",temp->groups->personal_record[i]->ptr_to_genes_count->indi_gene_array[j][0]);
                printf("Gene Count %d ",temp->groups->personal_record[i]->ptr_to_genes_count->indi_gene_array[j][1]);
/*                printf("R1 of Gene %s ", temp->groups->personal_record[i]->ptr_to_personal_r1->personal_gene_r1[j]);
                printf("Balance of R1 %d ", temp->groups->personal_record[i]->ptr_to_personal_r1->balance[j]);
                printf("R2 of Gene %s ", temp->groups->personal_record[i]->ptr_to_personal_r2->personal_gene_r2[j]);
                printf("Balance of R2 %d ",temp->groups->personal_record[i]->ptr_to_personal_r2->balance[j]);
*/              printf("\n");
            }
            for (j=0;j<genes_per_person;j++){
                while(temp->groups->personal_record[i]->ptr_to_new_genes_count!=NULL){
                    for(u=0;u<genes_per_person;u++){
                       /*     printf("New Gene No %d ",temp->groups->personal_record[i]->ptr_to_new_genes_count->indi_gene_array[u][0]);
                            printf("New Gene Count %d ",temp->groups->personal_record[i]->ptr_to_new_genes_count->indi_gene_array[u][1]);
                       */     printf("S of gene count %f",temp->groups->personal_record[i]->ptr_to_new_genes_count->personal_plastic_records->plastic_recs[u]);
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
            }
            printf("\n");
        }
        temp=temp->next;
    }
}

int main(){
   /* int num_for_delete,num_for_insert,num_of_gens;
    int input; */
    srand (time(NULL));
/*

    printf("\n");
    printf("For Insert Event press 1\n");
    printf("For Delete press 2\n");
    printf("For Print_Dump press 3\n");
    printf("For Aging press 4\n");
    printf("For Termination press 5\n");
    printf("\n");


    do{
        printf("Waiting for new event\n");
        input=getchar();
        getchar();
        switch(input){
            case'1':
                printf("Please enter number of insertions\n");
                scanf("%d", &num_for_insert);
                add_population(num_for_insert);
                printf("\n");
                break;
            case'2':
                printf("Please enter number of deletions\n");
                scanf("%d", &num_for_delete);
                delete_population(num_for_delete);
                printf("\n");
                break;
            case'3':
                print_dump();
                printf("\n");
                break;
            case'4':
                printf("Please enter number of generations\n");
                scanf("%d", &num_of_gens);
                aging(num_of_gens);
                printf("\n");
                break;
            default:
                printf("\n");
                break;
        }

    } while(input != '5');
*/

    add_population(1);
    aging(10);
    /*delete_population(2);*/
    general_plasticity();
    print_dump();

    return 0;
}
