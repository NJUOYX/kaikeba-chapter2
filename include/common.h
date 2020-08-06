#ifndef __COMMON_H__
#define __COMMON_H__
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

#define STR_BUFFER_SIZE 256

#define WORK_COMMAND "duty"
#define TIME_COMMAND "time"

#define log_error(error) printf(error)
#define log_info(info) printf(info)

#endif//__COMMON_H__