/*! 
*  @file ss_error.h
*  @brief     SS对外声明错误码,32位,用来统一错误码格式，最高一字节是模块标识。
*  @details   包括SS、LM、H5、IPC、NetAgent、SSprotect等错误值，其中最高第一字节是错误模块标识，其它由模块自定义
*             
*  @version   2.1.0
*  @date      2013-2015
*  @pre       提前声明所有错误值
*/
#ifndef __SS_ERROR_H__
#define __SS_ERROR_H__

//============================================================
//              一般错误码
//============================================================

#define SS_OK                                       0x00000000  //  成功
#define SS_ERROR_INVALID_PARAM                      0x00000002  //  不合法的参数
#define SS_ERROR_MEMORY_FAIELD                      0x00000003  //  内存错误
#define SS_ERROR_INSUFFICIENT_BUFFER                0x00000004  //  缓冲区大小不足
#define SS_ERROR_INVALID_HANDLE                     0x00000008  //  无效的句柄
#define SS_ERROR_TIMEOUT                            0x00000009  //  操作超时
#define SS_ERROR_UNSUPPORT                          0x00000010  //  不支持的操作
#define SS_ERROR_NET_ERROR                          0x00000040  //  网络错误

#define SS_ERROR_MASTER_UNSUPPORT_PIN               0x00000044  //  开发锁不支持PIN码功能，请立即向深思申请更换新开发锁
#define SS_ERROR_MASTER_PIN_NOT_ACTIVE              0x00000045  //  开发锁PIN码没有激活，请修改初始PIN码
#define SS_ERROR_MASTER_OUTDATED_VERSION            0x00000047  //  开发锁版本太低，必须更换开发锁
#define SS_ERROR_MASTER_PIN_WRONG                   0x00000048  //  PIN码错误
#define SS_ERROR_MASTER_PIN_BLOCKED                 0x00000049  //  PIN码被锁定
#define SS_ERROR_NET_TIMEOUT                        0x0000004A  //  网络请求超时

#define SS_ERROR_CONFIGURATION						0x0000004B  //  配置项出错，请在初始化前先调用配置接口初始化配置项（control api调用 slm_ctrl_init_cloud_server_config， runtime api 调用 slm_extensions_config）
#define SS_ERROR_MASTER_NEED_UPDATE                 0x0000004C  //  开发锁固件版本太低，需要升级固件
#define SS_ERROR_INIT_FAILED                        0x0000004D  //  初始化失败
//============================================================
//              SS 模块 (0x05)
//============================================================

#define SS_ERROR_SERVER_NOT_FOUND                   0x05000004  //  找不到服务器
#define SS_ERROR_NO_LOCK                            0x05000005  //  找不到锁
#define SS_ERROR_SLM_HANDLE_IS_FULL                 0x05000006  //  LM 句柄已达到上限
#define SS_ERROR_SYSTEM_ERROR                       0x0500000D  //  系统操作失败
#define SS_ERROR_WHITELISTED                        0x05000013  //  白名单触发
#define SS_ERROR_BLACKLISTED                        0x05000014  //  黑名单触发
#define SS_ERROR_LOCK_NOT_FOUND                     0x0500001F  //  锁没有找到

//============================================================
//          LM 模块(0x20): (runtime, control, develop)
//============================================================

