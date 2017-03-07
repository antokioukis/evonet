#include <time.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "robustness.h"
#include "maturity.h"
#include "generation_fit.h"
#include "events.h"
#include "generation_no_fit.h"

int curr_num_of_groups;
int sensitivity;
int event_index=0;

int **sensitivity_array;


void create_array_differences(float array_of_differences[11],float lamda,int optimal){
    int k,i,number_of_changes;
    float differences_distance;
    float differences_distance_exp;
    int active_div;
    int active_diff_array[10];
    int active_mod;
    int optimal_array[10];

        for(k=0;k<max_genes_per_person+1;k++){
            active_div=optimal;
            number_of_changes=0;
                        /*creation of differences vector onoma active_diff_array*/

            for(i=0;i<max_genes_per_person;i++){
                active_mod=active_div%10;
                optimal_array[i]=active_mod;
                active_div=active_div/10;
                if(number_of_changes<k){
                    number_of_changes++;
                    if (active_mod==0){
                        active_diff_array[i]=1;
                    }
                    else{
                        active_diff_array[i]=0;
                    }
                }
                else{
                    if (active_mod==0){
                        active_diff_array[i]=0;
                    }
                    else{
                        active_diff_array[i]=1;
                    }
                }
                /*printf("%d",active_diff_array[i]); */
            }
            /*printf("\n");*/
        differences_distance=eucledian_distance(active_diff_array,optimal_array);
        differences_distance_exp=exp(-lamda*differences_distance);
        array_of_differences[k]=differences_distance_exp;
        /*printf("%f\n",array_of_differences[k]);*/
        }    
}

void check_events(int generation_change[1000][2],int i,float lamda,int num_of_parents,int fitness,int row_swapping,
    int min_count, int max_count,double mutation_rate,gsl_rng *r,float recomb_rate ,int optimal,float array_of_differences[max_genes_per_person],
    FILE *f,FILE *d){

    if(i==generation_change[event_index][0]){
        if(curr_num_of_groups*persons_per_group>generation_change[event_index][1]){
            delete_groups(curr_num_of_groups-(generation_change[event_index][1]/persons_per_group),i%2);            
        }
        else{
            insert_groups((generation_change[event_index][1]/persons_per_group)-curr_num_of_groups,lamda,i%2,num_of_parents,fitness,row_swapping,
                min_count,max_count,mutation_rate,r,recomb_rate,optimal,array_of_differences,f,d);
        }
        event_index++;
    }
}

