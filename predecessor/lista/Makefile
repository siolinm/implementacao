CFLAGS = -Wall -ansi -g -pedantic -Wno-unused-result
O = heap.o util.o certificados.o main.o menu.o time.o heapsort.o

predecessor: $(O)
	gcc $(CFLAGS) $(O) -o predecessor 

%.o: %.c %.h debug.h
	gcc $(CFLAGS) -c $<

# main.o: main.c menu.o certificados.o heap.o util.o debug.h time.o lista.o
# 	gcc $(CFLAGS) -c main.c

# menu.o: menu.c menu.h heap.o time.o certificados.o debug.h
# 	gcc $(CFLAGS) -c menu.c

# certificados.o: certificados.c certificados.h heap.c heap.h util.c util.h debug.h time.c time.h
# 	gcc $(CFLAGS) -c certificados.c

# heapsort.o: heap.c heap.h util.c util.h debug.h
# 	gcc $(CFLAGS) -c heap.c

# util.o: util.c util.h debug.h
# 	gcc $(CFLAGS) -c util.c

# time.o: time.c time.h
# 	gcc $(CFLAGS) -c time.c

# lista.o: lista.c lista.h util.o certificados.o time.o
# 	gcc $(CFLAGS) -c lista.c

clean:
	rm *.o predecessor