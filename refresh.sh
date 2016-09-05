make clean
make all

./evonet -selection 0 -s2 1  -N 1000 -ploidy 2 -swapping 1 -freq 1 -min_R1R2 23 -max_R1R2 110 -min_count 3 -max_count 152 -generations 51 -n 10

#prwtos N generation num s2 1 fitness file matrix file r1r2 file
Rscript ptixiaki.R fitnoselect.png r1r2noselect.png 1000 51 1 fitness.txt matrix.txt R1R2.txt