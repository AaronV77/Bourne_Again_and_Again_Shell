all:
	gcc -c td_array.c
	gcc -c linked_list.c	
	gcc -c user_utility.c
	gcc -c dir_utility.c
	gcc -c builtin_commands.c
	gcc -c exec_utility.c
	gcc main.c -o main td_array.o linked_list.o user_utility.o dir_utility.o builtin_commands.o exec_utility.o

run:
	./main

clean:
	rm *.o main
