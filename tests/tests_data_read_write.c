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

Test(read_data_from_failure, invalid_file_descriptor)
{
    uint32_t return_from_function;
    struct socket_data_s data;

    data.fd = INVALID_VALUE;
    return_from_function = read_data_from(&data, SINGLE_ELEMENT);
    cr_assert(FAILURE == return_from_function);
}

Test(write_data_to_failure, invalid_file_descriptor)
{
    uint32_t return_from_function;
    struct socket_data_s data;

    data.fd = INVALID_VALUE;
    return_from_function = write_data_to(&data, SINGLE_ELEMENT);
    cr_assert(FAILURE == return_from_function);
}

Test(write_data_to_success, message_stdout)
{
    uint32_t return_from_function;
    struct socket_data_s data;

    data.fd = STDOUT;
    data.size = strlen(TESTING_STRING);
    data.data = malloc(data.size);
    return_from_function = write_data_to(&data, SINGLE_ELEMENT);
    cr_assert(SUCCESS == return_from_function);
    cr_assert(VALID_VALUE == data.size);
}
