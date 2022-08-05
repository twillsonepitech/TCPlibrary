/**
 * @file data_read_write.c
 * @author your name (emeric.caramanna@epitech.eu)
 * @brief Functions to read and write data on sockets
 * @version 0.1
 * @date 2022-07-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <sys/types.h>
#include <sys/select.h>
#include <stdlib.h>
#include <unistd.h>
#include "data_read_write.h"

#define NOT_IN_SET      -1
#define FAILED_IO       -1

/**
 * @brief Called after a select has been done. First checks if there is a
 * write or read to be performed on the given socket_data_s thanks to FD_ISSET, then
 * perfoms the desired operation.
 * 
 * @param data structure containing the fd, content, and size of content to perform the io.
 * @param io_function a function pointer to either read of write.
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfuly
 */
static uint32_t check_fd_and_run_io(struct socket_data_s *data, ssize_t (*io_function)(int, void *, size_t))
{
    ssize_t io_ret = INIT_INT;

    if (data->state == NOT_READY)
        return NOT_IN_SET;
    io_ret = io_function(data->fd, data->data, data->size);
    if (FAILED_IO == io_ret) {
        PUT_ERROR_MESSAGE(ERROR_FUNCTION("write() or read()"));
        return FAILURE;
    }
    data->size = data->size - io_ret;
    return SUCCESS;
}

/**
 * @brief Perfom read and write actions on sockets that are ready based on
 * the data contained in the socket_data_s data array.
 * 
 * @param data the socket_data_s array containing the fd, and the data that has to be read
 * or written.
 * @param size the size of the array.
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfuly
 */
uint32_t read_write_socket(struct socket_data_s *data, uint32_t size)
{
    for (uint32_t i = INIT_INT; i < size; i++) {
        if (data[i].action == READING && FAILURE == check_fd_and_run_io(&data[i], &read))
            return FAILURE;
        else if (data[i].action == WRITING && FAILURE == check_fd_and_run_io(&data[i], (ssize_t (*)(int, void *, size_t))&write)) {
            return FAILURE;
        }
    }
    return SUCCESS;
}