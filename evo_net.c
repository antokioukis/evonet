#include <stdlib.h>
#include <stdio.h>

#define population 1000
#define group_persons 100
#define genes_per_person 10

//kentriki idea exw kentrikos pinakas population grouparismenos o pli8ismos ana 100 se ka8e group
//psaxnw se poio group anoikei o individual kai apo ekei akolou8w pointer pou paei se individual groups kai apo ekei akolou8w allo
//pointer se personal genes
//problima o pinakas indi genes dimiourgeite ka8e fora me ta idia random

typedef struct indi_genes{
    int indi_genes [genes_per_person][2];
}indi_genes;

typedef struct indi_groups{
    int person_id;
    indi_genes *indi_genes;
    struct indi_groups *next;
}indi_groups;

typedef struct population_table{
    int value [population/group_persons][2];
}population_table;

indi_genes *create_indi_genes(){

    int i;
    indi_genes *array_of_indi;

    time_t t;
    srand((unsigned) time(&t));

    array_of_indi = (indi_genes *)malloc(sizeof(indi_genes));

    for (i=0;i<genes_per_person;i++){
        array_of_indi->indi_genes[i][0]=i;
        array_of_indi->indi_genes[i][1]=rand()%500;
    }

//   for (i=0;i<genes_per_person;i++){
//       printf("%d",array_of_indi->indi_genes[i][0]);
//       printf("%d",array_of_indi->indi_genes[i][1]);
//       printf("\n");
//    }

    return array_of_indi;

}

void push_indi_group(indi_groups * head, int val) {
    int j;
    indi_groups * current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    /* now we can add a new variable */
    current->next = (indi_groups *)malloc(sizeof(indi_groups));
    current->person_id=val;
    current->next->indi_genes = create_indi_genes();

//    for (j=0;j<genes_per_person;j++){
//            printf("%d ",current->next->indi_genes->indi_genes[j][1]);
//    }
    printf("\n");
    current->next->next = NULL;
}

indi_groups *create_indi_groups(){
    int i;
    indi_groups *array_of_groups = NULL;

    array_of_groups = (indi_groups *)malloc(sizeof(indi_groups));

    if (array_of_groups == NULL) {
        return NULL;
    }

    array_of_groups->indi_genes = create_indi_genes();
    array_of_groups->next = NULL;
    array_of_groups->person_id=0;


    for (i=1;i<group_persons;i++){
        push_indi_group(array_of_groups,i);
    }


    return array_of_groups;

}

void create_population(){
    int i;
    population_table *poptable = NULL;
    poptable = (population_table *)malloc(sizeof(population_table));

    for (i=0;i<population/group_persons;i++){
        poptable->value[i][0]=i*100;
        poptable->value[i][1]=create_indi_groups();
    }
//    for (i=0;i<population/group_persons;i++){
//        printf("mexri ari8mo: %d\n",poptable-> value[i][0]);
//    }
}

int main (void){
    int i,j;
    indi_groups *array_of_groups;
    indi_groups *temp;

//    create_indi_genes();
//    create_indi_genes();

    create_population();

//    array_of_groups=create_indi_groups();
//    temp=array_of_groups;
//
//    for (i=0;i<group_persons;i++){
//        printf("%d ",temp->person_id);
//        for (j=0;j<genes_per_person;j++){
//            printf("%d ",temp->indi_genes->indi_genes[j][1]);
//        }
//        printf("\n");
//        temp=temp->next;
//    }

}
