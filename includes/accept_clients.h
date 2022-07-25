/**
 * @file accept_clients.h
 * @author Emeric Caramanna (emeric.caramanna@epitech.eu)
 * @brief File that regroup
 *          - Structures
 *          - Functions
 *        to accept all new clients trying to connect.
 * @version 0.1
 * @date 2022-07-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ACCEPT_CLIENT_H_
#define ACCEPT_CLIENT_H_

#include "socket.h"

#define IS_NOT_SET      0 
#define SELECT_FAILURE  -1
#define ACCEPT_FAILURE  -1

/**
 * @brief Accepted clients structure gathering all the new
 * connected and accepted clients.
 * 
 * @param sockets The array of sockets fill by the accept_new_clients function.
 * @param size Size of the array.
 */
struct accepted_clients
{
    struct socket_s *sockets;
    uint32_t size;
};

uint32_t accept_new_clients(struct socket_s *socket_controller, struct accepted_clients *clients);


#endif  /* !ACCEPT_CLIENT_H_ */