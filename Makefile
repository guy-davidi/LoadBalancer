all: lb
.PHONY : all

CC = gcc
CFLAGS = -g -Wall

lb: lb.c socket_helper.c
	$(CC) $(CFLAGS) -o lb lb.c socket_helper.c


.PHONY : clean
clean:
	\rm lb || true
	\rm http_port || true
	\rm server_port || true

tidycode:
	clang-format -i *.c *.h
