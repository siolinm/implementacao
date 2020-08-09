CFLAGS = -Wall -ansi -g -pedantic -Wno-unused-result
O = heap.o util.o certificates.o main.o menu.o tempo.o heapsort.o

predecessor: $(O)
	gcc $(CFLAGS) $(O) -o predecessor 

%.o: %.c %.h debug.h
	gcc $(CFLAGS) -c $<

# main.o: main.c menu.o certificates.o heap.o util.o debug.h time.o lista.o
# 	gcc $(CFLAGS) -c main.c

# menu.o: menu.c menu.h heap.o time.o certificates.o debug.h
# 	gcc $(CFLAGS) -c menu.c

# certificates.o: certificates.c certificates.h heap.c heap.h util.c util.h debug.h time.c tempo.h
# 	gcc $(CFLAGS) -c certificates.c

# heapsort.o: heap.c heap.h util.c util.h debug.h
# 	gcc $(CFLAGS) -c heap.c

# util.o: util.c util.h debug.h
# 	gcc $(CFLAGS) -c util.c

# time.o: time.c tempo.h
# 	gcc $(CFLAGS) -c time.c

# lista.o: lista.c lista.h util.o certificates.o time.o
# 	gcc $(CFLAGS) -c lista.c

clean:
	rm *.o predecessor