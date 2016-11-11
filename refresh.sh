make clean
make all

#./evonet -selection 1 -s2 5  -N 1000 -ploidy 1 -swapping 1 -freq 100 -min_R1R2 10 -max_R1R2 11 -min_count 3 -max_count 152 -generations 1001 -n 10 -rob 1 -num_of_rob_mutation 50
#prwtos N |generation num |freq 10 |n 10 |fitness file |matrix file |discrete file |robustness file |
#Rscript mine.R fitness.png 100 11 10 10 fitness.txt discrete.txt robustness.txt matrix.txt robust_percent.txt

#./evonet -selection 1 -s2 5  -N 1000 -ploidy 1 -swapping 1 -freq 10 -min_R1R2 10 -max_R1R2 11 -min_count 3 -max_count 152 -generations 101 -n 10 -rob 1 -num_of_rob_mutation 10 -rob_last 0
#Rscript mine.R fitness.png 1000 11 10 10 fitness.txt discrete.txt robustness.txt matrix.txt robust_percent.txt
#mv apomonwmenoi.txt apomonwmenoi1.txt

#./evonet -selection 1 -s2 5  -N 1000 -ploidy 1 -swapping 1 -freq 100 -min_R1R2 10 -max_R1R2 11 -min_count 3 -max_count 152 -generations 101 -n 10 -rob 1 -num_of_rob_mutation 10
#Rscript mine.R fitness.png 100 11 10 10 fitness.txt discrete.txt robustness.txt matrix.txt robust_percent10.txt
#mv apomonwmenoi.txt apomonwmenoi10.txt

#./evonet -selection 1 -s2 5  -N 1000 -ploidy 1 -swapping 1 -freq 100 -min_R1R2 10 -max_R1R2 11 -min_count 3 -max_count 152 -generations 101 -n 10 -rob 1 -num_of_rob_mutation 25
#Rscript mine.R fitness.png 100 11 10 10 fitness.txt discrete.txt robustness.txt matrix.txt robust_percent25.txt
#mv apomonwmenoi.txt apomonwmenoi25.txt

#./evonet -selection 1 -s2 5  -N 1000 -ploidy 1 -swapping 1 -freq 100 -min_R1R2 10 -max_R1R2 11 -min_count 3 -max_count 152 -generations 101 -n 10 -rob 1 -num_of_rob_mutation 50
#Rscript mine.R fitness.png 100 11 10 10 fitness.txt discrete.txt robustness.txt matrix.txt robust_percent50.txt
#mv apomonwmenoi.txt apomonwmenoi50.txt

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

valgrind --leak-check=yes --track-origins=yes ./evonet -selection 1 -s2 5  -N 1000 -ploidy 1 -swapping 1 -freq 10 -min_R1R2 10 -max_R1R2 11 -min_count 3 -max_count 152 -generations 51 -n 10 -rob 1 -num_of_rob_mutation 10 -rob_last 0
#valgrind --leak-check=full --show-leak-kinds=all ./evonet -selection 1 -s2 5  -N 1000 -ploidy 1 -swapping 1 -freq 10 -min_R1R2 10 -max_R1R2 11 -min_count 3 -max_count 152 -generations 101 -n 10 -rob 1 -num_of_rob_mutation 10 -rob_last 0
