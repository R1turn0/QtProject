#ifndef _H_SS_HELP_H_
#define _H_SS_HELP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/d2c.h"
#include "../inc/ss_error.h"
#include "../inc/ss_define.h"
#include "../inc/ss_lm_control.h"

#include "common.h"
#include "cJSON/cJSON.h"
#include "../inc/ss_x509.h"

#pragma warning(disable : 4996)


#define CERT_SIZE 2048
#define LOCAL_MAKE	1			//	本地有锁，使用加密锁序列号和证书合成证书链
#define REMOTE_MAKE 2			//	本地无锁，使用数据库中序列号和证书链

#define FIND_DEVICE_INDEX          0                       // 获取查找到的第一把加密锁


#ifdef __cplusplus
extern "C" {
#endif

/*
*	name:	getUserDevSN	获取当前用户锁的序列号
*   param1: [in]  devp_id	指定开发商ID 查找
*	param2:	[out] deviceSN	当前用户锁的序列号
*	return:	error(1),ok(0)
*/
int getUserDevSN(const char *devp_id, char* deviceSN);

/*
*	name:	getUserDevP7b	获取用户锁的p7b证书
*   param1: [in]  devp_id	指定开发商ID 查找
*	param2:	[out]pCertP7b	p7b接收buffer
*	param3:	[out]pCertLen	p7b长度
*	return: error(1),ok(0)
*/
int getUserDevP7b(const char *devp_id, unsigned char *pCertP7b, unsigned int *pCertLen);

int masterPINVerify(MASTER_HANDLE hD2CHandle, char *pPIN, int nPinLen);
int masterPINDeauth(MASTER_HANDLE hD2CHandle);

#ifdef __cplusplus
}
#endif

#endif // _H_SS_HELP_H_

