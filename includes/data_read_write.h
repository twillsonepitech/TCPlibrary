/**
 * @file data_read_write.h
 * @author Emeric Caramanna (emeric.caramanna@epitech.eu)
 * @brief All the functions and structure to simplify reading and
 * wrinting on sockets.
 * @version 0.1
 * @date 2022-07-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef DATA_READ_WRITE_H_
#define DATA_READ_WRITE_H_

#include "socket.h"

/**
 * @brief Enumeration to define the usage of a socket.
 * This is used to identify which type of action has to be
 * done when select is used on the socket.
 * 
 */
enum use_e {
    READING,
    WRITING,
    LISTENING
};

/**
 * @brief structure to be used with the read_data_from and
 * write_data_to functions.
 * @param fd The fd field is the socket file descriptor.
 * @param size The size field is the number of bytes for the data field.
 * @param data The data field contains the bytes to be written or read.
 */
struct socket_data_s {
    int32_t fd;
    uint32_t size;
    void *data;
    enum use_e action;
    uint8_t state;
};

uint32_t read_write_socket(struct socket_data_s *data, uint32_t size);

#endif /* !DATA_READ_WRITE_H_ */
