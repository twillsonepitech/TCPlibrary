/**
 * @file socket.h
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief File that regroup
 *          - Libraries
 *          - Functions
 *          - Structures
 *        to create data socket and stuffs.
 * @version 0.1
 * @date 2022-07-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef SOCKET_H_
#define SOCKET_H_

#ifdef WIN32    /*  on Windows  */
#include <winsock2.h>
#else           /*  on Linux or MacOS   */
/**
 *  Create data socket libraries
 */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif /* !INCLUDES for platform */

/**
 *  Basic libraries
 */
#include <unistd.h>
#include <stdio.h>
#include "usage.h"

#define SOCKET_ERROR    (-1)
#define INVALID_SOCKET  (-1)
#define INVALID_PORT    ("Port is invalid, try a port between 1024 and 65534.")

#define MIN_PORT        (1024)
#define MAX_PORT        (65534)
#define SOCK_PROTOCOL   (0)

#define NETWORK_IP_SUCCESS  (1)
#define NETWORK_IP_ERROR    (0)
#define NETWORK_IP_FAILURE  (-1)

/**
 * @brief Socket structure that get port listening, server fd
 * server address and server address length.
 * 
 * @param socket_fd The socket fd created by socket function
 * @param port The port listener
 * @param address The address of the data socket connexion
 * @param socket_controller The structure controller
 */
struct socket_s {
    in_port_t port;
    int32_t fd;
    socklen_t sockaddr_length;
    struct sockaddr_in address;
};

/**
 * @brief Function that initialise the socket_controller and fill it
 * with the datas that he needs.
 * 
 * @param socket_fd The socket fd created by socket function
 * @param port The port listener
 * @param address The address of the data socket connexion
 * @param socket_controller The structure controller
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfully
 */
uint32_t manage_socket_controller_structure(int32_t socket_fd, in_port_t port, struct sockaddr_in *address, struct socket_s *socket_controller) __nonnull((3));

/**
 * @brief Set the flags for socket fd object,
 * to make the port and the address reusable.
 * 
 * @param socket_fd The socket fd created by socket function
 * @param port The port listener
 * @param address The address of the data socket connexion
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfully
 */
uint32_t set_flags_for_socket_fd(int32_t socket_fd, in_port_t port, struct sockaddr_in *address);

/**
 * @brief Create a socket file descriptor object, manage the data socket
 * and fill the socket controller structure that contains the data socket.
 * 
 * @param port The port listener
 * @param socket_controller The structure controller
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfully
 */
uint32_t create_socket_file_descriptor(in_port_t port, struct socket_s *socket_controller);


/**
 * @brief Bind socket controller file descriptor
 * specified by socket controller address.
 * 
 * @param socket_controller The structure controller
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfully
 */
uint32_t bind_data_socket(const struct socket_s *socket_controller) __nonnull((1));

/**
 * @brief Listen socket that will be used to accept incoming
 * connection, LISTEN_BACKLOG is the maximum length to which the queue
 * of pending connections for the socket controller file descriptor may grow.
 * 
 * @param socket_controller The structure controller
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfully
 */
uint32_t listen_data_socket(const struct socket_s *socket_controller) __nonnull((1));

/**
 * @brief Binding the file descriptor and listening it to manage incoming connexion.
 * 
 * @param socket_controller The structure controller
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfully
 */
uint32_t initialize_listener(const struct socket_s *socket_controller) __nonnull((1));

/**
 * @brief Structure to manage network ip address.
 * 
 * @param return_from_inet_pton_function Return value from the function `int inet_pton(int af, const char *src, void *dst);`
 * @param response_from_function Message to print in case of success / failure from the return inet pton function
 * @param fd_return_response Fd to check if the message response go in the standard output or error output
 * @param return_from_function Return value from the function `uint32_t handle_client_connection(const char *network_ip, const struct socket_s *socket_controller);`
 */
struct network_address {
    const int32_t return_from_inet_pton_function;
    const char *response_from_function;
    const int32_t fd_return_response;
    const uint32_t return_from_function;
};

/**
 * @brief Array that handle the structure to manage network ip address
 * and print messages in case of good ip or bad one.
 * 
 */
static const struct network_address MANAGE_NETWORK_IP[] = {
    {NETWORK_IP_SUCCESS, "Network address was successfully converted.", STDOUT_FILENO, SUCCESS},
    {NETWORK_IP_ERROR,   "Network address is not valid.",               STDERR_FILENO, FAILURE},
    {NETWORK_IP_FAILURE, "AF does not contain a valid address family.", STDERR_FILENO, FAILURE},
};

/**
 * @brief Function that allow client to connect on socket controller
 * file descriptor with given address.
 * 
 * @param socket_controller_fd Socket fd opened connection.
 * @param socket_fd Handle return value from `int connect(int __fd, const struct sockaddr *__addr, socklen_t __len)` function.
 * @param address Address that will be set by connect function.
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfully
 */
uint32_t connect_client_to_socket_fd(int32_t socket_controller_fd, struct sockaddr_in address);

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
uint32_t set_valid_network_address(const int8_t *network_address, struct sockaddr_in address) __nonnull((1));

/**
 * @brief Init address client that is connecting.
 * 
 * @param port Port listening.
 * @param address Address of client.
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfully
 */
uint32_t init_address(in_port_t port, struct sockaddr_in address);

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
uint32_t connect_socket_to_address(in_port_t port, const int8_t *network_address, struct socket_s *socket_controller) __nonnull((3));

#endif /* !SOCKET_H_ */
