#ifndef __USER_H__
#define __USER_H__
#include "library.h"

//用户组信息
typedef struct User
{
	char account[MAX_ACCOUNT];		//用户名
	char password[MAX_PASSWPRD];	//密码
	char is_deleted;				//标记字段，t表示存在，f表示已删除
	int power;						//权限
} user;

//登录_注册界面
int user_login_register(library* pLib);
//加载用户信息
void load_user_information(library* pLib);
//检查用户容量
void check_user_capacity(library* pLib);
//用户登录
int user_login(library* pLib);
//用户注册
void user_register(library* pLib);
//用户激活管理员
void user_activation(library* pLib);
//查找用户名
void find_user_by_account(const library* pLib, char account[MAX_ACCOUNT], seek_situation* situation);
//保存用户信息
void save_user_information(library* pLib);
#endif
