#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define population 100000
#define group_persons 1000
#define genes_per_person 10
#define max_gene_interaction 5
#define max_gene_count 1000

int debug_prints=0;

/*
step 1: create array of floats nxn where n is genes per person (done but problem with srand doesnt create distinct random values FIXED)
step 2: create array of genes per person (done rand works creates different sets of random values)
step 3: create pointers to each of the above mentioned data structures (done)
step 4: create person arrays each entry must have pointer to step 1 and step 2 (done)
step 5: create population hash-table with pointers to each group_persons(done)
step 6: check for errors in each malloc
step 7: create the kill functions, you will specify how many people must die and will get removed. Printed before and after
step 8: what about the 2 other matrixes?
*/

/*Logic of program
    Create array named population which points to each each group of persons. In order for the program to be scalable each bucket contains N persons
    Each bucket points to an array where all the people from that group have 2 pointers: 1 pointer to their personal gene counts and 1 pointer to their
    personal gene interactions

                min<id<max           personal_id
    population-------------->bucket---------------->personal reconds

    Basically population is a hash table
*/


typedef struct gene_interaction_matrix{
    float gene_inter_matrix[genes_per_person][genes_per_person];
}gene_inter_matrix;

typedef struct individual_gene_count{
    int indi_gene_array[genes_per_person][2];
}indi_gene_count;

typedef struct group_persons_array{
    int personal_id;
    indi_gene_count *ptr_to_genes_count;
    gene_inter_matrix *gene_dependancies;    //need a better name
}group_persons_array;

typedef struct population_table{
    int max_id [population/group_persons];
    group_persons_array *ptr_to_group_persons;
}population_table;

gene_inter_matrix* initialize_gene_inter_matrix(){
    int i,j;
    gene_inter_matrix *ptr_to_gene_inter_matrix;
    ptr_to_gene_inter_matrix=(gene_inter_matrix*)malloc(sizeof(gene_inter_matrix));


    for (i=0;i<genes_per_person;i++){
        for (j=0;j<genes_per_person;j++){
           ptr_to_gene_inter_matrix->gene_inter_matrix[i][j]=(((float)rand()/(float)(RAND_MAX)) * max_gene_interaction);
          }
    }
    /*
    printf("Pinakas Dependencies Sigkekrimenou Atomou\n");
    for (i=0;i<genes_per_person;i++){
        for (j=0;j<genes_per_person;j++){
           printf(" %f ",ptr_to_gene_inter_matrix->gene_inter_matrix[i][j]);
        }
        printf("\n");
    }
*/

    return ptr_to_gene_inter_matrix;

}

indi_gene_count* initialize_indi_gene_count(){
    int i;
    indi_gene_count *ptr_to_indi_gene_count;
    ptr_to_indi_gene_count = (indi_gene_count *)malloc(sizeof(indi_gene_count));

    for (i=0;i<genes_per_person;i++){
        ptr_to_indi_gene_count->indi_gene_array[i][0]=i;
        ptr_to_indi_gene_count->indi_gene_array[i][1]=rand()%500;
    }

/*
    for (i=0;i<genes_per_person;i++){
       printf("Gene No %d ",ptr_to_indi_gene_count->indi_gene_array[i][0]);
       printf("Gene Count %d ",ptr_to_indi_gene_count->indi_gene_array[i][1]);
       printf("\n");
    }

*/
    return ptr_to_indi_gene_count;
}

group_persons_array* initialize_group_persons_array(){
    int i,j,k,l;
    group_persons_array *ptr_to_group_persons_array;

    ptr_to_group_persons_array = (group_persons_array *)malloc(sizeof(group_persons_array));

    for (i=0;i<group_persons;i++){
        ptr_to_group_persons_array->personal_id=i;
        ptr_to_group_persons_array->ptr_to_genes_count=initialize_indi_gene_count();
        ptr_to_group_persons_array->gene_dependancies=initialize_gene_inter_matrix();
        if(debug_prints){
            printf("Gia to Atomo %d\n", ptr_to_group_persons_array->personal_id);
            for (j=0;j<genes_per_person;j++){
                printf("Gene No %d ", ptr_to_group_persons_array->ptr_to_genes_count->indi_gene_array[j][0]);
                printf("Gene Count %d ", ptr_to_group_persons_array->ptr_to_genes_count->indi_gene_array[j][1]);
                printf("\n");
            }

            printf("Pinakas Dependencies Sigkekrimenou Atomou\n");
            for (k=0;k<genes_per_person;k++){
                for (l=0;l<genes_per_person;l++){
                    printf(" %f ",ptr_to_group_persons_array->gene_dependancies->gene_inter_matrix[k][l]);
                }
                printf("\n");
            }
            printf("\n");
            }
    }
    return ptr_to_group_persons_array;
}


void create_population(){
    int i;
    population_table *poptable = NULL;
    poptable = (population_table *)malloc(sizeof(population_table));

    for (i=0;i<population/group_persons;i++){
        if(debug_prints) printf("Sto group me minimum id %d kai max id %d\n", poptable->max_id[i],poptable->max_id[i]+group_persons-1);
        poptable->max_id[i]=i*group_persons;
        poptable->ptr_to_group_persons=initialize_group_persons_array(debug_prints);
    }
}

void initialization(){
    srand(time(NULL));

//    gene_inter_matrix *i;
//    gene_inter_matrix *j;
//
//    indi_gene_count *k;
//    indi_gene_count *l;

//    group_persons_array *a;
//    group_persons_array *b;

//    i=initialize_gene_inter_matrix();
//    j=initialize_gene_inter_matrix();
//
//    k=initialize_indi_gene_count();
//    l=initialize_indi_gene_count();

//    a=initialize_group_persons_array();
//    b=initialize_group_persons_array();

    create_population();
}

int main (int argc, char *argv[]){
    initialization();
    return 0;
}
