/** 
*   @file	   ss_lm_control.h
*   @brief     ��˼Control API ���ڲ�ѯ��ɣ���ѯ�������Ȳ���.
*              ��Ӧ��̬��: slm_control.dll
*              ��Ӧ��̬��: slm_control_api.lib
*
*   ö������SS���豸�������ŵȲ���������˳������:
*
*       ��һ����ͨ������slm_client_open��IPC���
*       �ڶ�����ͨ������slm_ctrl_get_all_description��slm_get_cloud_description�Ⱥ�������ȡ�豸��������������
*       ����������������API����ȡ���������Ϣ
*       ���Ĳ�������slm_client_close�ر�IPC��������ý���
*
*   @version   2.1.0
*   @date      2014-2017
*
*/
#ifndef _H_DEF_SLM_CONTROL_API_
#define _H_DEF_SLM_CONTROL_API_

#include "ss_define.h"

#ifdef  _MSC_VER
#pragma comment(linker, "/defaultlib:setupapi.lib")
#elif defined __WATCOMC__
#pragma library("\watcom\lib386\nt\setupapi.lib")
#endif

#if _MSC_VER >= 1900   // 1900��VS2015�İ汾�ţ������̬����VS2015�±���ʧ�ܵ�����
#pragma comment(linker, "/defaultlib:legacy_stdio_definitions.lib")
#endif  // MSC_VER

#ifndef __SS_LM_RUMTIME_H__
/** ��ʱ���޸�ʱ���������󳤶� */
#define SLM_FIXTIME_RAND_LENGTH     8
#endif

/** Ӳ����������ɫ����ɫ */
#define SLM_CTRL_LED_COLOR_BLUE      0
/** Ӳ����������ɫ����ɫ */
#define SLM_CTRL_LED_COLOR_RED       1

/** Ӳ�������ƿ��ƣ��ر� */
#define SLM_CTRL_LED_STATE_CLOSE     0
/** Ӳ�������ƿ��ƣ��� */
#define SLM_CTRL_LED_STATE_OPEN      1
/** Ӳ�������ƿ��ƣ���˸ */
#define SLM_CTRL_LED_STATE_SHRINK    2

/** ������������ַ��󳤶� */
#define SLM_CTRL_MAX_CLOUD_SERVER_LENGTH    100
/** �����û�token��󳤶� */
#define SLM_CTRL_MAX_ACCESS_TOKEN_LENGTH    64

/** ��Ȩ�����󳤶� */
#define SLM_SLOCK_LICKEY_LENGTH             32

/** �������߽��c2d��������С���� */
#define SLM_SLOCK_OFFLINE_UNBIND_C2D_BUF_LENGTH    4096

/** Ӳ�������ƿ��ƽṹ */
typedef struct _ST_LOCK_LED_CONTROL {
    /**  0��ʾ��ɫLED��1��ʾ��ɫLED  */
    SS_UINT32   index;
    /**  0 = �رգ�1 = �򿪣� 2 = ��˸ */
    SS_UINT32   state;
    /**  ��������룩 */
    SS_UINT32   interval;
} ST_LOCK_LED_CONTROL;


/** ��Ȩ����ɵ�״̬ */
typedef enum _ENUM_LICENSE_KEY_STATUS
{
    /** δ֪ */
    ENUM_LICENSE_KEY_UNKNOW = 0,
    /** ���� */
    ENUM_LICENSE_KEY_NORMAL = 1,
    /** ��������и��� */ 
    ENUM_LICENSE_KEY_UPDATE = 2,
    /** �������ɾ�� */ 
    ENUM_LICENSE_KEY_DELETE = 3, 
    /** ������̽��� */ 
    ENUM_LICENSE_KEY_FORBID = 4,
    /** ��Ч(�����ڸ���Ȩ��) */ 
    ENUM_LICENSE_KEY_INVALID = 5,
    /** �Ѿ������ */
    ENUM_LICENSE_KEY_DEVICE_UNBIND = 6,
    /** �Ѿ���ǿ�ƻ��� */
    ENUM_LICENSE_KEY_FORCED_RECYCLING = 7,
    /** ��Ȩ�뼴�����ڣ���Ҫִ��ˢ�� */
    ENUM_LICENSE_KEY_STATUS_NEED_REFRESH = 100,
}ENUM_LICENSE_KEY_STATUS;

typedef enum
{
    SLM_ENUM_SLOCK_TYPE_ACCOUNT = 0,
    SLM_ENUM_SLOCK_TYPE_LICENSE_KEY = 1,
    SLM_ENUM_SLOCK_TYPE_BORROW_KEY = 2,
    SLM_ENUM_SLOCK_TYPE_LICKEY_TRAIL = 3
}SLM_ENUM_SLOCK_TYPE;

