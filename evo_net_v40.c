#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <assert.h>

#include "structs.h"
#include "mathss.h"
#include "creators.h"
#include "maturity.h"
#include "generation_no_fit.h"
#include "generation_fit.h"
#include "events.h"
#include "extract.h"

void print_dump(int num_of_generation){
  int i,j,k,l;
  group *temp=generation_array[num_of_generation]->groups_list;
  while(temp!=NULL){
    printf("Number of group: %d\n",i);
    for(j=0;j<persons_per_group;j++){
      printf("Id atomou: %d\n",temp->person_in_group[j]->id);
      printf("Fitness atomou: %f\n",temp->person_in_group[j]->fitness);
      printf("Gene dependancies matrix:\n");
      for(l=0;l<max_genes_per_person;l++){
	for(k=0;k<max_genes_per_person;k++){
	  printf("%f ",temp->person_in_group[j]->gene_interactions[l][k]);
	}
	printf("\n");
      }
      printf("R1-R2 atomou\n");
      for(l=0;l<max_genes_per_person;l++){
	printf("R1 %d R2 %d\n",temp->person_in_group[j]->gene_R1[l],temp->person_in_group[j]->gene_R2[l]);
      }
      for(l=0;l<max_genes_per_person;l++){
	printf("Gene Counts %d\n",temp->person_in_group[j]->gene_counts[l]);
      }
      printf("\n");
    }
    i++;
    temp=temp->next;
  }
}


void create_generations(int fitness,float lamda,int num_of_parents,int number_of_groups_wanted,int row_swapping,
                        int min_gene_R1R2,int max_gene_R1R2,int freq,
                        int min_count,int max_count,int generations_wanted,
                        int generation_change,int pop_size_change,double mutation_rate,
                        FILE *r1r2Output, FILE *matrixOutput, FILE *countsOutput,FILE *fitnessOutput,FILE *discreteOutput){

  
  int i;
  /*int type_of_event;
    int num_of_groups_affected; */
  for(i=0;i<generations_wanted;i++){
    
    if(i==0){
      generation_array[0]=create_population(number_of_groups_wanted,min_gene_R1R2,max_gene_R1R2,min_count,max_count);
    }
      
    else{
      printf("Creating Generation %d\n",i);
      
      if(fitness){
	generation_array[i]=create_gen_population_fit(i,num_of_parents,row_swapping,min_count,max_count,mutation_rate);
      }
      else{
	generation_array[i]=create_gen_population_no_fit(i,num_of_parents,row_swapping,min_count,max_count,mutation_rate);
      }
    }
    mature_generation(generation_array[i]);
    calculate_fitness(i,lamda);
    if(i==generation_change){
      if(curr_num_of_groups*persons_per_group>pop_size_change){
	delete_groups(curr_num_of_groups-(pop_size_change/persons_per_group),i);
      }
      else{
	insert_groups((pop_size_change/persons_per_group)-curr_num_of_groups,lamda,i,num_of_parents,fitness,row_swapping,min_count,max_count,mutation_rate);
      }
    }

    if(i%freq==0){
      extract_R1R2_generation(r1r2Output, i);
      extract_gene_dependancies_matrix_generation(matrixOutput, i);
      extract_gene_counts_generation(countsOutput, i);
      extract_discrete_generation(discreteOutput,i); 
      extract_fitness_generation(fitnessOutput,i);
    }
  }
}

void print_help(void){
  printf("Options\n");

  printf("\n");
  printf("-ploidy X:                  Number of parents per person (1 - 2)\n");
  printf("-swapping X:                R1R2_swapping or Row_swapping (Binary) \n");
  printf("-min_R1R2 X -max_R1R2 X:    Width of R1R2 selection (Integers)\n");
  printf("-min_count X -max_count X:  Width of gene_counts selection (Integers)\n");
  printf("-n X:                       Number of genes per person (Integer)\n");
  printf("-mutrate X:                 Mutation Rate (Double) (Default: 0.001) \n");

  printf("\n");
  printf("-N X:           Number of persons to be simulated (Integer)\n");
  printf("-generations X: Number of generations to be simulated (Integer)\n");
  printf("-selection X:   Inheritance based on fitness or neutral (Binary)\n");
  printf("-s2 X:          s^2 for the fitness function (Float)\n");
  printf("-eN X Y :       Create event at generation X, persons after event Y (Integers)\n");
    
  printf("\n");
  printf("-freq X:        Frequency of export of data (Integer)\n");
  printf("-r1r2out X:     Write R1R2_output at specified file (File) (Default R1R2.txt)\n");
  printf("-matout X:      Write gene_interaction_matrix_output at specified file (Default matrix.txt) \n");
  printf("-gencout X:     Write gene_counts_output at specified file (Default counts.txt)\n");
  printf("-fitout X:      Write fitness_output at specified file (Default fitness.txt)\n");
  printf("-disout X:      Write discrete_output at specified file (Default discrete.txt)\n");


  exit(0);
}



