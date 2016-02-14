#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define population 3
#define group_persons 1
#define genes_per_person 2
#define max_gene_interaction 5
#define minimum_gene_interaction 2
#define max_gene_count 1000

int debug_prints=1;

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

typedef struct balance_array{
    int balance[genes_per_person];
}balance_array;

typedef struct r1{
    char *indi_gene_r1[genes_per_person];
    balance_array *balance;
}r1;

typedef struct r2{
     char *indi_gene_r2[genes_per_person];
     balance_array *balance;
}r2;

typedef struct group_persons_array{
    int personal_id;
    indi_gene_count *ptr_to_genes_count;
    gene_inter_matrix *gene_dependancies;    /*need a better name*/
    r1* ptr_to_personal_r1;
    r2* ptr_to_personal_r2;
}group_persons_array;

typedef struct population_table{
    int max_id [population/group_persons];
    group_persons_array *ptr_to_group_persons;
}population_table;

/* convert integer to binary. Max integer (2^8)-1. Returns pointer to string representing the binary form*/
char *int_to_binary(int n)
{
    int c, d, count;
    char *pointer;

    count = 0;
    pointer = (char*)malloc(32+1);

    if ( pointer == NULL )
       exit(EXIT_FAILURE);
    for ( c = 7 ; c >= 0 ; c-- )
    {
       d = n >> c;
       if ( d & 1 )
          *(pointer+count) = 1 + '0';
       else
          *(pointer+count) = 0 + '0';
       count++;
    }
    *(pointer+count) = '\0';

    return  pointer;
}

/*take the first 4 bits of 8-bit string. Return pointer to that string + null terminated*/
char *break_binary_to_first_part(char *pointer){
    char first_part[5];
    char *ptr_to_first_part;
    strncpy(first_part, pointer,4);
    first_part[4] = '\0';

    ptr_to_first_part = (char *)malloc(sizeof(char));

    /*if (debug_prints){
        printf(" %s \n", first_part);
    }
*/

    ptr_to_first_part=first_part;

   return ptr_to_first_part;
}

/*take the last 4 bits of 8-bit string. Return pointer to that string + null terminated*/
char *break_binary_to_second_part(char *pointer){
    char second_part[5];
    char *ptr_to_second_part;
    strncpy(second_part, pointer + 4, 7 - 2);
    second_part[4] = '\0';

     ptr_to_second_part = (char *)malloc(sizeof(char));
/*
    if (debug_prints){
        printf(" %s \n", second_part);
    }
*/

    ptr_to_second_part=second_part;

   return ptr_to_second_part;
}

/*count how many 1s on first part and on second part and subtract them return the result*/
int create_balance(char *pointer){
    int count_first_part=0;
    int count_second_part=0;
    int i,j,balance;
    char *ptr_first_part;
    char *ptr_second_part;

    ptr_first_part=break_binary_to_first_part(pointer);
    for(i=0; ptr_first_part[i]; i++) {
        if(ptr_first_part[i] != '0') {
            count_first_part ++;
        }
    }

    ptr_second_part=break_binary_to_second_part(pointer);
    for(j=0; ptr_second_part[j]; j++) {
        if(ptr_second_part[j] != '0') {
            count_second_part ++;
        }
    }


    balance=count_first_part-count_second_part;
    return balance;
}

