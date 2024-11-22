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

typedef enum
{
	CONTROL_EXIT,
	CONTROL_ADD,
	CONTROL_DEL,
	CONTROL_SEEK,
	CONTROL_CHANGE,
	CONTROL_SHOW,
	CONTROL_SETUP
} control_choice;

typedef enum
{
	CHANGE_EXIT,
	CHANGE_PASSWORD,
	CHANGE_POWER
} change_choice;
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
//删除用户信息
void user_delete(library* pLib);
//查找用户信息
void user_seek(library* pLib);
//修改用户信息
void user_change(library* pLib);
//打印用户信息
void user_print(const library* pLib);
//根据用户名查找
void find_user_by_account(const library* pLib, char account[MAX_ACCOUNT], seek_situation* situation);
//初始化用户数据
void init_user_data(library* pLib);
//保存用户信息
void save_user_information(library* pLib);
//后台管理用户
void user_control(library* pLib);
#endif
