#define max_generations 50
#define num_of_groups 50
#define persons_per_group 100
#define genes_per_person 10

typedef struct person{

    int periodos;   /*maturity steps needed */
    int id;         /*personal UNIQUE id */
    bool mature;
    float fitness;

    int gene_counts[genes_per_person];
    float gene_interactions[genes_per_person][genes_per_person];

    int vector_of_signs[genes_per_person];
    int maturity_array[1024]; /*if genes_per_person change, change this also to 2^gene_per_person */

}person;

typedef struct group{
    person *person_in_group[persons_per_group];
}group;

typedef struct population{
    group *group_in_population[num_of_groups];
    float sum_of_fitness;
}population;

population *generation_array[max_generations];
