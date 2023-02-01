
#include "socket_helper.h"
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#define BIND_FAIL -1
#define UPPER_PORT_BOUND 64000
#define LOWER_PORT_BOUND 1024
#define TIMEOUT_SEC 5
#define TIMEOUT_MICRO_SEC 0
#define LOOPBACK_IP_ADDRESS "127.0.0.1"
int randNumberinRange(int lower, int upper) { return (rand() % (upper - lower + 1)) + lower; }

int BindSocketRandomPort(int socket_fd)
{

    int port_num, bind_status = BIND_FAIL;
    struct sockaddr_in adress_data;
    memset(&adress_data, 0, sizeof(adress_data));

    adress_data.sin_family = AF_INET;
    adress_data.sin_addr.s_addr = inet_addr(LOOPBACK_IP_ADDRESS);

    while (bind_status == BIND_FAIL) {
        port_num = randNumberinRange(LOWER_PORT_BOUND, UPPER_PORT_BOUND);
        adress_data.sin_port = htons(port_num);
        bind_status = bind(socket_fd, (struct sockaddr *)&adress_data, sizeof(adress_data));
    }

    return port_num;
}

bool SetTimeOutValues(int socket_fd)
{
    struct timeval timeout;
    timeout.tv_sec = TIMEOUT_SEC;
    timeout.tv_usec = TIMEOUT_MICRO_SEC;

    if (setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0) {
        return false;
    }

    if (setsockopt(socket_fd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0) {
        return false;
    }
    return true;
}
