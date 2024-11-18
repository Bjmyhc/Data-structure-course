#ifndef __USER_H__
#define __USER_H__
#include "library.h"

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
//查找用户名
void find_user_by_account(const library* pLib, char account[MAX_ACCOUNT], seek_situation* situation);
//保存用户信息
void save_user_information(library* pLib);
#endif
