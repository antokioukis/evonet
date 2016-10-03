all:
	gcc -ansi -Wall -pedantic evo_net_list.c -lm -lpthread -lgsl -lgslcblas -g -o evonet
clean:
	> matrix.txt
	> counts.txt
	> fitness.txt
	> discrete.txt
	> robustness.txt
	> R1.txt
	> R2.txt
	> apomonwmenoi.txt
	> countNa.txt
	> robust_percent.txt
	rm evonet
	clear
