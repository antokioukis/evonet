/*returns a random number from a normal_distribution based on the mu and the sigma*/
double random_normal_distrubution (double mu, double sigma){
  double U1, U2, W, mult;
  static double X1, X2;
  static int call = 0;
 /*got no clue how it does what it does but it works perfectly and that is good enough for me*/
    if(call == 1){
      call = !call;
      return (mu + sigma * (double) X2);
    }

    do{
      U1 = -1 + ((double) rand () / RAND_MAX) * 2;
      U2 = -1 + ((double) rand () / RAND_MAX) * 2;
      W = pow (U1, 2) + pow (U2, 2);
    }while (W >= 1 || W == 0);

    mult = sqrt ((-2 * log (W)) / W);
    X1 = U1 * mult;
    X2 = U2 * mult;

    call = !call;

    return (mu + sigma * (double) X1);
}

/*concatenate the vector to create 1 binary integer*/
unsigned int concatenate(unsigned x, unsigned y) {

  /* mporeis na baleis pow = 2? */

    unsigned pow = 10;

    /* check if this line is needed */
    while(y >= pow)
        pow *= 10;
    return x * pow + y;
}

float *matrix_multiplication(float first[genes_per_person][genes_per_person],int second[genes_per_person],float multiply[genes_per_person]){

  /*  int m, n, p, q */
    int c, d, k;
    float sum = 0;

    for (c = 0; c < genes_per_person; c++) {
        for (d = 0; d < genes_per_person; d++) {
            for (k = 0; k < genes_per_person; k++) {
                sum = sum + first[c][k]*second[k];
            }

            multiply[c] = sum;
            sum = 0;
        }
    }

  /*  printf("Product of entered matrices:-\n");

    for (c = 0; c < genes_per_person; c++) {
        printf(" %f ", multiply[c]);
    }printf("\n");*/
    return multiply;
}

/*convert binary 101010101 representing discrete genes of that step to integer used for comparison*/
long int binary_to_decimal(long int num){
    long int rem,sum=0,power=0;

    while(num>0){
        rem = num%10;
        num = num/10;
        sum = sum + rem * pow(2,power);
        power++;
    }
    return sum;
}

/*create discrete vector with elements based on the sign of the plastic records*/
void make_discrete(person *individual, float temp[genes_per_person]){
    int i;

    for (i=0;i<genes_per_person;i++){
        if(temp[i]>0){
            individual->vector_of_signs[i]=1;
        }
        else{
            individual->vector_of_signs[i]=0;
        }
    }

/*
    printf("Apotelesma discretion");
    for(i=0;i<genes_per_person;i++){
        printf(" %d ",individual->vector_of_signs[i]);
    }
    printf("\n");
*/
}

/*calculate eucledian distances of 2 vectors*/
float eucledian_distance(int final_form[],int optimal[]){
    float distance=0;
    float difference;
    int i;

    for(i=0;i<genes_per_person;i++){
        difference=final_form[i]-optimal[i];
        difference=difference*difference;
        distance+=difference;
        difference=0;
    }
    distance=sqrt(distance);
    return distance;
}
