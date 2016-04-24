all:
	gcc -pedantic -ansi -Wall evo_net_v31.c -lm -lpthread -o evonet -g
clean:
	rm evonet
	clear
run:
	./evonet
