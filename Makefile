all:
	gcc -ansi -Wall -pedantic evo_net_list.c -lm -lpthread -lgsl -lgslcblas -g -o evonet
clean:
	rm *.txt
	rm evonet
	clear
