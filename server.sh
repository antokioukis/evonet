# selection, s2 1, 1000 atoma , genies 5000

./evonet -selection 1 -s2 1 -N 1000 -ploidy 2 -swapping 1 -freq 1 -min_R1R2 23 -max_R1R2 110 -min_count 3 -max_count 152 -generations 1001 -n 10 -rob 1 -num_of_rob_mutation 15 -r1out r1s21N1000G5000fp2.txt -r2out r2s21N1000G5000fp2.txt -matout mats21N1000G5000fp2.txt -gencout counts21N1000G5000fp2.txt -fitout fits21N1000G5000fp2.txt -disout diss21N1000G5000fp2.txt -robout robs21N1000G5000fp2.txt
#prwtos N |generation num |freq 1 |fitness file |matrix file |r1r2 file |discrete file |robustness file | robustness_results file
Rscript ptixiaki.R fitness.png r1r2.png 1000 26 1 fitness.txt matrix.txt diss21N1000G5000fp2.txt robs21N1000G5000fp2.txt robper_s21N1000G5000fp2.txt

# selection, s2 5, 1000 atoma , genies 5000

./evonet -selection 1 -s2 5 -N 1000 -ploidy 2 -swapping 1 -freq 1 -min_R1R2 23 -max_R1R2 110 -min_count 3 -max_count 152 -generations 1001 -n 10 -rob 1 -num_of_rob_mutation 15 -r1out r1s25N1000G5000fp2.txt -r2out r2s25N1000G5000fp2.txt -matout mats25N1000G5000fp2.txt -gencout counts25N1000G5000fp2.txt -fitout fits25N1000G5000fp2.txt -disout diss25N1000G5000fp2.txt -robout robs25N1000G5000fp2.txt
Rscript ptixiaki.R fitness.png r1r2.png 1000 26 1 fitness.txt matrix.txt diss25N1000G5000fp2.txt robs25N1000G5000fp2.txt robper_s25N1000G5000fp2.txt

# selection, s2 10, 1000 atoma , genies 5000

./evonet -selection 1 -s2 10 -N 1000 -ploidy 2 -swapping 1 -freq 1 -min_R1R2 23 -max_R1R2 110 -min_count 3 -max_count 152 -generations 1001 -n 10 -rob 1 -num_of_rob_mutation 15 -r1out r1s210N1000G5000fp2.txt -r2out r2s210N1000G5000fp2.txt -matout mats210N1000G5000fp2.txt -gencout counts210N1000G5000fp2.txt -fitout fits210N1000G5000fp2.txt -disout diss210N1000G5000fp2.txt -robout robs210N1000G5000fp2.txt
Rscript ptixiaki.R fitness.png r1r2.png 1000 26 1 fitness.txt matrix.txt diss210N1000G5000fp2.txt robs210N1000G5000fp2.txt robper_s210N1000G5000fp2.txt
#####################################################################################################################################################################################################################################################################################################################

# neutral, s2 1, 1000 atoma , genies 5000

./evonet -selection 0 -s2 1 -N 1000 -ploidy 2 -swapping 1 -freq 1 -min_R1R2 23 -max_R1R2 110 -min_count 3 -max_count 152 -generations 1001 -n 10 -rob 1 -num_of_rob_mutation 15 -r1out r1s21N1000G5000p2.txt  -r2out r2s21N1000G5000p2.txt -matout mats21N1000G5000p2.txt -gencout counts21N1000G5000p2.txt -fitout fits21N1000G5000p2.txt -disout diss21N1000G5000p2.txt -robout robs21N1000G5000p2.txt
Rscript ptixiaki.R fitness.png r1r2.png 1000 26 1 fitness.txt matrix.txt diss21N1000G5000p2.txt robs21N1000G5000p2.txt robper_s21N1000G5000p2.txt
# neutral, s2 5, 1000 atoma , genies 5000

./evonet -selection 0 -s2 5 -N 1000 -ploidy 2 -swapping 1 -freq 1 -min_R1R2 23 -max_R1R2 110 -min_count 3 -max_count 152 -generations 1001 -n 10 -rob 1 -num_of_rob_mutation 15 -r1out r1s25N1000G5000p2.txt -r2out r2s25N1000G5000p2.txt -matout mats25N1000G5000p2.txt -gencout counts25N1000G5000p2.txt -fitout fits25N1000G5000p2.txt -disout diss25N1000G5000p2.txt -robout robs25N1000G5000p2.txt
Rscript ptixiaki.R fitness.png r1r2.png 1000 26 1 fitness.txt matrix.txt diss25N1000G5000p2.txt robs25N1000G5000p2.txt robper_s25N1000G5000p2.txt
# neutral, s2 10, 1000 atoma , genies 5000

./evonet -selection 0 -s2 10 -N 1000 -ploidy 2 -swapping 1 -freq 1 -min_R1R2 23 -max_R1R2 110 -min_count 3 -max_count 152 -generations 1001 -n 10 -rob 1 -num_of_rob_mutation 15 -r1out r1s210N1000G5000p2.txt -r2out r2s210N1000G5000p2.txt -matout mats210N1000G5000p2.txt -gencout counts210N1000G5000p2.txt -fitout fits210N1000G5000p2.txt -disout diss210N1000G5000p2.txt -robout robs210N1000G5000p2.txt
Rscript ptixiaki.R fitness.png r1r2.png 1000 26 1 fitness.txt matrix.txt diss210N1000G5000p2.txt robs210N1000G5000p2.txt robper_s210N1000G5000p2.txt
#####################################################################################################################################################################################################################################################################################################################

