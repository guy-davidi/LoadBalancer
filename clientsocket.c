#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define buffersize 1024

int main(int argc, char *argv[])
{
    if(argc < 2) {
        printf("Nope.\n");
        exit(0);
    }
    int sock = socket(AF_INET, SOCK_STREAM, 0);
  
    struct sockaddr_in adress_details;
    memset(&adress_details, 0, sizeof(adress_details));  
    
    adress_details.sin_family = AF_INET;  
    adress_details.sin_addr.s_addr = inet_addr("127.0.0.1");  

    adress_details.sin_port = htons(5566); 

    connect(sock, (struct sockaddr*)&adress_details, sizeof(adress_details));
   
    // create message
    char *message = (char*) calloc(strlen(argv[1])+1, sizeof(char)) ;
    strcpy(message, argv[1]) ;
    
    // send message
    send(sock, message, strlen(message)+1, 0) ;

    // get a response
    char *buffer = (char*) calloc(buffersize, sizeof(char)) ;
    read(sock, buffer, buffersize);
    printf("result: %s\n", buffer);

    free(message);
    free(buffer);
    close(sock);
    return 0;
}
