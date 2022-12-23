/** 
*   @file	   ss_lm_control.h
*   @brief     深思Control API 用于查询许可，查询加密锁等操作.
*              对应动态库: slm_control.dll
*              对应静态库: slm_control_api.lib
*
*   枚举所有SS上设备描述符号等操作，调用顺序如下:
*
*       第一步、通过调用slm_client_open打开IPC句柄
*       第二步，通过调用slm_ctrl_get_all_description、slm_get_cloud_description等函数，获取设备描述、云锁描述
*       第三步、调用其他API，获取其他相关信息
*       第四步、调用slm_client_close关闭IPC句柄，调用结束
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

#if _MSC_VER >= 1900   // 1900是VS2015的版本号，解决静态库在VS2015下编译失败的问题
#pragma comment(linker, "/defaultlib:legacy_stdio_definitions.lib")
#endif  // MSC_VER

#ifndef __SS_LM_RUMTIME_H__
/** 锁时钟修复时随机数的最大长度 */
#define SLM_FIXTIME_RAND_LENGTH     8
#endif

/** 硬件锁闪灯颜色：蓝色 */
#define SLM_CTRL_LED_COLOR_BLUE      0
/** 硬件锁闪灯颜色：红色 */
#define SLM_CTRL_LED_COLOR_RED       1

/** 硬件锁闪灯控制：关闭 */
#define SLM_CTRL_LED_STATE_CLOSE     0
/** 硬件锁闪灯控制：打开 */
#define SLM_CTRL_LED_STATE_OPEN      1
/** 硬件锁闪灯控制：闪烁 */
#define SLM_CTRL_LED_STATE_SHRINK    2

/** 云锁服务器地址最大长度 */
#define SLM_CTRL_MAX_CLOUD_SERVER_LENGTH    100
/** 云锁用户token最大长度 */
#define SLM_CTRL_MAX_ACCESS_TOKEN_LENGTH    64

/** 授权码的最大长度 */
#define SLM_SLOCK_LICKEY_LENGTH             32

/** 软锁离线解绑c2d缓冲区最小长度 */
#define SLM_SLOCK_OFFLINE_UNBIND_C2D_BUF_LENGTH    4096

/** 硬件锁闪灯控制结构 */
typedef struct _ST_LOCK_LED_CONTROL {
    /**  0表示蓝色LED，1表示红色LED  */
    SS_UINT32   index;
    /**  0 = 关闭，1 = 打开， 2 = 闪烁 */
    SS_UINT32   state;
    /**  间隔（毫秒） */
    SS_UINT32   interval;
} ST_LOCK_LED_CONTROL;