# selection, s2 1, 1000 atoma , genies 5000

./evonet -selection 1 -s2 1 -N 1000 -ploidy 1 -swapping 1 -freq 1 -min_R1R2 23 -max_R1R2 110 -min_count 3 -max_count 152 -generations 1001 -n 10 -rob 1 -num_of_rob_mutation 15 -r1out r1s21N1000G5000fp1.txt -r2out r2s21N1000G5000fp1.txt -matout mats21N1000G5000fp1.txt -gencout counts21N1000G5000fp1.txt -fitout fits21N1000G5000fp1.txt -disout diss21N1000G5000fp1.txt -robout robs21N1000G5000fp1.txt
Rscript ptixiaki.R fitness.png r1r2.png 1000 26 1 fitness.txt matrix.txt diss21N1000G5000fp1.txt robs21N1000G5000fp1.txt robper_s21N1000G5000fp1.txt

# selection, s2 5, 1000 atoma , genies 5000

./evonet -selection 1 -s2 5 -N 1000 -ploidy 1 -swapping 1 -freq 1 -min_R1R2 23 -max_R1R2 110 -min_count 3 -max_count 152 -generations 1001 -n 10 -rob 1 -num_of_rob_mutation 15 -r1out r1s25N1000G5000fp1.txt -r2out r2s25N1000G5000fp1.txt -matout mats25N1000G5000fp1.txt -gencout counts25N1000G5000fp1.txt -fitout fits25N1000G5000fp1.txt -disout diss25N1000G5000fp1.txt -robout robs25N1000G5000fv.txt
Rscript ptixiaki.R fitness.png r1r2.png 1000 26 1 fitness.txt matrix.txt diss25N1000G5000fp1.txt robs25N1000G5000fp1.txt robper_s25N1000G5000fp1.txt

# selection, s2 10, 1000 atoma , genies 5000

./evonet -selection 1 -s2 10 -N 1000 -ploidy 1 -swapping 1 -freq 1 -min_R1R2 23 -max_R1R2 110 -min_count 3 -max_count 152 -generations 1001 -n 10 -rob 1 -num_of_rob_mutation 15 -r1out r1s210N1000G5000fp1.txt -r2out r2s210N1000G5000fp1.txt -matout mats210N1000G5000fp1.txt -gencout counts210N1000G5000fp1.txt -fitout fits210N1000G5000fp1.txt -disout diss210N1000G5000fp1.txt -robout robs210N1000G5000fp1.txt
Rscript ptixiaki.R fitness.png r1r2.png 1000 26 1 fitness.txt matrix.txt diss210N1000G5000fp1.txt robs210N1000G5000fp1.txt robper_s210N1000G5000fp1.txt

#####################################################################################################################################################################################################################################################################################################################

# neutral, s2 1, 1000 atoma , genies 5000

./evonet -selection 0 -s2 1 -N 1000 -ploidy 1 -swapping 1 -freq 1 -min_R1R2 23 -max_R1R2 110 -min_count 3 -max_count 152 -generations 1001 -n 10 -rob 1 -num_of_rob_mutation 15 -r1out r1s21N1000G5000p1.txt -r2out r2s21N1000G5000p1.txt -matout mats21N1000G5000p1.txt -gencout counts21N1000G5000p1.txt -fitout fits21N1000G5000p1.txt -disout diss21N1000G5000p1.txt -robout robs21N1000G5000p1.txt
Rscript ptixiaki.R fitness.png r1r2.png 1000 26 1 fitness.txt matrix.txt diss21N1000G5000p1.txt robs21N1000G5000p1.txt robper_s21N1000G5000p1.txt

# neutral, s2 5, 1000 atoma , genies 5000

./evonet -selection 0 -s2 5 -N 1000 -ploidy 1 -swapping 1 -freq 1 -min_R1R2 23 -max_R1R2 110 -min_count 3 -max_count 152 -generations 1001 -n 10 -rob 1 -num_of_rob_mutation 15 -r1out r1s25N1000G5000p1.txt -r2out r2s25N1000G5000p1.txt -matout mats25N1000G5000p1.txt -gencout counts25N1000G5000p1.txt -fitout fits25N1000G5000p1.txt -disout diss25N1000G5000p1.txt -robout robs25N1000G5000p1.txt
Rscript ptixiaki.R fitness.png r1r2.png 1000 26 1 fitness.txt matrix.txt diss25N1000G5000p1.txt robs25N1000G5000p1.txt robper_s25N1000G5000p1.txt

# neutral, s2 10, 1000 atoma , genies 5000

./evonet -selection 0 -s2 10 -N 1000 -ploidy 1 -swapping 1 -freq 1 -min_R1R2 23 -max_R1R2 110 -min_count 3 -max_count 152 -generations 1001 -n 10 -rob 1 -num_of_rob_mutation 15 -r1out r1s210N1000G5000p1.txt -r2out r2s210N1000G5000p1.txt -matout mats210N1000G5000p1.txt -gencout counts210N1000G5000p1.txt -fitout fits210N1000G5000.txt -disout diss210N1000G5000p1.txt -robout robs210N1000G5000p1.txt
Rscript ptixiaki.R fitness.png r1r2.png 1000 26 1 fitness.txt matrix.txt diss210N1000G5000p1.txt robs210N1000G5000p1.txt robper_s210N1000G5000p1.txt

#####################################################################################################################################################################################################################################################################################################################
