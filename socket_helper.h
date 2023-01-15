#ifndef SOCKET_HELPER_H
#define SOCKET_HELPER_H

#include <stdbool.h>

int BindSocketRandomPort(int socket_fd);

bool SetTimeOutValues(int socket_fd);

#endif