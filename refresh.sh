make clean
make all

./evonet -selection 1 -s2 5  -N 100 -ploidy 2 -swapping 1 -freq 1 -min_R1R2 1 -max_R1R2 11 -min_count 3 -max_count 152 -generations 1 -n 10 -rob 1 -num_of_rob_mutation 15

#prwtos N |generation num |freq 10 |n 10 |fitness file |matrix file |discrete file |robustness file |
Rscript mine.R fitness.png 100 1 10 10 fitness.txt discrete.txt robustness.txt matrix.txt robust_percent.txt
