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
*	name:   ss_x509_init        ��ʼ��openssl�㷨�⣬֤������֤��Ҫ��ʼ���㷨��
*                               EVP_cleanup ���������������������ڴ�й¶
*/
void ss_x509_init();

/*
*	name:   ss_x509_cleanup     �ͷ� ss_x509_init �����ڴ�
*/
void ss_x509_cleanup();

/*
*	name:	ss_make_p7b			����p7b֤��
*	param1:	[in]cert_array		����֤������֤��ṹ��(�ɶ��)
*	param2:	[in]certcount		����֤������֤�����
*	param3:	[out]p7b_buf		����p7b������
*	param4:	[out]p7b_len		����p7b�ĳ���
*/
int ss_make_p7b(IN cert_st* cert_array, IN int certcount, OUT unsigned char *p7b_buf, OUT unsigned int *p7b_len);

/*
*	name:	ss_verify_p7b		У��p7b֤��
*	param1:	[in]p7b_buf			p7b������
*	param2:	[in]p7b_len			p7b�ĳ���
*   remark:	ʹ��ǰ������� ss_x509_init ���г�ʼ����������֤ʧ�ܡ�
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
