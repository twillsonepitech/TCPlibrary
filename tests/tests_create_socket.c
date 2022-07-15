#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include "socket.h"

#define SUCCESS_PORT    4242
#define FAILURE_PORT_1  1023
#define FAILURE_PORT_2  65539

#ifdef WIN32
    #define FD_USED_BY_CRITERION    7
#else
    #define FD_USED_BY_CRITERION    6
#endif

#define SOCKET_FD   (3 + FD_USED_BY_CRITERION)

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
    /**
     * !IMPORTANT! : Emeric si tu vois ce message, lorsque je crée un fd dans le main
     * le fd == 3, mais dans un test avec criterion, le fd == 9.
     * (Regarde le fprintf en-dessous avec make tests_run).
     */
    fprintf(stdout, "Socket fd : %d\n", socket_controller.fd);
    cr_assert(SOCKET_FD == socket_controller.fd);
    return_from_function = INIT_INT;
    return_from_function = close(socket_controller.fd);
    if (SOCKET_ERROR == return_from_function) {
        cr_assert_fail("Error when closing the data socket fd");
    }
    cr_assert(SUCCESS == return_from_function);
}

Test(create_socket_file_descriptor_failure, tests_port_1)
{
    in_port_t port;
    int32_t return_from_function;
    struct socket_s socket_controller;

    port = FAILURE_PORT_1;
    return_from_function = INIT_INT;
    return_from_function = create_socket_file_descriptor(port, &socket_controller);
    cr_assert(FAILURE == return_from_function);
}

Test(create_socket_file_descriptor_failure, tests_port_2)
{
    uint32_t port;
    int32_t return_from_function;
    struct socket_s socket_controller;

    port = FAILURE_PORT_2;
    return_from_function = INIT_INT;
    return_from_function = create_socket_file_descriptor(port, &socket_controller);
    cr_assert(FAILURE == return_from_function);
}
