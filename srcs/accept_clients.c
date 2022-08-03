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

#define NOT_FD  -1

/**
 * @brief Accepts the new incoming connection and stores it in the given 
 * structure, increasing its size in the meantime.
 * 
 * @param socket_controller The socket where a new connection is happenning.
 * @param clients The structure containing the array of sockets increasing with each connection.
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfuly
 */
static uint32_t accept_and_add_new_client(struct socket_s *socket_controller, struct socket_s *accepted_client)
{
    accepted_client->fd = accept(socket_controller->fd, (struct sockaddr *)&(accepted_client->address), \
                                                &(accepted_client->sockaddr_length));
    if (ACCEPT_FAILURE == accepted_client->fd) {
        PUT_ERROR_MESSAGE(ERROR_FUNCTION("accept()"));
        return FAILURE;
    }
    return SUCCESS;
}

int32_t find_socket_index_from_fd(int32_t fd, struct socket_s *socket_array, uint32_t size)
{
    for (int32_t i = INIT_INT; i < (int32_t)size; i++) {
        if (fd == socket_array[i].fd)
            return i;
    }
    return NOT_FD;
}

/**
 * @brief When called fills the accepted_clients structure with all the new
 * clients sockets trying to connect to the socket_controller.
 * 
 * @param socket_controller A previously opened socket on which bind() and listen() have been used.
 * @param client Accepted client structure to be filled by the call if there is new client connection.
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfuly
 */
uint32_t accept_new_client(struct socket_s *socket_controller, struct socket_s *client, uint8_t state)
{
    if (state == NOT_READY)
        return NO_ACCEPT;
    if (FAILURE == accept_and_add_new_client(socket_controller, client))
        return FAILURE;
    return SUCCESS;
}