#define SS_ERROR_D2C_NO_PACKAGE                     0x13000000  //  D2C包中无签发内容
#define SS_ERROR_DEVELOPER_CERT_ALREADY_EXIST       0x13000001  //  开发商证书已存在
#define SS_ERROR_PARSE_CERT                         0x13000003  //  解析证书错误
#define SS_ERROR_D2C_PACKAGE_TOO_LARGE              0x13000004  //  D2C包过大
#define SS_ERROR_RESPONSE                           0x13000005  //  错误的数据响应
#define SS_ERROR_RUNTIME_NOT_INITIALIZE             0x13000007  //  未调用Runtime初始化函数
#define SS_ERROR_RUNTIME_VERSION                    0x13000009  //  版本不匹配
#define SS_ERROR_LIC_NOT_FOUND                      0x13000020  //  许可未找到
#define SS_ERROR_USER_DATA_TOO_SMALL                0x13000024  //  用户数据区太小
#define SS_ERROR_INVALID_D2C_PACKAGE                0x13000027  //  错误的D2C升级包
#define SS_ERROR_CLOUD_RESPONSE                     0x13000028  //  云锁返回的数据错误
#define SS_ERROR_USER_DATA_TOO_LARGE                0x13000029  //  读写的数据过大
#define SS_ERROR_INVALID_MEMORY_ID                  0x1300002A  //  无效的内存ID
#define SS_ERROR_INVALID_MEMORY_OFFSET              0x1300002B  //  无效的内存偏移
#define SS_ERROR_NO_LOGGED_USER                     0x13000030  //  没有登录的用户
#define SS_ERROR_USER_AUTH_SERVER_NOT_RUNNING       0x13000031  //  用户认证服务未启动
#define SS_ERROR_LICENSE_MODULE_NOT_EXISTS          0x13000037  //  许可模块不存在
#define SS_ERROR_DEVELOPER_PASSWORD                 0x13000038  //  错误的开发商API密码
#define SS_ERROR_CALLBACK_VERSION                   0x13000039  //  错误的初始化回调版本号
#define SS_ERROR_INFO_RELOGIN                       0x1300003A  //  用户需重新登录
#define SS_ERROR_LICENSE_VERIFY                     0x1300003B  //  许可数据验签失败
#define SS_ERROR_LICENSE_NEED_TO_ACTIVATE           0x13000051  //  许可需要联网激活

//============================================================
//              IPC 模块 (0x02)
//============================================================

#define SS_ERROR_IPC_FAILED                         0x02000002  //  IPC 收发错误
#define SS_ERROR_IPC_CONNECT_FAILED                 0x02000003  //  连接失败

//============================================================
//              Net Agent 模块 (0x11)
//============================================================




//============================================================
//              安全模块 (0x12)
//============================================================



//============================================================
//              LM Service (0x24)
//============================================================

#define ERROR_LM_SVC_INVALID_SESSION                0x2400000D  //  无效的session
#define ERROR_LM_SVC_SESSION_ALREADY_DELETED        0x2400000E  //  session 已经被删除
#define ERROR_LM_SVC_LICENCE_EXPIRED                0x2400000F  //  许可已经过期
#define ERROR_LM_SVC_SESSION_TIME_OUT               0x24000010  //  session超时
#define ERROR_LM_REMOTE_LOGIN_DENIED                0x24000015  //  许可不允许远程登录

//============================================================
//              LM Native (0x21)
//============================================================


