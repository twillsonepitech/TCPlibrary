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

#define PUT_ERROR_MESSAGE(message)                                          \
    do                                                                      \
    {                                                                       \
        fprintf(stderr, "\033[1;31m/************************************/\033[0m\n\n");         \
        fprintf(stderr, "\033[1;31m\tERROR : \033[0m");                       \
        fprintf(stderr, "\033[1;31m[File : %s]\033[0m", __FILE__);          \
        fprintf(stderr, "\033[1;31m[Line : %d]\033[0m", __LINE__);          \
        fprintf(stderr, "\033[1;31m[Function : %s]\033[0m\n", __func__);    \
        fprintf(stderr, "\033[1;31m\tERROR : \033[0m");                       \
        fprintf(stderr, "\033[1;31m[Message : %s]\033[0m\n\n", message);      \
        fprintf(stderr, "\033[1;31m/************************************/\033[0m\n");         \
    } while (LOOP_ONCE);                                                    \

struct socket_s {
    in_port_t port;
    int32_t fd;
    socklen_t sockaddr_length;
    struct sockaddr_in address;
};

/**
 * @brief Create a socket file descriptor object, manage the data socket
 * and fill the socket controller structure that contains the data socket.
 * 
 * @param port The port listener
 * @param socket_controller The structure controller
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfuly
 */
uint32_t create_socket_file_descriptor(in_port_t port, struct socket_s *socket_controller);

#endif /* !SOCKET_H_ */
