all:
	gcc -ansi -pedantic -Wall evo_net_v35.c -lm -lpthread -lgsl -lgslcblas -o evonet -g
clean:
	rm evonet
	clear
run:
	./evonet