//============================================================
//              LM Firmware (0x22)
//============================================================
#define SS_ERROR_FIRM_LICENCE_ALL_DISABLED          0x2200000E  // 所有许可被禁用
#define SS_ERROR_FIRM_CUR_LICENCE_DISABLED          0x2200000F  // 当前许可被禁用
#define SS_ERROR_FIRM_LICENCE_INVALID               0x22000010  // 当前许可不可用
#define SS_ERROR_FIRM_LIC_STILL_UNAVALIABLE         0x22000011  // 许可尚不可用
#define SS_ERROR_FIRM_LIC_TERMINATED                0x22000012  // 许可已经到期
#define SS_ERROR_FIRM_LIC_RUNTIME_TIME_OUT          0x22000013  // 运行时间用尽
#define SS_ERROR_FIRM_LIC_COUNTER_IS_ZERO           0x22000014  // 次数用尽
#define SS_ERROR_FIRM_LIC_MAX_CONNECTION            0x22000015  // 已达到最大并发授权
#define SS_ERROR_FIRM_REACHED_MAX_SESSION           0x22000017  // 锁内已经到达最大会话数量
#define SS_ERROR_FIRM_NOT_ENOUGH_SHAREMEMORY        0x2200001A  // 没有足够的共享内存
#define SS_ERROR_FIRM_INVALID_DATA_LEN              0x2200001C  // 错误的数据文件长度    
#define SS_ERROR_FIRM_DATA_FILE_NOT_FOUND           0x2200001E  // 找不到对应的许可数据文件
#define SS_ERROR_FIRM_INVALID_PKG_TYPE              0x2200001F  // 远程升级包类型错误
#define SS_ERROR_FIRM_INVALID_TIME_STAMP            0x22000020  // 时间戳错误的远程升级包
#define SS_ERROR_FIRM_INVALID_UPD_LIC_ID            0x22000021  // 错误的远程升级许可序号
#define SS_ERROR_FIRM_LIC_ALREADY_EXIST             0x22000022  // 添加的许可已经存在
#define SS_ERROR_FIRM_LICENCE_SIZE_LIMITTED         0x22000023  // 许可数量受限
#define SS_ERROR_FIRM_INVALID_DATA_FILE_OFFSET      0x22000024  // 无效的许可数据文件偏移
#define SS_ERROR_FIRM_SESSION_ALREADY_LOGOUT        0x2200002C  // session已经退出登录
#define SS_ERROR_FIRM_INVALID_USER_DATA_TYPE        0x22000031  // 用户自定义字段类型错误
#define SS_ERROR_FIRM_INVALID_DATA_FILE_SIZE        0x22000032  // 用户自定义区域过大
#define SS_ERROR_FIRM_ALL_LIC_TERMINATED            0x22000034  // 所有许可时间到期不可用
#define SS_ERROR_FIRM_UPDATE_FAILED                 0x22000038  // 远程升级失败
#define SS_ERROR_FIRM_DATA_LENGTH_ALIGNMENT         0x2200003C  // 加解密数据长度不对齐
#define SS_ERROR_FIRM_DATA_CRYPTION                 0x2200003D  // 加解密数据错误
#define SS_ERROR_FIRM_SHORTCODE_UPDATE_NOT_SUPPORTED    0x2200003E  // 不支持短码升级
#define SS_ERROR_FIRM_LIC_USR_DATA_NOT_EXIST        0x22000040  // 用户自定义数据不存在
#define SS_ERROR_FIRM_FILE_NOT_FOUND                0x22000050  // 找不到文件
#define SS_ERROR_FIRM_INVLAID_DEVELOPER_ID          0x22000059  // 无效的开发商ID
#define SS_ERROR_FIRM_BEYOND_PKG_ITEM_SIZE          0x2200005D  // 升级包许可数量过大
#define SS_ERROR_FIRM_DEVICE_LOCKED                 0x2200005F  // 用户锁被锁定
#define SS_ERROR_FIRM_NOT_EXCHANGE_KEY              0x22000061  // 未进行秘钥协商（auth认证）
#define SS_ERROR_FIRM_INVALID_SHORTCODE_SWAP_FILE   0x22000062  // 无效的短码升级交互文件
#define SS_ERROR_FIRM_SHORTCODE_UPDATE_USER_DATA    0x22000063  // 短码升级用户数据区错误

//============================================================
//              MODE LIC TRANS 模块()0x28
//============================================================

//============================================================
//              AUTH SERVER 模块 (0x29)
//============================================================

#define SS_ERROR_AUTH_SERVER_INVALID_TOKEN          0x29000001  //无效的token
#define SS_ERROR_AUTH_SERVER_REFRESH_TOKEN          0x29000002  //刷新token失败
#define SS_ERROR_AUTH_SERVER_LOGIN_CANCELED         0x29000003  //用户取消登陆
#define SS_ERROR_AUTH_SERVER_GET_ALL_USER_INFO_FAIL 0x29000004  //获取所有用户信息失败

//============================================================
//              Cloud 模块 (0x30)
//============================================================
#define SS_ERROR_CLOUD_INVALID_TOKEN                0x30000010  //  不合法的token
#define SS_ERROR_CLOUD_LICENSE_ALREADY_LOGIN        0x30000011  //  许可已登陆
#define SS_ERROR_CLOUD_LICENSE_EXPIRED              0x30000012  //  许可已到期
#define SS_ERROR_CLOUD_SESSION_KICKED               0x30000013  //  许可已在其他终端登录，当前许可会话被踢出
#define SS_ERROR_CLOUD_DEVELOPER_ACCOUNT            0x30000014  //  软件供应商账户异常，请联系软件供应商解决
#define SS_ERROR_CLOUD_LICENSE_LOGGED               0x30000015  //  许可已在其他终端登录，当前终端无法登录许可，请在其他终端退出登录后重试
#define SS_ERROR_CLOUD_INVALID_SESSSION             0x30001002  //  无效的session
#define SS_ERROR_CLOUD_SESSION_TIMEOUT              0x30001004  //  会话超时
#define SS_ERROR_CLOUD_LICENSE_NOT_EXISTS           0x31001001  //  许可不存在
#define SS_ERROR_CLOUD_LICENSE_NOT_ACTIVE           0x31001002  //  许可未激活
#define SS_ERROR_CLOUD_LICENSE_EXPIRED2             0x31001003  //  许可已过期
#define SS_ERROR_CLOUD_LICENSE_COUNTER_IS_ZERO      0x31001004  //  许可无使用次数
#define SS_ERROR_CLOUD_LICENSE_RUNTIME_TIME_OUT     0x31001005  //  许可无使用时间
#define SS_ERROR_CLOUD_LICENSE_MAX_CONNECTION       0x31001006  //  许可并发量限制
#define SS_ERROR_CLOUD_LICENSE_LOCKED               0x31001007  //  许可被锁定
#define SS_ERROR_CLOUD_LICENSE_DATA_NOT_EXISTS      0x31001008  //  许可数据不存在
#define SS_ERROR_CLOUD_LICENSE_STILL_UNAVAILABLE    0x31001010  //  许可未到开始使用时间

