#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("Nope.\n");
    exit(0);
  }
  char buffesr[15] = {0};
  int sock = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in adress_details;
  memset(&adress_details, 0, sizeof(adress_details));

  adress_details.sin_family = AF_INET;
  adress_details.sin_addr.s_addr = inet_addr("127.0.0.1");

  int port_number_to_connect;

  FILE *port_file = fopen("http_port", "r");
  port_number_to_connect = atoi(fgets(buffesr, 10, port_file));
  printf("Connecting to %d\n", port_number_to_connect);
  fclose(port_file);

  adress_details.sin_port = htons(port_number_to_connect);

  connect(sock, (struct sockaddr *)&adress_details, sizeof(adress_details));

  // create message
  char *message = (char *)calloc(strlen(argv[1]) + 1, sizeof(char));
  strcpy(message, argv[1]);

  // send message
  send(sock, message, strlen(message) + 1, 0);

  // get a response
  char *buffer = (char *)calloc(BUFFER_SIZE, sizeof(char));
  read(sock, buffer, BUFFER_SIZE);
  printf("result: %s\n", buffer);

  free(message);
  free(buffer);
  close(sock);
  return 0;
}
