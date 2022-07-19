/**
 * @file tests_accept_clients.c
 * @author Emeric Caramanna (emeric.caramanna@epitech.eu)
 * @brief Unit tests for the accept clients function.
 * @version 0.1
 * @date 2022-07-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include "accept_clients.h"

#define INVALID_FD          -2
#define SUCCESS_PORT        4242
#define NO_NEW_CLIENT_SIZE  0
#define NEW_CLIENT_SIZE     1
#define BACKLOG             128
#define LOCAL_HOST_IP       "127.0.0.1"

Test(accept_new_clients_no_new_client, tests_select_accept1)
{
    in_port_t port;
    int32_t return_from_function;
    struct socket_s socket_controller;
    struct accepted_clients clients;

    port = SUCCESS_PORT;
    return_from_function = INIT_INT;
    return_from_function = create_socket_file_descriptor(port, &socket_controller);
    if (FAILURE == return_from_function) {
        cr_assert_fail("Error to create socket file descriptor");
    }
    if (FAILURE == bind(socket_controller.fd, (struct sockaddr *)&socket_controller.address, socket_controller.sockaddr_length))
        cr_assert_fail("Error with bind");
    if (FAILURE == listen(socket_controller.fd, 128))
        cr_assert_fail("Error with listen");

    return_from_function = INIT_INT;
    return_from_function = accept_new_clients(&socket_controller, &clients);
    cr_assert(SUCCESS == return_from_function);
    cr_assert(NO_NEW_CLIENT_SIZE == clients.size);
    return_from_function = INIT_INT;
    return_from_function = close(socket_controller.fd);
    if (SOCKET_ERROR == return_from_function) {
        cr_assert_fail("Error when closing the data socket fd");
    }
    cr_assert(SUCCESS == return_from_function);
}

Test(accept_new_clients_invalid_fd, tests_select)
{
    int32_t return_from_function;
    struct socket_s socket_controller;
    struct accepted_clients clients;

    socket_controller.fd = INVALID_FD;
    return_from_function = INIT_INT;
    return_from_function = accept_new_clients(&socket_controller, &clients);
    cr_assert(FAILURE == return_from_function);
}
