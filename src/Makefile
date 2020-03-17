CC = gcc
MFLAGS = 
CFLAGS = -I$(INC_DIR)
INC_DIR = include

HEADER_FILES = $(wildcard include/*.h)
SOURCE_FILES = $(wildcard *.c)
OBJECT_FILES = $(SOURCE_FILES:.c=.o)

all: main

debug: CFLAGS = -I$(INC_DIR) -g
debug: MFLAGS = -g
debug: main

%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) $(CCFLAGS) -c $<

main: $(OBJECT_FILES)
	$(CC) $(MFLAGS) -o $@ $^ 

run:
	./main

run_debug:
	valgrind --leak-check=full ./main
	
clean:
	rm *.o main
