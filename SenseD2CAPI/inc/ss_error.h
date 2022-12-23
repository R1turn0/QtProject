/*! 
*  @file ss_error.h
*  @brief     SS��������������,32λ,����ͳһ�������ʽ�����һ�ֽ���ģ���ʶ��
*  @details   ����SS��LM��H5��IPC��NetAgent��SSprotect�ȴ���ֵ��������ߵ�һ�ֽ��Ǵ���ģ���ʶ��������ģ���Զ���
*             
*  @version   2.1.0
*  @date      2013-2015
*  @pre       ��ǰ�������д���ֵ
*/
#ifndef __SS_ERROR_H__
#define __SS_ERROR_H__

//============================================================
//              һ�������
//============================================================

#define SS_OK                                       0x00000000  //  �ɹ�
#define SS_ERROR_INVALID_PARAM                      0x00000002  //  ���Ϸ��Ĳ���
#define SS_ERROR_MEMORY_FAIELD                      0x00000003  //  �ڴ����
#define SS_ERROR_INSUFFICIENT_BUFFER                0x00000004  //  ��������С����
#define SS_ERROR_INVALID_HANDLE                     0x00000008  //  ��Ч�ľ��
#define SS_ERROR_TIMEOUT                            0x00000009  //  ������ʱ
#define SS_ERROR_UNSUPPORT                          0x00000010  //  ��֧�ֵĲ���
#define SS_ERROR_NET_ERROR                          0x00000040  //  �������

#define SS_ERROR_MASTER_UNSUPPORT_PIN               0x00000044  //  ��������֧��PIN�빦�ܣ�����������˼��������¿�����
#define SS_ERROR_MASTER_PIN_NOT_ACTIVE              0x00000045  //  ������PIN��û�м�����޸ĳ�ʼPIN��
#define SS_ERROR_MASTER_OUTDATED_VERSION            0x00000047  //  �������汾̫�ͣ��������������
#define SS_ERROR_MASTER_PIN_WRONG                   0x00000048  //  PIN�����
#define SS_ERROR_MASTER_PIN_BLOCKED                 0x00000049  //  PIN�뱻����
#define SS_ERROR_NET_TIMEOUT                        0x0000004A  //  ��������ʱ

#define SS_ERROR_CONFIGURATION						0x0000004B  //  ������������ڳ�ʼ��ǰ�ȵ������ýӿڳ�ʼ�������control api���� slm_ctrl_init_cloud_server_config�� runtime api ���� slm_extensions_config��
#define SS_ERROR_MASTER_NEED_UPDATE                 0x0000004C  //  �������̼��汾̫�ͣ���Ҫ�����̼�
#define SS_ERROR_INIT_FAILED                        0x0000004D  //  ��ʼ��ʧ��
//============================================================
//              SS ģ�� (0x05)
//============================================================

#define SS_ERROR_SERVER_NOT_FOUND                   0x05000004  //  �Ҳ���������
#define SS_ERROR_NO_LOCK                            0x05000005  //  �Ҳ�����
#define SS_ERROR_SLM_HANDLE_IS_FULL                 0x05000006  //  LM ����Ѵﵽ����
#define SS_ERROR_SYSTEM_ERROR                       0x0500000D  //  ϵͳ����ʧ��
#define SS_ERROR_WHITELISTED                        0x05000013  //  ����������
#define SS_ERROR_BLACKLISTED                        0x05000014  //  ����������
#define SS_ERROR_LOCK_NOT_FOUND                     0x0500001F  //  ��û���ҵ�

//============================================================
//          LM ģ��(0x20): (runtime, control, develop)
//============================================================

