#include "book.h"
#include "user.h"
#include "library.h"

int main()
{
	//����ϵͳw
	library lib;
	//��ʼ��ϵͳ
	init_library(&lib);
	//�����¼_ע�����
	
	do
	{
		if(user_login_register(&lib) == 1)
			main_book_menu(&lib);//�����鼮��������
	}while(1);
	
	return 0;
}
