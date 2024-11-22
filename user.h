#ifndef __USER_H__
#define __USER_H__
#include "library.h"

//�û�����Ϣ
typedef struct User
{
	char account[MAX_ACCOUNT];		//�û���
	char password[MAX_PASSWPRD];	//����
	char is_deleted;				//����ֶΣ�t��ʾ���ڣ�f��ʾ��ɾ��
	int power;						//Ȩ��
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
//��¼_ע�����
int user_login_register(library* pLib);
//�����û���Ϣ
void load_user_information(library* pLib);
//����û�����
void check_user_capacity(library* pLib);
//�û���¼
int user_login(library* pLib);
//�û�ע��
void user_register(library* pLib);
//�û��������Ա
void user_activation(library* pLib);
//ɾ���û���Ϣ
void user_delete(library* pLib);
//�����û���Ϣ
void user_seek(library* pLib);
//�޸��û���Ϣ
void user_change(library* pLib);
//��ӡ�û���Ϣ
void user_print(const library* pLib);
//�����û�������
void find_user_by_account(const library* pLib, char account[MAX_ACCOUNT], seek_situation* situation);
//��ʼ���û�����
void init_user_data(library* pLib);
//�����û���Ϣ
void save_user_information(library* pLib);
//��̨�����û�
void user_control(library* pLib);
#endif
