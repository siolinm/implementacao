CFLAGS = -Wall -ansi -g -pedantic -Wno-unused-result
O = splay.o menu.o util.o heapsort.o main.o

par: $(O)
	gcc $(CFLAGS) $(O) -o par -lm

%.o: %.c %.h debug.h
	gcc $(CFLAGS) -c $<

clean:
	rm *.o par points brute *~

brute: brute.c
	gcc -o brute brute.c -lm

points: generate.c
	gcc -o points generate.c
