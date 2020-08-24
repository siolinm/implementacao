CFLAGS = -Wall -ansi -g -pedantic -Wno-unused-result
O = splay.o menu.o util.o heapsort.o main.o

par: $(O)
	gcc $(CFLAGS) $(O) -o par -lm

%.o: %.c %.h debug.h
	gcc $(CFLAGS) -c $<