int main(int argc, char** argv){
  int i;
  int generations;
  int min_count;
  int max_count;
  float s2;
  float lamda;
  int fitness;
  int num_of_parents;
  int population_wanted;
  int groups_wanted;
  int R1R2_swapping=0;
  int min_gene_R1R2;
  int max_gene_R1R2;
  int freq;
  int generation_change=-1;
  int pop_size_change;
  double mutation_rate=0.001;

  FILE *r1r2Output, *matrixOutput, *countsOutput, *fitnessOutput, *discreteOutput;

  r1r2Output=NULL;
  matrixOutput=NULL;
  countsOutput=NULL;
  fitnessOutput=NULL;
  discreteOutput=NULL;

  srand (time(NULL));

  for( i = 1; i < argc; ++i){
    /* neutral or selection */
    if( strcmp(argv[i], "-selection" ) == 0 ){
      fitness = atoi(argv[++i]);
      continue;
    }

    /* sigma^2, o paronomastis sto fitness function */
    if( strcmp(argv[i], "-s2" ) == 0 ){
      s2 = atof(argv[++i]);
      lamda=1/s2;
      continue;
    }

    /* o arithmos atomwn */
    if( strcmp(argv[i], "-N" ) == 0 ){
      population_wanted = atoi(argv[++i]);
      groups_wanted=population_wanted/persons_per_group;
      continue;
    }

    /* number of parents per person */
    if( strcmp(argv[i], "-ploidy" ) == 0 ){
      num_of_parents = atoi(argv[++i]);
      if( num_of_parents != 1 && num_of_parents != 2 ){
	printf("wrong number on -ploidy use 1 or 2\n");
	exit(1);
      }
      num_of_parents=num_of_parents-1;
      continue;
    }
    /*R1R2_swapping h row_swapping*/
    if( strcmp(argv[i], "-swapping" ) == 0 ){
      R1R2_swapping = atoi(argv[++i]);
      continue;
    }

    /*frequency of data export*/
    if( strcmp(argv[i], "-freq" ) == 0 ){
      freq = atoi(argv[++i]);
      continue;
    }
      
    if( strcmp(argv[i], "-min_R1R2" ) == 0 ){
      min_gene_R1R2 = atoi(argv[++i]);
      continue;
    }

    if( strcmp(argv[i], "-max_R1R2" ) == 0 ){
      max_gene_R1R2 = atoi(argv[++i]);
      continue;
    }

    if( strcmp(argv[i], "-min_count" ) == 0 ){
      min_count = atoi(argv[++i]);
      continue;
    }

    if( strcmp(argv[i], "-max_count" ) == 0 ){
      max_count = atoi(argv[++i]);
      continue;
    }


    if( strcmp( argv[i], "-eN") == 0 ){
      /* -eN 100 50 */
      generation_change=atoi(argv[++i]);
      pop_size_change=atoi(argv[++i]);
      continue;
    }

    if( strcmp(argv[i], "-generations" ) == 0 ){
      generations = atoi(argv[++i]);
      continue;
    }

    /* number of genes per person */
    if( strcmp(argv[i], "-n" ) == 0 ){
      genes_per_person = atoi(argv[++i]);
      continue;
    }

    if( strcmp(argv[i], "-r1r2out" ) == 0 ){
      r1r2Output=fopen(argv[++i],"w");
      continue;
    }

    if( strcmp(argv[i], "-matout" ) == 0 ){
      matrixOutput=fopen(argv[++i],"w");
      continue;
    }

    if( strcmp(argv[i], "-gencout" ) == 0 ){
      countsOutput=fopen(argv[++i],"w");
      continue;
    }

    if( strcmp(argv[i], "-fitout" ) == 0 ){
      fitnessOutput=fopen(argv[++i],"w");
      continue;
    }

    if( strcmp(argv[i], "-desout" ) == 0 ){
      discreteOutput=fopen(argv[++i],"w");
      continue;
    }

    if( strcmp(argv[i], "-help" ) == 0 ){
      print_help();
    }

    if( strcmp(argv[i], "-mutrate" ) == 0 ){
      mutation_rate=atof(argv[++i]);
      continue;
    }

    fprintf(stderr, "Argument %s is invalid\n\n\n", argv[i]);
    print_help();
        
  }

  if(r1r2Output==NULL)   r1r2Output = fopen("R1R2.txt", "w");
  if(matrixOutput==NULL) matrixOutput = fopen("matrix.txt", "w");
  if(countsOutput==NULL) countsOutput = fopen("counts.txt", "w");
  if(fitnessOutput==NULL) fitnessOutput = fopen("fitness.txt", "w");
  if(discreteOutput==NULL) discreteOutput = fopen("discrete.txt", "w");


  create_generations(fitness,lamda,num_of_parents,
		     groups_wanted,R1R2_swapping,min_gene_R1R2,max_gene_R1R2,freq,min_count,max_count,
		     generations,generation_change,pop_size_change,mutation_rate,
		     r1r2Output, matrixOutput, countsOutput,fitnessOutput,discreteOutput);

  fclose(r1r2Output);
  fclose(matrixOutput);
  fclose(countsOutput);
  fclose(fitnessOutput);
  fclose(discreteOutput);

  return 0;
}
