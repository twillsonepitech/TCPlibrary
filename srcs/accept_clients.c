/**
 * @file accept_clients.c
 * @author Emeric Caramanna (emeric.caramanna@epitech.eu)
 * @brief Set of fonctions allow new clients to be accepted.
 * @version 0.1
 * @date 2022-07-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <sys/types.h>
#include <sys/select.h>
#include <stdlib.h>
#include "accept_clients.h"

#define TIMEVAL_SEC     0
#define TIMEVAL_USEC    10

/**
 * @brief Accepts the new incoming connection and stores it in the given 
 * structure, increasing its size in the meantime.
 * 
 * @param socket_controller The socket where a new connection is happenning.
 * @param clients The structure containing the array of sockets increasing with each connection.
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfuly
 */
static uint32_t accept_and_add_new_client(struct socket_s *socket_controller, struct accepted_clients *clients)
{
    clients->sockets = realloc(clients->sockets, clients->size + 1);
    if (NULL == clients->sockets) {
        PUT_ERROR_MESSAGE(ERROR_FUNCTION("realloc()"));
        return FAILURE;
    }
    clients->sockets[clients->size].fd = accept(socket_controller->fd, (struct sockaddr *)&(clients->sockets[clients->size].address), \
                                                &(clients->sockets[clients->size].sockaddr_length));
    if (ACCEPT_FAILURE == clients->sockets[clients->size].fd) {
        PUT_ERROR_MESSAGE(ERROR_FUNCTION("accept()"));
        return FAILURE;
    }
    clients->size += 1;
    return SUCCESS;
}

/**
 * @brief Set up the timeout and fd_set with the given fd for an upcoming select.
 * 
 * @param set The fd_set to be initialized.
 * @param fd The fd to be added to the fd_set.
 * @param tv The timeval struct.
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfuly
 */
static uint32_t setup_fd_set_and_timeout(fd_set *set, int32_t fd, struct timeval *tv)
{
    FD_ZERO(set);
    FD_SET(fd, set);
    if (IS_NOT_SET == FD_ISSET(fd, set)) {
        PUT_ERROR_MESSAGE(ERROR_FUNCTION("FD_ISSET()"));
        return FAILURE;
    }
    tv->tv_sec = TIMEVAL_SEC;
    tv->tv_usec = TIMEVAL_USEC;
    return SUCCESS;
}

/**
 * @brief A short function to initializa a clean accepted_clients structure.
 * 
 * @param clients The accepted_clients structure to be initialized.
 */
static void init_new_clients(struct accepted_clients *clients)
{
    clients->size = INIT_INT;
    clients->sockets = NULL;
}

/**
 * @brief When called fills the accepted_clients structure with all the new
 * clients sockets trying to connect to the socket_controller.
 * 
 * @param socket_controller A previously opened socket on which bind() and listen() have been used.
 * @param clients Accepted clients structure to be filled by the call if there are new client connections.
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfuly
 */
uint32_t accept_new_clients(struct socket_s *socket_controller, struct accepted_clients *clients)
{
    fd_set set;
    struct timeval tv;
    int32_t select_ret;

    init_new_clients(clients);
    if (FAILURE == setup_fd_set_and_timeout(&set, socket_controller->fd, &tv))
        return FAILURE;
    select_ret = select(socket_controller->fd + 1, &set, NULL, NULL, &tv);
    while (select_ret) {
        if (SELECT_FAILURE == select_ret) {
            PUT_ERROR_MESSAGE(ERROR_FUNCTION("select()"));
            return FAILURE;
        }
        if (IS_NOT_SET != FD_ISSET(socket_controller->fd, &set)) {
            if (FAILURE == accept_and_add_new_client(socket_controller, clients))
                return FAILURE;
        }
        if (FAILURE == setup_fd_set_and_timeout(&set, socket_controller->fd, &tv))
            return FAILURE;
        select_ret = select(socket_controller->fd + 1, &set, NULL, NULL, &tv);
    }
    return SUCCESS;
}