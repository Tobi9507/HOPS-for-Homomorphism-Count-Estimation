CC = g++
CFLAGS =
LDFLAGS = -lgmpxx -lgmp
OBJECTS = adjlist.o homhops.o demo.o
HEADERS = graph.h

%.o:%.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

demo:$(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)