#include "structs.h"

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
    for ( c = 7 ; c >= 0 ; c-- ){
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
    char first_part[5];
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
    char second_part[5];
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

/*create personal r1 using rand%256*/
personal_r1* initialize_r1(){
    int j;
    personal_r1 *ptr_to_personal_r1;
    ptr_to_personal_r1 = (personal_r1 *)malloc(sizeof(personal_r1));
    if ( ptr_to_personal_r1 == NULL ){
        printf("No memory left ptr_to_personal_r1 on initialize R1\n");
        exit(EXIT_FAILURE);
    }

    /*For every gene create a R1 balance and save it*/
    for (j=0;j<genes_per_person;j++){
        ptr_to_personal_r1->personal_gene_r1[j]=int_to_binary(rand()%256);
        ptr_to_personal_r1->balance[j]=create_balance(ptr_to_personal_r1->personal_gene_r1[j]);
    }
    return ptr_to_personal_r1;
}

/*create personal r2 using rand%256*/
personal_r2* initialize_r2(){
    int j;
    personal_r2 *ptr_to_personal_r2;
    ptr_to_personal_r2 = (personal_r2 *)malloc(sizeof(personal_r2));
    if ( ptr_to_personal_r2 == NULL ){
        printf("No memory left ptr_to_personal_r2 on initialize R2\n");
        exit(EXIT_FAILURE);
    }

    /*For every gene create a R2 balance and save it*/
    for (j=0;j<genes_per_person;j++){
        ptr_to_personal_r2->personal_gene_r2[j]=int_to_binary(rand()%256);
        ptr_to_personal_r2->balance[j]=create_balance(ptr_to_personal_r2->personal_gene_r2[j]);
    }
    return ptr_to_personal_r2;
}
