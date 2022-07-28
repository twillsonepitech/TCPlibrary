/**
 * @file usage.h
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief Usage, contains define to print error, or global defines
 * for initialization.
 * @version 0.1
 * @date 2022-07-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef USAGE_H_
#define USAGE_H_

#define ERROR_FUNCTION(function_name) ("Error in " #function_name " function.")

#define SUCCESS     (0)
#define FAILURE     (1)

#define INIT_INT    (0)
#define INIT_UINT   (0)
#define INIT_PTR    (0)

#define LOOP_ONCE   (0)

#define PUT_ERROR_MESSAGE(__msg__)                                          \
    do                                                                      \
    {                                                                       \
        fprintf(stderr, "\033[1;31m/************************************/\033[0m\n\n");         \
        fprintf(stderr, "\033[1;31m\tERROR : \033[0m");                       \
        fprintf(stderr, "\033[1;31m[File : %s]\033[0m", __FILE__);          \
        fprintf(stderr, "\033[1;31m[Line : %d]\033[0m", __LINE__);          \
        fprintf(stderr, "\033[1;31m[Function : %s]\033[0m\n", __func__);    \
        fprintf(stderr, "\033[1;31m\tERROR : \033[0m");                       \
        fprintf(stderr, "\033[1;31m[Message : %s]\033[0m\n\n", __msg__);      \
        fprintf(stderr, "\033[1;31m/************************************/\033[0m\n");         \
    } while (LOOP_ONCE);                                                    \

#endif /* !USAGE_H_ */
