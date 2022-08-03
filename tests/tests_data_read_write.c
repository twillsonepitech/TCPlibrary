/**
 * @file tests_data_read_write.c
 * @author Emeric Caramanna (emeric.caramanna@epitech.eu)
 * @brief Unit tests for the read and write functions combined with select.
 * @version 0.1
 * @date 2022-07-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <string.h>
#include "data_read_write.h"

#define INVALID_VALUE   -2
#define SINGLE_ELEMENT  1
#define VALID_VALUE     0
#define STDOUT          1
#define TESTING_STRING  "testing\n"
#define TESTING_SIZE    10

Test(read_data_from_failure, invalid_file_descriptor)
{
    uint32_t return_from_function;
    struct socket_data_s data;

    data.fd = INVALID_VALUE;
    data.size = TESTING_SIZE;
    data.action = READING;
    data.state = READY;
    return_from_function = read_write_socket(&data, SINGLE_ELEMENT);
    cr_assert(FAILURE == return_from_function);
}

Test(write_data_to_failure, invalid_file_descriptor)
{
    uint32_t return_from_function;
    struct socket_data_s data;

    data.fd = INVALID_VALUE;
    data.size = TESTING_SIZE;
    data.action = WRITING;
    data.state = READY;
    return_from_function = read_write_socket(&data, SINGLE_ELEMENT);
    cr_assert(FAILURE == return_from_function);
}

Test(write_data_to_success, message_stdout)
{
    uint32_t return_from_function;
    struct socket_data_s data;

    data.fd = STDOUT;
    data.size = strlen(TESTING_STRING);
    data.data = strdup(TESTING_STRING);
    if (NULL == data.data)
        cr_log_error("Error when calling strdup function");
    data.action = WRITING;
    data.state = READY;
    return_from_function = read_write_socket(&data, SINGLE_ELEMENT);
    free(data.data);
    cr_assert(SUCCESS == return_from_function);
    cr_assert(VALID_VALUE == data.size);
}
