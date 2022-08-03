/**
 * @file selecting.c
 * @author Emeric Caramanna (emeric.caramanna@epitech.eu)
 * @brief File containing the functions to select and filter sockets.
 * @version 0.1
 * @date 2022-08-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <sys/types.h>
#include <sys/select.h>
#include <stdlib.h>
#include <unistd.h>
#include "data_read_write.h"

#define TIMEVAL_SEC     0
#define TIMEVAL_USEC    10
#define FAILED_SELECT   -1

/**
 * @brief Set the state field of the sockets in the array to ready if select
 * raised that read or write can be perfomed.
 * 
 * @param rd_fds read fd_set.
 * @param wr_fds write fd_set.
 * @param sockets array of sockets.
 * @param size size of the array.
 */
static void set_ready_socket(fd_set *rd_fds, fd_set *wr_fds, struct socket_data_s *sockets, uint32_t size)
{
    for (uint32_t i = 0; i < size; i++) {
        if ((sockets[i].action == LISTENING || sockets[i].action == READING)
            && FD_ISSET(sockets[i].fd, rd_fds)) {
                sockets[i].state = READY;
        } else if (sockets[i].action == WRITING && FD_ISSET(sockets[i].fd, wr_fds)) {
                sockets[i].state = READY;
        }
    }
}

/**
 * @brief Prepares the fd_set to perfom a select with the given array.
 * 
 * @param rd_fds read fd_set.
 * @param wr_fds write fd_set.
 * @param sockets array of sockets.
 * @param size size of the array.
 */
static void fill_fd_set(fd_set *rd_fds, fd_set *wr_fds, struct socket_data_s *sockets, uint32_t size)
{
    FD_ZERO(rd_fds);
    FD_ZERO(wr_fds);
    for (uint32_t i = 0; i < size; i++) {
        sockets[i].state = NOT_READY;
        if (sockets[i].action == LISTENING || sockets[i].action == READING) {
            FD_SET(sockets[i].fd, rd_fds);
        } else if (sockets[i].action == WRITING) {
            FD_SET(sockets[i].fd, wr_fds);
        }
    }
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
    int32_t highest = data[0].fd;
    for (uint32_t i = INIT_INT; i < size; i++) {
        if (highest < data[i].fd)
            highest = data[i].fd;
    }
    return highest;
}

/**
 * @brief Filters the array of socket depending on which action is asked
 * using select.
 * 
 * @param socket_array Array of socket_data_s.
 * @param size size of the array.
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfuly
 */
uint32_t filter_socket(struct socket_data_s *socket_array, uint32_t size)
{
    fd_set read_fds;
    fd_set write_fds;
    struct timeval tv = { .tv_sec = TIMEVAL_SEC, .tv_usec = TIMEVAL_USEC};
    int32_t select_ret;
    int32_t highest = highest_fd(socket_array, size);

    fill_fd_set(&read_fds, &write_fds, socket_array, size);
    select_ret = select(highest + 1, &read_fds, &write_fds, NULL, &tv);
    if (FAILED_SELECT == select_ret) {
        PUT_ERROR_MESSAGE(ERROR_FUNCTION("select()"));
        return FAILURE;
    }
    set_ready_socket(&read_fds, &write_fds, socket_array, size);
    return SUCCESS;
}