void create_generations(int fitness,int model_change,float lamda,int num_of_parents,int number_of_groups_wanted,int row_swapping,
                        int min_gene_R1R2,int max_gene_R1R2,int freq, int newfreq,
                        int min_count,int max_count,int generations_wanted,
                        int generation_change[1000][2],double mutation_rate,
                        int robustness, int robust_changes,int robust_last_bit,
                        gsl_rng *r,float recomb_rate,float target_fitness,int optimal,
                        FILE *start_in,
                        FILE *r1Output, FILE *r2Output,FILE *matrixOutput, FILE *countsOutput,FILE *fitnessOutput,
                        FILE *discreteOutput,FILE *robustOutput,FILE *genotypeOutput,FILE *fatherOutput, FILE *mutationOutput){
  
    int i,k,l,f,j,ii,/*m,*/o,p;
    int temp_for_free, geneID;
    population *robust_population = NULL;
    group* temp_robust_group = NULL;
    group *temp_normal_group = NULL;
    float array_of_differences[11];
    /*int number_of_changes;
    int active_mod;
    int optimal_array[10];
    float differences_distance;
    float differences_distance_exp;
    int active_div;
    int active_diff_array[10]; */
    int temp = 0;
    auxiliary_genotype_data *genotype_data=NULL; 
    /*pthread_t tid[number_of_threads];*/
    char neutral_output_filename[1024];
    thread_auxialiary *temp_auxialiary;
    FILE *file_neutral_gene=NULL;

    float generation_fitness=0;

    for( i = 0; i < max_genes_per_person; ++i){
      for( j = 0; j < neutRegionLength; ++j){
	       mutatedSites[i][j] = 0;
      }
    }

   create_array_differences(array_of_differences,lamda,optimal);
   
    /*printf("%f\n",target_fitness);*/
    /*kane opwsdipote ta generation wanted kai meta tsekare eisai se selection? kai den exeis ftasei to apaitoumeno fitness tote kane kai alla runs*/
    for(i=0;i<generations_wanted||((generation_fitness<=target_fitness)&&fitness);i++){
        for(o=0;o<genes_per_person;o++){
            for(j=0;j<2;j++){
                sensitivity_array[o][j]=0;
            }
        }
     
        for( ii = 0; ii < max_genes_per_person; ++ii){
	       for( j = 0; j < neutRegionLength; ++j){
	           mutatedSites[ii][j] = 0;
           }
        }
      
        if(i==0){
            generation_array[i%2]=create_population(number_of_groups_wanted,min_gene_R1R2,max_gene_R1R2,min_count,max_count,1,start_in);
        }
        else{
	        if (i%2==0) temp=2; else temp=1;
            if (model_change==i){
	      
	           if (fitness)
		          fitness=0;
	           else
		          fitness=1;
	      
	      freq = newfreq;
	    }
            if(fitness){
	           generation_array[i%2]=create_gen_population_fit(temp,num_of_parents,row_swapping,min_count,max_count,mutation_rate,r,
                                                                recomb_rate,fatherOutput,mutationOutput);
            }
            else{
                generation_array[i%2]=create_gen_population_no_fit(temp,num_of_parents,row_swapping,min_count,max_count,mutation_rate,r,
                                                                recomb_rate,fatherOutput,mutationOutput);
            }

            /*if( i % freq == 0){*/
             /* printf("temp: %d\n", temp); */
            /*HELLO HELLO HELLO*/
            for(p=0;p<genes_per_person;p++){
                create_mutation_vector(i%2, p);
            }
            /*
            printf("2. mutation vector............\n");
            for( ii = 0; ii < neutRegionLength; ++ii){
                printf("%d", mutatedSites[5][ii]);
            } 
            printf("\n\n");
            */    
        }
        mutate_population(generation_array[i%2],mutation_rate,r,i);

        /* ROBUSTNESS */
        if(i%freq==0 && robustness) {
            robust_population = create_population(curr_num_of_groups,min_gene_R1R2,max_gene_R1R2,min_count,max_count,0,NULL);
            temp_robust_group=robust_population->groups_list;
            temp_normal_group=generation_array[i%2]->groups_list;

            for(k=0;k<curr_num_of_groups;k++){ /*sarwse olo ton pli8ismo kai deep copy*/
                /*deep copy atomou*/
                for(l=0;l<persons_per_group;l++){
                    temp_robust_group->person_in_group[l]=deep_copy_person_robust(temp_robust_group->person_in_group[l],temp_normal_group->person_in_group[l]);
                }

                if(temp_robust_group->next!=NULL&&temp_normal_group->next!=NULL){
                    temp_robust_group=temp_robust_group->next;
                    temp_normal_group=temp_normal_group->next;
                }
            }

            for(k=0;k<curr_num_of_groups-1;k++){
                temp_robust_group=temp_robust_group->prev;
            }

            robust_population->groups_list=temp_robust_group;
            check_robustness(robustOutput,robust_population,robust_changes,robust_last_bit,1,r);
            
            /*freeing memory from robustness*/
            for(k=0;k<curr_num_of_groups;k++){
                for(l=0;l<persons_per_group;l++){
                    free(temp_robust_group->person_in_group[l]);
                }

                if(temp_robust_group->next!=NULL){
                    temp_robust_group=temp_robust_group->next;
                }
            }

            free(robust_population);
        }
        /*END OF ROBUSTNESS*/

        /*FREEING MEMORY*/
        if(i!=0){
            check_events(generation_change,i,lamda,num_of_parents,fitness,row_swapping,
                min_count,max_count,mutation_rate,r,recomb_rate,optimal,array_of_differences,fatherOutput,mutationOutput);
            if (i%2==0) temp_for_free=1; else temp_for_free = 0;
            while(generation_array[temp_for_free]->groups_list->next!=NULL){
                for(f=0;f<persons_per_group;f++){
                    free(generation_array[temp_for_free]->groups_list->person_in_group[f]);
                }
                    generation_array[temp_for_free]->groups_list=generation_array[temp_for_free]->groups_list->next;
                    free(generation_array[temp_for_free]->groups_list->prev);
            }

            for(f=0;f<persons_per_group;f++){
                    free(generation_array[temp_for_free]->groups_list->person_in_group[f]);
                }
            free(generation_array[temp_for_free]->groups_list);
            free(generation_array[temp_for_free]);
        }
    
        mature_generation(generation_array[i%2],1);
        generation_fitness=calculate_fitness(i%2,lamda,optimal,array_of_differences)/(curr_num_of_groups*persons_per_group);
        if (i%freq==0) printf("%f\n",generation_fitness);
        genotype_data=create_genotype_hash(generation_array[i%2]);
        if(i%freq==0){
            printf("Generation %d Simulated. \n",i);
            /*extract_R1R2_generation(r1Output, r2Output,i%2);
            extract_gene_dependancies_matrix_generation(matrixOutput, i%2);
            extract_gene_counts_generation(countsOutput, i%2);
            extract_discrete_generation(discreteOutput,i%2);
            extract_genotype_occ(genotypeOutput,genotype_data);
            extract_father_fitness(i%2,i); */
            extract_fitness_generation(fitnessOutput,i%2,mutation_rate);

            /*THREADED EXTRACT*/
            for( geneID = 0; geneID < genes_per_person && neut_flag; ++geneID){
                sprintf(neutral_output_filename, "neutralOutput%03d.txt", geneID);
                file_neutral_gene = fopen(neutral_output_filename, "a");
                temp_auxialiary=calloc(1,sizeof(thread_auxialiary));
                temp_auxialiary->num_of_gen=i%2;
                temp_auxialiary->index_of_gene=geneID;
                temp_auxialiary->f=file_neutral_gene;
                /*pthread_create(&(tid[geneID]), NULL, &extract_neutRegion1_generation, temp_auxialiary);*/
                extract_neutRegion1_generation(temp_auxialiary);
                fclose(file_neutral_gene);
            }
/*
            for (m = 0; m < max_genes_per_person; m++){
                pthread_join(tid[m], NULL);
            }*/
                /*geneID = 0;
                extract_neutRegion1_generation(neutralOutput, i%2, geneID);
                */ 
            /*
            fprintf(mutationOutput,"Generation %d \n",i);
            for(o=0;o<genes_per_person;o++){
                for(j=0;j<2;j++){
                    fprintf(mutationOutput,"%d ",sensitivity_array[o][j]);
                }
                fprintf(mutationOutput,"\n");
            }
            */
	    }
    }
}

