
/*!
*  @file      d2c.h
*  @brief     SLM���Զ������ͷ�ļ�.
*  @details   ���Զ�����������¡�ɾ������������������Ȳ���������ɾ����д�ļ�������������������ʱ�ӣ�ǩ����̬�������
*     
*   ʹ�����̣�
*
*   ǰ�ᣬ����master_open�򿪿�����������ǩ��d2c��
*
*       - ǩ�����
*       ��һ�������� d2c_lic_new ����d2c���
*       �ڶ��������� d2c_add_lic ����������
*       ������������ d2c_add_developer_cert ��D2C������豸֤����
*       ���Ĳ������� d2c_get ��ȡ���յ�d2c��Ϣ���ɽ����ֱ��ͨ��ss_lm_update�ṩ�Ľӿ����������ڣ�
*            ���߱���Ϊ*.d2c���ļ��첽��ʽ���������ڡ�
*       - ǩ���ļ�
*       ��һ�������� d2c_file_seed_new ����d2c���
*       �ڶ��������� d2c_add_pkg ����ļ�����
*       ������������ d2c_add_developer_cert ��D2C������豸֤����
*       ���Ĳ������� d2c_get ��ȡ���յ�d2c��Ϣ���ɽ����ֱ��ͨ��ss_lm_update�ṩ�Ľӿ����������ڣ�
*           ���߱���Ϊ*.d2c���ļ��첽��ʽ���������ڡ�
*       ��󣬵��� d2c_delete �ͷž��������master_close�رտ�����
*
*       D2C������Ϊ���ӣ���ϸʹ�÷�����ͨ��Virbox SDK�ṩ��Samples����ѧϰ
*
*  @version   2.2.0
*  @date      2014-2018
*/

#ifndef _D2C_H
#define _D2C_H

#include "ss_define.h"


/** ǩ�����˻���ɵ��˻�����󳤶� */
#define MAX_ACCOUNT_NAME_LENGTH         64      
/** �˻�GUID�ĳ��� */
#define D2C_GUID_LENGTH                 37      
/** �޸�ʱ�ӵ���������� */
#define FIXTIME_RAND_LENGTH             8       
/** ��Ƭ�������Ӵ�С */
#define SNIPPET_SEED_LENGTH             32      

/** �����ļ�Ȩ�޶��壺�ļ������߿ɶ� */
#define ACCESS_READ                     0x01    
/** �����ļ�Ȩ�޶��壺�ļ������߿��޸�ɾ�� */
#define ACCESS_WRITE_DELETE             0x02    
/** �����ļ�Ȩ�޶��壺�ļ������߿�ʹ�ã������Կ�ļ��� */
#define ACCESS_USE                      0x04    
/** �����ļ�Ȩ�޶��壺�ļ������߿�Զ������ */
#define ACCESS_WRITE_DELETE_RU          0x08    

/** �ļ�Entry�ɶ� */
#define ACCESS_ENTRY_READ               0x10    
/** �ļ�Entry���޸�ɾ�� */
#define ACCESS_ENTRY_WRITE_DELETE       0x20    
/** �ļ�Entry��ʹ�ã������Կ�ļ���*/
#define ACCESS_ENTRY_USE                0x40    
/** �ļ���Զ������ */
#define ACCESS_ENTRY_WRITE_DELETE_RU    0x80    

/** ϵͳ����CA */
#define PKI_CA_TYPE_SYSTEM                          0       
/** ������CA */
#define PKI_CA_TYPE_DEVELOPER                       1       
/** Ӳ���豸CA */
#define PKI_CA_TYPE_DEVICE                          2       
/** �˻�֤�� */
#define PKI_CA_TYPE_ACCOUNT                         3       
/** ��֤�� */
#define PKI_CA_TYPE_ROOT                            0x80    

/** ������PIN����С���� */
#define CTRL_PIN_MIN_SIZE               8
/** ������PIN����󳤶� */
#define CTRL_PIN_MAX_SIZE               255

/** D2C Developer2Customer�ľ�� */
typedef struct _D2C_HANDLE_INTERNAL* D2C_HANDLE;

/** �������ľ�� */
typedef struct _MASTER_HANDLE_INTERNAL* MASTER_HANDLE;

/** D2C����ǩ������(SIGN_TYPE) */
typedef enum _SIGN_TYPE 
{
    /** D2C��֤��ǩ����ǩ����ָ���û��� */
    SIGN_TYPE_CERT          = 1,    
    /** D2C��������ǩ��(�ݲ�֧��ǩ�����)��ǩ���������û��� */
    SIGN_TYPE_SEED          = 2,

    /** D2C��֤��ǩ����ǩ����ָ������ */
    SIGN_TYPE_SLOCK         = 3
    
} SIGN_TYPE;

/**   D2C����ǩ����ϣ���� */
typedef enum _D2C_HASH_ALGO 
{
    /** ��ϣ�㷨Ϊ��SHA-1 */
    D2C_HASH_ALGO_SHA1 = 1,
    /** ��ϣ�㷨Ϊ��SHA-256 */
    D2C_HASH_ALGO_SHA256 = 2
    
} D2C_HASH_ALGO;

/** �˻����ͣ�ָ�����ض���ǩ������ */
typedef enum _ACCOUNT_TYPE 
{
    /** ǩ�����˻���Ӳ�������豸��*/
    ACCOUNT_TYPE_NONE   = 0, 
    /** ǩ�������˻���Ӳ����������Ϊ�����˻��� */
    ACCOUNT_TYPE_USB    = 1,
    /** ǩ�������˻����ݲ�֧�֣� */
    ACCOUNT_TYPE_EMAIL  = 2,
    /** ǩ���ֻ��˻����ݲ�֧�֣� */
    ACCOUNT_TYPE_PHONE  = 3,
	/** ǩ������5-NetBox */
	ACCOUNT_TYPE_NETBOX = 4,
    /** ǩ����Ȩ������ */
    ACCOUT_TYPE_LICKEY = 5
    
} ACCOUNT_TYPE;

/**   ��Ƭ�������ӽṹ�������߲��ع��ģ� */
typedef struct _SNIPPET_CODE_CONTEXT 
{
    /**  �汾�� */
    SS_UINT32       version;    
    /**  �����ʶ */
    SS_UINT32       code_id;    
    /** ���ID */
    SS_UINT32       license_id; 
    /** ��Կ�����ģ�*/
    SS_BYTE         key[32];  
    /** ���ӣ����ģ�*/
    SS_BYTE         snippet_seed[SNIPPET_SEED_LENGTH]; 
} SNIPPET_CODE_CONTEXT;

/**
*   @defgroup D2CAPI Virbox D2C �ӿ�˵��
*   �˽ӿ�Ϊ Virobx D2C API ˵���ĵ��������������������ǩ�����ļ�ǩ���ȹ���
*   @{
*/

