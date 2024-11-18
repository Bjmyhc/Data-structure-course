#include "library.h"
#include "book.h"
#include "tool.h"
#include "user.h"
/////////////////////////ϵͳ���������ٺ���///////////////////////////////

/*��ʼ��ϵͳ*/
void init_library(library* pLib)
{
	//����������ݵ��ļ���
	struct stat sb;
	int flag = 0;
	
	if (stat("Library", &sb) != 0)//����ļ��в�����
		system("mkdir Library");
	
	//����������Ϣ
	load_setup_information(pLib);

	//����Ĭ������
	pLib->data = (book*)malloc(pLib->setup.default_capacity * sizeof(book));
	//�����û��ռ�
	pLib->user_data = (user*)malloc(DEFAULT_USER*sizeof(user));
	
	if(pLib->data == NULL)
	{
		perror("init_library:init_data");
		flag = 1;
	}
	else if(pLib->user_data == NULL)
	{
		perror("init_library:init_user");
		flag = 1;
	}
	
	if(flag == 1)
	{
		printf("�����������...");
		_getch();
		return;
	}
	
	//��ʼ���鼮����
	pLib->now_capacity = 0;
	pLib->show_capacity = 0;
	pLib->total_capacity = pLib->setup.default_capacity;
	load_book_information(pLib);
	//��ʼ���û�����
	pLib->now_user_capacity = 0;
	pLib->show_user_capacity = 0;
	pLib->total_user_capacity = DEFAULT_USER;//���������Ƿ񼯳ɵ���������
	load_user_information(pLib);
}

/*����ϵͳ*/
void destroyed_library(library* pLib)
{
	free(pLib->data);
	pLib->data = NULL;
}

//����������Ϣ
void load_setup_information(library* pLib)
{
	//�����������ļ���
	FILE* pSite = fopen(".\\Library\\setup.info", "rb");

	//������ݲ�ȱʧ
	if (pSite != NULL)
	{
		//��ȡ������Ϣ
		fread(&(pLib->setup), sizeof(setup), 1, pSite);
		//�ر��ļ���
		fclose(pSite);
		pSite = NULL;
	}
	else
	{
		//û��������Ϣ�����û�������
		pLib->setup.default_capacity = 10000;	//Ĭ������
		pLib->setup.expansion = 1000;			//ÿ����������
		pLib->setup.show_num = 12;				//ÿҳչʾ����
		pLib->setup.seek_way = 0;				//���Ҿ���
		pLib->setup.check_date = 0;				//����ʱ�������
		strcpy(pLib->setup.color, "color 01");	//��Ļ��ɫ
		save_setup_information(pLib);			//����һ��
	}
	//������Ļ��ɫ
	system(pLib->setup.color);
}

//������������
void save_setup_information(library* pLib)
{
	//���ļ�
	FILE* pWrite = fopen(".\\Library\\setup.info", "wb");
	//�������ʧ��
	if (pWrite == NULL)
	{
		perror("save_setup_information");
		printf("�����������...");
		_getch();
		return;
	}
	//�Զ����Ʒ�ʽд��
	fwrite(&(pLib->setup), sizeof(setup), 1, pWrite);

	//�ر��ļ���
	fclose(pWrite);
	pWrite = NULL;
}   

