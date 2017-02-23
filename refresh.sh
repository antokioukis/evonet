make clean
make all

#n fores pou 8a tre3ei
#r generations_Wanted
#N pli8ismos
#n=1
r=1
N=1000
#curDir=`pwd`
#for i in `seq 1 $n`;do
#    mkdir run$i
#    cd run$i
#   $curDir/evonet -selection 0 -s2 5 -N $N -ploidy 2 -swapping 0 -freq 1 -min_R1R2 11 -max_R1R2 11 -min_count 10 -max_count 10 -generations $r -n 10 -mutrate 0.1
#    cd $curDir
#done 2>out.txt


#./evonet -selection 0 -s2 5 -N $N -ploidy 1 -swapping 1 -freq 1 -min_R1R2 10 -max_R1R2 11 -min_count 3 -max_count 152 -generations $r -n 10
#./evonet -selection 0 -s2 5 -N $N -ploidy 2 -swapping 0 -freq 1 -min_R1R2 10 -max_R1R2 11 -min_count 3 -max_count 152 -generations $r -n 10
#./evonet -selection 0 -s2 5 -N $N -ploidy 2 -swapping 1 -freq 1 -min_R1R2 10 -max_R1R2 11 -min_count 3 -max_count 152 -generations $r -n 10

#./evonet -selection 1 -s2 5 -N $N -ploidy 1 -swapping 1 -freq 1 -min_R1R2 10 -max_R1R2 11 -min_count 3 -max_count 152 -generations $r -n 10 -tarfit 0.40 -optimal 10101

#./evonet -selection 1 -s2 5 -N $N -ploidy 1 -swapping 1 -freq 1 -min_R1R2 10 -max_R1R2 11 -min_count 3 -max_count 152 -generations $r -n 10 -tarfit 0.80
Rscript write_file.R
#./evonet -selection 1 -s2 5 -N $N -ploidy 1 -swapping 0 -freq 1 -min_R1R2 10 -max_R1R2 11 -min_count 10 -max_count 11 -mutrate 0.1 -generations $r -n 10 -optimal 1101100011
./evonet -selection 1  -s2 2 -N 1000 -ploidy 1  -swapping 0 -freq 10 -min_R1R2 10 -max_R1R2 11 -min_count 10 -max_count 11 -generations 1001 -n 10 -recomb_rate 0.005 -mutrate 0.005 -seed 5079724 -optimal 1101010101
#Rscript mutation_cat.R
#gcc fitnessSimple.c -lm -lgsl -lgslcblas -o fitnessSimple
#./fitnessSimple -mu 0.1 -l 10 -popsize 1000 -fm 1 -s 5 -p 2

#./evonet -selection 1 -s2 5 -N $N -ploidy 2 -swapping 1 -freq 1 -min_R1R2 10 -max_R1R2 11 -min_count 3 -max_count 152 -generations $r -n 10 -tarfit 0.99

#mv diff_geno.png diff_geno_neut.png

#./evonet -selection 1 -s2 5  -N $N -ploidy 2 -swapping 1 -freq 50 -min_R1R2 10 -max_R1R2 11 -min_count 3 -max_count 152 -generations $r -n 10 -recomb_rate 0.05
#Rscript variance.R
#mv diff_geno.png diff_geno_fit.png

#prwtos N |generation num |freq 10 |n 10 |fitness file |matrix file |discrete file |robustness file |
#Rscript mine.R fitness.png $N 11 10 10 fitness.txt discrete.txt robustness.txt matrix.txt robust_percent.txt

#optimal 1111111111 done
#./evonet -selection 1 -s2 5  -N 1000 -ploidy 1 -swapping 1 -freq 10 -min_R1R2 10 -max_R1R2 11 -min_count 3 -max_count 152 -generations 101 -n 10 -rob 1 -num_of_rob_mutation 50
#Rscript mine.R fitness.png 1000 11 10 10 fitness.txt discrete.txt robustness.txt matrix.txt robust_percent.txt
#mv apomonwmenoi.txt apomonwmenoi1.txt

#optimal 0000000000

#optimal 1010101010

#optimal 1111100000 done


#echo Assoi sto period.txt:
#grep -o "1" period.txt | wc -l

#echo Ana Generation posoi xreiazontai 3 bimata -exoun mideniko vector-
#sed '1,1!d' steps.txt | grep -o "3" | wc -l
#sed '2,2!d' steps.txt | grep -o "3" | wc -l
#sed '3,3!d' steps.txt | grep -o "3" | wc -l
#sed '4,4!d' steps.txt | grep -o "3" | wc -l
#sed '5,5!d' steps.txt | grep -o "3" | wc -l
#sed '6,6!d' steps.txt | grep -o "3" | wc -l
#sed '7,7!d' steps.txt | grep -o "3" | wc -l
#sed '8,8!d' steps.txt | grep -o "3" | wc -l
#sed '9,9!d' steps.txt | grep -o "3" | wc -l
#sed '10,10!d' steps.txt | grep -o "3" | wc -l
#sed '11,11!d' steps.txt | grep -o "3" | wc -l

#valgrind --leak-check=full --show-leak-kinds=all --show-reachable=no ./evonet -selection 1 -s2 5 -N 100 -ploidy 2 -swapping 1 -freq 1 -min_R1R2 10 -max_R1R2 11 -min_count 3 -max_count 152 -generations 1 -n 10
#valgrind --leak-check=full --show-reachable=no -v ./evonet -selection 1 -s2 5 -N 100 -ploidy 2 -swapping 1 -freq 1 -min_R1R2 10 -max_R1R2 11 -min_count 3 -max_count 152 -generations 1 -n 10
