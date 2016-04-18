#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "mathss.h"

#define debug_mode 0

#define group_persons 100
#define genes_per_person 10
#define max_gene_count 1000
#define num_of_max_generations 1000

typedef struct personal_gene_interaction_matrix{
    float gene_inter_matrix[genes_per_person][genes_per_person];
}personal_gene_interaction_matrix;

typedef struct personal_gene_count{
    int indi_gene_array[genes_per_person][2];
}personal_gene_count;

typedef struct personal_r1{
    char *personal_gene_r1[genes_per_person];
    int balance[genes_per_person];
}personal_r1;

typedef struct personal_r2{
     char *personal_gene_r2[genes_per_person];
     int balance[genes_per_person];
}personal_r2;

typedef struct personal_plastic_array{
    int plastic_recs[2^(genes_per_person)];
}personal_plastic_array;

typedef struct personal_plastics{
    int discrete_plastic[genes_per_person];
}personal_plastics;

typedef struct personal_records{
    int personal_id;
    personal_gene_count *ptr_to_genes_count;
    personal_gene_interaction_matrix *gene_dependancies;    /*need a better name*/
    personal_r1* ptr_to_personal_r1;
    personal_r2* ptr_to_personal_r2;
    personal_plastic_array *ptr_personal_plastic_array;
    personal_plastics *ptr_to_plastics;
    bool isplastic;
    float fitness;
}personal_records;

typedef struct array_of_group{
    personal_records* personal_record[group_persons];
}array_of_group;

typedef struct population_list{
    array_of_group* groups;
    struct population_list *next;
}population_list;
