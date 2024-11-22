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

#define DEFAULT_USER 3		//��ʼ�û�����
#define EXPANSION_USER 3
#define MAX_ACCOUNT 20
#define MAX_PASSWPRD 20


//������ѡ��
typedef enum {
	EXI,
	LOG,
	REG
} user_lr_choice;



//���Ҳ˵�ѡ��
typedef enum {
	//BY - ͨ��
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

//�����˵�ѡ��
typedef enum {
	EXIT,
	ADD,
	DEL,
	SEEK,
	CHANGE,
	SHOW,
	SETUP,
	USER
//	POWER
} main_choice;

//����ѡ��
typedef enum{
	SET_EXIT,
//	SET_DEFAULT_CAPACITY,
//	SET_EXPANSION,
	SET_SHOW_NUM,
	SET_SEEK_WAY,
//	SET_IMPORT,
//	SET_CHECK_DATE,
//	SET_EXPORT,
//	SET_BAK_DATA,
//	SET_DEL_LIB,
//	SET_RECOVER_DATA_BAK,
	SET_COLOR,
	SET_POWER,
	SET_PASSWORD,
	SET_EXIT_ACCOUNT,
	SET_HIGH_SETUP
} set_up_choice;

//�߼�����ѡ��
typedef enum{
	HIGH_SET_EXIT,
	HIGH_SET_DEFAULT_CAPACITY,
	HIGH_SET_EXPANSION,
	HIGH_SET_IMPORT,
	HIGH_SET_CHECK_DATE,
	HIGH_SET_EXPORT,
	HIGH_SET_BAK_DATA,
	HIGH_SET_DEL_LIB,
	HIGH_SET_RECOVER_DATA_BAK,
} high_set_up_choice;

//��������
typedef struct Setting
{
	int default_capacity;	//Ĭ������
	int expansion;			//ÿ����������
	int show_num;			//ÿҳչʾ����
	int seek_way;			//���Ҿ���
	int check_date;			//����ʱ�������
	char color[10];			//��Ļ��ɫ
} setup;

//�̲Ŀ�ṹ
typedef struct Library {
	struct Book* data;			//ָ��һ��ռ䣬���ڲ����鼮����
	struct User* user_data; 	//ָ��һ��ռ䣬���ڲ����û�����   	
	struct Setting setup;		//��������
	int now_capacity;			//��ǰ����
	int show_capacity;			//չʾ����
	int total_capacity;			//������						
	int now_user_capacity;		//��ǰ�û�����
	int show_user_capacity;		//չʾ�û�����
	int total_user_capacity;	//�û�������
	int login_user_location;	//�ѵ�¼�û��±�
} library;

//��¼���ҷ������
typedef struct Seek
{
	int* location;			//��¼���ҵõ���λ��
	int num;				//��¼���Ҹ���
} seek_situation;

//��ʼ��ϵͳ
void init_library(library* pLib);


//ϵͳ����
int system_set_up(library* pLib);
//������������
void load_setup_information(library* pLib);
//������������
void save_setup_information(library* pLib);

//����ϵͳ
void destroyed_library(library* pLib);
#endif
