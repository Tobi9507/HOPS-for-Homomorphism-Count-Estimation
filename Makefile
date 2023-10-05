CC = g++
CFLAGS =
LDFLAGS = -lgmpxx -lgmp
OBJECTS = homhops.o homhopsplus.o hops.o sghd.o adjlist.o demo.o
HEADERS = graph.h

%.o:%.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

demo:$(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)