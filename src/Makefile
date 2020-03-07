all:
	gcc -c mem.c
	gcc -c linked_list.c	
	gcc -c utility.c
	gcc main.c -o main mem.o linked_list.o utility.o

run:
	./main

clean:
	rm *.o main
