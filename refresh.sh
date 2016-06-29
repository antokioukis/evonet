
make clean
make all
./evonet -selection 1 -lamda 0.5 -N 1000 -ploidy 2 -swapping 1 -freq 1 -min_R1R2 23 -max_R1R2 52 -min_count 52 -max_count 89 -generations 2001 -n 5
## ftiaxe to swap, monogoneiko
## lambda -> s2

## outputs: r1, r2, gene counts, interaction matrix, fitness 
## TODO: export gene counts meta apo maturity
## TODO: mutation rate sto command line
## TODO: initialize variables
## TODO: o xristis na dinei to onoma tou arxeiou
## TODO: trexe valgrind (--track-origins, --leak-check=full)
