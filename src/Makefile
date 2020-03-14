all:
	gcc -c mem.c
	gcc -c linked_list.c	
	gcc -c user_utility.c
	gcc -c dir_utility.c
	gcc main.c -o main mem.o linked_list.o user_utility.o dir_utility.o

run:
	./main

clean:
	rm *.o main
