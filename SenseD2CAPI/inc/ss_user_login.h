
#ifndef _SS_USER_LOGIN_H
#define _SS_USER_LOGIN_H

#ifndef SSAPI
#if defined WIN32 || defined _WIN32 || defined _WIN64
#define SSAPI __stdcall
#else
#define SSAPI
#endif
#endif

#define SS_CLOUD_ERROR_SUCCESS						0 		//	�ɹ�	
#define SS_CLOUD_ERROR_PASSWORD						1		//	�û��������������
#define SS_CLOUD_ERROR_INVALID_PARAM				2		//	��������	
#define SS_CLOUD_ERROR_SERVICE_STOPPED 				3   	//	�û���¼����δ����
#define SS_CLOUD_ERROR_TIMEOUT 						4		//	��¼��ʱ
#define SS_CLOUD_ERROR_GET_USER_INFO                5       //  ��ȡ�û���Ϣʧ��
#define SS_CLOUD_ERROR_NET_ERROR                    6       //  �������
#define SS_CLOUD_ERROR_COULDNT_RESOLVE_HOST         7       //  ��������ַ���ɴ�
#define SS_CLOUD_ERROR_ACCOUNT_DISABLED             8       //  ��ǰ�˺ű�����
#define SS_CLOUD_ERROR_UNKNOWN      				-1		//	���������ϸ����

#define SS_CLOUD_MAX_USER_GUID_SIZE 				128		//	����û�GUID����


#ifdef __cplusplus
extern "C"{
#endif

/*
*	@param[in]  url		    ����˽�л�URL���ʵ�ַ�����ջ�ʹ��Ĭ��URL
*	@param[in]  user_name 	�û���
*	@param[in]  passwd 		����
*	@param[out] user_guid   �����û�GUID�ַ�����logout���������SS_CLOUD_MAX_USER_GUID_SIZE�ֽ�
*	@return �ɹ����� SS_CLOUD_ERROR_SUCCESS��ʧ�ܷ��������Ĵ�����
*/
int SSAPI ss_cloud_user_login(const char *url, const char *user_name, const char *passwd, char *user_guid);


/*
*	@param[in]  user_info ss_cloud_user_login ���ص�user_info
*	@return �ɹ����� SS_CLOUD_ERROR_SUCCESS��ʧ�ܷ��������Ĵ�����
*/
int SSAPI ss_cloud_user_logout(const char *user_guid);

/*  ���ýӿ�
*   @param[in]  config ���ò�����JSON��
*               1.ָ�������Ʒ����ַ�ͳ�ʱ��{"auth_url":"https://auth.senseyun.com", "timeout":6000}
*                   "auth_url"���˲������ڼ��ݾɰ汾���ã�Ҳ����ͨ�� ss_cloud_user_login ����ָ����������ʹ�����ýӿ�����URL��ַ��
*                   "timeout"������ʱ�����룩
*   @return �ɹ����� SS_CLOUD_ERROR_SUCCESS��ʧ�ܷ��������Ĵ�����
*   @remark ���ýӿڱ����ڵ��������ӿ�ǰ���ò�ָ������������Ч��
*/
int SSAPI ss_cloud_config(const char* config);

#ifdef __cplusplus
}
#endif

#endif
