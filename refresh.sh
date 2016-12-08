make clean
make all

#n fores pou 8a tre3ei
#r generations_Wanted
#N pli8ismos
n=1
r=1001
N=1000
#curDir=`pwd`
#for i in `seq 1 $n`;do
#    mkdir run$i
#    cd run$i
#    $curDir/evonet -selection 1 -s2 5 -N $N -eN 50 100 -ploidy 1 -swapping 0 -freq 10 -min_R1R2 32766 -max_R1R2 32767 -min_count 10 -max_count 10 -generations $r -n 10 -rob 0 -num_of_rob_mutation 10 -rob_last 0 -mutrate 0.1
#    cd $curDir
#done 2>out.txt

./evonet -selection 1 -s2 1 -N $N -ploidy 1 -swapping 0 -freq 100 -min_R1R2 32766 -max_R1R2 32767 -min_count 10 -max_count 10 -generations $r -n 10 -rob 0 -num_of_rob_mutation 10 -rob_last 0 -mutrate 0.1
Rscript countMut.R

#./evonet -selection 1 -s2 5  -N 1000 -ploidy 1 -swapping 1 -freq 100 -min_R1R2 10 -max_R1R2 11 -min_count 3 -max_count 152 -generations 1001 -n 10 -rob 1 -num_of_rob_mutation 50
#prwtos N |generation num |freq 10 |n 10 |fitness file |matrix file |discrete file |robustness file |
#Rscript mine.R fitness.png 100 11 10 10 fitness.txt discrete.txt robustness.txt matrix.txt robust_percent.txt

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

#valgrind --leak-check=full --show-leak-kinds=all --show-reachable=no ./evonet -selection 1 -s2 5 -eN 40 500 -eN 50 100 -N 100 -ploidy 1 -swapping 1 -freq 10 -min_R1R2 10 -max_R1R2 11 -min_count 3 -max_count 152 -generations 61 -n 10
