.SUFFIXES : .c .o
CC = gcc
CFLAGS = -g -Wall -ansi -std=c99
 all: test

OBJS = PriorityQueue.o Test_PriorityQueue.o
SRCS = $(OBJS:.o=.c)

test: $(OBJS)
	$(CC) -o PriorityQueue $(OBJS) 

clean: 
	rm -rf $(OBJS)
distclean: 
	rm -rf $(OBJS) PriorityQueue test
