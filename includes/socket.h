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

#define INVALID_SOCKET  -1
#define SOCKET_ERROR    -1
#define INVALID_PORT    "Port is invalid, try a port between 1024 and 65534."
#define ERROR_FUNCTION(function_name) "Error in " #function_name " function."

#define SUCCESS     0
#define FAILURE     1

#define INIT_INT    0
#define INIT_UINT   0
#define INIT_PTR    0

#define LOOP_ONCE   0

#define MIN_PORT    1024
#define MAX_PORT    65534
#define SOCK_PROTOCOL   0

#define NETWORK_IP_SUCCESS  1
#define NETWORK_IP_ERROR    0
#define NETWORK_IP_FAILURE  -1

#define PUT_ERROR_MESSAGE(__msg__)                                          \
    do                                                                      \
    {                                                                       \
        fprintf(stderr, "\033[1;31m/************************************/\033[0m\n\n");         \
        fprintf(stderr, "\033[1;31m\tERROR : \033[0m");                       \
        fprintf(stderr, "\033[1;31m[File : %s]\033[0m", __FILE__);          \
        fprintf(stderr, "\033[1;31m[Line : %d]\033[0m", __LINE__);          \
        fprintf(stderr, "\033[1;31m[Function : %s]\033[0m\n", __func__);    \
        fprintf(stderr, "\033[1;31m\tERROR : \033[0m");                       \
        fprintf(stderr, "\033[1;31m[Message : %s]\033[0m\n\n", __msg__);      \
        fprintf(stderr, "\033[1;31m/************************************/\033[0m\n");         \
    } while (LOOP_ONCE);                                                    \

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

uint32_t create_socket_file_descriptor(in_port_t port, struct socket_s *socket_controller);
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

uint32_t connect_socket_to_address(in_port_t port, const int8_t *network_address, struct socket_s *socket_controller) __nonnull((3));

#endif /* !SOCKET_H_ */
