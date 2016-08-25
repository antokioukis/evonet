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
void make_discrete(person *individual, float temp[max_genes_per_person]){
    int i;

    for (i=0;i<max_genes_per_person;i++){
        if(temp[i]>0){
            individual->vector_of_signs[i]=1;
        }
        else{
            individual->vector_of_signs[i]=0;
        }
    }

/*
    printf("Apotelesma discretion");
    for(i=0;i<max_genes_per_person;i++){
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

int decimal_to_binary(int n) {
    int remainder; 
    int binary = 0, i = 1;
     
    while(n != 0) {
        remainder = n%2;
        n = n/2;
        binary= binary + (remainder*i);
        i = i*10;
    }
    return binary;
}


int NumberOfSetBits(int i){
    i = i - ((i >> 1) & 0x55555555);
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

unsigned int rand_interval(unsigned int min, unsigned int max){
    int r;
    const unsigned int range = 1 + max - min;
    const unsigned int buckets = RAND_MAX / range;
    const unsigned int limit = buckets * range;
    assert(min <= max);
    
    /* Create equal size buckets all in a row, then fire randomly towards
     * the buckets until you land in one of them. All buckets are equally
     * likely. If you land off the end of the line of buckets, try again. */
    do
      {
        r = rand();
      } while (r >= limit);
    
    return min + (r / buckets);
}
