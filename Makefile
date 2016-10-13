
SOURCES =  evo_net_list.c creators.c events.c extract.c generation_fit.c generation_no_fit.c mathss.c maturity.c robustness.c  
OBJECTS = $(SOURCES:%.c=%.o)
TARGET = evonet



all: $(TARGET)

%.o: %.c
	gcc -ansi -Wall -pedantic $< -c -o $@

$(TARGET): $(OBJECTS)
	gcc -lm -lpthread -lgsl -lgslcblas $(OBJECTS) -o $@

clean:
	rm -f $(TARGET)
	rm -f $(OBJECTS)
	rm -f *.txt
