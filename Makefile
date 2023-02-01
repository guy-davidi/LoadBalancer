all: lb
.PHONY : all

CC = gcc
CFLAGS = -g -Wall

lb: lb.c socket_helper.c
	$(CC) $(CFLAGS) -o lb lb.c socket_helper.c


.PHONY : test
test: 
	./mytest.sh


.PHONY : clean
clean:
	\rm lb

tidycode:
	clang-format -i *.c *.h

format_test:
