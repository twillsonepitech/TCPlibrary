/**
 * @file create_socket.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief Unit tests for create socket function.
 * @version 0.1
 * @date 2022-07-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include <sys/stat.h>
#include "socket.h"

#define SUCCESS_PORT    (4242)
#define SOCKET_FD       (3)
#define IS_FD_TYPE      (1)

/**
 *  To execute tests, try `make tests_run 2> logs.out > logs.out ; cat logs.out`
 *  It will first of print messages in error output first in the logs.out file
 *  and then print the rest of messages in the file.
 *  Then, with `cat` command, you will see all logs.out made by `make tests_run`.
 */

Test(create_socket_file_descriptor_success, tests_create_data_socket)
{
    in_port_t port;
    int32_t return_from_function;
    struct socket_s socket_controller;

    port = SUCCESS_PORT;
    return_from_function = INIT_INT;
    return_from_function = create_socket_file_descriptor(port, &socket_controller);
    if (FAILURE == return_from_function) {
        cr_assert_fail("Error to create socket file descriptor");
    }
    cr_assert(SUCCESS == return_from_function);
    fprintf(stdout, "Socket fd : %d\n", socket_controller.fd);
    return_from_function = INIT_INT;
    return_from_function = isfdtype(socket_controller.fd, S_IFSOCK);
    if (INVALID_SOCKET == return_from_function) {
        cr_assert_fail("Error when looking for if fd is socket");
        return_from_function = INIT_INT;
        return_from_function = close(socket_controller.fd);
        if (SOCKET_ERROR == return_from_function) {
            cr_assert_fail("Error when closing the data socket fd");
        }
    }
    cr_assert(IS_FD_TYPE == return_from_function);
    return_from_function = INIT_INT;
    return_from_function = close(socket_controller.fd);
    if (SOCKET_ERROR == return_from_function) {
        cr_assert_fail("Error when closing the data socket fd");
    }
    cr_assert(SUCCESS == return_from_function);
}
