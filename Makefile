all:
	gcc evo_net_v27.c -lm -o a.out
clean:
	rm *.out
	clear
run:
	./a.out
