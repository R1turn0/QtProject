#ifndef _COMMON_H_
#define _COMMON_H_

 
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 开发锁登录PIN索引（固定0）
#define PIN_DEFAULT_INDEX   0

#ifdef __cplusplus
extern "C" {
#endif

	int	bytes_to_hexstr( const void* data, int count,  char* hex );
	int hexstr_to_bytes( const char* hex,  int count,  unsigned char* data);

    int read_file(const char *filename, void *buffer, unsigned int buffer_max_length, unsigned int *file_size);
    int write_file(const char *filename, void *data, int data_length);

	int read_file_text(const char *filename, void *buffer, unsigned int buffer_max_length, unsigned int *file_size);

	
#ifdef __cplusplus
}
#endif

#endif// _COMMON_H_