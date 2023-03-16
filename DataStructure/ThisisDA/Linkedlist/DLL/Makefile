.SUFFIXES : .c .o
CC = gcc
CFLAGS = -g -Wall -ansi -std=c99
 all: test

OBJS = DLL.o main.o
SRCS = $(OBJS:.o=.c) #메크로 치환 $(매크로 이름:이전 내용=새로운 내용)


test: $(OBJS)
	$(CC) -o DoublyLinkedList $(OBJS) 
# OBJS에 포함되는 파일들을 링킹해서 DoublyLinkedList라는 파일로 출력(-o의 output)

clean: 
	rm -rf $(OBJS)
distclean: 
	rm -rf $(OBJS) DoublyLinkedList test
