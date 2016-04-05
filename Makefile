all:
	gcc -Wall -ansi -pedantic evo_net_v23.c -lm -o a.out
clean:
	rm *.out
	clear
run:
	./a.out
