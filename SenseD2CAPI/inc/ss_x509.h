#ifndef __SS_X509_H__
#define __SS_X509_H__

/*
all memory used should managed by caller
all function return 0 is ok, else return !0 (todo)
*/

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef INOUT
#define INOUT
#endif

#define x509_CERT_SIZE 2048


typedef struct _cert_st
{
	unsigned char certbuf[x509_CERT_SIZE];
	unsigned int  certlen;
}cert_st;

#ifdef __cplusplus
extern "C"
{
#endif

// 
/*
*	name:   ss_x509_init        初始化openssl算法库，证书链验证需要初始化算法库
*                               EVP_cleanup 函数进行清理，否则会出现内存泄露
*/
void ss_x509_init();

/*
*	name:   ss_x509_cleanup     释放 ss_x509_init 申请内存
*/
void ss_x509_cleanup();

/*
*	name:	ss_make_p7b			制作p7b证书
*	param1:	[in]cert_array		制作证书链的证书结构体(可多个)
*	param2:	[in]certcount		制作证书链的证书个数
*	param3:	[out]p7b_buf		生成p7b的内容
*	param4:	[out]p7b_len		生成p7b的长度
*/
int ss_make_p7b(IN cert_st* cert_array, IN int certcount, OUT unsigned char *p7b_buf, OUT unsigned int *p7b_len);

/*
*	name:	ss_verify_p7b		校验p7b证书
*	param1:	[in]p7b_buf			p7b的内容
*	param2:	[in]p7b_len			p7b的长度
*   remark:	使用前必须调用 ss_x509_init 进行初始化，否则验证失败。
*/
int ss_verify_p7b(IN unsigned char *p7b_buf, IN int p7b_len);

//todo




#ifdef __cplusplus
}
#endif

//error code

#define VM_CERT_ERR_FORMAT			0x10
#define VM_CERT_ERR_SIGNATURE		0x11
#define VM_CERT_ERR_SUBJECT			0x12


#endif//__SS_X509_H__
