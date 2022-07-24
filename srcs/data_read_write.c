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

#define NO_READ_WRITE   0
#define FIRST_ELEMENT   0
#define TIMEVAL_SEC     0
#define TIMEVAL_USEC    10
#define NOT_IN_SET      -1
#define FAILED_IO       -1
#define READ            0
#define WRITE           1

/**
 * @brief Fills the given fd_set with the fd from the array of socket_data_s. If the
 * size field of the structure is at 0 does not add it to the fd_set.
 * 
 * @param set fd_set to be filled.
 * @param data array of socket_data_s containing fd to fill the set.
 * @param size size of the array.
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfuly
 */
static uint32_t fill_fd_set(fd_set *set, struct socket_data_s *data, uint32_t size)
{
    FD_ZERO(set);
    for (uint32_t i = INIT_INT; i < size; i++) {
        if (data[i].size > NO_READ_WRITE) {
            FD_SET(data[i].fd, set);
            if (FD_ISSET(data[i].fd, set) == 0) {
                PUT_ERROR_MESSAGE(ERROR_FUNCTION("FD_ISSET()"));
                return FAILURE;
            }
        }
    }
    return SUCCESS;
}

/**
 * @brief Determines the highest fd from an array of socket_data_s.
 * 
 * @param data array of socket_data_s containing fd to be checked.
 * @param size size of the array.
 * @return int32_t the value of the highest fd.
 */
static int32_t highest_fd(struct socket_data_s *data, uint32_t size)
{
    int32_t highest = data[FIRST_ELEMENT].fd;
    for (uint32_t i = INIT_INT; i < size; i++) {
        if (highest < data[i].fd)
            highest = data[i].fd;
    }
    return highest;
}

/**
 * @brief Fills the timeval object.
 * 
 * @param tv timeval structure to be filled.
 * @param sec seconds for the given timeval.
 * @param usec useconds for the given timeval.
 */
static void set_timeval(struct timeval *tv, __time_t sec, __suseconds_t usec)
{
    tv->tv_sec = sec;
    tv->tv_usec = usec;
}

/**
 * @brief Called after a select has been done. First checks if there is a
 * write or read to be performed on the given socket_data_s thanks to FD_ISSET, then
 * perfoms the desired operation.
 * 
 * @param data structure containing the fd, content, and size of content to perform the io.
 * @param set fd_set to check if the given fd is available for io.
 * @param io_function a function pointer to either read of write.
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfuly
 */
static uint32_t check_fd_and_run_io(struct socket_data_s *data, fd_set *set, ssize_t (*io_function)(int, void *, size_t))
{
    ssize_t io_ret = INIT_INT;

    if (FD_ISSET(data->fd, set) == 0)
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
 * @brief Called before doing write or read to check with select if the given fd are
 * available for the action. 
 * 
 * @param data array of socket_data_s containing fd to be checked.
 * @param size size of the array.
 * @param set fd_set to be filled and checked.
 * @param flag flag to determine if a read or write will be done.
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfuly
 */
static uint32_t set_up_and_select(struct socket_data_s *data, uint32_t size, fd_set *set, uint32_t flag)
{
    int32_t select_ret;
    int32_t highest;
    struct timeval tv;

    if (NO_READ_WRITE == size)
        return NO_READ_WRITE;
    if (FAILURE == fill_fd_set(set, data, size))
        return FAILED_IO;
    highest = highest_fd(data, size);
    set_timeval(&tv, TIMEVAL_SEC, TIMEVAL_USEC);
    if (READ == flag)
        select_ret = select(highest + 1, set, NULL, NULL, &tv);
    else
        select_ret = select(highest + 1, NULL, set, NULL, &tv);
    if (FAILED_IO == select_ret) {
        PUT_ERROR_MESSAGE(ERROR_FUNCTION("select()"));
        return FAILED_IO;
    }
    return (uint32_t)select_ret;
}

/**
 * @brief Given an array of socket_data_s read_data_from will check if the fd
 * in the array are available for read, perform the read, store the read data in
 * the data field of the structure and update the size field of the structure with
 * the difference between the number of bytes asked and the number of bytes read. If
 * the field is at 0 everything as been read, if not the read data are incomplete and
 * you can use the value to know how many bytes are left unread.
 * 
 * @param data array of socket_data_s.
 * @param size size of the array.
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfuly
 */
uint32_t read_data_from(struct socket_data_s *data, uint32_t size)
{
    fd_set read_set;
    int32_t select_ret;

    select_ret = set_up_and_select(data, size, &read_set, READ);
    if (FAILED_IO == select_ret)
        return FAILURE;
    if (NO_READ_WRITE == select_ret)
        return SUCCESS;
    for (uint32_t i = INIT_INT; i < size; i++) {
        if (FAILURE == check_fd_and_run_io(&data[i], &read_set, &read))
            return FAILURE;
    }
    return SUCCESS;
}

/**
 * @brief Given an array of socket_data_s write_data_to will check if the fd
 * in the array are available for write, perform the write, and update the size field 
 * of the structure with the difference between the number of bytes asked and the number 
 * of bytes written. If the field is at 0 everything as been written, if not the written data are 
 * incomplete and you can use the value to know how many bytes are left to write.
 * 
 * @param data array of socket_data_s.
 * @param size size of the array.
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfuly
 */
uint32_t write_data_to(struct socket_data_s *data, uint32_t size)
{
    fd_set write_set;
    int32_t select_ret;

    select_ret = set_up_and_select(data, size, &write_set, WRITE);
    if (FAILED_IO == select_ret)
        return FAILURE;
    if (NO_READ_WRITE == select_ret)
        return SUCCESS;
    for (uint32_t i = INIT_INT; i < size; i++) {
        if (FAILURE == check_fd_and_run_io(&data[i], &write_set, (ssize_t (*)(int, void *, size_t))&write))
            return FAILURE;
    }
    return SUCCESS;    
}