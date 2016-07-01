make clean
make all

valgrind --track-origins=yes --leak-check=full ./evonet -selection 1 -s2 0.5 -N 100 -ploidy 2 -swapping 1 -freq 10 -min_R1R2 23 -max_R1R2 52 -min_count 52 -max_count 89 -generations 50 -n 5

## TODO: export gene counts meta apo maturity