void print_help(void){
    printf("Options\n");

    printf("\n");
    printf("-ploidy X:                  Number of parents per person (1 - 2)\n");
    printf("-swapping X:                R1R2_swapping or Row_swapping (Binary)(0 R1R2 -1 Row_swapping) \n");
    printf("-min_R1R2 X -max_R1R2 X:    Width of R1R2 selection (Integers)\n");
    printf("-min_count X -max_count X:  Width of gene_counts selection (Integers)\n");
    printf("-n X:                       Number of genes per person (Integer)\n");
    printf("-mutrate X:                 Mutation Rate (Double) (Default: 0.001) \n");
    printf("-rob X:                     Check for robustness (Binary) \n");
    printf("-num_of_rob_mutation X:     Number of mutations per robustness check (Integer) \n");
    printf("-rob_last                   On robust mutations change last bit of R1 R2 interactions (Binary)\n");

    printf("\n");
    printf("-sense X:                   Number of sensitivity in R1 and R2 (Default:30)\n");
    printf("-mod_change X:              Number of generation after which the evolutionary model changes (Default:-1)\n");
    printf("-recomb_rate X:             Recombination Rate representing percentage(Float)(Default: 0)\n");
    printf("-seed X:                    Set the seed for the random distributions, (Default is taken from current time)\n");
    printf("-tarfit X:                  Set the target average generation fitness of population, if reached program will quit\n");
    printf("-optimal_num X              Set number of open genes instead of optimal vector\n");
    printf("-optimal_vec X:             Set the target optimal which the population tries to reach\n");
    printf("-st_geno X:                 File where the starting genotypes can be read\n");

    printf("\n");
    printf("-N X:           Number of persons to be simulated (Integer)\n");
    printf("-generations X: Number of generations to be simulated (Integer)\n");
    printf("-selection X:   Inheritance based on fitness or neutral (Binary)\n");
    printf("-s2 X:          s^2 for the fitness function (Float)\n");
    printf("-eN X Y :       Create event at generation X, persons after event Y (Integers)\n");

    printf("\n");
    printf("-freq X:        Frequency of export of data (Integer)\n");
    printf("-r1out X:       Write R1_output at specified file (File) (Default R1.txt)\n");
    printf("-r2out X:       Write R2_output at specified file (File) (Default R2.txt)\n");
    printf("-matout X:      Write gene_interaction_matrix_output at specified file (Default matrix.txt) \n");
    printf("-gencout X:     Write gene_counts_output at specified file (Default counts.txt)\n");
    printf("-fitout X:      Write fitness_output at specified file (Default fitnesss.txt)\n");
    printf("-disout X:      Write discrete_output at specified file (Default discrete.txt)\n");
    printf("-robout X:      Write robust_output at specified file (Default robustness.txt)\n");
    printf("-gentpout X:    Write genotype_occurence_output at specified file (Default genotype.txt)\n");
    exit(0);
}



