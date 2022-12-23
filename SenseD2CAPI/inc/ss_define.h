/*! 
*  @file ss_define.h
*  @brief     Virbox 对外声明的类似定义。
*  
*/
#ifndef __SS_DEFINE_H__
#define __SS_DEFINE_H__

typedef unsigned long long  SS_UINT64;
typedef unsigned int    SS_UINT32;
typedef unsigned short  SS_UINT16;
typedef unsigned char   SS_UINT8;

typedef long long       SS_INT64;
typedef int             SS_INT32;
typedef short           SS_INT16;
typedef char            SS_INT8;

typedef unsigned char   SS_BYTE;
typedef char            SS_CHAR;
typedef int             SS_BOOL;


#ifndef   IN
#define   IN
#endif

#ifndef   OUT
#define   OUT
#endif

#ifndef  INOUT
#define  INOUT
#endif

#ifndef SSAPI
  #if defined WIN32 || defined _WIN32 || defined _WIN64
    #define SSAPI __stdcall
  #else
    #define SSAPI
  #endif
#endif

/** 参数格式枚举  */
typedef enum _INFO_FORMAT_TYPE {

    /** JSON格式  */
    JSON = 2,
    /** 结构体格式  */
    STRUCT = 3,
    /**  字符串模式,遵行Key=value  */
    STRING_KV = 4,
    /** 加密二进制格式*/
    CIPHER = 5,
} INFO_FORMAT_TYPE;

/** 设备证书类型*/
typedef enum _CERT_TYPE{
    /** 证书类型：根证书  */
    CERT_TYPE_ROOT_CA = 0,

    /** 证书类型：设备子CA  */
    CERT_TYPE_DEVICE_CA = 1,
    
    /** 证书类型：设备证书  */
    CERT_TYPE_DEVICE_CERT = 2,

    /** 证书类型：深思设备证书  */
    CERT_TYPE_SENSE_DEVICE_CERT = 3,

} CERT_TYPE;

#endif //__SS_DEFINE_H__
