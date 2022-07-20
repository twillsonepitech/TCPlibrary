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

static int32_t highest_fd(struct socket_data_s *data, uint32_t size)
{
    int32_t highest = data[FIRST_ELEMENT].fd;
    for (uint32_t i = INIT_INT; i < size; i++) {
        if (highest < data[i].fd)
            highest = data[i].fd;
    }
    return highest;
}

static void set_timeval(struct timeval *tv, __time_t sec, __suseconds_t usec)
{
    tv->tv_sec = sec;
    tv->tv_usec = usec;
}

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