/*initialize personal nxn interaction matrix. Where n=gene_counts. Return pointer*/
gene_inter_matrix* initialize_gene_inter_matrix(){
    int i,j;
    gene_inter_matrix *ptr_to_gene_inter_matrix;
    ptr_to_gene_inter_matrix=(gene_inter_matrix*)malloc(sizeof(gene_inter_matrix));

    if(ptr_to_gene_inter_matrix==NULL)
    {
        printf("Not enough memory for personal gene interaction matrixes\n");
        exit(-1);
    }


    for (i=0;i<genes_per_person;i++){
        for (j=0;j<genes_per_person;j++){
           ptr_to_gene_inter_matrix->gene_inter_matrix[i][j]=((((float)rand()/(float)(RAND_MAX)) * max_gene_interaction)+ (-minimum_gene_interaction));
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

/*initialize personal gene counts,and put them on nx1 return pointer*/
indi_gene_count* initialize_indi_gene_count(){
    int i;
    indi_gene_count *ptr_to_indi_gene_count;
    ptr_to_indi_gene_count = (indi_gene_count *)malloc(sizeof(indi_gene_count));

    if(ptr_to_indi_gene_count==NULL)
    {
        printf("Not enough memory for personal gene counts matrix\n");
        exit(-1);
    }

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

/*initialize pointer to balance array if not seg-fault at when saving balances*/
balance_array *create_balance_array(){
    balance_array *ptr_to_balance_array;
    ptr_to_balance_array = (balance_array *)malloc(sizeof(balance_array));

    return ptr_to_balance_array;
}


r1* initialize_r1(){
    int j;
    r1 *ptr_to_personal_r1;
    ptr_to_personal_r1 = (r1 *)malloc(sizeof(r1));
    ptr_to_personal_r1->balance=create_balance_array();

    for (j=0;j<genes_per_person;j++){
        ptr_to_personal_r1->indi_gene_r1[j]=int_to_binary(rand()%256);
        ptr_to_personal_r1->balance->balance[j]=create_balance(ptr_to_personal_r1->indi_gene_r1[j]);
    }
    return ptr_to_personal_r1;
}


r2* initialize_r2(){
    int j;
    r2 *ptr_to_personal_r2;
    ptr_to_personal_r2 = (r2 *)malloc(sizeof(r2));
    ptr_to_personal_r2->balance=create_balance_array();

    for (j=0;j<genes_per_person;j++){
        ptr_to_personal_r2->indi_gene_r2[j]=int_to_binary(rand()%256);
        ptr_to_personal_r2->balance->balance[j]=create_balance(ptr_to_personal_r2->indi_gene_r2[j]);
    }
    return ptr_to_personal_r2;
}


group_persons_array* initialize_group_persons_array(){
    int i,j,k,l;
    group_persons_array *ptr_to_group_persons_array;

    ptr_to_group_persons_array = (group_persons_array *)malloc(sizeof(group_persons_array));

    if(ptr_to_group_persons_array==NULL)
    {
        printf("Not enough memory for group persons arrays\n");
        exit(-1);
    }

    for (i=0;i<group_persons;i++){
        ptr_to_group_persons_array->personal_id=i;
        ptr_to_group_persons_array->ptr_to_genes_count=initialize_indi_gene_count();
        ptr_to_group_persons_array->gene_dependancies=initialize_gene_inter_matrix();

        ptr_to_group_persons_array->ptr_to_personal_r1=initialize_r1();
        ptr_to_group_persons_array->ptr_to_personal_r2=initialize_r2();


        if(debug_prints){
            printf("Gia to Atomo %d\n", ptr_to_group_persons_array->personal_id);
            for (j=0;j<genes_per_person;j++){
                printf("Gene No %d ", ptr_to_group_persons_array->ptr_to_genes_count->indi_gene_array[j][0]);
                printf("Gene Count %d ", ptr_to_group_persons_array->ptr_to_genes_count->indi_gene_array[j][1]);
                printf("R1 of Gene %s ", ptr_to_group_persons_array->ptr_to_personal_r1->indi_gene_r1[j]);
                printf("Balance of R1 %d ", ptr_to_group_persons_array->ptr_to_personal_r1->balance->balance[j]);
                printf("R2 of Gene %s ", ptr_to_group_persons_array->ptr_to_personal_r2->indi_gene_r2[j]);
                printf("Balance of R2 %d ", ptr_to_group_persons_array->ptr_to_personal_r2->balance->balance[j]);

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


population_table* create_population(){
    int i;
    population_table *poptable = NULL;
    poptable = (population_table *)malloc(sizeof(population_table));

    if(poptable==NULL)
    {
        printf("Not enough memory for generic population table\n");
        exit(-1);
    }

    for (i=0;i<population/group_persons;i++){
        poptable->max_id[i]=i*group_persons;
        if(debug_prints) printf("Sto group me minimum id %d kai max id %d\n", poptable->max_id[i],poptable->max_id[i]+group_persons-1);
        poptable->ptr_to_group_persons=initialize_group_persons_array(debug_prints);
    }
    return poptable;
}


void delete_population(population_table *poptable,int num_for_deletion){
    /*sanity checks*/
    if(poptable==NULL)
    {
        printf("Population Table not initiated.Can't delete from empty table.Will exit now\n");
        return;
    }

    if(num_for_deletion>population){
        printf("Number of deletion bigger than total population.Will exit now\n");
        return;
    }
}


population_table* initialization(){
    srand(time(NULL));
    population_table *new_poptable;
    /*
    gene_inter_matrix *i;
    gene_inter_matrix *j;

    indi_gene_count *k;
    indi_gene_count *l;

    group_persons_array *a;
    group_persons_array *b;

    i=initialize_gene_inter_matrix();
    j=initialize_gene_inter_matrix();

    k=initialize_indi_gene_count();
    l=initialize_indi_gene_count();

    a=initialize_group_persons_array();
    b=initialize_group_persons_array();
    */

    new_poptable=create_population();
    return new_poptable;
}


int main (int argc,char **argv){
    population_table *new_poptable;
    new_poptable=initialization();
    return 0;
}
