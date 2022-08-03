/**
 * @file selecting.h
 * @author Emeric Caramanna (emeric.caramanna@epitech.eu)
 * @brief File containing declaration of functions to select fd that are ready for action.
 * @version 0.1
 * @date 2022-08-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SELECTING_H_
#define SELECTING_H_

#include "socket.h"

uint32_t filter_socket(struct socket_data_s *socket_array, uint32_t size);

#endif /* !ACCEPT_CLIENT_H_ */