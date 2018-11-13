#include "mathss.h"

/*convert binary 101010101 representing discrete genes of that step to integer used for comparison*/

float matrix_multiplication(float matrix[max_genes_per_person][max_genes_per_person],int vector[max_genes_per_person],int row){
	int c;
	float result=0;
	float old_result=0;

	/*to vector pernaei swsta*/
	/*if(row==0){
		for (c=0;c<genes_per_person;c++){
			printf("%d",vector[c]);
		}
		printf("\n");
	}
 */
	for (c = 0; c < genes_per_person; c++) {
		result = old_result + matrix[row][c]*vector[c];
		/* printf("%f=%f+%f*%d\n",result,old_result,matrix[row][c],vector[c]); */
		old_result=result;
	}
	return result;
}

int vector_to_decimal(int vector[max_genes_per_person]){
	int i;
	int result=0;

    for (i=0;i<genes_per_person;i++){
        result=result<<1;
        result=result+vector[i];
        /*printf("%d\n",result);*/
    }

	return result;
}

/*create discrete vector with elements based on the sign of the plastic records*/
void make_discrete(person *individual, float temp[max_genes_per_person]){
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
        difference= final_form[i] - optimal[i];
        difference=difference*difference;
        distance+=difference;
    }

    distance=sqrt(distance);

    return distance;
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

    /* Create equal size buckets all in a row, then fire randomly towards
     * the buckets until you land in one of them. All buckets are equally
     * likely. If you land off the end of the line of buckets, try again. */
    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}

unsigned concatenate(unsigned x, unsigned y) {
    unsigned pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;        
}
