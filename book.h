#ifndef __BOOK_H__
#define __BOOK_H__

#include "library.h"
//��ӡ�鼮�����˵�
void print_main_book_menu();
//�鼮�����˵�
void main_book_menu(library* pLib);
//����ϵͳ
void destroyed_library(library* pLib);
//��ӽ̲���Ϣ
void add_book_information(library* pLib);
//ɾ���̲���Ϣ
void dele_book_information(library* pLib);
//���ҽ̲���Ϣ
void seek_book_information(const library* pLib);
//�޸Ľ̲���Ϣ
void change_book_information(library* pLib);
//��ӡ�̲���Ϣ
void show_book_information(const library* pLib);

//����̲���Ϣ
void save_book_information(library* pLib);
//���ؽ̲���Ϣ
void load_book_information(library* pLib);

//����̲���Ϣ
void import_book_information(library* pLib);
//�����̲���Ϣ
void export_book_information(library* pLib);

#endif
