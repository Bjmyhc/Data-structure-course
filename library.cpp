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
	
	if (stat("Library", &sb) != 0)//����ļ��в�����
		system("mkdir Library");
	//����������Ϣ
	load_setup_information(pLib);
	//��ʼ���û�����
	init_user_data(pLib);
	//��ʼ��ͼ������
	init_book_data(pLib);
}

/*����ϵͳ*/
void destroyed_library(library* pLib)
{
	free(pLib->data);
	pLib->data = NULL;
	free(pLib->user_data);
	pLib->user_data = NULL;
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
		pLib->setup.default_capacity = 1000;	//Ĭ������
		pLib->setup.expansion = 1000;			//ÿ����������
		pLib->setup.show_num = 12;				//ÿҳչʾ����
		pLib->setup.seek_way = 0;				//���Ҿ���
		pLib->setup.check_date = 0;				//����̲�ʱ�������
//		pLib->setup.check_user_data = 0;		//�����û�ʱ������롢Ȩ��
		strcpy(pLib->setup.color, "color 0A");	//��Ļ��ɫ
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