#define SS_ERROR_SO_BEFORE_START_TIME               0x51004004  //  许可未到开始时间 
#define SS_ERROR_SO_EXPIRED                         0x51004005  //  许可已经过期
#define SS_ERROR_SO_LICENSE_BIND_ERROR              0x51004006  //  许可绑定错误
#define SS_ERROR_SO_LICENSE_BIND_FULL               0x51004007  //  许可同时绑定的机器数已达上限
#define SS_ERROR_SO_LICENSE_UNBOUND                 0x51004008  //  许可已经解绑
#define SS_ERROR_SO_LICENSE_MAX_BIND_FULL           0x51004009  //  许可最大绑定机器数已大上限
#define SS_ERROR_SO_NOT_SUPPORTED_OFFLINE_BIND      0x51004010  //  该许可不支持离线绑定
#define SS_ERROR_SO_EXPIRED_C2D                     0x51004011  //  过期的C2D包
#define SS_ERROR_SO_DEVELOPER_ACCOUNT               0x51004013  //  软件供应商账户异常，请联系软件供应商解决
#define SS_ERROR_SO_OUTDATED_VERSION                0x51004014  //  用户工具版本过低，请升级到最新版本

#define SS_ERROR_LICKEY_QUERY_STATUS_REQ_ERROR          0x51005001  //  查询授权码状态请求发生异常
#define SS_ERROR_LICKEY_EXCHANGE_REQ_ERROR              0x51005002  //  授权码兑换请求发生异常
#define SS_ERROR_LICKEY_NOT_EXIST                       0x51005003  //  授权码不存在
#define SS_ERROR_LICKEY_DEDUCT_FAILED                   0x51005004  //  授权码许可扣费失败
#define SS_ERROR_LICKEY_C2D_INVALID_CHAR_ENCODING       0x51005005  //  C2D文件有误(需要UTF-8编码)
#define SS_ERROR_LICKEY_C2D_UNSUPPORTED_PROTO_TYPE      0x51005006  //  C2D文件有误(不支持的协议类型)
#define SS_ERROR_LICKEY_C2D_UNSUPPORTED_PROTO_VER       0x51005007  //  C2D文件有误(不支持的协议版本)
#define SS_ERROR_LICKEY_C2D_UNSUPPORTED_HWFP_VER        0x51005008  //  C2D文件有误(不支持的硬件指纹版本)
#define SS_ERROR_LICKEY_C2D_INCOMPATIBLE_MACHINE_ID     0x51005009  //  C2D文件有误(不匹配的机器ID)
#define SS_ERROR_LICKEY_C2D_UNSUPPORTED_INFO_VER        0x5100500A  //  C2D文件有误(不支持的机器信息版本)
#define SS_ERROR_LICKEY_C2D_OVERDUE                     0x5100500B  //  C2D文件有误(已过期，请重新生成)
#define SS_ERROR_LICKEY_C2D_OLD_SS_VER                  0x5100500D  //  C2D文件有误(旧版C2D，请使用最新版本的Virbox用户工具重新生成)
#define SS_ERROR_LICKEY_C2D_PLATFORM_JUST_4_TRADITIONAL 0x5100500E  //  该授权码仅能用于传统平台(Windows/Linux/Mac-OS)
#define SS_ERROR_LICKEY_C2D_PLATFORM_JUST_4_ANDROID     0x5100500F  //  该授权码仅能用于安卓平台(Android)
#define SS_ERROR_LICKEY_BIND_NO_AVAILABLE_LICENSE       0x51005011  //  不能绑定(无正常可用许可)
#define SS_ERROR_LICKEY_BIND_LICENSE_NOT_START          0x51005012  //  不能绑定(还未到许可的开始使用时间)
#define SS_ERROR_LICKEY_BIND_LICENSE_EXPIRED            0x51005013  //  不能绑定(许可已经过期)
#define SS_ERROR_LICKEY_BINDING_LIMIT_EXCEEDED          0x51005014  //  不能绑定(授权码同时绑定设备数已达上限)
#define SS_ERROR_LICKEY_BOUND_LIMIT_EXCEEDED            0x51005015  //  不能绑定(授权码累积绑定设备数已达上限)
#define SS_ERROR_LICKEY_BIND_NO_AVAILABLE_PKG           0x51005016  //  不能绑定(无可用升级包)