#define SS_ERROR_D2C_NO_PACKAGE                     0x13000000  //  D2C������ǩ������
#define SS_ERROR_DEVELOPER_CERT_ALREADY_EXIST       0x13000001  //  ������֤���Ѵ���
#define SS_ERROR_PARSE_CERT                         0x13000003  //  ����֤�����
#define SS_ERROR_D2C_PACKAGE_TOO_LARGE              0x13000004  //  D2C������
#define SS_ERROR_RESPONSE                           0x13000005  //  �����������Ӧ
#define SS_ERROR_RUNTIME_NOT_INITIALIZE             0x13000007  //  δ����Runtime��ʼ������
#define SS_ERROR_RUNTIME_VERSION                    0x13000009  //  �汾��ƥ��
#define SS_ERROR_LIC_NOT_FOUND                      0x13000020  //  ���δ�ҵ�
#define SS_ERROR_USER_DATA_TOO_SMALL                0x13000024  //  �û�������̫С
#define SS_ERROR_INVALID_D2C_PACKAGE                0x13000027  //  �����D2C������
#define SS_ERROR_CLOUD_RESPONSE                     0x13000028  //  �������ص����ݴ���
#define SS_ERROR_USER_DATA_TOO_LARGE                0x13000029  //  ��д�����ݹ���
#define SS_ERROR_INVALID_MEMORY_ID                  0x1300002A  //  ��Ч���ڴ�ID
#define SS_ERROR_INVALID_MEMORY_OFFSET              0x1300002B  //  ��Ч���ڴ�ƫ��
#define SS_ERROR_NO_LOGGED_USER                     0x13000030  //  û�е�¼���û�
#define SS_ERROR_USER_AUTH_SERVER_NOT_RUNNING       0x13000031  //  �û���֤����δ����
#define SS_ERROR_LICENSE_MODULE_NOT_EXISTS          0x13000037  //  ���ģ�鲻����
#define SS_ERROR_DEVELOPER_PASSWORD                 0x13000038  //  ����Ŀ�����API����
#define SS_ERROR_CALLBACK_VERSION                   0x13000039  //  ����ĳ�ʼ���ص��汾��
#define SS_ERROR_INFO_RELOGIN                       0x1300003A  //  �û������µ�¼
#define SS_ERROR_LICENSE_VERIFY                     0x1300003B  //  ���������ǩʧ��
#define SS_ERROR_LICENSE_NEED_TO_ACTIVATE           0x13000051  //  �����Ҫ��������

//============================================================
//              IPC ģ�� (0x02)
//============================================================

#define SS_ERROR_IPC_FAILED                         0x02000002  //  IPC �շ�����
#define SS_ERROR_IPC_CONNECT_FAILED                 0x02000003  //  ����ʧ��

//============================================================
//              Net Agent ģ�� (0x11)
//============================================================




//============================================================
//              ��ȫģ�� (0x12)
//============================================================



//============================================================
//              LM Service (0x24)
//============================================================

#define ERROR_LM_SVC_INVALID_SESSION                0x2400000D  //  ��Ч��session
#define ERROR_LM_SVC_SESSION_ALREADY_DELETED        0x2400000E  //  session �Ѿ���ɾ��
#define ERROR_LM_SVC_LICENCE_EXPIRED                0x2400000F  //  ����Ѿ�����
#define ERROR_LM_SVC_SESSION_TIME_OUT               0x24000010  //  session��ʱ
#define ERROR_LM_REMOTE_LOGIN_DENIED                0x24000015  //  ��ɲ�����Զ�̵�¼

//============================================================
//              LM Native (0x21)
//============================================================


