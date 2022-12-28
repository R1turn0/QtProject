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
#define LOCAL_MAKE	1			//	����������ʹ�ü��������кź�֤��ϳ�֤����
#define REMOTE_MAKE 2			//	����������ʹ�����ݿ������кź�֤����

#define FIND_DEVICE_INDEX          0                       // ��ȡ���ҵ��ĵ�һ�Ѽ�����


#ifdef __cplusplus
extern "C" {
#endif

/*
*	name:	getUserDevSN	��ȡ��ǰ�û��������к�
*   param1: [in]  devp_id	ָ��������ID ����
*	param2:	[out] deviceSN	��ǰ�û��������к�
*	return:	error(1),ok(0)
*/
int getUserDevSN(const char *devp_id, char* deviceSN);

/*
*	name:	getUserDevP7b	��ȡ�û�����p7b֤��
*   param1: [in]  devp_id	ָ��������ID ����
*	param2:	[out]pCertP7b	p7b����buffer
*	param3:	[out]pCertLen	p7b����
*	return: error(1),ok(0)
*/
int getUserDevP7b(const char *devp_id, unsigned char *pCertP7b, unsigned int *pCertLen);

int masterPINVerify(MASTER_HANDLE hD2CHandle, char *pPIN, int nPinLen);
int masterPINDeauth(MASTER_HANDLE hD2CHandle);

#ifdef __cplusplus
}
#endif

#endif // _H_SS_HELP_H_

