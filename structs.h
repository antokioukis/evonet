#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>

#define max_generations 2
#define persons_per_group 10
#define num_of_groups 1000
#define max_genes_per_person 10
#define rate_of_mutation 1
#define size_of_maturity_array 1024
#define neutRegionLength 1000
#define number_of_threads 10

typedef struct thread_auxialiary_create_person{
    int i;
    int num_of_gen;
    int num_of_parents;
    int row_swapping;
    int min_count;
    int max_count;
    double mutation_rate;
    gsl_rng *r;
    FILE *f;
    FILE *d;
}thread_auxialiary_create_person;

typedef struct thread_auxialiary{
    FILE *f;
    int num_of_gen;
    int index_of_gene;
}thread_auxialiary;

typedef struct R1_R2_auxiliary{
  int R1[max_genes_per_person];
  int R2[max_genes_per_person];
  bool neutRegion1[max_genes_per_person][neutRegionLength];
}R1_R2_auxiliary;

typedef struct person{

    int periodos;   /*maturity steps needed */
    int id;         /*personal UNIQUE id */
    bool mature;
    float fitness;

    int gene_counts[max_genes_per_person];
    float gene_interactions[max_genes_per_person][max_genes_per_person];

    int vector_of_signs[max_genes_per_person];
    int maturity_array[size_of_maturity_array]; /*if max_genes_per_person change, change this also to 2^max_genes_per_person */

    int gene_R1[max_genes_per_person]; /*gia ka8e gonidio, to [10] einai oti 8a paw mexri ton 2^10 san max integer*/
    int gene_R2[max_genes_per_person];

    bool neutRegion1[max_genes_per_person][neutRegionLength]; /* for each gene create a neutral region of length neutRegionLength */

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

int genes_per_person, backmutations;

bool mutatedSites[max_genes_per_person][neutRegionLength];

int apos, total_mutations;

#endif
