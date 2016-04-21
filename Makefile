all:
	gcc -Wall evo_net_v31.c -lm -o evonet -g
clean:
	rm evonet
	clear
run:
	./evonet
