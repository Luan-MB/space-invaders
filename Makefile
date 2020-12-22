# GRR20190363 Luan Machado Bernardt

CC = gcc
CFLAGS = -Wall
LDFLAGS = -lncurses

OBJECTS= space_invaders

all: $(OBJECTS) clean

$(OBJECTS): $(OBJECTS).o lib_lista_si.o 
	$(CC) $(CFLAGS) $(OBJECTS).o lib_lista_si.o -o $(OBJECTS) $(LDFLAGS)

$(OBJECTS).o: $(OBJECTS).c lib_lista_si.h  
	$(CC) $(CFLAGS) $(OBJECTS).c -c $(LDFLAGS)

lib_lista_si.o: lib_lista_si.c lib_lista_si.h
	$(CC) $(CFLAGS) lib_lista_si.c -c $(LDFLAGS)

clean:
	-rm -f *.o

purge:
	-rm -f $(OBJECTS)
