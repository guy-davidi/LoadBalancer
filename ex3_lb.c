#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <time.h>


#define UPPER_PORT_BOUND 64000
#define LOWER_PORT_BOUND 1025
#define BUFFER_SIZE 1024
#define BIND_FAIL -1

int randNumberinRange(int lower, int upper) {
  return (rand() % (upper - lower+ 1)) + lower;
}


void writeNumberToFile(char *file_name, int num)
{
  FILE* fp = fopen(file_name, "w+");
  fprintf(fp, "%d", num);
  fclose(fp);
}

int createNewSocket(int *socket_fd) {

  int port_num, bind_status = BIND_FAIL;
  struct sockaddr_in adress_data;
  memset(&adress_data, 0, sizeof(adress_data));
  adress_data.sin_family = AF_INET;  
  adress_data.sin_addr.s_addr = inet_addr("127.0.0.1");  
  

  while(bind_status == BIND_FAIL)
  {
    port_num = randNumberinRange(LOWER_PORT_BOUND, UPPER_PORT_BOUND);
    printf("Generating random number: %d\n", port_num);
    adress_data.sin_port = htons(port_num);    
    bind_status = bind(*socket_fd, (struct sockaddr*)&adress_data, sizeof(adress_data));
  }
  
  return port_num;
}


int main(){
    srand(time(NULL));
    struct timeval timeout;
    timeout.tv_sec = 5; // sec
    timeout.tv_usec = 0; // ms


    int lb_client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int lb_client_port_number = createNewSocket(&lb_client_socket);
    writeNumberToFile("http_port", lb_client_port_number);


    int lb_server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int lb_server_port_number = createNewSocket(&lb_server_socket);
    writeNumberToFile("server_port", lb_server_port_number);
    
    
    listen(lb_client_socket, 20);
    listen(lb_server_socket, 20);




    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);

    struct sockaddr_in server_addr;
    socklen_t server_addr_size = sizeof(server_addr);

    while (true) {
      printf("\n\nWaiting for connection...\n");
      int client_connection = accept(lb_client_socket, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
      int server_connection = accept(lb_server_socket, (struct sockaddr*)&server_addr, &server_addr_size);
      
      // set recv and send timeout
      if( setsockopt (client_connection, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0 ) {
        printf( "setsockopt fail\n" );
      }
      
      if( setsockopt (client_connection, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0 ) {
        printf( "setsockopt fail\n" ) ;
      }
      if( setsockopt (server_connection, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0 ) {
        printf( "setsockopt fail\n" ) ;
      }
      if( setsockopt (server_connection, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0 ) {
        printf( "setsockopt fail\n" ) ;
      }


      // get request from user
      char *buffer = (char*) calloc(BUFFER_SIZE, sizeof(char));
      int buffer_size = BUFFER_SIZE;


      int num_bytes_received;
      int bytes_read = 0;
      
      while (true) {
          num_bytes_received = recv(client_connection, buffer+bytes_read, buffer_size-bytes_read, 0);
          bytes_read += num_bytes_received;

          printf("recieving data\n\n\n\n%s\n\n\n\n...", buffer);
          
          // Check if the buffer needs to be reallocated
          if (bytes_read == buffer_size ) {
            buffer_size *= 2;
            buffer = realloc(buffer, buffer_size);
            
            if(buffer == NULL)
              printf("\nERROR ALLOCATING\n");

            printf("Realloced ! :), new buffer size = %d\n", (int)buffer_size);
          }

          // Check if we've received the "\r\n\r\n" sequence
          // check for the desired string
          char* found = strstr(buffer, "\r\n\r\n");

          if (found != NULL) {
            // desired string found
            break;
          }
        }



      printf("LB received request:\n\n%s\n\n", buffer) ;



      char *returnvalue = (char*) calloc(BUFFER_SIZE, sizeof(char));

      /* SERVER FOWRARD */       
      send(server_connection, buffer, buffer_size, 0) ;

      /*LB GETS A RESPONSE FROM SERVER */
      recv(server_connection, returnvalue, BUFFER_SIZE, 0) ;
      printf("LB got a response: %s\n", returnvalue) ;


      /* SERVER RETURN RESPONSE */  
      send(client_connection, returnvalue, strlen(returnvalue), 0) ;

      /* ^^ SERVER RETURN ^^ */
      free(returnvalue);
      free(buffer);
      close(client_connection) ;

    }    
       
    close(lb_client_socket);
    return 0;
}