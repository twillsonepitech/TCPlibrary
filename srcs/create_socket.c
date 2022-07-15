#include <stdint.h>
#include <string.h>
#include "socket.h"

#define SOCK_PROTOCOL   0

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
 * @brief Set the flags for socket fd object,
 * to make the port and the address reusable.
 * 
 * @param socket_fd The socket fd created by socket function
 * @param port The port listener
 * @param address The address of the data socket connexion
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfuly
 */
static uint32_t set_flags_for_socket_fd(int32_t socket_fd, in_port_t port, struct sockaddr_in *address)
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

/**
 * @brief Checking if the port is valid.
 * A valid port is a port that is between 1024 and 65534.
 * Below 1024 : Those ports are already used for other stuff.
 * Above 65534 : A random port is normaly set, but we will return a FAILURE case for this one.
 * 
 * @param port The port listener
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfuly
 */
static uint32_t check_for_valid_port(in_port_t port)
{
    if (port < MIN_PORT) {
        PUT_ERROR_MESSAGE(INVALID_PORT);
        return FAILURE;
    }
    if (port > MAX_PORT) {
        PUT_ERROR_MESSAGE(INVALID_PORT);
        return FAILURE;
    }
    return SUCCESS;
}

/**
 * @brief Create a socket file descriptor object, manage the data socket
 * and fill the socket controller structure that contains the data socket.
 * 
 * @param port The port listener
 * @param socket_controller The structure controller
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfuly
 */
uint32_t create_socket_file_descriptor(in_port_t port, struct socket_s *socket_controller)
{
    int32_t socket_fd;
    struct sockaddr_in address;

    if (FAILURE == check_for_valid_port(port))
        return FAILURE;
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
