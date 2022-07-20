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

#define READ_MAX_SIZE 1024

struct socket_data_s {
    int32_t fd;
    uint32_t size;
    void *data;
};

uint32_t read_data_from(struct socket_data_s *data, uint32_t size);
uint32_t write_data_to(struct socket_data_s *data, uint32_t size);

#endif /* !DATA_READ_WRITE_H_ */
