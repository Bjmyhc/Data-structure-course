#ifndef __BOOK_H__
#define __BOOK_H__

#include "library.h"

//�̲�����
typedef struct Date {
	int y;
	int m;
	int d;
} date;

//�̲���Ϣ
typedef struct Book {
	struct Date date;		//���ڽṹ��
	float price;			//	�۸�
	char name[MAX_NAME];	//	����
	char author[MAX_AUTHOR];//	����
	char press[MAX_PRESS];  //	������
	char isbn[MAX_ISBN];    //	ISBN
	char is_deleted; 		// ����ֶΣ�t��ʾ���ڣ�f��ʾ��ɾ��
} book;




//��ӡ�鼮�����˵�
void print_main_book_menu();
//�鼮�����˵�
void main_book_menu(library* pLib);
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

//��ʼ���鼮����
void init_book_data(library* pLib);
//����̲���Ϣ
void save_book_information(library* pLib);
//���ؽ̲���Ϣ
void load_book_information(library* pLib);

//����̲���Ϣ
void import_book_information(library* pLib);
//�����̲���Ϣ
void export_book_information(library* pLib);

#endif
