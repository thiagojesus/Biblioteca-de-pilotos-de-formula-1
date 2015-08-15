CC = gcc
CFLAGS = -g -Wall

# Coloque a implementaÃ§Ã£o de vetor aqui...
ED = 379948_380385_ED2_T02

ALL = main

all: $(ALL)

$(ED).o: $(ED).h $(ED).c

main: $(ED).o main.c

clean:
	rm -f *.o *~ $(ALL)
	rm automobilismo.dat
uninstall:
	rm -f *.o *~ $(ALL)