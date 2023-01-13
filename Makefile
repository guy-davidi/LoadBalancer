all: ex3_lb
.PHONY : all

CC = gcc
CFLAGS = -g -Wall

ex3_lb: ex3_lb.c socket_helper.c
	$(CC) $(CFLAGS) -o ex3_lb ex3_lb.c socket_helper.c


.PHONY : test
test: 
	./mytest.sh


.PHONY : clean
clean:
	\rm ex3_lb

tidycode:
	clang-format -i *.c *.h