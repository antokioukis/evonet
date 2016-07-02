make clean
make all

./evonet -help
./evonet -selection 1 -s2 0.5 -N 10 -ploidy 2 -swapping 1 -freq 10 -min_R1R2 23 -max_R1R2 52 -min_count 52 -max_count 89 -generations 100 -n 10

## TODO: export gene counts meta apo maturity
