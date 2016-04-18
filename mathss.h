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

/*calculate eucledian distances of 2 vectors*/
float eucledian_distance(int final_form[],int optimal[]){
    float distance=0;
    float difference;
    int i;

    for(i=0;i<10;i++){
        difference=final_form[i]-optimal[i];
        difference=difference*difference;
        distance+=difference;
    }
    distance=sqrt(distance);
    return distance;
}

/* convert integer to binary. Max integer (2^8)-1. Returns pointer to string representing the binary form*/
char *int_to_binary(int n){
    int c, d, count;
    char *pointer;

    count = 0;
    pointer = (char*)malloc(32+1);

    if ( pointer == NULL ){
        printf("No memory left for pointer on making integer_to_binary\n");
        exit(EXIT_FAILURE);
    }
    for ( c = 7 ; c > 0 ; c-- ){
        d = n >> c;
        if ( d & 1 )
          *(pointer+count) = 1 + '0';
       else
          *(pointer+count) = 0 + '0';
       count++;
    }
    *(pointer+count) = '\0';
    return  pointer;
}

/*take the first 4 bits of 8-bit string. Return pointer to that string + null terminated*/
char *break_binary_to_first_part(char *pointer){
    char first_part[5]={0};
    char *ptr_to_first_part;
    strncpy(first_part, pointer,4);
    first_part[4] = '\0';

    ptr_to_first_part = (char *)malloc(sizeof(char));
    if(ptr_to_first_part==NULL){
        printf("No memory left for ptr_to_first_part on break_binary_to_first_part\n");
        exit(EXIT_FAILURE);
    }

    ptr_to_first_part=first_part;

   return ptr_to_first_part;
}

/*take the last 4 bits of 8-bit string. Return pointer to that string + null terminated*/
char *break_binary_to_second_part(char *pointer){
    char second_part[5]={0};
    char *ptr_to_second_part;
    strncpy(second_part, pointer + 4, 7 - 2);
    second_part[4] = '\0';

     ptr_to_second_part = (char *)malloc(sizeof(char));
     if ( ptr_to_second_part == NULL ){
        printf("No memory left for ptr_to_second_part on break_binary_to_second_part\n");
        exit(EXIT_FAILURE);
    }

    ptr_to_second_part=second_part;

   return ptr_to_second_part;
}

/*count how many 1s on first part and on second part and subtract them return the result*/
int create_balance(char *pointer){
    int count_first_part=0;
    int count_second_part=0;
    int i,j,balance;
    char *ptr_first_part;
    char *ptr_second_part;

    ptr_first_part=break_binary_to_first_part(pointer);
    for(i=0; ptr_first_part[i]; i++) {
        if(ptr_first_part[i] != '0') {
            count_first_part ++;
        }
    }

    ptr_second_part=break_binary_to_second_part(pointer);
    for(j=0; ptr_second_part[j]; j++) {
        if(ptr_second_part[j] != '0') {
            count_second_part ++;
        }
    }


    balance=count_first_part-count_second_part;
    return balance;
}

/*concatenate the vector to create 1 binary integer*/
unsigned int concatenate(unsigned x, unsigned y) {
    unsigned pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;
}

