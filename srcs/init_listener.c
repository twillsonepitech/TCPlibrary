/**
 * @file init_listener.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief Function that will bind the data socket and make it
 * listening by clients.
 * @version 0.1
 * @date 2022-07-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <string.h>
#include "socket.h"
#define LISTEN_BACKLOG  50

uint32_t bind_data_socket(const struct socket_s *socket_controller)
{
    if (SOCKET_ERROR == bind(socket_controller->fd, (struct sockaddr *)&socket_controller->address, sizeof(socket_controller->address))) {
        PUT_ERROR_MESSAGE(ERROR_FUNCTION("bind()"));
        return FAILURE;
    }
    return SUCCESS;
}

uint32_t listen_data_socket(const struct socket_s *socket_controller)
{
    if (SOCKET_ERROR == listen(socket_controller->fd, LISTEN_BACKLOG)) {
        PUT_ERROR_MESSAGE(ERROR_FUNCTION("listen()"));
        return FAILURE;
    }
    return SUCCESS;
}

uint32_t initialize_listener(const struct socket_s *socket_controller)
{
    if (FAILURE == bind_data_socket(socket_controller))
        return FAILURE;
    if (FAILURE == listen_data_socket(socket_controller))
        return FAILURE;
    return SUCCESS;
}
