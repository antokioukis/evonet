#define max_generations 50
#define num_of_groups 50
#define persons_per_group 100
#define genes_per_person 10
#define rate_of_mutation 1


typedef struct R1_R2_auxiliary{
    int R1[genes_per_person];
    int R2[genes_per_person];
    float dependancies[genes_per_person][genes_per_person];
}R1_R2_auxiliary;

typedef struct person{

    int periodos;   /*maturity steps needed */
    int id;         /*personal UNIQUE id */
    bool mature;
    float fitness;

    int gene_counts[genes_per_person];
    float gene_interactions[genes_per_person][genes_per_person];

    int vector_of_signs[genes_per_person];
    int maturity_array[1024]; /*if genes_per_person change, change this also to 2^genes_per_person */

    int gene_R1[genes_per_person]; /*gia ka8e gonidio, to [10] einai oti 8a paw mexri ton 2^10 san max integer*/
    int gene_R2[genes_per_person];

}person;

typedef struct group{
    person *person_in_group[persons_per_group];
    struct group *next;
    struct group *prev;
    int group_number;
}group;

typedef struct population{
    group *groups_list;
    float sum_of_fitness;
}population;

population *generation_array[max_generations];
 
struct group *group_head = NULL;

int curr_num_of_groups=0;
