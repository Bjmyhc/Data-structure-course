#define _CRT_SECURE_NO_WARNINGS 1
#ifndef __LIBRARY_H__
#define __LIBRARY_H__

#include <stdio.h>
#include <windows.h>	//system
#include <string.h>		//...
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>	//bool
#include <sys/stat.h>

#define MAX_NAME 256
#define MAX_AUTHOR 128
#define MAX_PRESS 128
#define MAX_DATE 20
#define MAX_ISBN 15

#define DEFAULT_USER 3		//初始用户数量
#define EXPANSION_USER 3
#define MAX_ACCOUNT 20
#define MAX_PASSWPRD 20


//主界面选项
typedef enum {
	EXI,
	LOG,
	REG
} user_lr_choice;

//书籍操作菜单选项
typedef enum {
	EXIT,
	ADD,
	DEL,
	SEEK,
	CHANGE,
	SHOW,
	SETUP,
	POWER
} main_choice;

//查找菜单选项
typedef enum {
	//BY - 通过
	BY_EXIT,
	BY_NAME,
	BY_AUTHOR,
	BY_PRESS,
	BY_DATE,
	BY_ISBN,
	BY_PRICE,
	RECOVER,
	SHOW_THIS,
	FIRST_PAGE,
	LAST_PAGE,
	A_PAGE
} seek_and_sort_choice;

//设置选项
typedef enum{
	SET_EXIT,
	SET_DEFAULT_CAPACITY,
	SET_EXPANSION,
	SET_SHOWNUM,
	SET_SEEK_WAY,
	SET_IMPORT,
	SET_CHECK_DATE,
	SET_EXPORT,
	SET_BAK_DATA,
	SET_DEL_LIB,
	SET_RECOVER_DATA_BAK,
	SET_COLOR
} set_up_choice;

//教材日期
typedef struct Date {
	int y;
	int m;
	int d;
} date;

//教材信息
typedef struct Book {
	struct Date date;		//日期结构体
	float price;			//	价格
	char name[MAX_NAME];	//	书名
	char author[MAX_AUTHOR];//	作者
	char press[MAX_PRESS];  //	出版社
	char isbn[MAX_ISBN];    //	ISBN
	char is_deleted; 		// 标记字段，t表示存在，f表示已删除
} book;

//用户组信息
typedef struct User
{
	char account[MAX_ACCOUNT];		//用户名
	char password[MAX_PASSWPRD];	//密码
	char is_deleted;				//标记字段，t表示存在，f表示已删除
	int power;						//权限
} user;

//基本配置
typedef struct Setting
{
	int default_capacity;	//默认容量
	int expansion;			//每次扩容容量
	int show_num;			//每页展示数量
	int seek_way;			//查找精度
	int check_date;			//导入时检查日期
	char color[10];			//屏幕颜色
} setup;

//教材库结构
typedef struct Library {
	struct Book* data;			//指向一块空间，用于操作书籍数据
	struct User* user_data; 	//指向一块空间，用于操作用户数据   	
	struct Setting setup;		//基本配置
	int now_capacity;			//当前容量
	int show_capacity;			//展示容量
	int total_capacity;			//总容量						
	int now_user_capacity;		//当前用户容量
	int show_user_capacity;		//展示用户容量
	int total_user_capacity;	//用户总容量
	int login_user_location;	//已登录用户下标
} library;

//记录查找返回情况
typedef struct Seek
{
	int* location;			//记录查找得到的位置
	int num;				//记录查找个数
} seek_situation;

//初始化系统
void init_library(library* pLib);


//系统设置
void system_set_up(library* pLib);
//加载配置数据
void load_setup_information(library* pLib);
//保存配置数据
void save_setup_information(library* pLib);

#endif
