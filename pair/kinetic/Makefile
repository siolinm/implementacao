CFLAGS = -Wall -ansi -g -pedantic -Wno-unused-result
OBJS   = cands.o cert.o hits.o menu.o orderedlist.o pq.o tourn.o util.o maxima.o heapsort.o kds.o
LIBS   = -lm

kineticpair: $(OBJS)
	gcc $(CFLAGS) $(OBJS) -o kineticpair $(LIBS)

%.o: %.c %.h debug.h
	gcc $(CFLAGS) -c $<

clean:
	rm *.o kineticpair *~