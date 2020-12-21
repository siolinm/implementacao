CFLAGS = -Wall -ansi -g3 -pedantic -Wno-unused-result # g3 remove qualquer otimização, remover essa flag depois
OBJS   = event.o menu.o orderedlist.o pq.o tourn.o util.o maxima.o heapsort.o kds.o splay_tree.o
LIBS   = -lm

kineticpair: $(OBJS)
	gcc $(CFLAGS) $(OBJS) -o kineticpair $(LIBS)

%.o: %.c %.h debug.h util.h
	gcc $(CFLAGS) -c $<

clean:
	rm *.o kineticpair *~