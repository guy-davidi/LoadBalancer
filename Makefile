all: client server
.PHONY : all

server: ex3_lb.c
	gcc -Wall -Wextra -g ex3_lb.c -o ex3_lb


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