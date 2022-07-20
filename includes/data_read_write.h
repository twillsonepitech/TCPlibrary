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
 * @brief structure to be used with the read_data_from and
 * write_data_to functions.
 * The fd field is the socket file descriptor.
 * The size field is the number of bytes for the data field.
 * The data field contains the bytes to be written or read.
 */
struct socket_data_s {
    int32_t fd;
    uint32_t size;
    void *data;
};

/**
 * @brief Given an array of socket_data_s read_data_from will check if the fd
 * in the array are available for read, perform the read, store the read data in
 * the data field of the structure and update the size field of the structure with
 * the difference between the number of bytes asked and the number of bytes read. If
 * the field is at 0 everything as been read, if not the read data are incomplete and
 * you can use the value to know how many bytes are left unread.
 * 
 * @param data array of socket_data_s.
 * @param size size of the array.
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfuly
 */
uint32_t read_data_from(struct socket_data_s *data, uint32_t size);

/**
 * @brief Given an array of socket_data_s write_data_to will check if the fd
 * in the array are available for write, perform the write, and update the size field 
 * of the structure with the difference between the number of bytes asked and the number 
 * of bytes written. If the field is at 0 everything as been written, if not the written data are 
 * incomplete and you can use the value to know how many bytes are left to write.
 * 
 * @param data array of socket_data_s.
 * @param size size of the array.
 * @return uint32_t FAILURE in case of error / SUCCESS if all has been done successfuly
 */
uint32_t write_data_to(struct socket_data_s *data, uint32_t size);

#endif /* !DATA_READ_WRITE_H_ */
