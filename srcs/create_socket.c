/**
 * @file create_socket.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief File that contain function to create a data socket,
 * fill address and struct socket_s, and make address and port reusable.
 * @version 0.1
 * @date 2022-07-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <string.h>
#include "socket.h"

uint32_t manage_socket_controller_structure(int32_t socket_fd, in_port_t port, struct sockaddr_in *address, struct socket_s *socket_controller)
{
    if (NULL == memset(socket_controller, INIT_PTR, sizeof(struct socket_s))) {
        PUT_ERROR_MESSAGE(ERROR_FUNCTION("memset()"));
        return FAILURE;
    }
    socket_controller->port = port;
    socket_controller->fd = socket_fd;
    socket_controller->sockaddr_length = sizeof(address);
    if (NULL == memcpy(&socket_controller->address, address, sizeof(struct sockaddr_in))) {
        PUT_ERROR_MESSAGE(ERROR_FUNCTION("memcpy()"));
        return FAILURE;
    }
    return SUCCESS;
}

uint32_t set_flags_for_socket_fd(int32_t socket_fd, in_port_t port, struct sockaddr_in *address)
{
    if (SOCKET_ERROR == setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &(int){1}, sizeof(int))) {
        PUT_ERROR_MESSAGE(ERROR_FUNCTION("setsockopt()"));
        return FAILURE;
    }
    if (NULL == memset(address, INIT_PTR, sizeof(struct sockaddr_in))) {
        PUT_ERROR_MESSAGE(ERROR_FUNCTION("memset()"));
        return FAILURE;
    }
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(port);
    return SUCCESS;
}

uint32_t create_socket_file_descriptor(in_port_t port, struct socket_s *socket_controller)
{
    int32_t socket_fd;
    struct sockaddr_in address;

    socket_fd = INIT_INT;
    socket_fd = socket(AF_INET, SOCK_STREAM, SOCK_PROTOCOL);
    if (SOCKET_ERROR == socket_fd) {
        PUT_ERROR_MESSAGE(ERROR_FUNCTION("socket()"));
        return FAILURE;
    }
    if (FAILURE == set_flags_for_socket_fd(socket_fd, port, &address))
        return FAILURE;
    if (FAILURE == manage_socket_controller_structure(socket_fd, port, &address, socket_controller))
        return FAILURE;
    return SUCCESS;
}
