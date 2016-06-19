all:
	gcc -ansi -Wall -pedantic evo_net_v38.c -lm -lpthread -lgsl -lgslcblas -o evonet -g
clean:
	rm evonet
	clear
run:
	./evonet
