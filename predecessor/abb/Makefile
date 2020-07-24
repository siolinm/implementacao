CFLAGS = -Wall -ansi -g -pedantic -Wno-unused-result
O = util.o certificados.o main.o menu.o tempo.o heapsort.o

predecessor: $(O)
	gcc $(CFLAGS) $(O) -o predecessor 

%.o: %.c %.h debug.h
	gcc $(CFLAGS) -c $<

clean:
	rm *.o predecessor