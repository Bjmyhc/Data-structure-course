#ifndef __USER_H__
#define __USER_H__
#include "library.h"

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
//�����û���
void find_user_by_account(const library* pLib, char account[MAX_ACCOUNT], seek_situation* situation);
//�����û���Ϣ
void save_user_information(library* pLib);
#endif
