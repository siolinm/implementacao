CFLAGS = -Wall -ansi -g -pedantic -Wno-unused-result
O = heap.o util.o certificados.o main.o menu.o time.o

heap: $(O)
	gcc $(CFLAGS) $(O) -o heap 
	
main.o: main.c menu.c menu.h certificados.c certificados.h heap.c heap.h util.c util.h debug.h time.c time.h
	gcc $(CFLAGS) -c main.c

menu.o: menu.c menu.h heap.c heap.h time.c time.h certificados.c certificados.h debug.h
	gcc $(CFLAGS) -c menu.c

certificados.o: certificados.c certificados.h heap.c heap.h util.c util.h debug.h time.c time.h
	gcc $(CFLAGS) -c certificados.c

heap.o: heap.c heap.h util.c util.h debug.h
	gcc $(CFLAGS) -c heap.c

util.o: util.c util.h debug.h
	gcc $(CFLAGS) -c util.c

time.o: time.c time.h
	gcc $(CFLAGS) -c time.c
