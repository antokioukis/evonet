#include<stdio.h>
#include<stdlib.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define llu  long long unsigned int


unsigned popcount(llu g)
{
  return(__builtin_popcountll(g));
}


char *intToString(llu x, int a){
  int i;	  
  char *tmp = calloc(a+1, sizeof(char));
  
  for(i = 0; i< a; ++i)
    {
      tmp[a-i-1] = popcount((x & (1LL << (llu)i))) + '0';
    }
  
  tmp[a]='\0';
  return(tmp);
}


int initializePop(int popsize, int genes, llu *pop)
{
  int i;
  for( i = 0; i < popsize; ++i)
    pop[i] = 0;
  return 1;
}

int mutatePop(int popsize, int genes, llu *pop, double mutRate, gsl_rng* r)
{
  int i;
  /* first calculate how many mutations are expected */
  /* It will be a poisson number of mutations. The expected
     number will be the mutationRate x populationSize */
  unsigned numOfMutations = gsl_ran_poisson(r, mutRate*popsize);
  for( i = 0; i < numOfMutations; ++i)
    {
      /* choose a random individual to mutate */
      unsigned int anInd = gsl_rng_uniform_int(r, RAND_MAX) % popsize;

      /* choose a gene to mutate */
      unsigned int aGene = gsl_rng_uniform_int(r, RAND_MAX) % genes;

      /* shift 1 left as many times as defined by the aGene
	 then mutation will just change the bit at the specific
	 location */
      pop[anInd] = pop[anInd] ^ ( 1 << aGene);
      
    }
  
  return numOfMutations;
}

unsigned difGenotypes(llu g1, llu g2)
{
  return(__builtin_popcountll(g1^g2));
}

unsigned numberOfBestGenotypes(llu *pop, llu optimal, int popsize, int genes, double *lut, double *optFit, int *leastDif)
{
  int i, n=0, dif = 0, minDif = RAND_MAX;
    
  for(i = 0; i < popsize; ++i)
    {
      
      dif = difGenotypes(pop[i], optimal);
      /* fprintf(stderr, "%s\t%s\t%d\n", intToString(pop[i], genes), intToString(optimal, genes), dif); */
      if( dif < minDif){
	minDif = dif;
	n=1;
      }
      else if( dif == minDif)
	n++;
    }
  
  *optFit = lut[minDif];
  *leastDif = minDif;
  
  return n;

}

double fitnessValue(unsigned x, double sigma, double p, int mode)
{
  if(mode == 1)
    return exp(-abs( pow(x, p) )/ sigma);
  else if(mode == 2)
    return sigma + p *x;

  else return 1.0;
}


int fitnesslut(double sigma, double* lut, int genes, int mode, double p)
{
  int i;
  /* double  maxFitness=1., minFitness =0.01; */
  
  for(i = 0; i < genes +1; ++i)
    {
      /* lut[i] = exp(-(i*i)/sigma); */
      lut[i] = fitnessValue(i, sigma, p, mode);
            
      /* fprintf(stderr, "i: %d, lut: %.20f\n", i, lut[i]); */
      /* lut[i] = (lut[i] - lut[genes])/(lut[0] - lut[genes]) *  (maxFitness - minFitness) + minFitness; */ 
    }
  return 1;
}

double getFitness(double *fitnesses, int popsize, int genes, llu *pop, llu optimum, double sigma, double *lut)
{

  int i, tempdif = 0, previousi = 0;
  double avFitness = 0.;
  
  for(i = 0; i < popsize; ++i)
    {
      tempdif = difGenotypes(optimum, pop[i]);
      fitnesses[i] = fitnesses[previousi] + lut[tempdif];
      previousi++;
      if( i == 0) previousi = 0;
    }
  avFitness = fitnesses[popsize - 1]/popsize;
  return avFitness;
}
	

double reproduce(int popsize, int genes, llu* pop, double sigma, llu optimum, gsl_rng*r, double *lut)
{
  int i;
  double avFitness = 0., *fitnesses = calloc(popsize, sizeof(double));

  avFitness = getFitness(fitnesses, popsize, genes, pop, optimum, sigma, lut);
    
  llu *tmpPop = calloc(popsize, sizeof(llu));
  
  for(i = 0; i <popsize; ++i)
    {
      /* get a random fitness */
      double randFit = gsl_rng_uniform(r) * fitnesses[popsize - 1];
      
      int ci = 0;
      while( fitnesses[ci] < randFit )
	{
	  ci++;
	  assert(ci < popsize);
	}

      tmpPop[i] = pop[ci];
    }

  /* fprintf(stderr, "."); */
  for( i = 0; i < popsize; ++i)
    pop[i] = tmpPop[i];

  
  free(tmpPop);
  free(fitnesses);
  
  return avFitness;
}




