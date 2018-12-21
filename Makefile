SOURCES =  evo_net_list.c creators.c events.c extract.c generation_fit.c generation_no_fit.c mathss.c maturity.c robustness.c  
OBJECTS = $(SOURCES:%.c=%.o)
TARGET = evonet



all: $(TARGET)

%.o: %.c
	gcc -Wall -pg -O3 -pedantic -fopenmp -g $< -c -o $@

$(TARGET): $(OBJECTS)
	gcc $(OBJECTS) -o $@ -lm -lgsl -lgslcblas -g -lpthread -fopenmp

clean:
	clear
	rm  $(TARGET)
	rm  $(OBJECTS)
