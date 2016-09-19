make clean
make all

./evonet -selection 1 -s2 5  -N 10 -ploidy 2 -swapping 1 -freq 10 -min_R1R2 1 -max_R1R2 11 -min_count 3 -max_count 152 -generations 101 -n 10 -rob 1 -num_of_rob_mutation 5

#prwtos N generation num freq 1 fitness file matrix file r1r2 file