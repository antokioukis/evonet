#ifndef MATHSS_H
#define MATHSS_H

#include <math.h>
#include "structs.h"


/*returns a random number from a normal_distribution based on the mu and the sigma*/
double random_normal_distrubution (double mu, double sigma);

/*convert binary 101010101 representing discrete genes of that step to integer used for comparison*/

float matrix_multiplication(float matrix[max_genes_per_person][max_genes_per_person],int vector[max_genes_per_person],int row);

int vector_to_decimal(int vector[max_genes_per_person]);

/*create discrete vector with elements based on the sign of the plastic records*/
void make_discrete(person *individual, float temp[max_genes_per_person]);

/*calculate eucledian distances of 2 vectors*/
float eucledian_distance(int final_form[],int optimal[]);

int NumberOfSetBits(int i);

unsigned int rand_interval(unsigned int min, unsigned int max);

unsigned concatenate(unsigned x, unsigned y);

#endif