//============================================================
//              LM Firmware (0x22)
//============================================================
#define SS_ERROR_FIRM_LICENCE_ALL_DISABLED          0x2200000E  // ������ɱ�����
#define SS_ERROR_FIRM_CUR_LICENCE_DISABLED          0x2200000F  // ��ǰ��ɱ�����
#define SS_ERROR_FIRM_LICENCE_INVALID               0x22000010  // ��ǰ��ɲ�����
#define SS_ERROR_FIRM_LIC_STILL_UNAVALIABLE         0x22000011  // ����в�����
#define SS_ERROR_FIRM_LIC_TERMINATED                0x22000012  // ����Ѿ�����
#define SS_ERROR_FIRM_LIC_RUNTIME_TIME_OUT          0x22000013  // ����ʱ���þ�
#define SS_ERROR_FIRM_LIC_COUNTER_IS_ZERO           0x22000014  // �����þ�
#define SS_ERROR_FIRM_LIC_MAX_CONNECTION            0x22000015  // �Ѵﵽ��󲢷���Ȩ
#define SS_ERROR_FIRM_REACHED_MAX_SESSION           0x22000017  // �����Ѿ��������Ự����
#define SS_ERROR_FIRM_NOT_ENOUGH_SHAREMEMORY        0x2200001A  // û���㹻�Ĺ����ڴ�
#define SS_ERROR_FIRM_INVALID_DATA_LEN              0x2200001C  // ����������ļ�����    
#define SS_ERROR_FIRM_DATA_FILE_NOT_FOUND           0x2200001E  // �Ҳ�����Ӧ����������ļ�
#define SS_ERROR_FIRM_INVALID_PKG_TYPE              0x2200001F  // Զ�����������ʹ���
#define SS_ERROR_FIRM_INVALID_TIME_STAMP            0x22000020  // ʱ��������Զ��������
#define SS_ERROR_FIRM_INVALID_UPD_LIC_ID            0x22000021  // �����Զ������������
#define SS_ERROR_FIRM_LIC_ALREADY_EXIST             0x22000022  // ��ӵ�����Ѿ�����
#define SS_ERROR_FIRM_LICENCE_SIZE_LIMITTED         0x22000023  // �����������
#define SS_ERROR_FIRM_INVALID_DATA_FILE_OFFSET      0x22000024  // ��Ч����������ļ�ƫ��
#define SS_ERROR_FIRM_SESSION_ALREADY_LOGOUT        0x2200002C  // session�Ѿ��˳���¼
#define SS_ERROR_FIRM_INVALID_USER_DATA_TYPE        0x22000031  // �û��Զ����ֶ����ʹ���
#define SS_ERROR_FIRM_INVALID_DATA_FILE_SIZE        0x22000032  // �û��Զ����������
#define SS_ERROR_FIRM_ALL_LIC_TERMINATED            0x22000034  // �������ʱ�䵽�ڲ�����
#define SS_ERROR_FIRM_UPDATE_FAILED                 0x22000038  // Զ������ʧ��
#define SS_ERROR_FIRM_DATA_LENGTH_ALIGNMENT         0x2200003C  // �ӽ������ݳ��Ȳ�����
#define SS_ERROR_FIRM_DATA_CRYPTION                 0x2200003D  // �ӽ������ݴ���
#define SS_ERROR_FIRM_SHORTCODE_UPDATE_NOT_SUPPORTED    0x2200003E  // ��֧�ֶ�������
#define SS_ERROR_FIRM_LIC_USR_DATA_NOT_EXIST        0x22000040  // �û��Զ������ݲ�����
#define SS_ERROR_FIRM_FILE_NOT_FOUND                0x22000050  // �Ҳ����ļ�
#define SS_ERROR_FIRM_INVLAID_DEVELOPER_ID          0x22000059  // ��Ч�Ŀ�����ID
#define SS_ERROR_FIRM_BEYOND_PKG_ITEM_SIZE          0x2200005D  // �����������������
#define SS_ERROR_FIRM_DEVICE_LOCKED                 0x2200005F  // �û���������
#define SS_ERROR_FIRM_NOT_EXCHANGE_KEY              0x22000061  // δ������ԿЭ�̣�auth��֤��
#define SS_ERROR_FIRM_INVALID_SHORTCODE_SWAP_FILE   0x22000062  // ��Ч�Ķ������������ļ�
#define SS_ERROR_FIRM_SHORTCODE_UPDATE_USER_DATA    0x22000063  // ���������û�����������

//============================================================
//              MODE LIC TRANS ģ��()0x28
//============================================================

//============================================================
//              AUTH SERVER ģ�� (0x29)
//============================================================

#define SS_ERROR_AUTH_SERVER_INVALID_TOKEN          0x29000001  //��Ч��token
#define SS_ERROR_AUTH_SERVER_REFRESH_TOKEN          0x29000002  //ˢ��tokenʧ��
#define SS_ERROR_AUTH_SERVER_LOGIN_CANCELED         0x29000003  //�û�ȡ����½
#define SS_ERROR_AUTH_SERVER_GET_ALL_USER_INFO_FAIL 0x29000004  //��ȡ�����û���Ϣʧ��

