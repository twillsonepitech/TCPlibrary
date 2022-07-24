/**
 * @file create_socket.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief Unit tests for client connection function.
 * @version 0.1
 * @date 2022-07-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#define _GNU_SOURCE
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <time.h>
#include "socket.h"

#define SUCCESS_PORT    (4242)
#define SUCCESS_IP      ("localhost")
#define FAILURE_IP      ("127.0..0.1")
#define FUNCTION_ERROR_CODE (-1)

Test(client_connection_success, tests_client_connection)
{
    cr_log_info("Starting client_connection tests.\n\n");
    in_port_t port;
    char *ip;
    char *cmd;
    int32_t return_from_function;
    struct socket_s socket_controller;

    port = SUCCESS_PORT;
    ip = SUCCESS_IP;
    cr_log_info("Client connection ip: %s, port: %d.\n", ip, port);
    if (FUNCTION_ERROR_CODE == asprintf(&cmd, "nc -lv %s %d&", ip, port)) {
        cr_log_error("Error when calling asprintf function");
    }
    if (FUNCTION_ERROR_CODE == system(cmd)) {
        cr_log_error("Error when calling system function");
    }
    return_from_function = INIT_INT;
    return_from_function = create_socket_file_descriptor(port, &socket_controller);
    if (FAILURE == return_from_function) {
        cr_log_error("Error when creating socket file descriptor");
    }
    cr_log_info("Socket fd : %d\n", socket_controller.fd);
    cr_log_warn("Waiting before connect...\n");
    sleep(2);
    return_from_function = INIT_INT;
    return_from_function = connect_socket_to_address(port, (const int8_t *) ip, &socket_controller);
    if (FAILURE == return_from_function) {
        cr_log_error("Error when connect socket to address");
    }
    return_from_function = INIT_INT;
    return_from_function = close(socket_controller.fd);
    if (INVALID_SOCKET == return_from_function) {
        cr_log_error("Error when closing the data socket fd");
    }
    cr_assert(SUCCESS == return_from_function);
}

Test(client_connection_failure, tests_client_connection)
{
    in_port_t port;
    char *ip;
    char *cmd;
    int32_t return_from_function;
    struct socket_s socket_controller;

    port = SUCCESS_PORT;
    ip = FAILURE_IP;
    cr_log_info("Client connection ip: %s, port: %d.\n", ip, port);
    if (FUNCTION_ERROR_CODE == asprintf(&cmd, "nc -lv %s %d&", ip, port)) {
        cr_log_error("Error when calling asprintf function");
    }
    if (FUNCTION_ERROR_CODE == system(cmd)) {
        cr_log_error("Error when calling system function");
    }
    return_from_function = INIT_INT;
    return_from_function = create_socket_file_descriptor(port, &socket_controller);
    if (FAILURE == return_from_function) {
        cr_log_error("Error when creating socket file descriptor");
    }
    cr_log_info("Socket fd : %d\n", socket_controller.fd);
    cr_log_warn("Waiting before connect...\n");
    sleep(2);
    return_from_function = INIT_INT;
    return_from_function = connect_socket_to_address(port, (const int8_t *) ip, &socket_controller);
    cr_assert(FAILURE == return_from_function);
    return_from_function = INIT_INT;
    return_from_function = close(socket_controller.fd);
    if (INVALID_SOCKET == return_from_function) {
        cr_log_error("Error when closing the data socket fd");
    }
    cr_assert(SUCCESS == return_from_function);
}