all:
	gcc -ansi -Wall -pedantic evo_net_v40.c -lm -lpthread -lgsl -lgslcblas -g -o evonet
clean:
	> R1R2.txt
	> matrix.txt
	> counts.txt
	> fitness.txt
	> discrete.txt
	rm evonet
	clear