int main(int argc, char** argv)
{

  int popsize = 200, fitMode = 1;
  double maxFitness = 0.95;
  double mutRate = 0.001;
  double sigma = 5., p=2.;
  int genes = 10;
  llu optimum= 0;
  int i;
  
  assert(genes < 64);


  FILE *genout = fopen("generations.txt", "w");
  FILE *info = fopen("infofile.txt", "w");
  FILE *log = fopen("log.txt", "w");
  FILE *fitnesslutfile = fopen("fitness.txt", "w");
  FILE *curOptFile = fopen("curOptFile.txt", "w");

  long seed =  191920;

  for( i = 1; i < argc; ++i)
    {
      if( !strcmp("-seed", argv[i])) {
	seed = atol(argv[++i]);
	continue;
      }

      if( !strcmp("-mu", argv[i])){
	mutRate = atof(argv[++i]);
	continue;
      }

      if( !strcmp("-popsize", argv[i])){
	popsize = atoi(argv[++i]);
	continue;
      }

      if( !strcmp("-l", argv[i]) ){
	genes = atoi(argv[++i]);
	continue;
      }
      
      if( !strcmp("-s", argv[i])){
	sigma = atof(argv[++i]);
	continue;
      }

      if( !strcmp("-p", argv[i])){
	p = atof(argv[++i]);
	continue;
      }

      if( !strcmp("-fm", argv[i])){
	fitMode = atoi(argv[++i]);
	continue;
      }

      
      
      fprintf(stderr, "\nArgument %s does not exist...\n\n", argv[i]);
      exit(0);
    }
  
  for( i = 0; i < argc; ++i)
    fprintf(log, "%s ", argv[i]);
  fprintf(log, "\n");

  fclose(log);
  
  llu *pop = calloc(popsize, sizeof(llu));
  double *lut = calloc(genes+1, sizeof(double));
  fitnesslut(sigma, lut, genes, fitMode, p);

  maxFitness = lut[genes] + 0.95*(lut[0]-lut[genes]);
  
  fprintf(stdout,"maxFitness: %f\n", maxFitness);

  fprintf(fitnesslutfile, "dif\tfitness\n");
  for(i = 0; i < genes+1; ++i)
    {
      fprintf(fitnesslutfile, "%d\t%.20f\n", i, lut[i]);
    }
  fclose(fitnesslutfile);
  
  /* gsl stuff here */
  const gsl_rng_type * T;
  gsl_rng * r;
  /* create a generator chosen by the 
     environment variable GSL_RNG_TYPE */
  gsl_rng_env_setup();
  T = gsl_rng_default;
  r = gsl_rng_alloc (T);
  gsl_rng_set(r, seed);
  
  for(i = 0; i <genes; ++i)
    {
      optimum = optimum | (1 << i);
    }

  int curDif = 0;
  double fitness = 0., curOpt = 0.;

  initializePop(popsize, genes, pop);
  
  int numOfMutations = mutatePop(popsize, genes, pop, mutRate, r);

  int generations = 0;


  /* iterate until a fitness level has been reached */
  while( fitness < maxFitness)
    {
      int b = numberOfBestGenotypes(pop, optimum, popsize, genes, lut, &curOpt, &curDif);
      fprintf(curOptFile, "%d\t%d\t%d\t%d\t%.40f\n", generations, b, numOfMutations, curDif, curOpt);
      fitness = reproduce(popsize, genes, pop, sigma, optimum, r, lut);
      /*fprintf(stderr, "fitness: %f, maxFit: %f\n", fitness, maxFitness);*/
      numOfMutations = mutatePop(popsize, genes, pop, mutRate, r);
      ++generations;
    }

  fclose(curOptFile);

  fprintf(genout, "%d\t%f\t%f\n", generations, mutRate, fitness);
  fprintf(stderr, "%d\n", generations);

  for( i = 0; i <popsize; ++i)
    {
      fprintf(info, "%llu\t%s\n", pop[i], intToString(pop[i], genes));
    }

  fclose(genout);
  fclose(info);
  return 0;
}
