/*create personal r1 using rand%256*/
personal_r1* initialize_r1(){
    int j;
    personal_r1 *ptr_to_personal_r1;
    ptr_to_personal_r1 = (personal_r1 *)malloc(sizeof(personal_r1));

    if(debug_mode) printf("Creting personal R1");

    if ( ptr_to_personal_r1 == NULL ){
        printf("No memory left ptr_to_personal_r1 on initialize R1\n");
        exit(EXIT_FAILURE);
    }

    /*For every gene create a R1 balance and save it*/
    for (j=0;j<genes_per_person;j++){
        ptr_to_personal_r1->personal_gene_r1[j]=int_to_binary(rand()%256);
        ptr_to_personal_r1->balance[j]=1;
        //ptr_to_personal_r1->balance[j]=create_balance(ptr_to_personal_r1->personal_gene_r1[j]);
    }
    return ptr_to_personal_r1;
}

/*create personal r2 using rand%256*/
personal_r2* initialize_r2(){
    int j;
    personal_r2 *ptr_to_personal_r2;
    ptr_to_personal_r2 = (personal_r2 *)malloc(sizeof(personal_r2));

    if(debug_mode) printf("Creting personal R2");

    if ( ptr_to_personal_r2 == NULL ){
        printf("No memory left ptr_to_personal_r2 on initialize R2\n");
        exit(EXIT_FAILURE);
    }

    /*For every gene create a R2 balance and save it*/
    for (j=0;j<genes_per_person;j++){
        ptr_to_personal_r2->personal_gene_r2[j]=int_to_binary(rand()%256);
        ptr_to_personal_r2->balance[j]=2;
        //ptr_to_personal_r2->balance[j]=create_balance(ptr_to_personal_r2->personal_gene_r2[j]);
    }
    return ptr_to_personal_r2;
}

