all:
	gcc -ansi -pedantic -Wall evo_net_v32.c -lm -lpthread -o evonet -g
clean:
	rm evonet
	clear
run:
	./evonet
