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
#include <stdint.h>
#include <string.h>
#include "socket.h"
#define LISTEN_BACKLOG  50

/**
 * @brief Function that initialise the socket_controller and fill it
 * with the datas that he needs.
 * 
 * @param socket_fd The socket fd created by socket function
 * @param port The port listener
 * @param address The address of the data socket connexion
 * @param socket_controller The structure controller
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfuly
 */
static uint32_t manage_socket_controller_structure(int32_t socket_fd, in_port_t port, struct sockaddr_in *address, struct socket_s *socket_controller)
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

/**
 * @brief Bind socket controller file descriptor
 * specified by socket controller address.
 * 
 * @param socket_controller The structure controller
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfuly
 */
static uint32_t bind_data_socket(const struct socket_s *socket_controller)
{
    if (SOCKET_ERROR == bind(socket_controller->fd, (struct sockaddr *)&socket_controller->address, sizeof(socket_controller->address))) {
        PUT_ERROR_MESSAGE(ERROR_FUNCTION("bind()"));
        return FAILURE;
    }
    return SUCCESS;
}

/**
 * @brief Listen socket that will be used to accept incoming
 * connection, LISTEN_BACKLOG is the maximum length to which the queue
 * of pending connections for the socket controller file descriptor may grow.
 * 
 * @param socket_controller The structure controller
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfuly
 */
static uint32_t listen_data_socket(const struct socket_s *socket_controller)
{
    if (SOCKET_ERROR == listen(socket_controller->fd, LISTEN_BACKLOG)) {
        PUT_ERROR_MESSAGE(ERROR_FUNCTION("listen()"));
        return FAILURE;
    }
    return SUCCESS;
}

/**
 * @brief Initialize listener structure by fill the structure,
 * binding the file descriptor and listening it to manage incoming connexion.
 * 
 * @param socket_fd The socket fd created by socket function
 * @param port The port listener
 * @param address The address of the data socket connexion
 * @param socket_controller The structure controller
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfuly
 */
uint32_t initialize_socket_controller(int32_t socket_fd, in_port_t port, struct sockaddr_in *address, struct socket_s *socket_controller)
{
    if (FAILURE == manage_socket_controller_structure(socket_fd, port, address, socket_controller))
        return FAILURE;
    if (FAILURE == bind_data_socket(socket_controller))
        return FAILURE;
    if (FAILURE == listen_data_socket(socket_controller))
        return FAILURE;
    return SUCCESS;
}