#define SS_ERROR_LICKEY_TERMINAL_UNBIND  			    0x51005018	//  授权码终端解绑失败，请联系软件供应商
#define SS_ERROR_LICKEY_TERMINAL_NOT_EXIST				0x51005019	//  服务端无法查找到绑定记录，请联系软件供应商
#define SS_ERROR_LICKEY_C2D_PKG_TYPE					0x51005020	//  C2D 文件有误（错误的数据包类型，请确保 C2D 文件是通过正确的方法获取的）
#define SS_ERROR_LICKEY_LICENSE_LOCKED					0x51005021	//  授权码许可无法绑定，原因是许可被锁定，请联系软件供应商解决
#define SS_ERROR_LICKEY_DOES_NOT_ALLOW_BIND             0x51005025  //  授权码不允许绑定
#define SS_ERROR_LICKEY_PASSWD_ENABLE                   0x51005030  //  授权码已启用密码，请输入正确的密码
#define SS_ERROR_LICKEY_PASSWD_ERROR                    0x51005031  //  授权码密码错误
#define SS_ERROR_BORROW_KEY_DISABLE                     0x51005032  //  授权码已关闭借阅功能
#define SS_ERROR_LICKEY_CLIENT_OUTDATED_VERSION         0x51005033  //  暂时无法激活许可，用户工具需要升级到最新版本
#define SS_ERROR_LICKEY_DEVICE_FORBIDDEN                0x51005034  //  软件供应商回收了该设备的使用权，不能再绑定当前授权码，请联系软件供应商解决

#define SS_ERROR_LICKEY_NOT_EXIST_V2                    0x5100612F  //  授权码不存在，请确认授权码是否正确
#define SS_ERROR_LICKEY_INVALID_C2D_DATA                0x51006130  //  无效的硬件信息数据
#define SS_ERROR_LICKEY_ABNORMAL_COST                   0x51006134  //  授权码许可扣费失败，请联系软件供应商

#define SS_ERROR_BORROW_KEY_NOT_EXIST                   0x51005026  //  借阅码不存在
#define SS_ERROR_BORROW_KEY_DELETED                     0x51005027  //  借阅码已删除
#define SS_ERROR_BORROW_KEY_ALREADY_REVOKED             0x51005028  //  借阅码已被回收
#define SS_ERROR_BORROW_KEY_EXPIRED                     0x51005029  //  借阅码已过期
#define SS_ERROR_BORROW_KEY_ALREADY_BOUND               0x5100502A  //  借阅码已经绑定
#define SS_ERROR_BORROW_KEY_BIND_FAILED                 0x5100502B  //  借阅码绑定失败
#define SS_ERROR_BORROW_KEY_BIND_NOT_EXIST              0x5100502C  //  不能解绑(未绑定)
#define SS_ERROR_BORROW_KEY_UNMATCHED_MACHINE_ID        0x5100502D  //  不能解绑(解绑请求与记录信息不一致)
#define SS_ERROR_BORROW_KEY_MAKE_PACKAGE_FAILED         0x5100502E  //  借阅码组装数据包失败


//============================================================
//              用户管理模块 (0x60)
//============================================================


//============================================================
//              web_server模块 (0x70)
//============================================================
#define SS_ERROR_WEB_SERVER_INIT_FAILED			0x70000000
#define SS_ERROR_WEB_INVALID_URI				0x70000001
#define SS_ERROR_MAKE_P7B						0x70000002

// 宏
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