#ifdef __cplusplus
extern "C" {
#endif

    /*!
    *   @brief      ��ǩ���豸����������
    *   @param[out] device_handle       �������豸���
    *   @return     �ɹ����� SS_OK��ʧ�ܷ�����Ӧ�Ĵ�����
    *   @remarks    һ�е�ǩ�����ܶ��벻���������������򿪿��������������ǩ���Ĳ��������ܽ���
    *   @see        master_close d2c_lic_new
    */
    SS_UINT32 SSAPI master_open(OUT MASTER_HANDLE* device_handle);

    /*!
    *   @brief      �ر�ǩ���豸����������
    *   @param[in]  device_handle       �������豸�����ͨ������ #master_open �õ�
    *   @return     �ɹ�����SS_OK��ʧ�ܷ�����Ӧ�Ĵ�����
    *   @see        master_open
    */
    SS_UINT32 SSAPI master_close(IN MASTER_HANDLE device_handle);

    /*!
    *   @brief      ��ȡ������������ID
    *   @param[in]  device_handle   �������豸�����ͨ������ #master_open �õ�
    *   @param[out] developer_id    ������ID
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
    *   @remarks    ������ID ��ÿ��������Ψһ��һ����ʶ�ţ�ÿ�������߶�����ͨ����ȡ�������Ŀ�����ID�����жϴ˿������Ƿ�Ϊ�������С�
    *               �ʹ�õ�����ʽ������ Demo ����������ʽ��������
    *   @code
    *       {
    *           MASTER_HANDLE master_handle ;
    *           SS_BYTE developer_id[8] = {0};
    *           SS_UINT32 status = SS_OK;
    *
    *           status = master_open(&master_handle);
    *           if(status != SS_OK)
    *               return status;
    *
    *           status = master_get_developer_id(master_handle, developer_id);
    *           if(status == SS_OK)
    *           {
    *               // todo
    *               // HEXTOSTRING(developer_id);    // ��ʮ������ת��Ϊ�ַ���
    *           }
    *           master_close(master_handle);
    *       }
    *   @endcode
    */
    SS_UINT32 SSAPI master_get_developer_id(IN MASTER_HANDLE device_handle, OUT SS_BYTE *developer_id);

    /*!
    *   @brief      ��ȡ�������������еĸ�֤������
    *   @param[in]  device_handle   �������豸�����ͨ������ #master_open �õ�
    *   @param[out] count           ��֤������
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
    *   @remarks    �� 2018��1��1�� ��VirboxLM �Կ��������û������а�ȫ��������������֧�ֶ��֤�飬���û�����ʹ���µĸ�֤�顣
    *               Ϊ����֮ǰ�汾���û������������н�ӵ�ж����֤��
    */
    SS_UINT32 SSAPI master_get_root_count(IN MASTER_HANDLE device_handle, OUT SS_UINT32 *count);

    /*!
    *   @brief      ͨ��֤�����ͣ���ȡ������ CA ֤��
    *   @param[in]  device_handle       �������豸�����ͨ������ #master_open �õ�
    *   @param[in]  ca_type             ֤�����ͣ���� #PKI_CA_TYPE_DEVELOPER ��
    *   @param[out] ca_cert             �����CA֤��Ļ�����
    *   @param[in]  cert_bufsize        ��������С
    *   @param[out] cert_size           CA ֤���С
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
    *   @remarks    ǩ�������Ҫ���Ͽ�����֤��������˻�ȡ��������֤�顢CA ���ǲ��ɻ�ȱ�Ľӿڡ�
    *   @code
    *       {
    *           SS_UINT32 status = SS_OK;
    *           MASTER_HANDLE  master_handle;
    *               SS_BYTE    ca[2048] = { 0 };   // ֤�����CA�Ĵ�Сһ�㲻�ᳬ��1.5k�����ﻺ����ʹ��2k�㹻����
    *               SS_UINT32  ca_size = 0;
    *           
    *           master_open(&master_handle);
    *
    *           status = master_get_ca_cert(master_handle, PKI_CA_TYPE_DEVELOPER, ca, sizeof(ca), &ca_size);
    *           if(status == SS_OK)
    *           {
    *               // save ca to file
    *           }
    *           master_close(master_handle);
    *       }
    *   @endcode
    */
    SS_UINT32 SSAPI master_get_ca_cert(IN MASTER_HANDLE device_handle, IN SS_BYTE ca_type,
        OUT SS_BYTE *ca_cert, IN SS_UINT32 cert_bufsize, OUT SS_UINT32 *cert_size);


    /*!
    *   @brief      ͨ��֤�����ͣ���ȡ������ CA ֤��
    *   @param[in]  device_handle       �������豸�����ͨ������ #master_open �õ�
    *   @param[in]  ca_type             ֤�����ͣ���� #PKI_CA_TYPE_DEVELOPER ��
    *   @param[in]  root_index          ��֤���������
    *   @param[out] ca_cert             �����CA֤��Ļ�����
    *   @param[in]  cert_bufsize        ��������С
    *   @param[out] cert_size           CA ֤���С
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
    *   @remarks    ǩ�������Ҫ���Ͽ�����֤��������˻�ȡ��������֤�顢CA ���ǲ��ɻ�ȱ�Ľӿڡ�
    *   @see        master_get_ca_cert
    */
    SS_UINT32 SSAPI master_get_ca_cert_ex(IN MASTER_HANDLE device_handle, IN SS_BYTE ca_type, IN SS_UINT32 root_index,
        OUT SS_BYTE *ca_cert, IN SS_UINT32 cert_bufsize, OUT SS_UINT32 *cert_size);

    /*!
    *   @brief      ��ȡ������ Virbox Root CA ֤��
    *   @param[in]  device_handle       �������豸�����ͨ������ #master_open �õ�
    *   @param[out] root_ca             ��ſ����� Virbox Root CA ֤��Ļ�����
    *   @param[in]  root_bufsize        ��������С
    *   @param[out] root_size           ������ Virbox Root CA ֤���С
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
    *   @see        master_open master_get_ca_cert
    */
    SS_UINT32 SSAPI master_get_root_ca(IN MASTER_HANDLE device_handle,
        OUT SS_BYTE *root_ca, IN SS_UINT32 root_bufsize, OUT SS_UINT32 *root_size);

    /*!
    *   @brief      ��ȡ�������豸 CA ֤��
    *   @param[in]  device_handle       �������豸�����ͨ������ #master_open �õ�
    *   @param[out] device_ca           ����豸 CA ֤��Ļ�����
    *   @param[in]  device_bufsize      ��������С
    *   @param[out] device_size         �豸 CA ֤���С
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
    *   @see        master_open master_get_ca_cert
    */
    SS_UINT32 SSAPI master_get_device_ca(IN MASTER_HANDLE device_handle,
        OUT SS_BYTE *device_ca, IN SS_UINT32 device_bufsize, OUT SS_UINT32 *device_size);

    /*!
    *   @brief      ��ȡ������������ CA ֤��
    *   @param[in]  device_handle       �������豸�����ͨ������ #master_open �õ�
    *   @param[out] developer_ca        ��ſ����� CA ֤��Ļ�����
    *   @param[in]  ca_bufsize          ��������С
    *   @param[out] ca_size             ������ CA ֤���С  
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
    *   @see        master_open master_get_ca_cert
    */
    SS_UINT32 SSAPI master_get_developer_ca(IN MASTER_HANDLE device_handle,
        OUT SS_BYTE *developer_ca, IN SS_UINT32 ca_bufsize, OUT SS_UINT32 *ca_size);

    /*!
    *   @brief      ��ȡ������������֤��
    *   @param[in]  device_handle       �������豸�����ͨ������ #master_open �õ�
    *   @param[out] developer_cert      ��ſ�����֤��Ļ�����
    *   @param[in]  cert_bufsize        ��������С
    *   @param[out] cert_size           ������֤���С
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
    *   @see        master_open master_get_ca_cert
    */
    SS_UINT32 SSAPI master_get_developer_cert(IN MASTER_HANDLE device_handle,
        OUT SS_BYTE *developer_cert, IN SS_UINT32 cert_bufsize, OUT SS_UINT32 *cert_size);

    /*!
    *   @brief      ���ݸ�֤����������ȡ������������֤�飨��չ�ӿڣ�
    *   @param[in]  device_handle       �������豸�����ͨ������ #master_open �õ�
    *   @param[in]  root_index          ��֤���������
    *   @param[out] developer_cert      ��ſ�����֤��Ļ�����
    *   @param[in]  cert_bufsize        ��������С
    *   @param[out] cert_size           ������֤���С
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
    *   @see        master_open master_get_ca_cert
    */
    SS_UINT32 SSAPI master_get_developer_cert_ex(IN MASTER_HANDLE device_handle, IN SS_UINT32 root_index,
        OUT SS_BYTE* developer_cert, IN SS_UINT32 cert_bufsize, OUT SS_UINT32* cert_size);

    /*! 
    *   @brief      ��֤������ CA ֤��
    *   @param[in]  device_handle       �������豸�����ͨ������ #master_open �õ�
    *   @param[in]  store               ��֤ʱ���Ƿ�֤��洢�����ڡ�TRUE���洢��FALSE�����洢��
    *   @param[in]  ca_type             ֤�����ͣ�ֻ����֤ ������CA�� ��� #PKI_CA_TYPE_DEVELOPER 
    *   @param[in]  ca_cert             ֤�黺����
    *   @param[in]  ca_len              ֤�鳤��
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
    *   @remarks    �˽ӿڽ��� #PKI_CA_TYPE_DEVELOPER ������֤��Ч
    *   @code
    *       {
    *           SS_UINT32 status = SS_OK;
    *           MASTER_HANDLE  master_handle;
    *           SS_BYTE    ca[2048] = { 0 };   // ֤�����CA�Ĵ�Сһ�㲻�ᳬ��1.5k�����ﻺ����ʹ��2k�㹻����
    *           SS_UINT32  ca_size = 0;
    *
    *           master_open(&master_handle);
    *
    *           // ͨ�� master_get_ca_cert��master_get_developer_ca ��ȡ��������ca�����߼����ⲿ�洢�Ŀ����� ca
    *           // ... ... 
    *
    *           status = master_verify_ca(master_handle, FALSE, PKI_CA_TYPE_DEVELOPER, ca, ca_size);
    *           if(status == SS_OK)
    *           {
    *               // save ca to file
    *           }
    *           master_close(master_handle);
    *       }
    *   @endcode
    */
    SS_UINT32 SSAPI master_verify_ca(IN MASTER_HANDLE device_handle, IN SS_BOOL store, 
        IN SS_BYTE ca_type, IN SS_BYTE *ca_cert, IN SS_UINT32 ca_len);

    /*!
    *   @brief      ��֤������CA֤�飨��չ�ӿڣ�
    *   @param[in]  device_handle       �������豸�����ͨ������ #master_open �õ�
    *   @param[in]  store               ��֤ʱ���Ƿ�֤��洢�����ڡ�TRUE���洢��FALSE�����洢��
    *   @param[in]  ca_type             ֤�����ͣ�ֻ����֤ ������CA �� �豸CA ��� #PKI_CA_TYPE_DEVELOPER �� #PKI_CA_TYPE_DEVICE
    *   @param[in]  root_index          ��֤�����
    *   @param[in]  ca_cert             ֤�黺����
    *   @param[in]  ca_len              ֤�鳤��
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
    *   @remarks    �˽ӿڽ��� #PKI_CA_TYPE_DEVELOPER �� #PKI_CA_TYPE_DEVICE CA ��֤��Ч
    */
    SS_UINT32 SSAPI master_verify_ca_ex(IN MASTER_HANDLE device_handle, IN SS_BOOL store,
        IN SS_BYTE ca_type, IN SS_UINT32 root_index, IN SS_BYTE *ca_cert, IN SS_UINT32 ca_len);

    /*!
    *   @brief      ��ȡǩ���豸����������Կ�������빫Կ��
    *   @param[in]  device_handle   �������豸�����ͨ������ #master_open �õ�
    *   @param[out] key             ������
    *   @param[in]  max_key_len     ����������
    *   @param[out] key_len         ֤��ĳ���
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
    */
    SS_UINT32 SSAPI master_get_seedkey(
        IN  MASTER_HANDLE   device_handle,
        OUT SS_BYTE*        key,
        IN  SS_UINT32       max_key_len,
        OUT SS_UINT32*      key_len
        );

    /*!
    *   @brief      ��ȡ�������豸��Ϣ
    *   @param[in]  device_handle   �������豸�����ͨ������ #master_open �õ�
    *   @param[in]  type            ��ȡ��Ϣ���ͣ���ǰֻ�� = 1
    *   @param[out] info            ��ȡ������Ϣ��json�ṹ
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
    *   @remarks    info ��Ҫ���� #master_heap_free �ͷ�
    *   @code
    *     - info �� json �ṹ
    *       {
    *           "support_pin":true, 
    *           "enable_pin":true, 
    *           "developer_id":"0300000000000009",
    *           "lock_firmware_version":"3.1.16", 
    *           "lm_firmware_version":"1.2.1.0",    (PIN ����֤ͨ�����ȡ��Ϣ�ǲ��д��ֶ�)
    *           "sn":"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    *           "shared" : {                        // �����������Ϣ���̼��汾������ 3.1.24�������� Entry �汾������ 1.4.1.0��
    *               "version":1,                    // ��������Ϣ��֯��ʽ�汾��ʶ
    *               "developers":[                  // ������֧�ֿ�����ID��Ϣ�б�
    *                   { 
    *                       "developer_id":"0800000000000113",
    *                       "index":1,
    *                       "license_id":1001       // ���ڻ�ȡ LM license ��Ϣ #master_lm_read_license
    *                   }
    *               ]
    *           }
    *       }
    *   @endcode
    */
    SS_UINT32 SSAPI master_get_info(IN MASTER_HANDLE device_handle, IN SS_BYTE type, OUT char **info);

    /*!
    *   @brief      �ͷ��ڴ�
    *   @param[in]  buf             �ڲ�������ڴ�
    *   @return     ��Զ���� SS_OK
    *   @remarks    ���� #master_get_info ������ڴ�
    */
    SS_UINT32 SSAPI master_heap_free(IN void *buf);

    /*!
    *   @brief      �޸Ŀ����̿����� PIN ��
    *   @param[in]  device_handle   �������豸�����ͨ������ #master_open �õ�
    *   @param[in]  pin_index       PIN �����ڵ�����λ�ã�Ŀǰֻ֧�� 1 �� PIN �룬��ǰΪ 0
    *   @param[in]  old_pin         ��ǰʹ���е� PIN ��
    *   @param[in]  old_pin_len     ��ǰʹ�õ� PIN �볤��
    *   @param[in]  new_pin         �� PIN ��
    *   @param[in]  new_pin_len     �� PIN �볤��
    *   @param[in]  hash            �� PIN ��� sha256 hash ����������ڲ�У��
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
    *   @remarks    PIN ����ѭ���¸�ʽ��
    *               - ���Ȳ��õ��� 8 ���ַ������ô��� 255 ���ַ�
    *               - ����ʹ�ú��֣�ȫ���ַ���
    *               - ���ó��ֶ����� 0 �Ȼ�Ӱ����ʵ���ȵ��ַ�
    *               - ��ʼ PIN ������޸ģ������ʼ PIN ���޷�ͨ����֤����ʼ PIN ��� VirboxLM ���������Ļ�ȡ��https://developer.lm.virbox.com��
    */
    SS_UINT32 SSAPI master_pin_change(
        IN MASTER_HANDLE    device_handle,
        IN SS_BYTE          pin_index,
        IN SS_BYTE          *old_pin,
        IN SS_UINT32        old_pin_len,
        IN SS_BYTE          *new_pin,
        IN SS_UINT32        new_pin_len,
        IN SS_BYTE          *hash
        );

    /*!
    *   @brief      ��֤������ PIN ��
    *   @param[in]  device_handle   �������豸�����ͨ������ #master_open �õ�
    *   @param[in]  pin_index       PIN �����ڵ�����λ�ã�Ŀǰֻ֧�� 1 �� PIN �룬��ǰΪ 0
    *   @param[in]  pin             ��ǰʹ���е� PIN ��
    *   @param[in]  pin_len         ��ǰʹ�õ� PIN �볤��
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
    *   @remarks    PIN ��֤��ѭ���¹���
    *               - ��ʼ PIN �벻��ͨ����֤
    *               - ����ͨ�� PIN ����֤����ǩ��������
    */
    SS_UINT32 SSAPI master_pin_verify(
        IN MASTER_HANDLE    device_handle,
        IN SS_BYTE          pin_index,
        IN SS_BYTE          *pin,
        IN SS_UINT32        pin_len
        );

    /*!
    *   @brief      ȷ�� PIN ���Ƿ���֤ͨ��
    *   @param[in]  device_handle   �������豸�����ͨ������ #master_open �õ�
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
    *   @remarks    ������� SS_ERROR_MASTER_OUTDATED_VERSION ����ʾ�������汾̫�ͣ����������������
    *               ������� 0x0100000D ������û�н��� PIN ����֤��
    */
    SS_UINT32 SSAPI master_pin_is_verified(MASTER_HANDLE device_handle);

    /*!
    *   @brief      ���ÿ����� PIN ��
    *   @param[in]  device_handle   �������豸�����ͨ������ #master_open �õ�
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
    *   @remarks    ���ÿ����� PIN ����
    */
    SS_UINT32 SSAPI master_pin_enable(MASTER_HANDLE device_handle);

    /*!
    *   @brief      ���ÿ����� PIN ��
    *   @param[in]  device_handle   �������豸�����ͨ������ #master_open �õ�
    *   @return     �ɹ����� SS_OK��ʧ�ܷ�����Ӧ�Ĵ�����
    *   @remarks    ���õ�ǰ�������� PIN ���ܣ����ȵ��� #master_pin_verify
    */
    SS_UINT32 SSAPI master_pin_disable(MASTER_HANDLE device_handle);

    /*!
    *   @brief      ��� PIN Ȩ��
    *   @param[in]  device_handle   �������豸�����ͨ������ #master_open �õ�
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
    *   @remarks    �����ǰ PIN Ȩ�޺��´�ǩ�����ʱ����Ҫ���µ��� #master_pin_verify
    */
    SS_UINT32 SSAPI master_pin_deauth(MASTER_HANDLE device_handle);

    /*!
    *   @brief  �Կ������������������������е�������������������ʧ�ܻ����ִ�к�������������
    *   @param[in] device_handle    �������豸�����ͨ������ #master_open �õ�
    *   @param[in] pkg              ��������json
    *   @param[out]msg              ���������json����Ҫ���� #master_heap_free �ͷ�
    *   @return �ɹ�����0��ʧ�ܷ��ش����루������ʧ�ܴ��󣬴��������ѯÿ�����������������
    *           ��������������ʧ�ܣ����� SS_ERROR_FIRM_UPDATE_FAILED ������Ҫ�����߸��ݷ��ص���ϸ��Ϣ�����߼����������������˳��Ҫ�������ȼ���һ����ϸ����
    *   @code
    *       һ��������������pkg��ʾ����
    *       {
    *           "device_pkg": [{                // ������������������������
    *               "desc": "entry delete",     // ע������˳�򣨲��ϸ�Լ��˳�������������ⲿ�����֤��
    *               "type": "entry",
    *               "data": "base64_string"
    *           },
    *           {
    *               "desc": "entry create",
    *               "type": "entry",
    *               "data": "base64_string"
    *           },
    *           {
    *               "desc": "developer id",     // ���������������������빲����Ȩ������ID������˼��������ǩ����
    *               "type": "file",
    *               "data": "base64_string"
    *           },
    *           {
    *               "desc": "license pub",      // ������ɵĿ����̹�Կ������ LMS ���ʱ��Ҫͨ����Կ��֤���ݰ�����Ч�ԣ�������� LMS ��ɵĿ���������Ҫ���´˹�Կ��
    *               "type": "file",
    *               "data": "base64_string"
    *           }],
    *           "lm_pkg": [{                    // LMSҵ��ӿ�
    *               "desc": "sl_auth",          // �ļ�����
    *               "type": "file",             // ���������� file
    *               "data": "base64_string"     // ����������
    *           },
    *           {
    *               "desc": "1",                // ���ID
    *               "type": "license",          // ���������� license
    *               "data": "base64_string"     // ����������
    *           }]
    *       }
    *       �������ؽ����msg��ʾ����
    *       {
    *           "device_pkg": [{
    *               "index": 1,                  // ������˳������ֵ��
    *               "desc": "entry delete",      // ����������
    *               "status": 0,                 // �������
    *               "detail": ""                 // ��ϸ����
    *           },
    *           {
    *               "index": 2,
    *               "desc": "entry delete",
    *               "status": 0,
    *               "detail": ""
    *           }],
    *           "lm_pkg": [{
    *               "index": 1,
    *               "desc": "sl_auth",
    *               "status": 0,
    *               "detail": ""
    *           },
    *           {
    *               "index": 2,                  
    *               "desc": "1",
    *               "status": 0,
    *               "detail": ""
    *           }]
    *   @endcode
    *   @remark 
    */
    SS_UINT32 SSAPI master_update(
        IN  MASTER_HANDLE   device_handle,
        IN  const char      *pkg,
        OUT char            **msg
        );

    /*!
    *   @brief  ͨ�����ID ��ȡ���������Ϣ
    *   @param[in] device_handle    �������豸�����ͨ������ #master_open �õ�
    *   @param[in] license_id       ���ڴ��ڵ����ID
    *   @param[out]lic_info			�����Ϣ��json �ṹ
    *   @return	�ɹ�����0��ʧ�ܷ��ش�����
    *   @code
    *       - lic_info �ṹ
    *        {
    *           "license_id": number,
    *           "status":0 | 1 | 2,     // 0 = ɾ����1 = ���ã�2 = ����
    *           "sign_time":utc sec,    // ���ǩ��ʱ��
    *           "last_use":utc sec,     // ���һ��ʹ��ʱ��
    *           "max_count":number,     // ������
    *           "curr_count":number,    // ʣ�����
    *           "type":"slock | dongle | share",     // slock = �������͵���ɣ�dongle = Ӳ���������������͵���ɣ�share = ���������
    *           
    *           "pc_count":number,          // type = slock ʱ��Ч���󶨻�������
    *           "pc_curr_count":number,     // type = slock ʱ��Ч��ʣ����õİ󶨻�����
    *           "net_count":number,         // type = slock ʱ��Ч������ڵ�����
    *           "net_curr_count":number,    // type = slock ʱ��Ч��ʣ����õ�����ڵ�
    *           
    *           "devp_id":"hex string",     // type = share ʱ��Ч���������ϼ�������ID      
    *        }
    *   @endcode
    */
    SS_UINT32 SSAPI master_lm_read_license(
        IN  MASTER_HANDLE   device_handle,
        IN  SS_UINT32       license_id,
        OUT char            **lic_info
        );

    /*!
    *   @brief  ���ɹ�����������
    *   @param[in]  device_handle   �������豸�����ͨ������ #master_open �õ�
    *   @param[in]  developer_id    ��Ҫ���ɹ�������ʼ���������Ŀ�����ID����Ҫ���ȵ��� #master_get_info ��ȡ֧�ֵĿ������б�
    *   @param[in]  cert            �������û���֤����
    *   @param[in]  cert_size       �������û���֤��������
    *   @param[out] pkg             ��������������������Ҫ���� #master_heap_free �ͷ�
    *   @param[out] pkg_size        ����������������ʵ�ʳ���
    *   @return	�ɹ�����0��ʧ�ܷ��ش�����
    */
    SS_UINT32 SSAPI gen_shared_update_pkg(
        IN  MASTER_HANDLE   device_handle,
        IN  SS_BYTE*        developer_id,
        IN  SS_BYTE*        cert,
        IN  SS_UINT32       cert_size,
        OUT SS_BYTE**       pkg,
        OUT SS_UINT32*      pkg_size
        );

    /*!
    *   @brief      ���� D2C ���������ǩ�����
    *   @param[in]  device_handle   �������豸�����ͨ������ #master_open �õ�
    *   @param[out] d2c_license     ���� D2C �ľ��
    *   @param[in]  account_type    �˺����ͣ��ο� #ACCOUNT_TYPE
    *   @param[in]  account_id      �˻������ַ����������ţ�16�ֽ����ţ�
    *   @param[in]  account_size    �˻�������
    *   @param[in]  cert            ֤�飬����� account_type = #ACCOUNT_TYPE_NONE ������Ӳ�����豸֤�������˻���������ƿ�����֤����
    *   @param[in]  cert_size       ֤�鳤��
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ����룬SS_ERROR_PARSE_CERT ��ʾ�����豸֤��ʧ�ܡ�
    *   @remarks    ���� D2C ��������� D2C ���ĳ�ʼ��������
    *   @see        d2c_delete d2c_add_developer_cert d2c_add_pkg d2c_get
    */
    SS_UINT32 SSAPI d2c_lic_new(
        IN  MASTER_HANDLE   device_handle,
        OUT D2C_HANDLE*     d2c_license,
        IN  ACCOUNT_TYPE    account_type,
        IN  SS_BYTE*        account_id,
        IN  SS_UINT32       account_size,
        IN  SS_BYTE*        cert,
        IN  SS_UINT32       cert_size
        );

    /*!
    *   @brief      ����D2C���������ǩ�����������������������ǩ���ļ�
    *   @param[in]  device_handle   �������豸�����ͨ������ #master_open �õ�
    *   @param[out] d2c_file        ���� D2C �ľ��
    *   @param[in]  sign_type       ǩ�����ͣ��ο� #SIGN_TYPE
    *   @param[in]  param           ������豸֤�飬�����豸֤������������ǩ������ Virbox Root CA
    *   @param[in]  param_size      ֤�����Ĵ�С����ǩ����ǩ���� Virbox��֤���С
    *   @return     �ɹ�����S S_OK��ʧ�ܷ�����Ӧ�Ĵ�����
    *   @remarks    ��2018��1��1����VirboxLM �Կ��������û������а�ȫ��������������֧�ֶ��֤�飬���û�����ʹ���µĸ�֤�飬
    *               ԭ���� d2c_file_seed_new �����������Ϊ��ǰ�� #d2c_file_new ��
    *               ��Ҫ�����
    *                   - ��ʹ��������ǩ���ļ�ʱ��param ������ԭ���Ĵ��գ���ɴ��� Virbox Root CA��
    *
    *               Virbox Root CA ����ͨ�� #master_get_ca_cert_ex �� #master_get_root_count ��ȡ��
    *               ��Ϊ��ȷ��֤���ȡ�����������ǣ�
    *                   - �����̴ӹ̼��汾�� 3.1.20 ���°汾���û����У���ȡ�� Virbox Root CA �ɰ汾��֤�� ��ֵ��
    *                   - �����̴ӹ̼��汾�� 3.1.20 ���ϣ��� 3.1.20 ���汾���û����У���ȡ Virbox Root CA �°汾��֤�� ��ֵ��
    *                   - �����̴���˼�����ṩ�� �豸֤�����л�ȡ��Ӧ��֤�顣
    *
    *               ���ڸ�֤�鶼��һ���ģ�ֻ�����û���ʹ���°汾��֤�飬�������֤��ֻ��Ҫȡһ�α��漴�ɡ�
    */
    SS_UINT32 SSAPI d2c_file_new(
        IN  MASTER_HANDLE   device_handle,
        OUT D2C_HANDLE*     d2c_file,
        IN  SIGN_TYPE       sign_type,
        IN  SS_BYTE*        param,
        IN  SS_UINT32       param_size
        );

    /*!
    *   @brief      ���ӿ�����֤����������Ҫ�ٵ����ˣ�������Ϊ�����ԣ�
    *   @param[in]  d2c_handle      D2C ������� #d2c_lic_new �� #d2c_file_new �õ�
    *   @param[in]  cert            ������֤����
    *   @param[in]  cert_len        ֤���С
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
    *   @remarks    D2C ������ʱ���Զ���ӿ�����֤������ D2C ���У������ٵ��ô˽ӿڴ���֤������
    */
    SS_UINT32 SSAPI d2c_add_developer_cert(D2C_HANDLE d2c_handle, SS_BYTE* cert, SS_UINT32 cert_len);

    /*!
    *   @brief      ǩ����̬����
    *   @param[in]  device_handle   �������豸�����ͨ������ #master_open �õ�
    *   @param[in]  sign_type       ǩ�����ͣ��ο� #SIGN_TYPE
    *   @param[in]  param           �豸֤���� (������ǩ����ʽ���Ӧ�� Virbox Root CA)
    *   @param[in]  param_size      ֤�������� (������ǩ����ʽ���Ӧ�� Virbox Root CA ���ȣ�
    *   @param[in]  exec_code       ��̬���� 
    *   @param[in]  code_size       �����С�����֧�� 2048 �ֽڴ�С�Ķ�̬���룩
    *   @param[in]  bound_info      ����Ϣ�����ID ���飬���ID Ϊ 4 ���ֽڣ�
    *   @param[in]  bound_size      ����Ϣ�ĳ��ȣ���λ���ֽڣ�
    *   @param[out] pkg             ������������û�������
    *   @param[in]  max_pkg_len     �������ĳ���
    *   @param[out] pkg_len         ǩ�õĴ��볤
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����    
    *   @remarks    �� 2018��1��1�� ��VirboxLM �Կ��������û������а�ȫ��������������֧�ֶ��֤�飬���û�����ʹ���µĸ�֤��
    *               ��Ҫ�����
    *                   - ��ʹ��������ǩ����̬����ʱ��param ������ԭ���Ĵ��գ���ɴ��� Virbox Root CA��
    *
    *               Virbox Root CA ����ͨ�� #master_get_ca_cert_ex �� #master_get_root_count ��ȡ��
    *               ��Ϊ��ȷ��֤���ȡ�����������ǣ�
    *                   - �����̴ӹ̼��汾�� 3.1.20 ���°汾���û����У���ȡ�� Virbox Root CA �ɰ汾��֤�� ��ֵ��
    *                   - �����̴ӹ̼��汾�� 3.1.20 ���ϣ��� 3.1.20 ���汾���û����У���ȡ Virbox Root CA �°汾��֤�� ��ֵ��
    *                   - �����̴���˼�����ṩ�� �豸֤�����л�ȡ��Ӧ��֤�顣
    *
    *               ���ڸ�֤�鶼��һ���ģ�ֻ�����û���ʹ���°汾��֤�飬�������֤��ֻ��Ҫȡһ�α��漴�ɡ�
    */
    SS_UINT32 SSAPI gen_dynamic_code(
        IN  MASTER_HANDLE   device_handle,
        IN  SIGN_TYPE       sign_type,
        IN  SS_BYTE*        param,
        IN  SS_UINT32       param_size,
        IN  SS_BYTE*        exec_code,
        IN  SS_UINT32       code_size,
        IN  SS_UINT32*      bound_info,
        IN  SS_UINT32       bound_size,
        OUT SS_BYTE*        pkg,
        IN  SS_UINT32       max_pkg_len,
        OUT SS_UINT32*      pkg_len
        );

    /*!
    *   @brief      ����������������������������������� D2C����Է���������ݵ�����
    *   @param[in]  d2c_file        �ļ� D2C ������� #d2c_file_new �õ�
    *   @param[in]  param           ������json��
    *   @param[in]  opr_desc        �������ַ���
    *   @exception  û���쳣
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
    *   @remarks
    *   - ��������
    *       -#  �����ļ�ʱ��ִ���ļ��� offset ����Ϊ 0
    *       -#  �����뷽ʽ������ǩ�����
    *   - ������ע�����
    *       -#  ����������ʱ���뱣����ǩ��������ʱ����ͬ����������������ʧ�ܵ������
    *       -#  ��ʱ���С���������޶���ʼʱ�䣬�������������ʱ�����������ͬ���������ݰ���
    *       -#  ��ʱ��������������޶�����ʱ�䣬����ǩ����������������
    *   @code
    *       json ����˵����
    *       �ļ�������
    *       {
    *           "op":           "addfile" | "updatefile" | "delfile"    �ļ��������ͣ�����Ϊ����� | ���� |ɾ�� 
    *           "filename":     "file_name.xxx",                        �ļ�����������С�� 16 �ֽ�
    *           "filetype":     "evx" | "evd" | "key"                   �ļ����ͣ�����Ϊ����ִ���ļ� | �����ļ� | ��Կ�ļ��� ��ɾ���ļ�ʱ����Ҫ��д���ͣ�
    *           "access":       number                                  �ļ��ķ���Ȩ�ޣ���ӣ����£�ɾ���ļ�ʱ���������ã�Ĭ��Ϊ 0x0F ������������Ȩ�ޣ� Entry ���ɷ��ʣ����ο� #ACCESS_READ �Ⱥ�
    *           "timestamp":    number(0 ~ 0xFFFFFFFF)                  �ļ�������ʱ�䣨���ڿ��طţ������JSON��û�д����ʹ�õ�ǰʱ������һ��ʱ���
    *           "filebuffer":   "0123456789ABCDEF"                      �ļ����� HEX16 �ַ�����ɾ���ļ�ʱ����Ҫ��д���
    *           "fileoffset":   number  (��ѡ)                          �ļ�ƫ�ƣ�Ĭ��Ϊ 0��ɾ���ļ�ʱ����Ҫ��
    *           "bind_lic":     [1,2,3,4]                               ��ִ���ļ��󶨵���ɣ����ļ�����Ϊ evx (��ִ�г���)ʱ��Ч
    *       }
    *
    *       ��������
    *       {
    *           "op":           "reset"             �������ͣ�������
    *           "not_before":   UTC ʱ�䣨��Ч��ʼʱ�䣩
    *           "not_after":    UTC ʱ�䣨��Ч��ֹʱ�䣩������������ֹʱ�䷶Χ�ڣ�������ֹ����һ�룩���ظ�ʹ�á�
    *       }
    *
    *       �޶�ʱ�ӣ�
    *       {
    *           "op" :          "fixtime",                  �������ͣ��޸�ʱ��
    *           "lock_time":      number,					�û�����ʱ��
    *           "rand":         "0102030405060708"          8 ���ֽ� HEX16 �ַ���
    *           "diff":          number,                    ʱ��� (pc_time - lock_time)
    *       }
    *
    *   @endcode
    *   @see d2c_lic_new d2c_add_developer_cert
    *
    */
    SS_UINT32 SSAPI d2c_add_pkg(
        IN  D2C_HANDLE          d2c_file,
        IN  SS_CHAR*            param,
        IN  SS_CHAR*            opr_desc
        );

    /*!
    *   @brief      �����������������������������������D2C�������������ݵ�����
    *   @param[in]  d2c_license     ��� D2C������� #d2c_lic_new �����õ�
    *   @param[in]  param           ������ json ��
    *   @param[in]  opr_desc        �����������ַ������������Զ���
    *   @param[out] guid            ��� GUID
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
    *   @remarks
    *   - ��������
    *       -#  �����뷽ʽ������ǩ�����
    *   - json ����˵����
    *   @code
    *       ��������            ��������    ��ѡ�ֶ�      ����ֵ                  ��������
    *       "op"                string     ��           "installlic"            ��װ���
    *                                                   "addlic"                ������
    *                                                   "activelic"             �������
    *                                                   "updatelic"             �������
    *                                                   "dellic"                ɾ�����
    *                                                   "lockalllic"            ����������ɣ�0�����ר�ã�
    *                                                   "unlockalllic"          ����������ɣ�0�����ר�ã�
    *                                                   "delalllic"             ɾ��������ɣ�0�����ר�ã�
    *       "version"           string     ��            "op number"            ��ɰ汾�ţ����֣���Χ�� 1 ~ 0xFFFFFFFF��   op: '+' | '-' | '='    eg. "=123"    
    *       "license_id"        number     ��(��op)      --                     ���ID�����֣���Χ�� 1 ~ 0xFFFFFFFF����lockalllic, delalllic, unlockalllic����Ҫ��
    *       "force"             bool       ��            true/false             �Ƿ�ǿ����������Ϊ true ���������Ĳ���Ϊ��
    *                                                                           [addlic]������ӣ����򸲸�
    *                                                                           [dellic]����ɾ��������ɹ�
    *       "start_time"        string     ��            "op number"            ��ʼʱ��(UTC ��)                           op : '+' | '-' | '=' | 'disable'    eg. "=123456", "disable"(�������ã������ڸ���ʱ����ԭ��������)
    *       "end_time"          string     ��            "op number"            ��ֹʱ�䣬�����ñ������������(UTC��)     op : '+' | '-' | '=' | 'disable'    eg. "+456789"
    *       "counter"           string     ��            "op number"            ʹ�ô���                                  op : '+' | '-' | '=' | 'disable'   eg. "-123"
    *       "span"   	        string     ��            "op number"            ʱ����(UTC ��)                           op : '+' | '-' | '=' | 'disable'   eg. "=987654"
    *       "concurrent"        string     ��            "op number"            ��󲢷���(0~65535)                       op : '+' | '-' | '=' | 'disable'   eg. "=654"
    *       "concurrent_type"   string     ��            "process"              �Խ������Ʋ��� 
    *                                                    "win_user_session",    �� Windows �Ự���Ʋ�����    
    *       "module":           json_array ��            [1,2,3,4,5,...,64]     ģ������json ��������ṹ����������Ա�ʾģ�飬��Χ�� 1 �� 64  
    *       "timestamp":        number     ��            --                     ��ɵ�ǩ��ʱ��������ڷ��طţ����JSON��û�д����ʹ�õ�ǰʱ������һ��ʱ���
    *       "serial":           number     ��            --                     ��ɵ�ǩ����ˮ�ţ����ڷ��طţ����JSON��û�д������ʱ�����ϣ�����һ����ˮ��
    *       "rom":              json       ��            --                     ֻ�������� 
    *                                                    {
    *                                                        "data":"HEX�ַ���",     ����������
    *                                                        "offset":number,        д����������ƫ�ƣ�Ĭ��Ϊ 0
    *                                                        "resize":number         ������ڴ��ֶΣ���ʾ������������С��ֵ��Ϊ�µĴ�С
    *                                                    }           
    *       "raw":              json       ��            {"data":"HEX�ַ���", "offset":number,"resize":number}           ��д�����������ݲο�ֻ��ȡ����
    *       "pub":              json       ��            {"data":"HEX�ַ���", "offset":number,"resize":number}           ���������������ݲο�ֻ��ȡ����
    *
    *       ע�� ��"lockalllic", "unlockalllic", "delalllic"�⣬������������Ҫ����"license_id"�ֶ�
    *   @endcode
    *   @see d2c_lic_new d2c_add_developer_cert
    *
    */
    SS_UINT32 SSAPI d2c_add_lic(
        IN  D2C_HANDLE          d2c_license,
        IN  SS_CHAR*            param,
        IN  SS_CHAR*            opr_desc,
        OUT SS_CHAR             guid[D2C_GUID_LENGTH]
        );
    
    /*!
    *   @brief      �� D2C ����л�ȡ D2C �����ɱ���Ϊ .d2c �ļ���������
    *   @param[in]  d2c_handle  D2C ������� #d2c_lic_new �� #d2c_file_new �õ�
    *   @param[out] d2c_buf     �õ��� D2C ����������������Ϊ�ַ�����ʽ
    *                           ���Ϊ 0���� out_len ������Ҫ�ĳ���
    *   @param[in]  max_buf_len d2c_buf �Ļ�������С
    *   @param[out] out_len     �õ��� D2C ����������
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
    *   @remarks    ͨ���˽ӿڻ�ȡ�����յ� D2C �����ݣ���ֱ�ӽ�����д�����ڣ�Ҳ�ɱ���Ϊ .d2c �ļ����첽д�����ڡ�
    *   @code
    *       {
    *           ["pkg_type":"type", "pkg_data":"base64", "pkg_desc":"desc"]
    *           ["pkg_type":"type", "pkg_data":"base64", "pkg_desc":"desc"]
    *       }
    *   @endcode
    *   @see d2c_lic_new d2c_add_developer_cert
    */
    SS_UINT32 SSAPI d2c_get(
        IN  D2C_HANDLE      d2c_handle,
        OUT SS_CHAR*        d2c_buf,
        IN  SS_UINT32       max_buf_len,
        OUT SS_UINT32*      out_len
        );

    /*!
    *  @brief       ��ÿ������Զ���� D2C ��������
    *  @param[in]   d2c_handle      D2C������� #d2c_lic_new �� #d2c_file_new �õ�
    *  @param[in]   index           pkg���������� 1 ��ʼ
    *  @return      �ַ���������ֵ����Ҫ�ͷţ���������
    */
    const SS_CHAR* d2c_get_pkg_desc(
        IN  D2C_HANDLE      d2c_handle,
        IN  SS_UINT32       index
        );

    /*!
    *  @brief       ɾ�� D2C ���
    *  @param[in]   d2c_handle      D2C������� #d2c_lic_new �� #d2c_file_new �õ�
    *  @return      ���Ƿ���SS_OK
    *  @see         d2c_lic_new
    */
    SS_UINT32 SSAPI d2c_delete(
        IN  D2C_HANDLE      d2c_handle
        );

    /*!
    *   @brief      D2C ǩ�� �������߲��ع��ģ�
    *   @param[in]  master_handle   �������豸�����ͨ������ #master_open �õ�
    *   @param[in]  hash_algo       ��ϣ�㷨���ͣ��ο� #D2C_HASH_ALGO
    *   @param[in]  root_index      Virbox Root CA ��֤�����
    *   @param[in]  data_in         Ҫǩ��������
    *   @param[in]  data_len        Ҫǩ�����ݵĳ���
    *   @param[out] sign            ǩ���������
    *   @param[in]  max_sign_len    ǩ�����������ȣ�����Ϊ 256 + 64 �ֽ�
    *   @param[out] sign_len        ǩ�����ݳ���
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
    *   @remarks    sign ���� 256�ֽڵĿ�����ǩ��������� 64 �ֽڵĿ�������Ϣ�����ǰ 256 �ֽ�Ϊǩ������ 64 �ֽ�Ϊ��������Ϣ��
    */
    SS_UINT32 SSAPI d2c_sign(IN MASTER_HANDLE master_handle, D2C_HASH_ALGO hash_algo, IN SS_UINT32 root_index, IN SS_BYTE* data_in, IN SS_UINT32 data_len,
        OUT SS_BYTE* sign, IN SS_UINT32 max_sign_len, OUT SS_UINT32* sign_len);

    /*!
    *   @brief      D2C���� �������߲��ع��ģ�
    *   @param[in]  certs           ֤����
    *   @param[in]  certs_len       ����������
    *   @param[in]  plain           ����
    *   @param[in]  plain_len       ���ĳ���
    *   @param[out] cipher          ����
    *   @param[in]  max_cipher_len  ��������С
    *   @param[out] cipher_len      ���ĳ���
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
    */
    SS_UINT32 SSAPI d2c_encrypt(IN SS_BYTE* certs, IN SS_UINT32 certs_len, IN const SS_BYTE* plain, IN SS_UINT32 plain_len,
        OUT SS_BYTE* cipher, IN SS_UINT32 max_cipher_len, OUT SS_UINT32* cipher_len);

    /*!
    *   @brief      ��ȡ��Ƭ�������ӣ������߲��ع��ģ�
    *   @param[in]  master          �������豸�����ͨ������ #master_open �õ�
    *   @param[in]  license_id      ���ID
    *   @param[out] snippet_seed    ��Ƭ�������ӣ�32 �ֽڣ�
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
    */
    SS_UINT32 SSAPI get_snippet_seed(IN MASTER_HANDLE master, IN SS_UINT32 license_id, OUT SS_BYTE snippet_seed[SNIPPET_SEED_LENGTH]);

    /*!
    *   @brief      ������Ƭ���루�����߲��ع��ģ�
    *   @param[in]  master              �������豸�����ͨ������ #master_open �õ�
    *   @param[in]  license_id          �󶨵����ID
    *   @param[in]  evx_code            ִ�е�ԭʼ�ļ�
    *   @param[in]  evx_size            ִ���ļ��Ĵ�С
    *   @param[out] snippet_code        ������ɵ���Ƭ����Ļ�����
    *   @param[in]  snippet_buf_size    ������ snippet_code �Ĵ�С
    *   @param[out] snippet_size        ���ɵ���Ƭ����Ĵ�С
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
    */
    SS_UINT32 SSAPI gen_snippet_code(IN MASTER_HANDLE master, IN SS_UINT32 license_id, IN const SS_BYTE* evx_code, IN SS_UINT32 evx_size,
        OUT SS_BYTE* snippet_code, IN SS_UINT32 snippet_buf_size, OUT SS_UINT32* snippet_size);
    
    /*!
    *   @brief      ��ȡ������Ƭ�������󣨿����߲��ع��ģ�
    *   @param[in]  sc_ctx          ��Ƭ����������
    *   @param[in]  evx             ִ�д���ԭ��
    *   @param[in]  evx_size        ִ�д���ԭ�Ĵ�С
    *   @param[out] snippet_code    ��Ƭ���뻺����
    *   @param[in]  snippet_bufsize ��Ƭ���뻺������С
    *   @param[out] snippet_size   ��Ƭ�����С
    *   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
    */
    SS_UINT32 SSAPI gen_snippet_code_with_key(IN const SNIPPET_CODE_CONTEXT* sc_ctx, IN const SS_BYTE* evx, IN SS_UINT32 evx_size,
        OUT SS_BYTE* snippet_code, IN SS_UINT32 snippet_bufsize, OUT SS_UINT32* snippet_size);

    /*!
    *   @brief      ʹ�ÿ�����������ɼ��ܣ������߲��ع��ģ�
    *   @param[in]  master      �������豸�����ͨ������ #master_open �õ�
    *   @param[in]  license_id  ���ID
    *   @param[in]  plain       ����
    *   @param[in]  len         ���ܳ��ȣ�������16�ı�����
    *   @param[out] cipher      ����
    *   @return     �ɹ����� SS_OK ��ʧ���򷵻���Ӧ�Ĵ�����
    */
    SS_UINT32 SSAPI license_encrypt(IN MASTER_HANDLE master, IN SS_UINT32 license_id, IN const SS_BYTE* plain, IN SS_UINT32 len, OUT SS_BYTE* cipher);

#ifdef __cplusplus
}
#endif

/**
*   @} 
*/

#endif  //  _D2C_H
