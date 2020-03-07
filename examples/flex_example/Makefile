all:
	bison -d bison.y
	flex flex.l
	gcc *.c -lfl -o b

run:
	./b

clean:
	rm b lex.yy.c bison.tab*

