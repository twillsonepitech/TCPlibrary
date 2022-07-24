/**
 * @file create_socket.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief Unit tests for init listener function.
 * @version 0.1
 * @date 2022-07-15
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
#define FAILURE_PORT_1  (1023)
#define FAILURE_PORT_2  (65539)
#define SOCKET_FD       (3)
#define IS_FD_TYPE      (1)

Test(init_listener_success, tests_init_listener)
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
    return_from_function = INIT_INT;
    return_from_function = initialize_listener(&socket_controller);
    if (FAILURE == return_from_function) {
        cr_assert_fail("Error to initialize listener");
    }
    return_from_function = INIT_INT;
    return_from_function = close(socket_controller.fd);
    if (SOCKET_ERROR == return_from_function) {
        cr_assert_fail("Error when closing the data socket fd");
    }
    cr_assert(SUCCESS == return_from_function);
}

Test(init_listener_failure_port_1, tests_init_listener)
{
    in_port_t port;
    int32_t return_from_function;
    struct socket_s socket_controller;

    port = FAILURE_PORT_1;
    return_from_function = INIT_INT;
    return_from_function = create_socket_file_descriptor(port, &socket_controller);
    if (FAILURE == return_from_function) {
        cr_assert_fail("Error to create socket file descriptor");
    }
    cr_assert(SUCCESS == return_from_function);
    return_from_function = INIT_INT;
    return_from_function = initialize_listener(&socket_controller);
    if (FAILURE == return_from_function) {
        return_from_function = INIT_INT;
        return_from_function = close(socket_controller.fd);
        if (SOCKET_ERROR == return_from_function) {
            cr_assert_fail("Error when closing the data socket fd");
        }
    }
}

Test(init_listener_failure_port_2, tests_init_listener)
{
    uint32_t port;
    int32_t return_from_function;
    struct socket_s socket_controller;

    port = FAILURE_PORT_2;
    return_from_function = INIT_INT;
    return_from_function = create_socket_file_descriptor(port, &socket_controller);
    if (FAILURE == return_from_function) {
        cr_assert_fail("Error to create socket file descriptor");
    }
    cr_assert(SUCCESS == return_from_function);
    return_from_function = INIT_INT;
    return_from_function = initialize_listener(&socket_controller);
    if (FAILURE == return_from_function) {
        return_from_function = INIT_INT;
        return_from_function = close(socket_controller.fd);
        if (SOCKET_ERROR == return_from_function) {
            cr_assert_fail("Error when closing the data socket fd");
        }
    }
}
