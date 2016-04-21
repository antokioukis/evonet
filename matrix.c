int *matrix_multiplication(float first[genes_per_person][genes_per_person],int second[genes_per_person]){

  int m, n, p, q, c, d, k, sum = 0;
  int multiply[genes_per_person][genes_per_person];

    for (c = 0; c < genes_per_person; c++) {
      for (d = 0; d < genes_per_person; d++) {
        for (k = 0; k < genes_per_person; k++) {
          sum = sum + first[c][k]*second[k];
        }

        multiply[c][d] = sum;
        sum = 0;
      }
    }

    printf("Product of entered matrices:-\n");

    for (c = 0; c < genes_per_person; c++) {
      for (d = 0; d < genes_per_person; d++)
        printf("%d\t", multiply[c][d]);

      printf("\n");
    }
  }

  return multiply;
}