//============================================================
//              Cloud ģ�� (0x30)
//============================================================
#define SS_ERROR_CLOUD_INVALID_TOKEN                0x30000010  //  ���Ϸ���token
#define SS_ERROR_CLOUD_LICENSE_ALREADY_LOGIN        0x30000011  //  ����ѵ�½
#define SS_ERROR_CLOUD_LICENSE_EXPIRED              0x30000012  //  ����ѵ���
#define SS_ERROR_CLOUD_SESSION_KICKED               0x30000013  //  ������������ն˵�¼����ǰ��ɻỰ���߳�
#define SS_ERROR_CLOUD_DEVELOPER_ACCOUNT            0x30000014  //  �����Ӧ���˻��쳣������ϵ�����Ӧ�̽��
#define SS_ERROR_CLOUD_LICENSE_LOGGED               0x30000015  //  ������������ն˵�¼����ǰ�ն��޷���¼��ɣ����������ն��˳���¼������
#define SS_ERROR_CLOUD_INVALID_SESSSION             0x30001002  //  ��Ч��session
#define SS_ERROR_CLOUD_SESSION_TIMEOUT              0x30001004  //  �Ự��ʱ
#define SS_ERROR_CLOUD_LICENSE_NOT_EXISTS           0x31001001  //  ��ɲ�����
#define SS_ERROR_CLOUD_LICENSE_NOT_ACTIVE           0x31001002  //  ���δ����
#define SS_ERROR_CLOUD_LICENSE_EXPIRED2             0x31001003  //  ����ѹ���
#define SS_ERROR_CLOUD_LICENSE_COUNTER_IS_ZERO      0x31001004  //  �����ʹ�ô���
#define SS_ERROR_CLOUD_LICENSE_RUNTIME_TIME_OUT     0x31001005  //  �����ʹ��ʱ��
#define SS_ERROR_CLOUD_LICENSE_MAX_CONNECTION       0x31001006  //  ��ɲ���������
#define SS_ERROR_CLOUD_LICENSE_LOCKED               0x31001007  //  ��ɱ�����
#define SS_ERROR_CLOUD_LICENSE_DATA_NOT_EXISTS      0x31001008  //  ������ݲ�����
#define SS_ERROR_CLOUD_LICENSE_STILL_UNAVAILABLE    0x31001010  //  ���δ����ʼʹ��ʱ��

#define SS_ERROR_SO_BEFORE_START_TIME               0x51004004  //  ���δ����ʼʱ�� 
#define SS_ERROR_SO_EXPIRED                         0x51004005  //  ����Ѿ�����
#define SS_ERROR_SO_LICENSE_BIND_ERROR              0x51004006  //  ��ɰ󶨴���
#define SS_ERROR_SO_LICENSE_BIND_FULL               0x51004007  //  ���ͬʱ�󶨵Ļ������Ѵ�����
#define SS_ERROR_SO_LICENSE_UNBOUND                 0x51004008  //  ����Ѿ����
#define SS_ERROR_SO_LICENSE_MAX_BIND_FULL           0x51004009  //  ������󶨻������Ѵ�����
#define SS_ERROR_SO_NOT_SUPPORTED_OFFLINE_BIND      0x51004010  //  ����ɲ�֧�����߰�
#define SS_ERROR_SO_EXPIRED_C2D                     0x51004011  //  ���ڵ�C2D��
#define SS_ERROR_SO_DEVELOPER_ACCOUNT               0x51004013  //  �����Ӧ���˻��쳣������ϵ�����Ӧ�̽��
#define SS_ERROR_SO_OUTDATED_VERSION                0x51004014  //  �û����߰汾���ͣ������������°汾