/** 
*   @defgroup ControlAPI  Virbox Control �ӿ�˵��
*   ���ĵ��� Virbox Control API ˵���ĵ���������������Ϣ��ѯ�������Ϣö�٣��Ự��������ɹ���ȹ���
*   @{
*/
#ifdef __cplusplus
extern "C" {
#endif

/*!
*   @brief      �ͻ��˴� IPC������� Virbox��ɷ��� ����ͨ��
*   @param[out] ipc      ����IPC���
*   @return     �ɹ����� SS_OK��ʧ�ܷ�����Ӧ�Ĵ�����
*   @remarks    #slm_ctrl_client_open �� @link ControlAPI @endlink ���ȵ��õ�һ���ӿڣ����ڴ��� Virbox��ɷ��� �� IPC ͨ�Źܵ�
*               ������ Virbox��ɷ��� �����Ĳ���������Ҫ���ȴ� IPC��
*/
SS_UINT32 SSAPI slm_ctrl_client_open(OUT void** ipc);

/*!
*   @brief      �رտͻ���IPC���
*   @param[in]  ipc     IPC�����ͨ�� #slm_ctrl_client_open ���
*   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
*   @remarks    IPC ��ʹ����Ϻ󣬱���Ҫ�رգ�����������Դ�˷ѡ��ڴ�й¶�����⡣
*   @see        slm_ctrl_client_open
*/
SS_UINT32 SSAPI slm_ctrl_client_close(IN void* ipc);

/*!
*   @brief      ��ȡ����Ӳ�����豸����
*   @param[in]  ipc             IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  format_type     �������ͣ� #JSON )
*   @param[out] desc            �豸������json���飬��Ҫ���� #slm_ctrl_free �ͷ�
*   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ������
*   @remarks    ÿһ��Ӳ������������Ӧ���豸�������豸����Ҳ�ǲ���Ӳ�����豸��Ϊ�ؼ��Ĳ�����������Ҫ�����йصĽ�����
*               ����Ҫ�������Ӧ���豸������
*   @code
*      - desc json��ʽ(json����)
*       [
*           {
*               "developer_id":"xxxxxxxxxxxxxxxx",
*               "sn":"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
*               "type":"local/remote/cloud",
*               "host_name":"xx-PC",
*               "lm":"pub"
*           }
*       ]
*
*       //Sample
*       {
*           SS_UINT32 status = SS_OK;
*           void *ipc = 0;
*           char *desc = 0;
*           
*           // 1����ipc
*           status = slm_ctrl_client_open(&ipc);
*           if (status != SS_OK)
*           {
*               //todo: deal error code!
*               return status;
*           }
*           // 2����ȡ�豸����
*           status = slm_ctrl_get_all_description(ipc, JSON, &desc);
*           if (status == SS_OK && desc)
*           {
*               // json�Ľ���ʹ�õ�����json�⣺jsoncpp (��ͬ��������ַ��https://github.com/open-source-parsers/jsoncpp)
*               Json::Value  root;
*               Json::Reader reader;
*               
*               reader.parse(desc, root);
*               
*               for (int index = 0; index != root.size(); ++index)
*               {
*                   puts("--------------------------------------------------");
*                   printf(root[index].toStyledString().c_str());
*                   //ͨ���õ����豸��������ִ����������
*                   //... ... 
*               }
*               slm_ctrl_free(desc);
*           }
*           else
*           {
*               //todo: error code!
*           }
*           // 3���ر�ipc
*           slm_ctrl_client_close(ipc);
*           return status;
*       }
*   @endcode
*   @see        slm_ctrl_client_open
*/
SS_UINT32 SSAPI slm_ctrl_get_all_description(
    IN  void*       ipc,
    IN  INFO_FORMAT_TYPE format_type,
    OUT char**      desc
    );


/*!
*   @brief      ��ȡ��������
*   @param[in]  ipc             IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  access_token    �û� token
*   @param[in]  user_guid       �û��� GUID(��ѡ��
*   @param[out] descriptions    ����������Ϣ( json ���飬����ѡ�����е�һ��������ɲ�ѯ������Ҫ���� #slm_ctrl_free �ͷ�
*   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ������
*   @remarks    ����������������˵�ǵ�ǰ�˻�����˼��ƽ̨�ϵ�һЩ������Ϣ���˻����ܶ�Ӧ���������ߣ���˵�ǰ�˻���ȡ�����������������ж��������ID������
*   @code
*     - description json����
*       [
*           {
*               "developer_id":"0300000000000006",    // ������ID
*               "type":"cloud",                       // ����Ϊ����
*               "lm":"pub",                           
*               "access_token":"667751ce-eeda-44a3-8add-dee83e218228"   
*           },
*           ... ...
*       ]
*   @endcode
*   @see        slm_ctrl_client_open
*/
SS_UINT32 SSAPI slm_ctrl_get_cloud_description(
    IN  void*               ipc,
    IN  const SS_CHAR*      access_token,
    IN  const SS_CHAR*      user_guid,
    OUT SS_CHAR**           descriptions
    );

/*!
*   @brief      ��ȡ�����豸����
*   @param[in]  ipc             IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  format_type     ��������( #JSON )
*   @param[out] desc            �豸������json���飬��Ҫ���� #slm_ctrl_free �ͷ�
*   @return     �ɹ�����SS_OK��ʧ�ܷ�����Ӧ������
*   @remarks    Ӳ�����б����������������֣���ȡ�����豸����ΪӲ�����豸������ȡ��ʽ��һ�֣���Ϊ��ȷ��ֻ��ȡ��������Ӳ����������
*               ���÷�ʽ�ο� #slm_ctrl_get_all_description ���� desc ����Ҳһ��
*   @see        slm_ctrl_client_open slm_ctrl_get_all_description
*/
SS_UINT32 SSAPI slm_ctrl_get_local_description(
    IN  void*       ipc,
    IN  INFO_FORMAT_TYPE format_type,
    OUT char**      desc
    );


/*!
*   @brief      ��ȡ�����豸����
*   @param[in]  ipc             IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  format_type     ��������( #JSON )
*   @param[out] desc            �豸������json ���飬��Ҫ���� #slm_ctrl_free �ͷ�
*   @return     �ɹ�����SS_OK��ʧ�ܷ�����Ӧ������
*   @remarks    ͬ #slm_ctrl_get_all_description �� #slm_ctrl_get_local_description ��ֻ��ȡ����Ӳ�����豸������
*               ���÷�ʽ�ο� #slm_ctrl_get_all_description���� desc ����Ҳһ��
*   @see        slm_ctrl_client_open slm_ctrl_get_all_description
*/
SS_UINT32 SSAPI slm_ctrl_get_remote_description(
    IN  void*       ipc,
    IN  INFO_FORMAT_TYPE format_type,
    OUT char**      desc
    );


/*!
*   @brief      ��ȡָ���豸�����µ��������ID
*   @param[in]  ipc     IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  type    ��������( #JSON )
*   @param[in]  desc    �豸������ͨ�� #slm_ctrl_get_all_description �Ⱥ�����õ��豸�����У�ȡ������Ҫ���������ݽ��в�ѯ
*   @param[out] result  ���ID��json���飬��Ҫ���� #slm_ctrl_free �ͷ�
*   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
*   @remarks    ��ǰ�ӿڿ��Լ򵥵ĵõ�ָ���豸�е����ID�б�����ͳ��ָ���豸�е���ɸ�����
*   @code
*     - ���ID json�ṹ
*       [1,2,3,4]
*   @endcode
*   @see    slm_ctrl_client_open slm_ctrl_get_all_description
*/
SS_UINT32 SSAPI slm_ctrl_get_license_id(
    IN  void *              ipc,
    IN  INFO_FORMAT_TYPE    type,
    IN  const char*         desc,
    OUT char**              result
    );

/*!
*   @brief      ��ȡָ�����Ϳ�����ID�µ����������Ϣ
*   @param[in]  ipc         IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  type        ��������( #JSON ��
*   @param[in]  desc        �豸������ͨ�� #slm_ctrl_get_all_description �Ⱥ�����õ��豸�����У�ȡ������Ҫ���������ݽ��в�ѯ
*   @param[out] result      �����Ϣ����Ҫ���� #slm_ctrl_free �ͷ�
*   @return     �ɹ�����SS_OK�����򷵻���Ӧ�Ĵ�����
*   @remarks    �����ߵ��ô˽ӿ�����ȡָ���豸�С�������ɵ���ϸ��Ϣ������ֵ��ϸ�������˵�ǰ��ɵĲ�Ʒ��Ϣ��������������ǰ״̬���Ƿ���á����ڡ��������ڡ������þ�������Ϣ
*   @code
*     - �����Ϣ json�ṹ
*       [
*         {
*             "license_id": 1405608497, 
*             "enable" : true / false, 
*             "start_time" : 1405608497,
*             "end_time" : 1405608497, 
*             "first_use_time" : 1405608497, 
*             "span_time" : 23234234, 
*             "counter" : 25, 
*             "concurrent" : 123, 
*             "concurrent_type" : 
*             "win_user_session"��Windows�û��Ự�� / "process"�����̣�, 
*             "version" : 342512, 
*             "last_update_timestamp": 42342525, 
*             "last_update_timesn":2342 ,
*             "lock_time" : 23542532    //��ɱ�������ʱ��
*             "lic_status":
*                 {
*                     "status":0/1/2/4,    // 0����������� 1����ɼ������ڣ� 2������ѹ��ڣ� 4����ɴ����þ�
*                     "message":"NORMAL/WILL EXPIRE/EXPIRE/USE UP"     // ���״̬����
*                 }
*         },
*         ... ... 
*       ]
*
*       //Sample
*       {
*           SS_UINT32 status = SS_OK;
*           char *desc = 0;
*           void *ipc = 0;
*           char *lic;
*
*           // 1����ipc���ο�slm_client_open
*           // 2����ȡ�豸�������ο�slm_ctrl_get_all_description�Ⱥ���
*           // 3����ȡ�������
*           status = slm_ctrl_read_brief_license_context(ipc, JSON, description.c_str(), &lic);
*           if (status == SS_OK)
*           {
*               Json::Value json_license;
*               Json::Reader reader;
*
*               reader.parse(lic, json_license);
*
*               for (int index = 0; index != json_license.size(); ++index)
*               {
*                   puts("--------------------------------------------------");
*                   printf(json_license[index].toStyledString().c_str());
*               }
*               slm_ctrl_free(lic);
*           }
*           // 4���ر�ipc
*           slm_ctrl_client_close(ipc);
*       }
*   @endcode
*   @see slm_ctrl_client_open slm_ctrl_get_all_description
*/
SS_UINT32  SSAPI slm_ctrl_read_brief_license_context(
    IN  void                 *ipc,
    IN  INFO_FORMAT_TYPE     type,
    IN  const char           *desc,
    OUT char                 **result
    );

/*!
*   @brief      ��ȡ��������С
*   @param[in]  ipc             IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  license_id      ���ID
*   @param[in]  desc            �豸������ͨ�� #slm_ctrl_get_all_description �Ⱥ�����õ��豸�����У�ȡ������Ҫ���������ݽ��в�ѯ
*   @param[out] len             ���ع������Ĵ�С
*   @return     �ɹ����� SS_OK �����򷵻���Ӧ�Ĵ�����
*   @remarks    ͨ���˽ӿڿ��Ի�ȡ��ָ���豸�С�ָ����ɵĹ�������С����������������ο�����ĵ��е�������
*   @see        slm_ctrl_read_pub_data slm_ctrl_get_all_description
*/
SS_UINT32 SSAPI slm_ctrl_get_pub_size(
    IN  void*           ipc,
    IN  SS_UINT32       license_id,
    IN  const char*     desc,
    OUT SS_UINT32*      len
    );

/*!
*   @brief      ��ȡ�û���������
*   @param[in]  ipc          IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  license_id   ���ID
*   @param[in]  desc         �豸����
*   @param[out] readbuf      ��ȡ�Ļ�����
*   @param[in]  offset       ��ȡ��ƫ��
*   @param[in]  len          ��ȡ�ĳ���
*   @return     �ɹ����� SS_OK �����򷵻���Ӧ�Ĵ�����
*   @remarks    ͨ���˽ӿ�����ȡ��ɹ��������ݣ���������Сͨ�� #slm_ctrl_get_pub_size ��ȡ����ȡ���Ȳ�Ӧ�ó��� #slm_ctrl_get_pub_size ��ȡ�������ݴ�С��
*               ��ϸ���Ϳɲο�����ĵ���
*   @code
*       {
*           void *ipc;
*           SS_UINT32 size = 0;
*           SS_BYTE   *buff = 0;
*           SS_UINT32 status = SS_OK;
*           SS_UINT32 license_id = 1;   // ��Ҫ��ȡ�����������ID
*           char *desc;
*
*           // 1����IPC
*           status = slm_ctrl_client_open(&ipc);
*           if (status != SS_OK)
*           {
*               //todo: deal error code!
*               return status;
*           }
*
*           // 2����ȡ�豸��������ο� slm_ctrl_get_all_description�е�ʾ��
*
*           // 3����ȡ��������С����������
*           status = slm_ctrl_get_pub_size(ipc, license_id, desc, &size);   // ��ȡָ����ɵĹ���������
*           if (status == SS_OK && size > 0)
*           {
*               buff = (SS_BYTE *)calloc(sizeof(SS_BYTE), size);
*               status = slm_user_data_read(slm_handle, license_id, desc, buff, 0, size);
*               if(status != SS_OK)
*               {
*                   // todo: deal error code
*               }
*               // ���ڴ˴����ȡ���Ĺ���������
*
*               free(buff);
*               buff = 0;
*           }
*           // 4���ر�IPC���
*           slm_ctrl_client_close(ipc);
*       }
*   @endcode
*   @see        slm_ctrl_client_open slm_ctrl_read_pub_data slm_ctrl_get_all_description
*/
SS_UINT32 SSAPI slm_ctrl_read_pub_data(
    IN  void*           ipc,
    IN  SS_UINT32       license_id,
    IN  const char*     desc,       //  �豸����
    OUT SS_BYTE*        readbuf,
    IN  SS_UINT32       offset,
    IN  SS_UINT32       len
    );

/*!
*   @brief      ��������ϸ��Ϣ
*   @param[in]  ipc         IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  type        ��������( #JSON )
*   @param[in]  license_id  ���ID
*   @param[in]  desc        �豸������ͨ�� #slm_ctrl_get_all_description �Ⱥ�����õ��豸�����У�ȡ������Ҫ���������ݽ��в�ѯ
*   @param[out] result      �������ݵ�ָ�룬��Ҫ���� #slm_ctrl_free �ͷ�
*   @return     �ɹ����� SS_OK�����򷵻���Ӧ�Ĵ�����
*   @remarks    �˽ӿ����� #slm_ctrl_read_brief_license_context ��ֻ��ǰ�߻�ȡ��ָ���豸��������ɵ����ݣ��˽ӿڷ��ص���ָ���豸��ָ����ɵ������ϸ��Ϣ��
*               ���÷�ʽ�ο� #slm_ctrl_read_brief_license_context ���� result �����ṹ��ͬ��
*/
SS_UINT32 SSAPI slm_ctrl_read_license_context(
    IN  void                *ipc,
    IN  INFO_FORMAT_TYPE    type,
    IN  SS_UINT32           license_id,
    IN  const char          *desc,
    OUT char                **result
    );

/*!
*   @brief      ��ȡ��������ĳ��������ID�µ�����session��Ϣ
*   @param[in]  ipc     IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  type    �������� ( #JSON )
*   @param[in]  desc    �豸��������ͨ�� #slm_ctrl_get_all_description �Ⱥ�����õ��豸�����У�ȡ������Ҫ���������ݽ��в�ѯ
*   @param[out] result  ��ȡ����Ļ�����
*   @return     �ɹ����� SS_OK �����򷵻���Ӧ�Ĵ�����
*   @remarks    ��ȡָ���豸�µ����лỰ��Ϣ���Ự��Ϣ��ָӦ�ó���ͨ�� @link Vribox RuntimeAPI @endlink ����ü����������ʱ��������ʱ�Ự���ûغϱ�����Ӧ�ó����������֮��
*               �໥ͨ�ŵ�һЩ��Ҫ��Ϣ��ͨ���˽ӿڿ��Ի�ȡ��ָ���豸��������ɶ�Ӧ��Ӧ�ó���ĻỰ��Ϣ��������Ҳ����ͨ���˽ӿڻ�ȡ���Ľ��������
*               #slm_ctrl_kick_session �ӿ�������ǰ�豸�еĻỰ��
*               һ��Ӧ�ó���ǳ���ɣ���Ự��ǿ���߳����Ự��Ϣ����ʧЧ��
*   @code
*   - ���� json ʾ����
*       [{
*           "license_id": 1,
		    "concurrent_type":	"process",       // ���Ϊ�������ʱ�д˲���
		    "curr_concurrent":	1,               // ��ɵ�ǰ����������concurrent_type�������
*           "sessions": 
*               [{
*                   "session_id": 1, 
*                   "max_concurrent": 5000,
*                   "process_name": "notepad.exe", 
*                   "process_id": 5234, 
*                   "win_session_id": 1, 
*                   "computer_name": "ABC-PC"
				    "license_id":	1,
				    "ip":	"127.0.0.1",
				    "time_stamp":	1234567890
*               },
*               ... ...
*               ]
*       },{
*           "license_id": 2, 
*           "sessions": 
*               [{
*                   "session_id": 2, 
*                   "max_concurrent": 5000,
*                   "process_name": "calc.exe", 
*                   "process_id": 2346, 
*                   "win_session_id": 1, 
*                   "computer_name": "DEF-PC"
				    "license_id":	2,
				    "ip":	"127.0.0.1",
				    "time_stamp":	1234567890
*               },
*               ... ...
*               ]
*       }]
*   @endcode
*   @see    slm_ctrl_client_open slm_ctrl_get_all_description
*/
SS_UINT32  SSAPI slm_ctrl_read_session_context(
    IN  void*               ipc,
    IN  INFO_FORMAT_TYPE    type,
    IN  const char*         desc,
    OUT char**              result
    );

/*!
*   @brief      �߳�ָ������ɻỰ
*   @param[in]  ipc     IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  desc    �豸��������ͨ�� #slm_ctrl_get_all_description �Ⱥ�����õ��豸�����У�ȡ������Ҫ���������ݽ��в�ѯ
*   @param[in]  session_id Ҫ�߳��� session ID
*   @return     �ɹ�����SS_OK��ʧ�ܷ�����Ӧ�Ĵ�����
*   @remarks    ͨ�� #slm_ctrl_read_session_context ��ȡ�� session_id��ͨ�� session_id ������Ӧ�ĻỰ���й���
*   @see        slm_ctrl_client_open slm_ctrl_get_all_description slm_ctrl_read_session_context
*/
SS_UINT32 SSAPI slm_ctrl_kick_session(
    IN  void*       ipc,
    IN  const char* desc,
    IN  SS_UINT32   session_id
    );

/*!
*   @brief      �����������������ʷ��¼��ֻ֧��Ӳ������
*   @param[in]  ipc     IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  desc    �豸��������ͨ�� #slm_ctrl_get_all_description �Ⱥ�����õ��豸�����У�ȡ������Ҫ���������ݽ��в�ѯ
*   @remarks    �˲�������������������¼����ʧЧ�����������ܻ����¿��á�Ҫ����ʹ�ã�
*/
SS_UINT32 SSAPI slm_ctrl_clear_history(
    IN  void*       ipc,
    IN  const char* desc
    );


/*!
*   @brief      ���Ӳ����������Ϣ��ֻ֧��Ӳ������
*   @param[in]  ipc     IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  desc    �豸��������ͨ�� #slm_ctrl_get_all_description �Ⱥ�����õ��豸�����У�ȡ������Ҫ���������ݽ��в�ѯ
*   @param[in]  result  �������ݵ�ָ�룬�ṹΪjson���飬��Ҫ���� #slm_ctrl_free �ͷ�
*   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ������ 
*   @remarks    ��ȡӲ�����豸��Ϣ����Ҫ��ȡ����ʱ�䡢���ڴ洢�ռ���Ϣ���̼��汾���������ڵ����ݣ����ڶ�Ӳ�������й���
*   @code
*   - json �ֶ�˵����
*       -# "clock":1497927112,                  // ����ʱ�䣨UTC��
*       -# "available_space":476160,            // ���ڿ��ÿռ�
*       -# "total_space":524288,                // �����ܿռ��С
*       -# "communication_protocol":2,          // ͨѸЭ��
*       -# "lock_firmware_version":"3.1.6",     // ���̼��汾
*       -# "lm_firmware_version":"2.10.2.1",    // Entry�汾
*       -# "h5_device_type":0,                  // Ӳ�������ͣ�0�����澫��5Ӳ������2������5ʱ����
*       -# "power_drop_times",                  // ����5ʱ�������У���ʾ�������
*       -# "clock_type",                        // ����ʱ�����ͣ�0��ʾ����ʱ�ӣ�2��ʾӲ��ʱ��
*       -# "device_model":"e5",                 // �豸�ͺ�
*       -# "hardware_version":"0.0.2.0",        // Ӳ���汾��
*       -# "manufacture_date":"2016-01-25 17:11:05",        // ��������
*       -# "lock_sn":"9733c801000702051061000300xxxxxx",    // Ӳ����оƬ��
*       -# "slave_addr":238,                    // Ӳ�������ڵ��豸���ߵ�ַ
*       -# "shell_num":"099900000054",          // Ӳ������Ǻ�
*       -# "user_info":"string",                // �û���Ϣ���ɺ��ԣ�
*       -# "inner_info":"string"                // �ڲ���Ϣ���ɺ��ԣ�
*   @endcode
*/
SS_UINT32  SSAPI slm_ctrl_get_device_info(
    IN  void*           ipc,
    IN  const char*     desc,
    OUT char**          result
    );

/*!
*   @brief      ��Ӳ������ȡʱ��У׼����ֻ֧��Ӳ������
*   @param[in]  ipc         IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  desc        �豸��������ͨ�� #slm_ctrl_get_all_description �Ⱥ�����õ��豸�����У�ȡ������Ҫ���������ݽ��в�ѯ
*   @param[out] rand        �����
*   @param[out] lock_time   �����豸ʱ��
*   @param[inout] pc_time  �����UTCʱ��
*   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
*/
SS_UINT32 SSAPI slm_ctrl_adjust_time_request(
    IN  void*               ipc,
    IN  const char*         desc,
    OUT SS_BYTE             rand[SLM_FIXTIME_RAND_LENGTH],
    OUT SS_UINT32*          lock_time,
    IN OUT SS_UINT32*       pc_time
    );
/*!
*   @brief      ���Ӳ�������ļ���Ϣ��ֻ֧��Ӳ������
*   @param[in]  ipc     IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  desc    �豸��������ͨ�� #slm_ctrl_get_all_description �Ⱥ�����õ��豸�����У�ȡ������Ҫ���������ݽ��в�ѯ
*   @param[in]  result  �������ݵ�ָ�룬�ṹΪjson���飬��Ҫ���� #slm_ctrl_free �ͷ�
*   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
*   @remarks    �˽ӿڿ��Ի�ȡ��Ӳ�������ļ�����Ϣ���ļ����� json �б���ʽչ�֣���Ҫ�����ļ������ļ����͡���С���޸�ʱ��
*               �����ݣ����ڿ���������͹��������ļ�������
*   @code
*   - json �ֶ�˵����
*       -# "validate"��number   ��־��Щ����Ч�����������ļ�������ʹ��
*       -# "type"��number       �ļ����ͣ������޸�
*       -# "privilege":number   �ļ�����Ȩ��
*       -# "size":number        �ļ���С
*       -# "time":number        �ļ��޸�ʱ��
*       -# "name":""            �ļ���  ��ǰ�ļ����Ƴ���16�ֽ�
*   @endcode
*/
SS_UINT32  SSAPI slm_ctrl_get_filelist_info(
	IN  void*            ipc,
	IN  const char*      desc,
	OUT char**           result
	);

/*!
*   @brief      ��ȡ��������֤��(��֧�ֱ��ؼ�����)
*   @param[in]  ipc         IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  desc        �豸��������ͨ�� #slm_ctrl_get_all_description �Ⱥ�����õ��豸�����У�ȡ������Ҫ���������ݽ��в�ѯ
*   @param[in]  cert_type   ֤�����ͣ��ο� #CERT_TYPE  
*   @param[out] cert        �豸֤�黺����
*   @param[in]  cert_size   ��������С
*   @param[out] cert_len    ���ص��豸֤���С
*   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
*   @remarks    ��ȡ�豸֤�飬�˴����豸ָӲ������������
*               ��� cert_type = #CERT_TYPE_DEVICE_CERT���书���� #slm_ctrl_get_device_cert ��ȫһ�£� 
*               ���Ϊ�������ͣ����֧��Ӳ������
*               ͨ���˽ӿڿ��Ի�ȡ�������ĸ�֤�顢�豸��CA ���豸������ϳ��豸֤������
*   @see        slm_ctrl_get_all_description slm_ctrl_get_device_cert
*/
SS_UINT32 SSAPI slm_ctrl_get_cert(
    IN  void*               ipc,
    IN  const char*         desc,
    IN  CERT_TYPE           cert_type,
    OUT SS_BYTE*            cert,
    IN  SS_UINT32           cert_size,
    OUT SS_UINT32*          cert_len
    );

/*!
*   @brief      ��ȡ���������豸֤�飨��ǰ֧��������Ӳ������
*   @param[in]  ipc         IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  desc        �豸��������ͨ�� #slm_ctrl_get_all_description �Ⱥ�����õ��豸�����У�ȡ������Ҫ���������ݽ��в�ѯ
*   @param[out] device_cert �豸֤�黺����
*   @param[in]  buff_size   ��������С
*   @param[out] return_size ���ص��豸֤���С
*   @return     �ɹ�����SS_OK��ʧ�ܷ�����Ӧ�Ĵ�����
*   @remarks    ��ȡ������֤�飬�˴��ļ�����ָӲ������������
*               ����豸Ϊ�����豸����ͨ���˽ӿڻ�ȡ���������Զ�����豸֤�飻��Ϊ�Ƕ����豸���˽ӿڿ�ֱ�ӻ�ȡ����˼�豸֤�顣
*               ���������������ڶ�����Ƕ������⡣
*               �ر�˵������˼�Ѳ���ͨ���κ������ṩ�����豸������ #slm_ctrl_get_device_cert �� #slm_ctrl_get_sense_device_cert �ӿڽ�Ϊ��֤�����ԡ�
*   @see
*/
SS_UINT32 SSAPI slm_ctrl_get_device_cert(
    IN  void*               ipc,
    IN  const char*         desc,
    OUT SS_BYTE*            device_cert,
    IN  SS_UINT32           buff_size,
    OUT SS_UINT32*          return_size
    );


/*!
*   @brief      ��ȡӲ��������˼�豸֤�飨������������֧�֣�
*   @param[in]  ipc         IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  desc        �豸��������ͨ�� #slm_ctrl_get_all_description �Ⱥ�����õ��豸�����У�ȡ������Ҫ���������ݽ��в�ѯ
*   @param[out] device_cert �豸֤�黺����
*   @param[in]  buff_size   ��������С
*   @param[out] return_size ���ص��豸֤���С
*   @return     �ɹ�����SS_OK��ʧ�ܷ�����Ӧ�Ĵ�����
*   @remarks    ͨ���˽ӿڿ���ֱ�ӻ�ȡ����˼���豸֤�飬�˽ӿ�����˼�����豸���У����豸Ϊ�����豸�� #slm_ctrl_get_device_cert ֻ�ܻ�ȡ���������Զ���֤�飬
*               ͨ���˽ӿڲ��ܻ�ȡ����˼�豸֤�顣
*               �ر�˵������˼�Ѳ���ͨ���κ������ṩ�����豸������ #slm_ctrl_get_device_cert �� #slm_ctrl_get_sense_device_cert �ӿڽ�Ϊ��֤�����ԡ�
*   @see
*/
SS_UINT32 SSAPI slm_ctrl_get_sense_device_cert(
    IN  void*               ipc,
    IN  const char*         desc,
    OUT SS_BYTE*            device_cert,
    IN  SS_UINT32           buff_size,
    OUT SS_UINT32*          return_size
    );


/*!
*   @brief      �豸������֤����֧��Ӳ������
*   @param[in]  ipc                 IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  desc                �豸��������ͨ�� #slm_ctrl_get_all_description �Ⱥ�����õ��豸�����У�ȡ������Ҫ���������ݽ��в�ѯ
*   @param[in]  verify_data         ��֤���ݣ��������ַ�"SENSELOCK"(9�ֽ�)��ͷ��
*   @param[in]  verify_data_size    ��֤���ݴ�С����С����Ϊ #SLM_VERIFY_DATA_SIZE (41)���ֽ�
*   @param[out] signature           ���ص�ǩ�����
*   @param[in]  signature_buf_size  ��������С
*   @param[out] signature_size      ǩ�������С
*   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
*   @remarks    ����ʹ���豸˽Կǩ������Ҫ��Ӳ����֤�鹫Կ��ǩ
*   @code
*       {
*           SS_UINT32       status = SS_OK;
*           SS_BYTE         verify_data[41] = {0};
*           SS_BYTE         my_data[32] = {"verify data..."};
*           const SS_BYTE   header[9] = {"SENSELOCK"};
*           SS_BYTE         signature[2048] = {0};
*           SS_UINT32       signature_size = 0;
*
*           ... ...
*
*           memcpy(verify_data, header, sizeof(header));
*           memcpy(verify_data + sizeof(header), my_data, sizeof(my_data));
*
*           status = slm_ctrl_sign_by_device(ipc, desc, verify_data, sizeof(verify_data), signature, sizeof(signature), &signature_size);
*           if(status != SS_OK)
*           {
*               // todo: deal error code
*           }
*           ... ...
*       }
*   @endcode
*   @see        slm_login
*/
SS_UINT32 SSAPI slm_ctrl_sign_by_device(
    IN  void*               ipc,
    IN  const char*         desc,
    IN  SS_BYTE*            verify_data,
    IN  SS_UINT32           verify_data_size,
    OUT SS_BYTE*            signature,
    IN  SS_UINT32           signature_buf_size,
    OUT SS_UINT32*          signature_size
    );

/*!
*   @brief      Ӳ�����豸ָʾ�ƿ���
*   @param[in]  ipc                 IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  desc                �豸��������ͨ�� #slm_ctrl_get_all_description �Ⱥ�����õ��豸�����У�ȡ������Ҫ���������ݽ��в�ѯ
*   @param[in]  led_ctrl            ���ƽṹ���ο� #ST_LOCK_LED_CONTROL
*   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ�Ĵ�����
*   @see        ST_LOCK_LED_CONTROL
*/
SS_UINT32 SSAPI slm_ctrl_led_control(
    IN  void*               ipc,
    IN  const char*         desc,
    IN  ST_LOCK_LED_CONTROL*     led_ctrl
    );

/*!
*   @brief      �ͷ�API���ɵĻ�����
*   @param[in]  buffer      API ���ɵĻ�����
*/
void SSAPI slm_ctrl_free(
    IN  void*   buffer
    );

/*!
*   @brief      ��ѯ������ɵİ�װ��Ϣ
*   @param[in]  ipc         IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  desc        �豸��������ͨ�� #slm_ctrl_get_all_description ��õ��豸�����У�ȡ������Ҫ���������ݽ��в�ѯ
*   @param[in]  license_id  ��Ҫ��ѯ�������ID
*   @param[out] result      ����ɰ�װ��Ϣ����Ҫ���� #slm_ctrl_free �ͷ�
*   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ������
*   @remarks
*   @code
*   [{
*       "pc_name":"SENSE-PC", 
*       "os":"Windows 10 Professional 64 Edition", 
*       "inet_ip": "123.45.23.23", 
*       "ip_mac":
*           [
*               {"ip":"192.168.1.1", "mac":"00-00-00-00-00-00"},
*               {"ip":"10.10.9.6", "mac":"11-11-11-11-11-11"}
*           ]
*    },{
*       "pc_name":"SENSE-PC", 
*       "os":"Windows 10 Professional 32 Edition", 
*       "inet_ip": "123.45.23.23", 
*       "ip_mac":
*           [
*               {"ip":"192.168.1.1", "mac":"00-00-00-00-00-00"},
*               {"ip":"10.10.9.6", "mac":"11-12-11-11-11-11"}
*           ]
*   }]
*   @endcode
*/
SS_UINT32 SSAPI slm_ctrl_query_bind_info(
    IN  void*           ipc,          
    IN  const char*     desc, 
    IN  SS_UINT32       license_id,
    OUT char**          result
    );

/*!
*   @brief      ���������
*   @param[in]  ipc         IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  desc        �豸��������ͨ�� #slm_ctrl_get_all_description ��õ��豸�����У�ȡ������Ҫ���������ݽ��в�ѯ(�������˺�������δ�󶨵�������Ϣ��
*   @param[in]  license_id  ��Ҫ�󶨵������ID
*   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ������
*/
SS_UINT32 SSAPI slm_ctrl_bind_offline_license(
    IN void*        ipc, 
    IN const char*  desc, 
    IN SS_UINT32    license_id
    );

/*!
*   @brief ö���Ѱ󶨵������豸�������������غ�Զ��
*   @param[in]  ipc     IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[out] desc    �������豸��������Ҫ���� #slm_ctrl_free �ͷ�
*   @return �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ������
*   @remarks
*   @code
*   - JSON �ֶ�˵����
*       -# "type":string                    ���������ͣ������ֵ�� slock �� smart_offline��ǰ�߱�ʾ���ص������豸�豸���������߱�ʾƽ̨�ϲ�ѯ������Ϣ
*       -# "user_guid":string               ������˺�����ɣ�����Ϊ�˺���ʮ�������ַ�����ʾ�� GUID���������Ȩ������ɣ�����Ϊ��Ȩ��� Ψһ����
*       -# "vclock":number                  ����������ʱ�� utc ʱ����
*       -# "slock_type":number              ���������͡������ֵ account ��ʾ�˻�������license key ��ʾ��Ȩ������
*       -# "account_name":string            �� slock_type=account ʱ�д��ֶΣ���ʾ��ǰ�������˻�����
*       -# "license_key":string             �� slock_type=license key ʱ�д��ֶΣ���ʾ��ǰ��������Ȩ��������Ϣ��������ǰ��8�ֽ����ݣ��м�8�ֽ��������أ�
*       -# "status":number                  �� slock_type=license key ʱ�д��ֶΣ���ʾ��ǰ������״̬���ο� ENUM_LICENSE_KEY_STATUS
*       -# "developer_id":string            ������ID
*       -# "delta_time":number              ����ʱ���뱾��ʱ���ʱ�������ж������Ч�ԣ���ǰ�������޷���ȷ�ж������Ч�ԣ�����ʹ�ã�
*
*     [
*       {"type":"slock", "user_guid":"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "vclock":12345678, "slock_type":"account", "account_name":"xxxx@sense.com.cn", "developer_id":"0300000000000009", "delta_time":0}
*       {"type":"slock", "user_guid":"SC000100000001", "vclock":12345678, "slock_type":"license key", "license_key":"1234-xxxx-xxxx-abcd", "status":0, "developer_id":"0300000000000009", "delta_time":0}
*     ]
*   @endcode
*/
SS_UINT32 SSAPI slm_ctrl_get_offline_desc(IN void* ipc, OUT char** desc);

/*!
*   @brief ö���Ѱ󶨵ı��������豸����
*   @param[in]  ipc     IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[out] desc    ���������豸��������Ҫ���� #slm_ctrl_free �ͷ�
*   @return �ɹ�����SS_OK��ʧ�ܷ�����Ӧ������
*/
SS_UINT32 SSAPI slm_ctrl_get_offline_local_desc(IN void* ipc, OUT char** desc);

/*!
*   @brief ö���Ѱ󶨵�Զ�������豸����
*   @param[in]  ipc     IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[out] desc    Զ�������豸��������Ҫ���� #slm_ctrl_free �ͷ�
*   @return �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ������
*/
SS_UINT32 SSAPI slm_ctrl_get_offline_remote_desc(IN void* ipc, OUT char** desc);

/*!
*   @brief      ����������
*   @param[in]  ipc         IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  desc        �����豸������ͨ�� #slm_ctrl_get_offline_desc ���
*   @param[in]  license_id  ��Ҫ���������ID
*   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ������
*/
SS_UINT32 SSAPI slm_ctrl_unbind_offline_license(IN void* ipc, IN const char* desc, IN SS_UINT32 license_id);

// -------------------
/*!
*   @brief      �����߼�����ϵ��ã���ȡ���߰�c2d��Ϣ
*   @param[in]  ipc             IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[out] bind_c2d        ���߰��õ�C2D��Ϣ
*   @param[in]  c2d_buf_size    C2D ��������С
*   @param[out] c2d_length      C2D ʵ�ʳ���
*   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ������
*/
SS_UINT32 SSAPI slm_ctrl_offline_bind_c2d(
    IN void         *ipc, 
    OUT SS_BYTE     *bind_c2d,
    IN SS_UINT32    c2d_buf_size,
    OUT SS_UINT32   *c2d_length);

/*!
*   @brief      �����߼�����ϵ��ã���ȡ���߽��c2d��Ϣ
*   @param[in]  ipc             IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  desc            �����豸������ͨ�� #slm_ctrl_get_offline_desc ���
*   @param[out] unbind_c2d      ���߰��õ�C2D��Ϣ
*   @param[in]  c2d_buf_size    C2D ��������С����С�� #SLM_SLOCK_OFFLINE_UNBIND_C2D_BUF_LENGTH ��
*   @param[out] c2d_length      C2D ʵ�ʳ���
*   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ������
*   @remarks    ���ýӿڻ��Ƚ�󱾵ص�������ɣ��ٷ��ؽ����ɵ�C2D��Ϣ��
*               ���ýӿڳɹ�ʱ������������ѽ���޷�ʹ�ã��û������������������C2D�ļ��ϴ�����ƽ̨�������ƽ̨�󶨼�¼����������ռ��һ��ͬʱ������
*               ���C2D���ݶ�ʧ���û����޷�ͨ��C2D�ļ�����ƽ̨�󶨼�¼��ֻ���ɿ����ߵ�¼��������վ����ǿ�ƽ�������
*/
SS_UINT32 SSAPI slm_ctrl_offline_unbind_c2d(
    IN void         *ipc, 
    IN const char   *desc, 
    IN SS_UINT32    license_id,    
    OUT SS_BYTE     *unbind_c2d,
    IN SS_UINT32    c2d_buf_size,
    OUT SS_UINT32   *c2d_length
    );

/*!
*   @brief      �����߼�����ϵ��ã����������������
*   @param[in]  ipc         IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  d2c         ����������ݵ� D2C��
*   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ������
*   @remarks    ���߻����ϵ��ã����������ߵĻ����ϵ��ô˽ӿڣ������Ѿ���ȡ�������� D2C�� �����ؼ����������
*/
SS_UINT32 SSAPI slm_ctrl_offline_bind_d2c(
    IN void         *ipc, 
    IN char         *d2c
    );

/*!
*   @brief      ������������ϵ��ã�����ƽ̨��ȡ�������������
*   @param[in]  ipc         IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  desc        �����豸������ͨ�� #slm_ctrl_get_offline_desc ���
*   @param[in]  license_id  Ҫ�󶨶����ID
*   @param[in]  bind_c2d    �� C2D ��Ϣ
*   @param[in]  c2d_length  C2D ����
*   @param[out] result      ����������ݵ� D2C������Ҫ���� #slm_ctrl_free �ͷ�
*   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ������
*   @remarks    �������Ļ����ϵ��ô˽ӿڣ��� C2D �ϴ�����ƽ̨��ͬʱ�һ������������������
*               result �ڲ���Ҫ��ʱ����Ҫ���� #slm_ctrl_free �ͷ���Դ
*/
SS_UINT32 SSAPI slm_ctrl_cloud_offline_get_d2c(
    IN  void            *ipc, 
    IN  const char      *desc,
    IN  SS_UINT32       license_id,
    IN  SS_BYTE         *bind_c2d, 
    IN  SS_UINT32       c2d_length,
    OUT char            **result
    );

/*!
*   @brief      ������������ϵ��ã�����ƽ̨����������
*   @param[in]  ipc             IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  user_guid       �ѵ�¼�û��� guid��ͨ�� #ss_user_login ���ȡ
*   @param[in]  unbind_c2d      ��� C2D ��Ϣ
*   @param[in]  c2d_length      C2D ����
*   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ������
*   @remarks    �˺���ͨ���������ж���ɽ���Ƿ�ɹ���SS_OK ��ʾ���ɹ���������ʾ���ʧ�ܡ�������ʧ�ܣ����� VirboxLM ���������� �����ֶ����
*/
SS_UINT32 SSAPI slm_ctrl_cloud_offline_unbind(
    IN  void            *ipc,
    IN  const char      *user_guid,
    IN  SS_BYTE         *unbind_c2d,
    IN  SS_UINT32       c2d_length
    );

/*!
*   @brief      ������������ϵ��ã����߰���Ȩ�����
*   @param[in]  ipc             IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  license_key     ��Ҫ�󶨵���Ȩ��
*   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ������
*   @remarks    �����̿��Ե��ô˽ӿڣ�������Ȩ�룬��ɷ����Զ�����ƽ̨�ж�Ӧ����Ȩ����ɰ󶨵�����
*/
SS_UINT32 SSAPI slm_ctrl_bind_license_key(
    IN void             * ipc, 
    IN const char       *license_key
    );

/*!
*   @brief      ������������ϵ��ã����߰���Ȩ����ɣ���ǰ�ӿ��� #slm_ctrl_bind_license_key ��չ����������֧�ִ������ ��Ȩ����� ��
*   @param[in]  ipc             IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  license_key     ��Ҫ�󶨵���Ȩ��
*   @param[in]  password        ��Ȩ������롣���Ҫ�󶨵���Ȩ�벻��Ҫ���룬���Դ� NULL���� ���ַ���
*   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ������
*   @remarks    �����̿��Ե��ô˽ӿڣ�������Ȩ�룬��ɷ����Զ�����ƽ̨�ж�Ӧ����Ȩ����ɰ󶨵�����
*/
SS_UINT32 SSAPI slm_ctrl_bind_license_key_with_psd(
    IN void             * ipc,
    IN const char       *license_key,
    IN const char       *password
    );

/*!
*   @brief      ˢ�µ�ǰ���������Ϣ
*   @param[in]  ipc             IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  desc            �������豸������ͨ�� #slm_ctrl_get_offline_desc ���
*   @param[in]  license_id      ���ID����ѡ��
*   @param[in]  license_key     ��Ȩ�루��ѡ��
*   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ������
*   @remarks    ����ǰ�������Ϊ�˺�����ɣ�����Ҫ����Ҫˢ�µ� ���ID������Ĭ��ˢ�� 0����ɣ����ܴﲻ���û�������Ŀ�ģ�
*               ����ǰ�������Ϊ��Ȩ������ɣ�����Դ�����Ҫˢ�µ���Ȩ�룬��������Ȩ�룬��Ĭ��ˢ�µ�ǰ�豸�����µ���Ȩ������ɡ�
*/
SS_UINT32 SSAPI slm_ctrl_slock_refresh_license(
    IN  void            *ipc,
    IN  char            *desc,
    IN  SS_UINT32       license_id,
    IN  char            *license_key
    );

/*!
*   @brief      ˢ�µ�ǰ���������Ϣ
*   @param[in]  ipc             IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  desc            �������豸������ͨ�� #slm_ctrl_get_offline_desc ���
*   @param[in]  license_id      ���ID����ѡ��
*   @param[in]  license_key     ��Ȩ�루��ѡ��
*   @param[in]  password        �����Ȩ��ʹ�ã���Ȩ������롣���Ҫ�󶨵���Ȩ�벻��Ҫ���룬���Դ� NULL���� ���ַ�������ѡ��
*   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ������
*   @remarks    ����ǰ�������Ϊ�˺�����ɣ�����Ҫ����Ҫˢ�µ� ���ID������Ĭ��ˢ�� 0����ɣ����ܴﲻ���û�������Ŀ�ģ�
*               ����ǰ�������Ϊ��Ȩ������ɣ�����Դ�����Ҫˢ�µ���Ȩ�룬��������Ȩ�룬��Ĭ��ˢ�µ�ǰ�豸�����µ���Ȩ������ɡ�
*/
SS_UINT32 SSAPI slm_ctrl_slock_refresh_license_with_psd(
    IN  void            *ipc,
    IN  char            *desc,
    IN  SS_UINT32       license_id,
    IN  char            *license_key,
    IN  const char      *password
    );
	
/*!
*   @brief      ����Ӳ������ɣ�D2C�� �� @link D2CAPI @endlink �� VirboxLM ���������� ����
*   @param[in]  d2c_pkg     d2c�ļ�����
*   @param[out] error_msg   ������Ϣ����Ҫ���� #slm_ctrl_free �ͷ�
*   @return     �ɹ����� SS_OK ��ʧ�ܷ��ش�����
*   @remarks:   D2C���ڿ��ܰ����������ݣ���˷��صĴ�������ϢҲ�� json ����ṹ����Ҫ�ֱ������
*               ˵������ǰ�ӿڽ�֧��Ӳ�����������������Ҫ��������ɣ������ #slm_ctrl_update_ex �ӿ�
*   @code
*     [
*       {"pkg_order":1, "pkg_desc":"package decription.", "status": 0},
*       {"pkg_order":2, "pkg_desc":"package decription.", "status": 0}
*     ]
*   @endcode
*/
SS_UINT32 SSAPI slm_ctrl_update(
    IN  char            *d2c_pkg, 
    OUT char            **error_msg
    );

/*!
*   @brief      �����ɿ������� VirboxLM ���������� ǩ����Ӳ�������������
*   @param[in]  lock_sn     Ӳ�������������ţ�Ψһ���к�,ʮ�������ַ�����ʽ������ѡ
*   @param[in]  d2c_pkg     d2c�ļ����ݣ�����
*   @param[out] error_msg   ������Ϣ����ʹ����Ҫ���� #slm_ctrl_free �ͷ�
*   @return     �ɹ����� SS_OK ��ʧ�ܷ��ش�����
*   @remarks:
*           - �˽ӿ�֧��Ӳ����������������ݵ�����
*           - ��������ΪӲ�������ʱ������ָ�� lock_sn���������Ч�ʣ�Ҳ�ɲ���д����������Ϊ�����ʱ��lock_sn ��ֵ����������
*           - ��������ΪӲ�������ʱ��D2C���ڿ��ܰ����������ݣ�ÿ���������Ĵ�����Ϣ���� json �ṹ��ʽͨ�� error_msg ���أ���Ҫ�ֱ����
*           - ��������Ϊ�������ʱ�������뽫ֱ���Է���ֵ��ʽ���أ�error_msg ����������
*   @code
*     error_msg �ṹ��
*     [
*       {"pkg_order":1, "pkg_desc":"package decription.", "status": 0},
*       {"pkg_order":2, "pkg_desc":"package decription.", "status": 0}
*     ]
*   @endcode
*   @see    slm_ctrl_update
*/
SS_UINT32 SSAPI slm_ctrl_update_ex(
    IN  SS_BYTE         *lock_sn, 
    IN  char            *d2c_pkg, 
    OUT char            **error_msg
    );

// ----------------------------------------

/*!
*   @brief      �����Ʒ����ַ
*   @param[in]  cloud_server_config    ���� URL(json �ṹ)
*               ���磺{"urls": {"cloud_runtime_url": "http://rt.senseyun.com","slock_url": "http://sl.senseyun.com","dl_url": "http://ll.senseyun.com"}}
*   @return     �ɹ�����SS_OK��ʧ�ܷ�����Ӧ������
*   @remarks    ��֧�ֶ��̵߳��ã���ʼ����ȫ����Ч���л�����ʱ�ɵ����߱�֤���߳����ݰ�ȫ��
*/
SS_UINT32 SSAPI slm_ctrl_init_cloud_server_config(IN const char *cloud_server_config);


// -----------------------------------------
// ����ͳһ�ӿ�
/*!
*   @brief      ���� slock_type ������������ɣ�slock_type �������˺����(�ݲ�֧�֣�����Ȩ�����(�ݲ�֧��)�����������
*   @param[in]  ipc             IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  slock_type      ����������ͣ�Ŀǰ��֧�� SLM_ENUM_SLOCK_TYPE_BORROW_KEY
*   @param[in]  param           �󶨲��������������ID����Ȩ�룬�����롣Ŀǰ��֧�� ������
*   @param[in]  param_length    �󶨲����ĳ��ȡ���������ID ��һ���� 4 �ֽڳ��ȣ��������Ȩ�룬һ���� 19 �ֽڳ��ȣ�����ս����룬һ���� 11 �ֽڳ���
*   @return     �ɹ����� SS_OK ��ʧ�ܷ��ش�����
*   @remarks:   
*               - ��ǰ�ӿ�ͳһ���������͵�����ɽӿڣ���ǰ��֧�ֽ��������
*               - ����������Ϊ�˺� (SLM_ENUM_SLOCK_TYPE_ACCOUNT) ʱ��Ҫ�󱾵��Ѿ���½�����˺ţ�Ȼ��ͨ���˽ӿڲ��� param �������ID ���ɰ�
*               - ����������Ϊ��Ȩ�� (SLM_ENUM_SLOCK_TYPE_LICENSE_KEY) ʱ��param ������Ҫ������Ȩ��
*               - ����������Ϊ��Ȩ�� (SLM_ENUM_SLOCK_TYPE_BORROW_KEY) ʱ��param ������Ҫ���������
*/
SS_UINT32 SSAPI slm_ctrl_slock_license_bind(
    IN void*        ipc,
    IN SS_UINT32    slock_type,
    IN void         *param,
    IN SS_UINT32    param_length
    );

/*!
*   @brief      ���߽�����������
*   @param[in]  ipc         IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  desc        �����豸������ͨ�� #slm_ctrl_get_offline_desc ���
*   @param[in]  license_id  ��Ҫ�������ID
*   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ������
*   @remarks    �������豸����Ϊ�˺�����ɵ�ʱ����Ҫ����ָ���� license_id ��Ϊ�����󣻵��豸����Ϊ�������ͣ�����Ȩ�룬������ȣ�ʱ�� license_id ���ᱻ����
*/
SS_UINT32 SSAPI slm_ctrl_slock_license_unbind(
    IN  void*        ipc,
    IN  const char   *desc,
    IN  SS_UINT32    license_id
    );

/*!
*   @brief      ����ˢ�����������
*   @param[in]  ipc         IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  desc        �����豸������ͨ�� #slm_ctrl_get_offline_desc ���
*   @param[in]  license_id  ��Ҫˢ�µ����ID
*   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ������
*   @remarks    �������豸����Ϊ�˺�����ɵ�ʱ����Ҫ����ָ���� license_id ��Ϊˢ�¶��󣻵��豸����Ϊ�������ͣ�����Ȩ�룬������ȣ�ʱ�� license_id ���ᱻ����
*/
SS_UINT32 SSAPI slm_ctrl_slock_license_refresh(
    IN  void*               ipc,
    IN  const char*         desc,
    IN  SS_UINT32           license_id
    );

/*!
*   @brief      ���߸�����Ȩ������������ɵ�״̬
*   @param[in]  ipc         IPC�����ͨ�� #slm_ctrl_client_open ���
*   @param[in]  desc        �����豸������ͨ�� #slm_ctrl_get_offline_desc ���
*   @param[in]  license_id  ��Ҫˢ�µ����ID
*   @return     �ɹ����� SS_OK ��ʧ�ܷ�����Ӧ������
*   @remarks    ��ǰ��֧����Ȩ��ͽ�������ɵ�״̬ˢ��
*/
SS_UINT32 SSAPI slm_ctrl_slock_license_query_status(
    IN  void                *ipc,
    IN  SS_UINT32           slock_type
    );

#ifdef __cplusplus
};
#endif //__cplusplus

/**
*   @}
*/



#endif //_H_DEF_SLM_CONTROL_API_
