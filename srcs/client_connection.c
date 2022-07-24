/**
 * @file client_connection.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief Allow the client to connect to a data socket
 * 
 * @version 0.1
 * @date 2022-07-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <string.h>
#include "socket.h"

/**
 * @brief Function that allow client to connect on socket controller
 * file descriptor with given address.
 * 
 * @param socket_controller_fd Socket fd opened connection.
 * @param socket_fd Handle return value from `int connect(int __fd, const struct sockaddr *__addr, socklen_t __len)` function.
 * @param address Address that will be set by connect function.
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfully
 */
static uint32_t connect_client_to_socket_fd(int32_t socket_controller_fd, struct sockaddr_in address)
{
    int32_t return_from_connect_function;

    return_from_connect_function = INIT_INT;
    return_from_connect_function = connect(socket_controller_fd, (struct sockaddr *)&address, sizeof(address));
    if (INVALID_SOCKET == return_from_connect_function) {
        PUT_ERROR_MESSAGE(ERROR_FUNCTION("connect()"));
        return FAILURE;
    }
    return SUCCESS;
}

/**
 * @brief Set the valid network address object using
 * `int inet_pton(int __af, const char *__restrict__ __cp, void *__restrict__ __buf)` function.
 * If network ip address is localhost, the function convert it to 127.0.0.1 to allow
 * inet pton function to work.
 * 
 * @param network_address Network ip address that the client will be connected to.
 * @param address Address that will be fill by inet_pton function (sin_addr variable on structure).
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfully
 */
static uint32_t set_valid_network_address(const int8_t *network_address, struct sockaddr_in address)
{
    int32_t return_from_inet_pton_function;

    return_from_inet_pton_function = INIT_INT;
    return_from_inet_pton_function = strcmp((const char *) network_address, "localhost") == 0
                                ? inet_pton(AF_INET, (const char *) "127.0.0.1", &address.sin_addr)
                                : inet_pton(AF_INET, (const char *) network_address, &address.sin_addr);
    for (uint32_t i = 0; i < sizeof(MANAGE_NETWORK_IP) / sizeof(MANAGE_NETWORK_IP[0]); i += 1) {
        if (MANAGE_NETWORK_IP[i].return_from_inet_pton_function == return_from_inet_pton_function) {
            dprintf(MANAGE_NETWORK_IP[i].fd_return_response, "inet_pton: [%s]\n", MANAGE_NETWORK_IP[i].response_from_function);
            return MANAGE_NETWORK_IP[i].return_from_function;
        }
    }
    return SUCCESS;
}

/**
 * @brief Init address client that is connecting.
 * 
 * @param port Port listening.
 * @param address Address of client.
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfully
 */
static uint32_t init_address(in_port_t port, struct sockaddr_in address)
{
    if (NULL == memset(&address, INIT_PTR, sizeof(struct sockaddr_in))) {
        PUT_ERROR_MESSAGE(ERROR_FUNCTION("memset()"));
        return FAILURE;
    }
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    return SUCCESS;
}

/**
 * @brief Function that handle client connection by setting up the Port and Ip address.
 * Then connect the client on the socket file descriptor created and putted in socket controller
 * by filling the socket connection structure.
 * 
 * @param port Port listening.
 * @param network_address Network ip address.
 * @param socket_controller The socket where a new connection is happenning.
 * @param socket_connection Client socket structure.
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfully
 */
uint32_t connect_socket_to_address(in_port_t port, const int8_t *network_address, struct socket_s *socket_controller)
{
    if (FAILURE == init_address(port, socket_controller->address))
        return FAILURE;
    if (FAILURE == set_valid_network_address(network_address, socket_controller->address))
        return FAILURE;
    if (FAILURE == connect_client_to_socket_fd(socket_controller->fd, socket_controller->address))
        return FAILURE;
    return SUCCESS;
}
