#ifndef __TOOL_H__
#define __TOOL_H__

#include "library.h"

#define MAX_TIME 64

//�����麯��
void input(char* hint, char* output, size_t size);
// 1|0 �����ж��Ƿ����
int if_input();
//��ӡ������Ϣ����
void warn_printf(int power);
//�޸ı���/������ɫ
void revise_screen_color(library* pLib);
//��ȡ����ʱ��
void local_time(char* local_time);
#endif