int main(int argc, char** argv){
    int i,m,j;
    int temp=1;
    double time_spent;
    int model_change;
    int generations=0;
    int min_count=0;
    int max_count=0;
    float s2;
    float lamda=0;
    int fitness=-1;
    int num_of_parents=0;
    int population_wanted;
    int groups_wanted=0;
    int R1R2_swapping=0;
    int min_gene_R1R2=0;
    int max_gene_R1R2=0;
    int freq=100000;
    int newfreq = 2;
    int generation_change[1000][2]={{-1}};
    double mutation_rate=0.001;
    int robustness=0;
    int robust_changes=0;
    int robust_last_bit=0;
    float recomb_rate=0;
    long int seed;
    int optimal_num=-1;
    clock_t end,begin;
    float target_fitness=-1;
    int optimal=0;
    int optimal_div;
    int optimal_array[max_genes_per_person];
    int optimal_mod;
    float min_distance;
    float max_distance;
    int xeiroteros[max_genes_per_person];
    int kaliteros[max_genes_per_person];
    float max_distance_exp;
    float min_distance_exp;

    const gsl_rng_type * T;
    gsl_rng * r;

    


    FILE *r1Output,*r2Output, *matrixOutput, *countsOutput, *fitnessOutput, *discreteOutput, *robustOutput, *genotypeOutput , *fatherOutput, *mutationOutput;
    FILE *infofile,*start_in;

    sensitivity=30;
    curr_num_of_groups=0;
    model_change=-1;
    m=0;

    start_in=NULL;
    r2Output=NULL;
    r1Output=NULL;
    matrixOutput=NULL;
    countsOutput=NULL;
    fitnessOutput=NULL;
    discreteOutput=NULL;
    robustOutput=NULL;
    genotypeOutput = NULL;
    fatherOutput = NULL;
    mutationOutput = NULL;

    seed = time(NULL);
    
    
    
    begin = clock();
    /* create a generator chosen by the
    environment variable GSL_RNG_TYPE */

    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc (T);


    for( i = 1; i < argc; ++i){
        /* neutral or selection */
        if( strcmp(argv[i], "-selection" ) == 0 ){
            fitness = atof(argv[++i]);
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
            if( R1R2_swapping != 0 && R1R2_swapping != 1 ){
                printf("wrong number on -swapping use 0 or 1\n");
                exit(1);
            }
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
            generation_change[m][0]=atoi(argv[++i]);
            generation_change[m][1]=atoi(argv[++i]);
            m++;
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

        if( strcmp(argv[i], "-r1out" ) == 0 ){
            r1Output=fopen(argv[++i],"w");
            continue;
        }

        if( strcmp(argv[i], "-r2out" ) == 0 ){
            r2Output=fopen(argv[++i],"w");
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

        if( strcmp(argv[i], "-fatout" ) == 0 ){
            fatherOutput=fopen(argv[++i],"w");
            continue;
        }

        if( strcmp(argv[i], "-disout" ) == 0 ){
            discreteOutput=fopen(argv[++i],"w");
            continue;
        }

        if( strcmp(argv[i], "-robout" ) == 0 ){
            robustOutput=fopen(argv[++i],"w");
            continue;
        }

        if( strcmp(argv[i], "-mutout" ) == 0 ){
            mutationOutput=fopen(argv[++i],"w");
            continue;
        }

        if( strcmp(argv[i], "-help" ) == 0 ){
            print_help();
        }

        if( strcmp(argv[i], "-mutrate" ) == 0 ){
            mutation_rate=atof(argv[++i]);
            continue;
        }

        if( strcmp(argv[i], "-tarfit" ) == 0 ){
            target_fitness=atof(argv[++i]);
            continue;
        }

        if( strcmp(argv[i], "-recomb_rate" ) == 0 ){
            recomb_rate=atof(argv[++i]);
            continue;
        }

        if( strcmp(argv[i], "-rob" ) == 0 ){
            robustness=atof(argv[++i]);
            continue;
        }

        if( strcmp(argv[i], "-num_of_rob_mutation" ) == 0 ){
            robust_changes=atoi(argv[++i]);
            continue;
        }

        if( strcmp(argv[i], "-sense" ) == 0 ){
            sensitivity=atoi(argv[++i]);
            continue;
        }

        if( strcmp(argv[i], "-st_geno" ) == 0 ){
            start_in=fopen(argv[++i],"r");

            continue;
        }

        if( strcmp(argv[i], "-optimal_vec" ) == 0 ){
            optimal=atoi(argv[++i]);
            continue;
        }

        if( strcmp(argv[i], "-optimal_num" ) == 0 ){
            optimal_num=atoi(argv[++i]);
            continue;
        }

        if( strcmp(argv[i], "-mod_change" ) == 0 ){
	       model_change=atoi(argv[++i]);
	       newfreq = atoi(argv[++i]);
	       continue;
        }

        if( strcmp(argv[i], "-rob_last" ) == 0 ){
            robust_last_bit=atoi(argv[++i]);
            if( robust_last_bit != 0 && robust_last_bit != 1 ){
                printf("wrong number on -rob_last use 0 or 1\n");
                exit(1);
            }
            continue;
        }

	if(strcmp(argv[i], "-seed") == 0){
	  seed = atol(argv[++i]);
	  continue;
	}

        fprintf(stderr, "Argument %s is invalid\n\n\n", argv[i]);
/*        print_help();
*/
    }



    infofile = fopen("infofile.txt", "w");

    for(i= 0; i < argc; ++i)
      fprintf(infofile, "%s ", argv[i]);
    fprintf(infofile, "\n");
    fclose(infofile);

    srand (seed);
    gsl_rng_set(r, seed);

    if(r1Output==NULL)          r1Output = fopen("R1.txt", "w");
    if(r2Output==NULL)          r2Output = fopen("R2.txt", "w");
    if(matrixOutput==NULL)      matrixOutput = fopen("matrix.txt", "w");
    if(countsOutput==NULL)      countsOutput = fopen("counts.txt", "w");
    if(fitnessOutput==NULL)     fitnessOutput = fopen("fitnesss.txt", "w");
    if(discreteOutput==NULL)    discreteOutput = fopen("discrete.txt", "w");
    if(robustOutput==NULL)      robustOutput = fopen("robustness.txt", "w");
    if(genotypeOutput == NULL)  genotypeOutput = fopen("genotype.txt", "w");
    if(fatherOutput==NULL)      fatherOutput = fopen("father.txt", "w");
    if(mutationOutput==NULL)    mutationOutput = fopen("mutations.txt", "w");
    if(start_in==NULL)          start_in = fopen("R1R2_input.txt", "r");

    
    if (target_fitness==-1){
        optimal_div=optimal;
        for(i=0;i<max_genes_per_person;i++){
            optimal_mod=optimal_div%10;
            optimal_array[i]=optimal_mod;
            optimal_div=optimal_div/10;
            if (optimal_mod==0){
                xeiroteros[i]=1;
                kaliteros[i]=0;
            }
            else{
                xeiroteros[i]=0;
                kaliteros[i]=1;
            }
        }
        max_distance=eucledian_distance(xeiroteros,optimal_array);
        min_distance=eucledian_distance(kaliteros,optimal_array);
        max_distance_exp=exp(-lamda*max_distance);
        min_distance_exp=exp(-lamda*min_distance);
        target_fitness=0.95*(min_distance_exp-max_distance_exp)+max_distance_exp;
        printf("target_fitness %f max_distance %f, min_distance %f\n",target_fitness,max_distance_exp,min_distance_exp);
    }

    if (optimal_num!=-1){
        temp=1;
        optimal=1;
        for(i=1;i<max_genes_per_person;i++){
            if (i<optimal_num){
                optimal=concatenate(optimal,1);
            }
            else{
                optimal=concatenate(optimal,0);
            }
        }
    }
    printf("%d\n",optimal);

    sensitivity_array = (int **)calloc(max_genes_per_person,sizeof(int *));
    for(i=0;i<max_genes_per_person;i++){
        sensitivity_array[i]=(int *)calloc(2,sizeof(int));
    }

    create_generations(fitness,model_change,lamda,num_of_parents,
		       groups_wanted,R1R2_swapping,min_gene_R1R2,max_gene_R1R2,freq, newfreq, 
		       min_count,max_count,
		       generations,generation_change,mutation_rate,robustness,robust_changes,robust_last_bit,r,recomb_rate,target_fitness,optimal,start_in,
		       r1Output, r2Output, matrixOutput, countsOutput,fitnessOutput,discreteOutput,robustOutput,genotypeOutput,fatherOutput, mutationOutput);

    for(i=0;i<max_genes_per_person;i++){
        free(sensitivity_array[i]);
    }
    free(sensitivity_array);
    gsl_rng_free (r);
    fclose(r1Output);
    fclose(r2Output);
    fclose(matrixOutput);
    fclose(countsOutput);
    fclose(fitnessOutput);
    fclose(discreteOutput);
    fclose(robustOutput);
    fclose(genotypeOutput);
    fclose(fatherOutput);
    fclose(mutationOutput);
    if (start_in!=NULL) fclose(start_in);
    

    end = clock();
    time_spent= (double)(end - begin) / CLOCKS_PER_SEC;

    printf("%f\n",time_spent);

    return 0;
}
