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

#define ACCEPT_FAILURE  -1
#define NO_ACCEPT       2

uint32_t accept_new_client(struct socket_s *socket_controller, struct socket_s *client, uint8_t state);
int32_t find_socket_index_from_fd(int32_t fd, struct socket_s *socket_array, uint32_t size);


#endif  /* !ACCEPT_CLIENT_H_ */