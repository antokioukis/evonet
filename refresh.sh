make clean
make all

./evonet -selection 1 -s2 0.01 -N 1000 -ploidy 2 -swapping 1 -freq 100 -min_R1R2 23 -max_R1R2 110 -min_count 3 -max_count 152 -generations 301 -n 10
## TODO: export gene counts meta apo maturity