#define SS_ERROR_LICKEY_QUERY_STATUS_REQ_ERROR          0x51005001  //  ��ѯ��Ȩ��״̬�������쳣
#define SS_ERROR_LICKEY_EXCHANGE_REQ_ERROR              0x51005002  //  ��Ȩ��һ��������쳣
#define SS_ERROR_LICKEY_NOT_EXIST                       0x51005003  //  ��Ȩ�벻����
#define SS_ERROR_LICKEY_DEDUCT_FAILED                   0x51005004  //  ��Ȩ����ɿ۷�ʧ��
#define SS_ERROR_LICKEY_C2D_INVALID_CHAR_ENCODING       0x51005005  //  C2D�ļ�����(��ҪUTF-8����)
#define SS_ERROR_LICKEY_C2D_UNSUPPORTED_PROTO_TYPE      0x51005006  //  C2D�ļ�����(��֧�ֵ�Э������)
#define SS_ERROR_LICKEY_C2D_UNSUPPORTED_PROTO_VER       0x51005007  //  C2D�ļ�����(��֧�ֵ�Э��汾)
#define SS_ERROR_LICKEY_C2D_UNSUPPORTED_HWFP_VER        0x51005008  //  C2D�ļ�����(��֧�ֵ�Ӳ��ָ�ư汾)
#define SS_ERROR_LICKEY_C2D_INCOMPATIBLE_MACHINE_ID     0x51005009  //  C2D�ļ�����(��ƥ��Ļ���ID)
#define SS_ERROR_LICKEY_C2D_UNSUPPORTED_INFO_VER        0x5100500A  //  C2D�ļ�����(��֧�ֵĻ�����Ϣ�汾)
#define SS_ERROR_LICKEY_C2D_OVERDUE                     0x5100500B  //  C2D�ļ�����(�ѹ��ڣ�����������)
#define SS_ERROR_LICKEY_C2D_OLD_SS_VER                  0x5100500D  //  C2D�ļ�����(�ɰ�C2D����ʹ�����°汾��Virbox�û�������������)
#define SS_ERROR_LICKEY_C2D_PLATFORM_JUST_4_TRADITIONAL 0x5100500E  //  ����Ȩ��������ڴ�ͳƽ̨(Windows/Linux/Mac-OS)
#define SS_ERROR_LICKEY_C2D_PLATFORM_JUST_4_ANDROID     0x5100500F  //  ����Ȩ��������ڰ�׿ƽ̨(Android)
#define SS_ERROR_LICKEY_BIND_NO_AVAILABLE_LICENSE       0x51005011  //  ���ܰ�(�������������)
#define SS_ERROR_LICKEY_BIND_LICENSE_NOT_START          0x51005012  //  ���ܰ�(��δ����ɵĿ�ʼʹ��ʱ��)
#define SS_ERROR_LICKEY_BIND_LICENSE_EXPIRED            0x51005013  //  ���ܰ�(����Ѿ�����)
#define SS_ERROR_LICKEY_BINDING_LIMIT_EXCEEDED          0x51005014  //  ���ܰ�(��Ȩ��ͬʱ���豸���Ѵ�����)
#define SS_ERROR_LICKEY_BOUND_LIMIT_EXCEEDED            0x51005015  //  ���ܰ�(��Ȩ���ۻ����豸���Ѵ�����)
#define SS_ERROR_LICKEY_BIND_NO_AVAILABLE_PKG           0x51005016  //  ���ܰ�(�޿���������)

#define SS_ERROR_LICKEY_TERMINAL_UNBIND  			    0x51005018	//  ��Ȩ���ն˽��ʧ�ܣ�����ϵ�����Ӧ��
#define SS_ERROR_LICKEY_TERMINAL_NOT_EXIST				0x51005019	//  ������޷����ҵ��󶨼�¼������ϵ�����Ӧ��
#define SS_ERROR_LICKEY_C2D_PKG_TYPE					0x51005020	//  C2D �ļ����󣨴�������ݰ����ͣ���ȷ�� C2D �ļ���ͨ����ȷ�ķ�����ȡ�ģ�
#define SS_ERROR_LICKEY_LICENSE_LOCKED					0x51005021	//  ��Ȩ������޷��󶨣�ԭ������ɱ�����������ϵ�����Ӧ�̽��
#define SS_ERROR_LICKEY_DOES_NOT_ALLOW_BIND             0x51005025  //  ��Ȩ�벻�����
#define SS_ERROR_LICKEY_PASSWD_ENABLE                   0x51005030  //  ��Ȩ�����������룬��������ȷ������
#define SS_ERROR_LICKEY_PASSWD_ERROR                    0x51005031  //  ��Ȩ���������
#define SS_ERROR_BORROW_KEY_DISABLE                     0x51005032  //  ��Ȩ���ѹرս��Ĺ���
#define SS_ERROR_LICKEY_CLIENT_OUTDATED_VERSION         0x51005033  //  ��ʱ�޷�������ɣ��û�������Ҫ���������°汾
#define SS_ERROR_LICKEY_DEVICE_FORBIDDEN                0x51005034  //  �����Ӧ�̻����˸��豸��ʹ��Ȩ�������ٰ󶨵�ǰ��Ȩ�룬����ϵ�����Ӧ�̽��

