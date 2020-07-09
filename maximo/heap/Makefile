CFLAGS = -Wall -ansi -g -pedantic -Wno-unused-result
O = heap.o util.o certificados.o main.o menu.o time.o pq.o

heap: $(O)
	gcc $(CFLAGS) $(O) -o heap 

%.o: %.c %.h debug.h
	gcc $(CFLAGS) -c $<

clean:
	rm *.o heap
