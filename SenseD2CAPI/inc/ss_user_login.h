
#ifndef _SS_USER_LOGIN_H
#define _SS_USER_LOGIN_H

#ifndef SSAPI
#if defined WIN32 || defined _WIN32 || defined _WIN64
#define SSAPI __stdcall
#else
#define SSAPI
#endif
#endif

#define SS_CLOUD_ERROR_SUCCESS						0 		//	成功	
#define SS_CLOUD_ERROR_PASSWORD						1		//	用户不存在密码错误
#define SS_CLOUD_ERROR_INVALID_PARAM				2		//	参数错误	
#define SS_CLOUD_ERROR_SERVICE_STOPPED 				3   	//	用户登录服务未启动
#define SS_CLOUD_ERROR_TIMEOUT 						4		//	登录超时
#define SS_CLOUD_ERROR_GET_USER_INFO                5       //  获取用户信息失败
#define SS_CLOUD_ERROR_NET_ERROR                    6       //  网络错误
#define SS_CLOUD_ERROR_COULDNT_RESOLVE_HOST         7       //  请求服务地址不可达
#define SS_CLOUD_ERROR_ACCOUNT_DISABLED             8       //  当前账号被禁用
#define SS_CLOUD_ERROR_UNKNOWN      				-1		//	待定义的详细错误

#define SS_CLOUD_MAX_USER_GUID_SIZE 				128		//	最大用户GUID长度


#ifdef __cplusplus
extern "C"{
#endif

/*
*	@param[in]  url		    传入私有化URL访问地址，传空会使用默认URL
*	@param[in]  user_name 	用户名
*	@param[in]  passwd 		密码
*	@param[out] user_guid   返回用户GUID字符串（logout），最大需SS_CLOUD_MAX_USER_GUID_SIZE字节
*	@return 成功返回 SS_CLOUD_ERROR_SUCCESS，失败返回其它的错误码
*/
int SSAPI ss_cloud_user_login(const char *url, const char *user_name, const char *passwd, char *user_guid);


/*
*	@param[in]  user_info ss_cloud_user_login 返回的user_info
*	@return 成功返回 SS_CLOUD_ERROR_SUCCESS，失败返回其它的错误码
*/
int SSAPI ss_cloud_user_logout(const char *user_guid);

/*  配置接口
*   @param[in]  config 配置参数（JSON）
*               1.指定访问云服务地址和超时，{"auth_url":"https://auth.senseyun.com", "timeout":6000}
*                   "auth_url"：此参数用于兼容旧版本调用，也可以通过 ss_cloud_user_login 参数指定，但优先使用配置接口设置URL地址。
*                   "timeout"：请求超时（毫秒）
*   @return 成功返回 SS_CLOUD_ERROR_SUCCESS，失败返回其它的错误码
*   @remark 配置接口必须在调用其他接口前调用并指定参数才能生效。
*/
int SSAPI ss_cloud_config(const char* config);

#ifdef __cplusplus
}
#endif

#endif
