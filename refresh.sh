make clean
make all
time ./evonet -selection 1 -lamda 0.5 -N 1000 -ploidy 2 -swapping 1 -freq 100 -min_R1R2 23 -max_R1R2 52 -min_count 52 -max_count 89 -generations 501 -n 5
