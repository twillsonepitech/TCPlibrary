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

struct accepted_clients
{
    struct socket_s *sockets;
    uint32_t size;
};

/**
 * @brief When called fills the accepted_clients structure with all the new
 * clients sockets trying to connect to the socket_controller.
 * 
 * @param socket_controller A previously opened socket on which bind() and listen() have been used.
 * @param clients Accepted clients structure to be filled by the call if there are new client connections.
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfuly
 */
uint32_t accept_new_clients(struct socket_s *socket_controller, struct accepted_clients *clients);


#endif  /* !ACCEPT_CLIENT_H_ */