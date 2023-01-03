all: client server
.PHONY : all

server: serversocket.c
	gcc -Wall -Wextra -g serversocket.c -o server


client: clientsocket.c
	gcc -Wall -Wextra -g clientsocket.c -o client


.PHONY : test
test: 
	./mytest.sh

.PHONY : clean
clean:
	\rm server
	\rm client


tidycode:
	clang-format -i *.c *.h
