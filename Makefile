all:
	gcc -ansi -Wall -pedantic evo_net_v38.c -lm -lpthread -lgsl -lgslcblas -o evonet -g
clean:
	> R1R2.txt
	> matrix.txt
	> counts.txt
	rm evonet
	clear
run:
	./evonet
