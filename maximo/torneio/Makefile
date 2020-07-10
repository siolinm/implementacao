CFLAGS = -Wall -ansi -g -pedantic -Wno-unused-result
O = torneio.o util.o certificados.o main.o menu.o time.o pq.o

torneio: $(O)
	gcc $(CFLAGS) $(O) -o torneio 

%.o: %.c %.h debug.h
	gcc $(CFLAGS) -c $<

clean:
	rm *.o torneio