/** 授权码许可的状态 */
typedef enum _ENUM_LICENSE_KEY_STATUS
{
    /** 未知 */
    ENUM_LICENSE_KEY_UNKNOW = 0,
    /** 正常 */
    ENUM_LICENSE_KEY_NORMAL = 1,
    /** 软件厂商有更新 */ 
    ENUM_LICENSE_KEY_UPDATE = 2,
    /** 软件厂商删除 */ 
    ENUM_LICENSE_KEY_DELETE = 3, 
    /** 软件厂商禁用 */ 
    ENUM_LICENSE_KEY_FORBID = 4,
    /** 无效(不存在该授权码) */ 
    ENUM_LICENSE_KEY_INVALID = 5,
    /** 已经被解绑 */
    ENUM_LICENSE_KEY_DEVICE_UNBIND = 6,
    /** 已经被强制回收 */
    ENUM_LICENSE_KEY_FORCED_RECYCLING = 7,
    /** 授权码即将过期，需要执行刷新 */
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
*   @defgroup ControlAPI  Virbox Control 接口说明
*   此文档是 Virbox Control API 说明文档，包含加密锁信息查询，许可信息枚举，会话管理，软许可管理等功能
*   @{
*/
#ifdef __cplusplus
extern "C" {
#endif

/*!
*   @brief      客户端打开 IPC句柄，与 Virbox许可服务 进行通信
*   @param[out] ipc      返回IPC句柄
*   @return     成功返回 SS_OK，失败返回相应的错误码
*   @remarks    #slm_ctrl_client_open 是 @link ControlAPI @endlink 最先调用的一个接口，由于打开与 Virbox许可服务 的 IPC 通信管道
*               所有与 Virbox许可服务 交互的操作，都需要率先打开 IPC。
*/
SS_UINT32 SSAPI slm_ctrl_client_open(OUT void** ipc);

/*!
*   @brief      关闭客户端IPC句柄
*   @param[in]  ipc     IPC句柄，通过 #slm_ctrl_client_open 获得
*   @return     成功返回 SS_OK ，失败返回相应的错误码
*   @remarks    IPC 打开使用完毕后，必须要关闭，否则会存在资源浪费、内存泄露等问题。
*   @see        slm_ctrl_client_open
*/
SS_UINT32 SSAPI slm_ctrl_client_close(IN void* ipc);

/*!
*   @brief      获取所有硬件锁设备描述
*   @param[in]  ipc             IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  format_type     参数类型（ #JSON )
*   @param[out] desc            设备描述，json数组，需要调用 #slm_ctrl_free 释放
*   @return     成功返回 SS_OK ，失败返回相应错误码
*   @remarks    每一个硬件锁都会有相应的设备描述，设备描述也是操作硬件锁设备最为关键的参数，凡是需要与所有关的交互，
*               都需要这把锁相应的设备描述。
*   @code
*      - desc json格式(json数组)
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
*           // 1、打开ipc
*           status = slm_ctrl_client_open(&ipc);
*           if (status != SS_OK)
*           {
*               //todo: deal error code!
*               return status;
*           }
*           // 2、获取设备描述
*           status = slm_ctrl_get_all_description(ipc, JSON, &desc);
*           if (status == SS_OK && desc)
*           {
*               // json的解析使用第三方json库：jsoncpp (下同，下载网址：https://github.com/open-source-parsers/jsoncpp)
*               Json::Value  root;
*               Json::Reader reader;
*               
*               reader.parse(desc, root);
*               
*               for (int index = 0; index != root.size(); ++index)
*               {
*                   puts("--------------------------------------------------");
*                   printf(root[index].toStyledString().c_str());
*                   //通过得到的设备描述可以执行其他操作
*                   //... ... 
*               }
*               slm_ctrl_free(desc);
*           }
*           else
*           {
*               //todo: error code!
*           }
*           // 3、关闭ipc
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
*   @brief      获取云锁描述
*   @param[in]  ipc             IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  access_token    用户 token
*   @param[in]  user_guid       用户的 GUID(可选）
*   @param[out] descriptions    云锁描述信息( json 数组，可以选择其中的一个进行许可查询），需要调用 #slm_ctrl_free 释放
*   @return     成功返回 SS_OK ，失败返回相应错误码
*   @remarks    云锁的描述，简单来说是当前账户在深思云平台上的一些基本信息，账户可能对应过个开发者，因此当前账户获取到的云锁描述可能有多个开发商ID等内容
*   @code
*     - description json内容
*       [
*           {
*               "developer_id":"0300000000000006",    // 开发商ID
*               "type":"cloud",                       // 类型为云锁
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
*   @brief      获取本地设备描述
*   @param[in]  ipc             IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  format_type     参数类型( #JSON )
*   @param[out] desc            设备描述，json数组，需要调用 #slm_ctrl_free 释放
*   @return     成功返回SS_OK，失败返回相应错误码
*   @remarks    硬件锁有本地锁和网络锁两种，获取本地设备描述为硬件锁设备描述获取方式的一种，更为精确的只获取本地锁的硬件锁描述。
*               调用方式参考 #slm_ctrl_get_all_description ，其 desc 参数也一致
*   @see        slm_ctrl_client_open slm_ctrl_get_all_description
*/
SS_UINT32 SSAPI slm_ctrl_get_local_description(
    IN  void*       ipc,
    IN  INFO_FORMAT_TYPE format_type,
    OUT char**      desc
    );


/*!
*   @brief      获取网络设备描述
*   @param[in]  ipc             IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  format_type     参数类型( #JSON )
*   @param[out] desc            设备描述，json 数组，需要调用 #slm_ctrl_free 释放
*   @return     成功返回SS_OK，失败返回相应错误码
*   @remarks    同 #slm_ctrl_get_all_description 和 #slm_ctrl_get_local_description ，只获取网络硬件锁设备描述。
*               调用方式参考 #slm_ctrl_get_all_description，其 desc 参数也一致
*   @see        slm_ctrl_client_open slm_ctrl_get_all_description
*/
SS_UINT32 SSAPI slm_ctrl_get_remote_description(
    IN  void*       ipc,
    IN  INFO_FORMAT_TYPE format_type,
    OUT char**      desc
    );


/*!
*   @brief      获取指定设备描述下的所有许可ID
*   @param[in]  ipc     IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  type    参数类型( #JSON )
*   @param[in]  desc    设备描述，通过 #slm_ctrl_get_all_description 等函数获得的设备描述中，取其中需要的描述内容进行查询
*   @param[out] result  许可ID，json数组，需要调用 #slm_ctrl_free 释放
*   @return     成功返回 SS_OK ，失败返回相应的错误码
*   @remarks    当前接口可以简单的得到指定设备中的许可ID列表，便于统计指定设备中的许可个数。
*   @code
*     - 许可ID json结构
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
*   @brief      读取指定锁和开发商ID下的所有许可信息
*   @param[in]  ipc         IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  type        参数类型( #JSON ）
*   @param[in]  desc        设备描述，通过 #slm_ctrl_get_all_description 等函数获得的设备描述中，取其中需要的描述内容进行查询
*   @param[out] result      许可信息，需要调用 #slm_ctrl_free 释放
*   @return     成功返回SS_OK，否则返回相应的错误码
*   @remarks    开发者调用此接口来获取指定设备中、所有许可的详细信息，返回值详细的描述了当前许可的产品信息、限制条件、当前状态（是否可用、过期、即将过期、次数用尽）等信息
*   @code
*     - 许可信息 json结构
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
*             "win_user_session"（Windows用户会话） / "process"（进程）, 
*             "version" : 342512, 
*             "last_update_timestamp": 42342525, 
*             "last_update_timesn":2342 ,
*             "lock_time" : 23542532    //许可被锁定的时间
*             "lic_status":
*                 {
*                     "status":0/1/2/4,    // 0：许可正常； 1：许可即将过期； 2：许可已过期； 4：许可次数用尽
*                     "message":"NORMAL/WILL EXPIRE/EXPIRE/USE UP"     // 许可状态描述
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
*           // 1、打开ipc，参考slm_client_open
*           // 2、获取设备描述，参考slm_ctrl_get_all_description等函数
*           // 3、获取许可描述
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
*           // 4、关闭ipc
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
*   @brief      读取公开区大小
*   @param[in]  ipc             IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  license_id      许可ID
*   @param[in]  desc            设备描述，通过 #slm_ctrl_get_all_description 等函数获得的设备描述中，取其中需要的描述内容进行查询
*   @param[out] len             返回公开区的大小
*   @return     成功返回 SS_OK ，否则返回相应的错误码
*   @remarks    通过此接口可以获取到指定设备中、指定许可的公开区大小，公开区的描述请参考相关文档中的描述。
*   @see        slm_ctrl_read_pub_data slm_ctrl_get_all_description
*/
SS_UINT32 SSAPI slm_ctrl_get_pub_size(
    IN  void*           ipc,
    IN  SS_UINT32       license_id,
    IN  const char*     desc,
    OUT SS_UINT32*      len
    );

/*!
*   @brief      读取用户公开内容
*   @param[in]  ipc          IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  license_id   许可ID
*   @param[in]  desc         设备描述
*   @param[out] readbuf      读取的缓冲区
*   @param[in]  offset       读取的偏移
*   @param[in]  len          读取的长度
*   @return     成功返回 SS_OK ，否则返回相应的错误码
*   @remarks    通过此接口来获取许可公开区内容，公开区大小通过 #slm_ctrl_get_pub_size 获取，读取长度不应该超过 #slm_ctrl_get_pub_size 获取到的数据大小。
*               详细解释可参考相关文档。
*   @code
*       {
*           void *ipc;
*           SS_UINT32 size = 0;
*           SS_BYTE   *buff = 0;
*           SS_UINT32 status = SS_OK;
*           SS_UINT32 license_id = 1;   // 需要获取数据区的许可ID
*           char *desc;
*
*           // 1、打开IPC
*           status = slm_ctrl_client_open(&ipc);
*           if (status != SS_OK)
*           {
*               //todo: deal error code!
*               return status;
*           }
*
*           // 2、获取设备描述符请参考 slm_ctrl_get_all_description中的示例
*
*           // 3、获取公开区大小和数据内容
*           status = slm_ctrl_get_pub_size(ipc, license_id, desc, &size);   // 获取指定许可的公开区内容
*           if (status == SS_OK && size > 0)
*           {
*               buff = (SS_BYTE *)calloc(sizeof(SS_BYTE), size);
*               status = slm_user_data_read(slm_handle, license_id, desc, buff, 0, size);
*               if(status != SS_OK)
*               {
*                   // todo: deal error code
*               }
*               // 可在此处理获取到的公开区数据
*
*               free(buff);
*               buff = 0;
*           }
*           // 4、关闭IPC句柄
*           slm_ctrl_client_close(ipc);
*       }
*   @endcode
*   @see        slm_ctrl_client_open slm_ctrl_read_pub_data slm_ctrl_get_all_description
*/
SS_UINT32 SSAPI slm_ctrl_read_pub_data(
    IN  void*           ipc,
    IN  SS_UINT32       license_id,
    IN  const char*     desc,       //  设备描述
    OUT SS_BYTE*        readbuf,
    IN  SS_UINT32       offset,
    IN  SS_UINT32       len
    );

/*!
*   @brief      获得许可详细信息
*   @param[in]  ipc         IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  type        参数类型( #JSON )
*   @param[in]  license_id  许可ID
*   @param[in]  desc        设备描述，通过 #slm_ctrl_get_all_description 等函数获得的设备描述中，取其中需要的描述内容进行查询
*   @param[out] result      接收数据的指针，需要调用 #slm_ctrl_free 释放
*   @return     成功返回 SS_OK，否则返回相应的错误码
*   @remarks    此接口类似 #slm_ctrl_read_brief_license_context ，只是前者获取到指定设备中所有许可的内容，此接口返回的是指定设备、指定许可的许可详细信息。
*               调用方式参考 #slm_ctrl_read_brief_license_context ，其 result 参数结构相同。
*/
SS_UINT32 SSAPI slm_ctrl_read_license_context(
    IN  void                *ipc,
    IN  INFO_FORMAT_TYPE    type,
    IN  SS_UINT32           license_id,
    IN  const char          *desc,
    OUT char                **result
    );

/*!
*   @brief      获取单个锁的某个开发商ID下的所有session信息
*   @param[in]  ipc     IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  type    参数类型 ( #JSON )
*   @param[in]  desc    设备描述符，通过 #slm_ctrl_get_all_description 等函数获得的设备描述中，取其中需要的描述内容进行查询
*   @param[out] result  获取结果的缓冲区
*   @return     成功返回 SS_OK ，否则返回相应的错误码
*   @remarks    获取指定设备下的所有会话信息。会话信息是指应用程序通过 @link Vribox RuntimeAPI @endlink 库调用加密锁内许可时产生的临时会话，该回合保存了应用程序与加密锁之间
*               相互通信的一些必要信息，通过此接口可以获取到指定设备下所有许可对应的应用程序的会话信息。开发者也可以通过此接口获取到的结果，调用
*               #slm_ctrl_kick_session 接口来管理当前设备中的会话。
*               一旦应用程序登出许可，或会话被强行踢出，会话信息将会失效。
*   @code
*   - 返回 json 示例：
*       [{
*           "license_id": 1,
		    "concurrent_type":	"process",       // 许可为并发许可时有此参数
		    "curr_concurrent":	1,               // 许可当前并发数，与concurrent_type参数相关
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
*   @brief      踢除指定的许可会话
*   @param[in]  ipc     IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  desc    设备描述符，通过 #slm_ctrl_get_all_description 等函数获得的设备描述中，取其中需要的描述内容进行查询
*   @param[in]  session_id 要踢除的 session ID
*   @return     成功返回SS_OK，失败返回相应的错误码
*   @remarks    通过 #slm_ctrl_read_session_context 获取到 session_id，通过 session_id 来对相应的会话进行管理
*   @see        slm_ctrl_client_open slm_ctrl_get_all_description slm_ctrl_read_session_context
*/
SS_UINT32 SSAPI slm_ctrl_kick_session(
    IN  void*       ipc,
    IN  const char* desc,
    IN  SS_UINT32   session_id
    );

/*!
*   @brief      清理锁内许可升级历史记录（只支持硬件锁）
*   @param[in]  ipc     IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  desc    设备描述符，通过 #slm_ctrl_get_all_description 等函数获得的设备描述中，取其中需要的描述内容进行查询
*   @remarks    此操作将清理锁内升级记录，已失效的升级包可能会重新可用。要谨慎使用！
*/
SS_UINT32 SSAPI slm_ctrl_clear_history(
    IN  void*       ipc,
    IN  const char* desc
    );


/*!
*   @brief      获得硬件锁锁内信息（只支持硬件锁）
*   @param[in]  ipc     IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  desc    设备描述符，通过 #slm_ctrl_get_all_description 等函数获得的设备描述中，取其中需要的描述内容进行查询
*   @param[in]  result  接收数据的指针，结构为json数组，需要调用 #slm_ctrl_free 释放
*   @return     成功返回 SS_OK ，失败返回相应错误码 
*   @remarks    获取硬件锁设备信息，主要获取锁内时间、锁内存储空间信息、固件版本、生产日期等内容，便于对硬件锁进行管理。
*   @code
*   - json 字段说明：
*       -# "clock":1497927112,                  // 锁内时间（UTC）
*       -# "available_space":476160,            // 锁内可用空间
*       -# "total_space":524288,                // 锁内总空间大小
*       -# "communication_protocol":2,          // 通迅协议
*       -# "lock_firmware_version":"3.1.6",     // 锁固件版本
*       -# "lm_firmware_version":"2.10.2.1",    // Entry版本
*       -# "h5_device_type":0,                  // 硬件锁类型，0代表常规精锐5硬件锁；2代表精锐5时钟锁
*       -# "power_drop_times",                  // 精锐5时钟锁特有，表示掉电次数
*       -# "clock_type",                        // 锁内时钟类型，0表示虚拟时钟，2表示硬件时钟
*       -# "device_model":"e5",                 // 设备型号
*       -# "hardware_version":"0.0.2.0",        // 硬件版本号
*       -# "manufacture_date":"2016-01-25 17:11:05",        // 生产日期
*       -# "lock_sn":"9733c801000702051061000300xxxxxx",    // 硬件锁芯片号
*       -# "slave_addr":238,                    // 硬件锁所在的设备总线地址
*       -# "shell_num":"099900000054",          // 硬件锁外壳号
*       -# "user_info":"string",                // 用户信息（可忽略）
*       -# "inner_info":"string"                // 内部信息（可忽略）
*   @endcode
*/
SS_UINT32  SSAPI slm_ctrl_get_device_info(
    IN  void*           ipc,
    IN  const char*     desc,
    OUT char**          result
    );

/*!
*   @brief      向硬件锁获取时钟校准请求（只支持硬件锁）
*   @param[in]  ipc         IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  desc        设备描述符，通过 #slm_ctrl_get_all_description 等函数获得的设备描述中，取其中需要的描述内容进行查询
*   @param[out] rand        随机数
*   @param[out] lock_time   锁内设备时间
*   @param[inout] pc_time  计算机UTC时间
*   @return     成功返回 SS_OK ，失败返回相应的错误码
*/
SS_UINT32 SSAPI slm_ctrl_adjust_time_request(
    IN  void*               ipc,
    IN  const char*         desc,
    OUT SS_BYTE             rand[SLM_FIXTIME_RAND_LENGTH],
    OUT SS_UINT32*          lock_time,
    IN OUT SS_UINT32*       pc_time
    );
/*!
*   @brief      获得硬件锁内文件信息（只支持硬件锁）
*   @param[in]  ipc     IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  desc    设备描述符，通过 #slm_ctrl_get_all_description 等函数获得的设备描述中，取其中需要的描述内容进行查询
*   @param[in]  result  接收数据的指针，结构为json数组，需要调用 #slm_ctrl_free 释放
*   @return     成功返回 SS_OK ，失败返回相应的错误码
*   @remarks    此接口可以获取到硬件锁内文件的信息，文件将以 json 列表形式展现，主要包括文件名、文件类型、大小、修改时间
*               等内容，便于开发者梳理和管理锁内文件数量。
*   @code
*   - json 字段说明：
*       -# "validate"：number   标志哪些域有效，仅在设置文件属性中使用
*       -# "type"：number       文件类型，不能修改
*       -# "privilege":number   文件访问权限
*       -# "size":number        文件大小
*       -# "time":number        文件修改时间
*       -# "name":""            文件名  当前文件名称长度16字节
*   @endcode
*/
SS_UINT32  SSAPI slm_ctrl_get_filelist_info(
	IN  void*            ipc,
	IN  const char*      desc,
	OUT char**           result
	);

/*!
*   @brief      获取加密锁的证书(仅支持本地加密锁)
*   @param[in]  ipc         IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  desc        设备描述符，通过 #slm_ctrl_get_all_description 等函数获得的设备描述中，取其中需要的描述内容进行查询
*   @param[in]  cert_type   证书类型，参考 #CERT_TYPE  
*   @param[out] cert        设备证书缓冲区
*   @param[in]  cert_size   缓冲区大小
*   @param[out] cert_len    返回的设备证书大小
*   @return     成功返回 SS_OK ，失败返回相应的错误码
*   @remarks    获取设备证书，此处的设备指硬件锁、云锁。
*               如果 cert_type = #CERT_TYPE_DEVICE_CERT，其功能与 #slm_ctrl_get_device_cert 完全一致； 
*               如果为其他类型，则仅支持硬件锁。
*               通过此接口可以获取加密锁的根证书、设备子CA 和设备，方便合成设备证书链。
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
*   @brief      获取加密锁的设备证书（当前支持云锁和硬件锁）
*   @param[in]  ipc         IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  desc        设备描述符，通过 #slm_ctrl_get_all_description 等函数获得的设备描述中，取其中需要的描述内容进行查询
*   @param[out] device_cert 设备证书缓冲区
*   @param[in]  buff_size   缓冲区大小
*   @param[out] return_size 返回的设备证书大小
*   @return     成功返回SS_OK，失败返回相应的错误码
*   @remarks    获取加密锁证书，此处的加密锁指硬件锁、云锁。
*               如果设备为定制设备，可通过此接口获取到开发者自定义的设备证书；若为非定制设备，此接口可直接获取到深思设备证书。
*               云锁、软锁不存在定制与非定制问题。
*               特别说明：深思已不再通过任何渠道提供定制设备，保留 #slm_ctrl_get_device_cert 和 #slm_ctrl_get_sense_device_cert 接口仅为保证兼容性。
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
*   @brief      获取硬件锁的深思设备证书（云锁、软锁不支持）
*   @param[in]  ipc         IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  desc        设备描述符，通过 #slm_ctrl_get_all_description 等函数获得的设备描述中，取其中需要的描述内容进行查询
*   @param[out] device_cert 设备证书缓冲区
*   @param[in]  buff_size   缓冲区大小
*   @param[out] return_size 返回的设备证书大小
*   @return     成功返回SS_OK，失败返回相应的错误码
*   @remarks    通过此接口可以直接获取到深思的设备证书，此接口是深思定制设备特有，若设备为定制设备， #slm_ctrl_get_device_cert 只能获取到开发者自定义证书，
*               通过此接口才能获取到深思设备证书。
*               特别说明：深思已不再通过任何渠道提供定制设备，保留 #slm_ctrl_get_device_cert 和 #slm_ctrl_get_sense_device_cert 接口仅为保证兼容性。
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
*   @brief      设备正版验证（仅支持硬件锁）
*   @param[in]  ipc                 IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  desc                设备描述符，通过 #slm_ctrl_get_all_description 等函数获得的设备描述中，取其中需要的描述内容进行查询
*   @param[in]  verify_data         验证数据（必须以字符"SENSELOCK"(9字节)开头）
*   @param[in]  verify_data_size    验证数据大小，大小必须为 #SLM_VERIFY_DATA_SIZE (41)个字节
*   @param[out] signature           返回的签名结果
*   @param[in]  signature_buf_size  缓冲区大小
*   @param[out] signature_size      签名结果大小
*   @return     成功返回 SS_OK ，失败返回相应的错误码
*   @remarks    锁内使用设备私钥签名，需要用硬件锁证书公钥验签
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
*   @brief      硬件锁设备指示灯控制
*   @param[in]  ipc                 IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  desc                设备描述符，通过 #slm_ctrl_get_all_description 等函数获得的设备描述中，取其中需要的描述内容进行查询
*   @param[in]  led_ctrl            控制结构，参考 #ST_LOCK_LED_CONTROL
*   @return     成功返回 SS_OK ，失败返回相应的错误码
*   @see        ST_LOCK_LED_CONTROL
*/
SS_UINT32 SSAPI slm_ctrl_led_control(
    IN  void*               ipc,
    IN  const char*         desc,
    IN  ST_LOCK_LED_CONTROL*     led_ctrl
    );

/*!
*   @brief      释放API生成的缓冲区
*   @param[in]  buffer      API 生成的缓冲区
*/
void SSAPI slm_ctrl_free(
    IN  void*   buffer
    );

/*!
*   @brief      查询软锁许可的安装信息
*   @param[in]  ipc         IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  desc        设备描述符，通过 #slm_ctrl_get_all_description 获得的设备描述中，取其中需要的描述内容进行查询
*   @param[in]  license_id  需要查询的软许可ID
*   @param[out] result      软许可安装信息，需要调用 #slm_ctrl_free 释放
*   @return     成功返回 SS_OK ，失败返回相应错误码
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
*   @brief      绑定软锁许可
*   @param[in]  ipc         IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  desc        设备描述符，通过 #slm_ctrl_get_all_description 获得的设备描述中，取其中需要的描述内容进行查询(必须是账号软锁的未绑定的描述信息）
*   @param[in]  license_id  需要绑定的软许可ID
*   @return     成功返回 SS_OK ，失败返回相应错误码
*/
SS_UINT32 SSAPI slm_ctrl_bind_offline_license(
    IN void*        ipc, 
    IN const char*  desc, 
    IN SS_UINT32    license_id
    );

/*!
*   @brief 枚举已绑定的软锁设备描述，包括本地和远程
*   @param[in]  ipc     IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[out] desc    软锁的设备描述，需要调用 #slm_ctrl_free 释放
*   @return 成功返回 SS_OK ，失败返回相应错误码
*   @remarks
*   @code
*   - JSON 字段说明：
*       -# "type":string                    加密锁类型，这里的值是 slock 和 smart_offline。前者表示本地的软锁设备设备描述；后者表示平台上查询到的信息
*       -# "user_guid":string               如果是账号软许可，内容为账号以十六进制字符串表示的 GUID；如果是授权码软许可，内容为授权码的 唯一锁号
*       -# "vclock":number                  软锁的虚拟时钟 utc 时间秒
*       -# "slock_type":number              软锁的类型。这里的值 account 表示账户软锁；license key 表示授权码软锁
*       -# "account_name":string            若 slock_type=account 时有此字段，表示当前软锁的账户名称
*       -# "license_key":string             若 slock_type=license key 时有此字段，表示当前软锁的授权码缩略信息（仅保留前后8字节数据，中间8字节数据隐藏）
*       -# "status":number                  若 slock_type=license key 时有此字段，表示当前软锁的状态，参考 ENUM_LICENSE_KEY_STATUS
*       -# "developer_id":string            开发商ID
*       -# "delta_time":number              软锁时间与本地时间的时间差，用于判断许可有效性（当前方法还无法正确判断许可有效性，请勿使用）
*
*     [
*       {"type":"slock", "user_guid":"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", "vclock":12345678, "slock_type":"account", "account_name":"xxxx@sense.com.cn", "developer_id":"0300000000000009", "delta_time":0}
*       {"type":"slock", "user_guid":"SC000100000001", "vclock":12345678, "slock_type":"license key", "license_key":"1234-xxxx-xxxx-abcd", "status":0, "developer_id":"0300000000000009", "delta_time":0}
*     ]
*   @endcode
*/
SS_UINT32 SSAPI slm_ctrl_get_offline_desc(IN void* ipc, OUT char** desc);

/*!
*   @brief 枚举已绑定的本地软锁设备描述
*   @param[in]  ipc     IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[out] desc    本地软锁设备描述，需要调用 #slm_ctrl_free 释放
*   @return 成功返回SS_OK，失败返回相应错误码
*/
SS_UINT32 SSAPI slm_ctrl_get_offline_local_desc(IN void* ipc, OUT char** desc);

/*!
*   @brief 枚举已绑定的远程软锁设备描述
*   @param[in]  ipc     IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[out] desc    远程软锁设备描述，需要调用 #slm_ctrl_free 释放
*   @return 成功返回 SS_OK ，失败返回相应错误码
*/
SS_UINT32 SSAPI slm_ctrl_get_offline_remote_desc(IN void* ipc, OUT char** desc);

/*!
*   @brief      解绑软锁许可
*   @param[in]  ipc         IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  desc        软锁设备描述，通过 #slm_ctrl_get_offline_desc 获得
*   @param[in]  license_id  需要解绑的软许可ID
*   @return     成功返回 SS_OK ，失败返回相应错误码
*/
SS_UINT32 SSAPI slm_ctrl_unbind_offline_license(IN void* ipc, IN const char* desc, IN SS_UINT32 license_id);

// -------------------
/*!
*   @brief      在离线计算机上调用，获取离线绑定c2d信息
*   @param[in]  ipc             IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[out] bind_c2d        离线绑定用的C2D信息
*   @param[in]  c2d_buf_size    C2D 缓冲区大小
*   @param[out] c2d_length      C2D 实际长度
*   @return     成功返回 SS_OK ，失败返回相应错误码
*/
SS_UINT32 SSAPI slm_ctrl_offline_bind_c2d(
    IN void         *ipc, 
    OUT SS_BYTE     *bind_c2d,
    IN SS_UINT32    c2d_buf_size,
    OUT SS_UINT32   *c2d_length);

/*!
*   @brief      在离线计算机上调用，获取离线解绑c2d信息
*   @param[in]  ipc             IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  desc            软锁设备描述，通过 #slm_ctrl_get_offline_desc 获得
*   @param[out] unbind_c2d      离线绑定用的C2D信息
*   @param[in]  c2d_buf_size    C2D 缓冲区大小（不小于 #SLM_SLOCK_OFFLINE_UNBIND_C2D_BUF_LENGTH ）
*   @param[out] c2d_length      C2D 实际长度
*   @return     成功返回 SS_OK ，失败返回相应错误码
*   @remarks    调用接口会先解绑本地的软锁许可，再返回解绑许可的C2D信息。
*               调用接口成功时本地软锁许可已解绑，无法使用，用户可以在联网计算机将C2D文件上传至云平台，解绑云平台绑定记录，不解绑否则将占用一个同时绑定数。
*               如果C2D数据丢失，用户将无法通过C2D文件绑云平台绑定记录，只能由开发者登录开发者网站进行强制解绑操作。
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
*   @brief      在离线计算机上调用，离线升级软锁许可
*   @param[in]  ipc         IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  d2c         包含许可内容的 D2C包
*   @return     成功返回 SS_OK ，失败返回相应错误码
*   @remarks    离线机器上调用，可以在离线的机器上调用此接口，升级已经获取到的离线 D2C包 到本地计算机软锁中
*/
SS_UINT32 SSAPI slm_ctrl_offline_bind_d2c(
    IN void         *ipc, 
    IN char         *d2c
    );

/*!
*   @brief      在联网计算机上调用，从云平台获取离线许可升级包
*   @param[in]  ipc         IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  desc        软锁设备描述，通过 #slm_ctrl_get_offline_desc 获得
*   @param[in]  license_id  要绑定定许可ID
*   @param[in]  bind_c2d    绑定 C2D 信息
*   @param[in]  c2d_length  C2D 长度
*   @param[out] result      包含许可内容的 D2C包，需要调用 #slm_ctrl_free 释放
*   @return     成功返回 SS_OK ，失败返回相应错误码
*   @remarks    在联网的机器上调用此接口，将 C2D 上传给云平台，同时兑换到离线许可升级包。
*               result 在不需要的时候，需要调用 #slm_ctrl_free 释放资源
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
*   @brief      在联网计算机上调用，从云平台解绑离线许可
*   @param[in]  ipc             IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  user_guid       已登录用户的 guid，通过 #ss_user_login 库获取
*   @param[in]  unbind_c2d      解绑 C2D 信息
*   @param[in]  c2d_length      C2D 长度
*   @return     成功返回 SS_OK ，失败返回相应错误码
*   @remarks    此函数通过错误码判断许可解绑是否成功，SS_OK 表示解绑成功，其他表示解绑失败。如果解绑失败，可在 VirboxLM 开发者中心 进行手动解绑
*/
SS_UINT32 SSAPI slm_ctrl_cloud_offline_unbind(
    IN  void            *ipc,
    IN  const char      *user_guid,
    IN  SS_BYTE         *unbind_c2d,
    IN  SS_UINT32       c2d_length
    );

/*!
*   @brief      在联网计算机上调用，在线绑定授权码许可
*   @param[in]  ipc             IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  license_key     需要绑定的授权码
*   @return     成功返回 SS_OK ，失败返回相应错误码
*   @remarks    开发商可以调用此接口，传入授权码，许可服务将自动将云平台中对应的授权码许可绑定到本地
*/
SS_UINT32 SSAPI slm_ctrl_bind_license_key(
    IN void             * ipc, 
    IN const char       *license_key
    );

/*!
*   @brief      在联网计算机上调用，在线绑定授权码许可，当前接口由 #slm_ctrl_bind_license_key 扩展而来，用于支持带密码的 授权码许可 绑定
*   @param[in]  ipc             IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  license_key     需要绑定的授权码
*   @param[in]  password        授权码的密码。如果要绑定的授权码不需要密码，可以传 NULL，或 空字符串
*   @return     成功返回 SS_OK ，失败返回相应错误码
*   @remarks    开发商可以调用此接口，传入授权码，许可服务将自动将云平台中对应的授权码许可绑定到本地
*/
SS_UINT32 SSAPI slm_ctrl_bind_license_key_with_psd(
    IN void             * ipc,
    IN const char       *license_key,
    IN const char       *password
    );

/*!
*   @brief      刷新当前软锁许可信息
*   @param[in]  ipc             IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  desc            软锁的设备描述，通过 #slm_ctrl_get_offline_desc 获得
*   @param[in]  license_id      许可ID（可选）
*   @param[in]  license_key     授权码（可选）
*   @return     成功返回 SS_OK ，失败返回相应错误码
*   @remarks    若当前软锁许可为账号软许可，则需要传入要刷新的 许可ID，否则将默认刷新 0号许可，可能达不到用户的最终目的；
*               若当前软锁许可为授权码软许可，则可以传入需要刷新的授权码，若不传授权码，则默认刷新当前设备描述下的授权码软许可。
*/
SS_UINT32 SSAPI slm_ctrl_slock_refresh_license(
    IN  void            *ipc,
    IN  char            *desc,
    IN  SS_UINT32       license_id,
    IN  char            *license_key
    );

/*!
*   @brief      刷新当前软锁许可信息
*   @param[in]  ipc             IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  desc            软锁的设备描述，通过 #slm_ctrl_get_offline_desc 获得
*   @param[in]  license_id      许可ID（可选）
*   @param[in]  license_key     授权码（可选）
*   @param[in]  password        配合授权码使用，授权码的密码。如果要绑定的授权码不需要密码，可以传 NULL，或 空字符串（可选）
*   @return     成功返回 SS_OK ，失败返回相应错误码
*   @remarks    若当前软锁许可为账号软许可，则需要传入要刷新的 许可ID，否则将默认刷新 0号许可，可能达不到用户的最终目的；
*               若当前软锁许可为授权码软许可，则可以传入需要刷新的授权码，若不传授权码，则默认刷新当前设备描述下的授权码软许可。
*/
SS_UINT32 SSAPI slm_ctrl_slock_refresh_license_with_psd(
    IN  void            *ipc,
    IN  char            *desc,
    IN  SS_UINT32       license_id,
    IN  char            *license_key,
    IN  const char      *password
    );
	
/*!
*   @brief      升级硬件锁许可，D2C包 由 @link D2CAPI @endlink 或 VirboxLM 开发者中心 生成
*   @param[in]  d2c_pkg     d2c文件数据
*   @param[out] error_msg   错误信息，需要调用 #slm_ctrl_free 释放
*   @return     成功返回 SS_OK ，失败返回错误码
*   @remarks:   D2C包内可能包含多条数据，因此返回的错误码信息也是 json 数组结构，需要分别解析。
*               说明：当前接口仅支持硬件锁许可升级，若需要升级软许可，请调用 #slm_ctrl_update_ex 接口
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
*   @brief      升级由开发锁或 VirboxLM 开发者中心 签发的硬件锁、软锁许可
*   @param[in]  lock_sn     硬件加密锁的锁号（唯一序列号,十六进制字符串格式），可选
*   @param[in]  d2c_pkg     d2c文件数据，必填
*   @param[out] error_msg   错误信息，不使用需要调用 #slm_ctrl_free 释放
*   @return     成功返回 SS_OK ，失败返回错误码
*   @remarks:
*           - 此接口支持硬件锁和软锁许可数据的升级
*           - 当升级包为硬件锁许可时，可以指定 lock_sn，提高升级效率，也可不填写；当升级包为软许可时，lock_sn 的值将不被处理
*           - 当升级包为硬件锁许可时，D2C包内可能包含多条数据，每条升级包的错误信息将以 json 结构形式通过 error_msg 返回，需要分别解析
*           - 当升级包为软锁许可时，错误码将直接以返回值形式返回，error_msg 将不被处理
*   @code
*     error_msg 结构：
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
*   @brief      设置云服务地址
*   @param[in]  cloud_server_config    服务 URL(json 结构)
*               例如：{"urls": {"cloud_runtime_url": "http://rt.senseyun.com","slock_url": "http://sl.senseyun.com","dl_url": "http://ll.senseyun.com"}}
*   @return     成功返回SS_OK，失败返回相应错误码
*   @remarks    不支持多线程调用，初始化后全局生效，切换配置时由调用者保证多线程数据安全。
*/
SS_UINT32 SSAPI slm_ctrl_init_cloud_server_config(IN const char *cloud_server_config);


// -----------------------------------------
// 软锁统一接口
/*!
*   @brief      根据 slock_type 来升级软锁许可，slock_type 可以是账号许可(暂不支持），授权码许可(暂不支持)，借阅码许可
*   @param[in]  ipc             IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  slock_type      软锁许可类型，目前仅支持 SLM_ENUM_SLOCK_TYPE_BORROW_KEY
*   @param[in]  param           绑定参数，可以是许可ID，授权码，借阅码。目前仅支持 借阅码
*   @param[in]  param_length    绑定参数的长度。如果是许可ID ，一般是 4 字节长度；如果是授权码，一般是 19 字节长度；如果收借阅码，一般是 11 字节长度
*   @return     成功返回 SS_OK ，失败返回错误码
*   @remarks:   
*               - 当前接口统一了所有类型的软许可接口，当前仅支持借阅码许可
*               - 当软锁类型为账号 (SLM_ENUM_SLOCK_TYPE_ACCOUNT) 时，要求本地已经登陆了云账号，然后通过此接口参数 param 传入许可ID 即可绑定
*               - 当软锁类型为授权码 (SLM_ENUM_SLOCK_TYPE_LICENSE_KEY) 时，param 参数需要传入授权码
*               - 当软锁类型为授权码 (SLM_ENUM_SLOCK_TYPE_BORROW_KEY) 时，param 参数需要传入借阅码
*/
SS_UINT32 SSAPI slm_ctrl_slock_license_bind(
    IN void*        ipc,
    IN SS_UINT32    slock_type,
    IN void         *param,
    IN SS_UINT32    param_length
    );

/*!
*   @brief      在线解绑软许可数据
*   @param[in]  ipc         IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  desc        软锁设备描述，通过 #slm_ctrl_get_offline_desc 获得
*   @param[in]  license_id  需要解绑的许可ID
*   @return     成功返回 SS_OK ，失败返回相应错误码
*   @remarks    当软锁设备描述为账号软许可的时候，需要传入指定的 license_id 作为解绑对象；当设备描述为其他类型（如授权码，借阅码等）时， license_id 不会被处理
*/
SS_UINT32 SSAPI slm_ctrl_slock_license_unbind(
    IN  void*        ipc,
    IN  const char   *desc,
    IN  SS_UINT32    license_id
    );

/*!
*   @brief      在线刷新软许可数据
*   @param[in]  ipc         IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  desc        软锁设备描述，通过 #slm_ctrl_get_offline_desc 获得
*   @param[in]  license_id  需要刷新的许可ID
*   @return     成功返回 SS_OK ，失败返回相应错误码
*   @remarks    当软锁设备描述为账号软许可的时候，需要传入指定的 license_id 作为刷新对象；当设备描述为其他类型（如授权码，借阅码等）时， license_id 不会被处理
*/
SS_UINT32 SSAPI slm_ctrl_slock_license_refresh(
    IN  void*               ipc,
    IN  const char*         desc,
    IN  SS_UINT32           license_id
    );

/*!
*   @brief      在线更新授权码或借阅码软许可的状态
*   @param[in]  ipc         IPC句柄，通过 #slm_ctrl_client_open 获得
*   @param[in]  desc        软锁设备描述，通过 #slm_ctrl_get_offline_desc 获得
*   @param[in]  license_id  需要刷新的许可ID
*   @return     成功返回 SS_OK ，失败返回相应错误码
*   @remarks    当前仅支持授权码和借阅码许可的状态刷新
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