#define SS_ERROR_LICKEY_NOT_EXIST_V2                    0x5100612F  //  ��Ȩ�벻���ڣ���ȷ����Ȩ���Ƿ���ȷ
#define SS_ERROR_LICKEY_INVALID_C2D_DATA                0x51006130  //  ��Ч��Ӳ����Ϣ����
#define SS_ERROR_LICKEY_ABNORMAL_COST                   0x51006134  //  ��Ȩ����ɿ۷�ʧ�ܣ�����ϵ�����Ӧ��

#define SS_ERROR_BORROW_KEY_NOT_EXIST                   0x51005026  //  �����벻����
#define SS_ERROR_BORROW_KEY_DELETED                     0x51005027  //  ��������ɾ��
#define SS_ERROR_BORROW_KEY_ALREADY_REVOKED             0x51005028  //  �������ѱ�����
#define SS_ERROR_BORROW_KEY_EXPIRED                     0x51005029  //  �������ѹ���
#define SS_ERROR_BORROW_KEY_ALREADY_BOUND               0x5100502A  //  �������Ѿ���
#define SS_ERROR_BORROW_KEY_BIND_FAILED                 0x5100502B  //  �������ʧ��
#define SS_ERROR_BORROW_KEY_BIND_NOT_EXIST              0x5100502C  //  ���ܽ��(δ��)
#define SS_ERROR_BORROW_KEY_UNMATCHED_MACHINE_ID        0x5100502D  //  ���ܽ��(����������¼��Ϣ��һ��)
#define SS_ERROR_BORROW_KEY_MAKE_PACKAGE_FAILED         0x5100502E  //  ��������װ���ݰ�ʧ��


//============================================================
//              �û�����ģ�� (0x60)
//============================================================


//============================================================
//              web_serverģ�� (0x70)
//============================================================
#define SS_ERROR_WEB_SERVER_INIT_FAILED			0x70000000
#define SS_ERROR_WEB_INVALID_URI				0x70000001
#define SS_ERROR_MAKE_P7B						0x70000002

// ��
#define MAKE_ERROR(mode, errcode)           (((mode) << 24) | (errcode))
#define MAKE_COMMON_ERROR(mode, errcode)    (((mode) << 24) | (errcode))
#define MAKE_H5_RUNTIME(errorcode)          (((errorcode)==H5_ERROR_SUCCESS) ? 0 : (MAKE_COMMON_ERROR(MODE_H5_RUNTIME,(errorcode))))
#define MAKE_SYS_ERROR(errorcode)          (((errorcode)==0) ? 0 : (MAKE_COMMON_ERROR(MODE_SYSTEM,(errorcode))))
#define MAKE_NETAGENT(errorcode)            MAKE_COMMON_ERROR(MODE_NETAGENT,(errorcode))
#define MAKE_SSPROTECT(errorcode)           MAKE_COMMON_ERROR(MODE_NETAGENT,(errorcode))
#define MAKE_LM_FIRM_ERROR(errorcode)       MAKE_COMMON_ERROR(MODE_LM_FIRM,(errorcode))
#define MAKE_LM_SES_ERROR(errorcode)        MAKE_COMMON_ERROR(MODE_LM_SES,(errorcode))
#define GET_ERROR_MODULE(errorcode)          ((errorcode) >> 24)


#endif //__SS_ERROR_H__
