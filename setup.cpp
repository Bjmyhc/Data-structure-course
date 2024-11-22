#include "book.h"
#include "user.h"
#include "tool.h"
#include "library.h"

/*��ӡ���ò˵�*/
void print_set_up_menu(library* pLib)
{
	system("cls");
	printf("         ����           \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~ \n");
	printf("�޸ĨK                  \n");
//	printf("  %u.Ĭ��������%d       \n", SET_DEFAULT_CAPACITY, pLib->setup.default_capacity);
//	printf("  %u.�������ݣ�%d       \n", SET_EXPANSION, pLib->setup.expansion);
	printf("  %u.ÿҳչʾ��%d       \n", SET_SHOW_NUM, pLib->setup.show_num);
	printf("  %u.���Ҿ��ȣ�%s       \n", SET_SEEK_WAY, pLib->setup.seek_way > 0 ? "��ȷ" : "ģ��");
//	printf("~~~~~~~~~~~~~~~~~~~~~~~ \n");
//	printf("����K                  \n");
//	printf("  %u.����̲�(.txt)     \n", SET_IMPORT);
//	printf("  %u.�������(y-m-d)��%s\n", SET_CHECK_DATE, pLib->setup.check_date > 0 ? "��" : "��");
//	printf("~~~~~~~~~~~~~~~~~~~~~~~ \n");
//	printf("�����K                  \n");
//	printf("  %u.�����̲�(.txt)     \n", SET_EXPORT);
//	printf("~~~~~~~~~~~~~~~~~~~~~~~ \n");
//	printf("�����K                  \n");
//	printf("  %u.������������       \n", SET_BAK_DATA);
//	printf("  %u.�����������       \n", SET_DEL_LIB);
//	printf("  %u.�ָ���������       \n", SET_RECOVER_DATA_BAK);
	printf("~~~~~~~~~~~~~~~~~~~~~~~ \n");
	printf("���Ի��K                \n");
	printf("  %u.�޸���Ļ��ɫ       \n", SET_COLOR);
	printf("~~~~~~~~~~~~~~~~~~~~~~~ \n");
	printf("�˺ŨK                  \n");
	printf("  %u.������Կ           \n", SET_POWER);
	printf("  %u.�޸�����           \n", SET_PASSWORD);
	printf("  %u.�˳��˺�           \n", SET_EXIT_ACCOUNT);
	printf("~~~~~~~~~~~~~~~~~~~~~~~ \n");
	if(pLib->user_data[pLib->login_user_location].power > 0){
		printf("  %u.�߼�����           \n", SET_HIGH_SETUP);
		printf("~~~~~~~~~~~~~~~~~~~~~~~ \n");
	}
	printf("  %u.�ص���ҳ           \n", SET_EXIT);
	printf("~~~~~~~~~~~~~~~~~~~~~~~ \n\n");
	printf("��ѡ��:>");
}

/*��ӡ�߼����ò˵�*/
void print_high_set_up_menu(library* pLib)
{
	system("cls");
	printf("        �߼�����        \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("�޸ĨK                  \n");
	printf("  %u.Ĭ��������%d       \n", HIGH_SET_DEFAULT_CAPACITY, pLib->setup.default_capacity);
	printf("  %u.�������ݣ�%d       \n", HIGH_SET_EXPANSION, pLib->setup.expansion);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("����K                  \n");
	printf("  %u.����̲�(.txt)     \n", HIGH_SET_IMPORT);
	printf("  %u.�������(y-m-d)��%s\n", HIGH_SET_CHECK_DATE, pLib->setup.check_date > 0 ? "��" : "��");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("�����K                  \n");
	printf("  %u.�����̲�(.txt)     \n", HIGH_SET_EXPORT);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("�����K                  \n");
	printf("  %u.������������       \n", HIGH_SET_BAK_DATA);
	printf("  %u.�����������       \n", HIGH_SET_DEL_LIB);
	printf("  %u.�ָ���������       \n", HIGH_SET_RECOVER_DATA_BAK);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("  %u.�˳��߼�����       \n", SET_EXIT);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf("��ѡ��:>");
}


/*�ı�Ĭ������*/
void change_default_capacity(library* pLib)
{
	int new_default_capacity = 0;
	
	do
	{
		printf("������Ĭ������:>");
		scanf(" %d", &new_default_capacity);
		getchar();
		
		if (new_default_capacity > 0)
		{
			if (pLib->now_capacity != 0)
			{
				printf("���ڽ̲ģ��޷��޸�\n");
				printf("�����������...");
				_getch();
				return;
			}
			else
			{
				pLib->setup.default_capacity = new_default_capacity;
				//ִ�����ݲ���
				book* ptr = (book*)realloc(pLib->data, (pLib->setup.default_capacity) * sizeof(book));
				//�������ʧ��
				if (ptr == NULL)
				{
					perror("realloc_capacity_by_situp");
				}
				else
				{
					pLib->data = ptr;
					pLib->total_capacity = pLib->setup.default_capacity;
					printf("���ݳɹ���\n");
					return;
				}
				printf("�����������...");
				_getch();
			}
		}
		else
		{
			printf("��������Чֵ\n");
		}
	}
	while (1);
}

/*�ı�ÿ��������*/
void change_expansion(library* pLib)
{
	int new_expansion = 0;
	do
	{
		printf("��������������:>");
		scanf("%d", &new_expansion);
		getchar();
		
		if (new_expansion > 0)
		{
			pLib->setup.expansion = new_expansion;
			printf("�޸ĳɹ���\n");
			break;
		}
		else
		{
			printf("��������Чֵ\n");
		}
	}
	while (1);
}

/*�ı�ÿҳչʾ����*/
void change_show_num(library* pLib)
{
	int new_show_num = 0;
	do
	{
		printf("����ÿҳչʾ��:>");
		scanf("%d", &new_show_num);
		getchar();
		if (new_show_num > 0)
		{
			pLib->setup.show_num = new_show_num;
			printf("�޸ĳɹ���\n");
			break;
		}
		else
		{
			printf("��������Чֵ\n");
		}
	}
	while (1);
}

/*�ָ������ļ�*/
void recover_data_bak(library* pLib)
{
	if (if_input())
	{
		//�������ļ�������Ϊ�����ļ�
		int result = rename(".\\Library\\book_information.dat.bak", ".\\Library\\book_information.date");
		//��������ɹ�
		if (result == 0)
		{
			//�������ļ�������Ϊ�����ļ�
			rename(".\\Library\\book_information.dat", ".\\Library\\book_information.dat.bak");
			//�������ļ�������Ϊ�����ļ�
			int re = rename(".\\Library\\book_information.date", ".\\Library\\book_information.dat");
			
			if (re == 0)
			{
				printf("�ָ��ɹ���");
				init_library(pLib);
			}
			else
			{
				printf("�ָ�ʧ�ܣ�");
			}
		}
		else
		{
			printf("���ޱ��ݣ�\n");
			
		}
		printf("�����������...");
		_getch();
	}
}

/*��������*/
void back_information()
{
	if (CopyFile(".\\Library\\book_information.dat", ".\\Library\\book_information.dat.bak", FALSE))
		printf("\n���ݾ����ݳɹ�\n");
	else
		printf("\n���ݾ�����ʧ��\n");
}

/*�������*/
void delete_library(library* pLib)
{
	if (if_input())
	{
		if (pLib->now_capacity == 0)
		{
			printf("�̲Ŀ�Ϊ��\n");
		}
		else
		{
			remove(".\\Library\\book_information.dat");
			
			printf("ɾ���ɹ� ");
			init_book_data(pLib);
		}
		printf("�����������...");
		_getch();
	}
}

void change_password(library* pLib)
{

	
	if(if_input())
	{
		char space[MAX_PASSWPRD];
		input("�����������:>", space, MAX_PASSWPRD);
		if(0 == strcmp(space, pLib->user_data[pLib->login_user_location].password))
		{
			input("������������:>", space, MAX_PASSWPRD);
			strcpy(pLib->user_data[pLib->login_user_location].password, space);
			printf("�޸ĳɹ���\n");
		}
		else
		{
			printf("�������\n");
		}
		printf("�����������...");
		_getch();
	}
}
//�߼�ϵͳ����
void high_system_set_up(library* pLib)
{
	high_set_up_choice user_choice;
	
	do
	{
		//��ӡ�߼����ò˵�
		print_high_set_up_menu(pLib);
		
		scanf("%u", (unsigned int*)&user_choice);
		getchar();
		
		switch (user_choice)
		{
		case SET_EXIT:
			return;
		case HIGH_SET_DEFAULT_CAPACITY:
			change_default_capacity(pLib);//�ı�Ĭ������
			break;
		case HIGH_SET_EXPANSION:
			change_expansion(pLib);
			break;
		case HIGH_SET_RECOVER_DATA_BAK:
			recover_data_bak(pLib);
			break;
		case HIGH_SET_DEL_LIB:
			delete_library(pLib);
			break;
		case HIGH_SET_IMPORT:
			//����̲���Ϣ
			import_book_information(pLib);
			break;
		case HIGH_SET_CHECK_DATE:
			if (pLib->setup.check_date == 1)
				pLib->setup.check_date = 0;
			else
				pLib->setup.check_date = 1;
			break;
		case HIGH_SET_EXPORT:
			//�����̲���Ϣ
			export_book_information(pLib);
			break;
		case HIGH_SET_BAK_DATA:
			//��������
			back_information();
			printf("----------\n");
			printf("�����������...");
			_getch();
			break;
		default:
			printf("\a");
			//Sleep(400);//��ͣ400����
			break;
		}
	}
	while (1);
}

//ϵͳ����
int system_set_up(library* pLib)
{
	int power = 0;
	
	set_up_choice user_choice;
	
	do
	{
		power = pLib->user_data[pLib->login_user_location].power;
		//��ӡ���ò˵�
		print_set_up_menu(pLib);
		
		scanf("%u", (unsigned int*)&user_choice);
		getchar();
		
		switch (user_choice)
		{
		case SET_EXIT:
			return 0;
//		case SET_DEFAULT_CAPACITY:
//			change_default_capacity(pLib);//�ı�Ĭ������
//			break;
//		case SET_EXPANSION:
//			change_expansion(pLib);
//			break;
		case SET_SHOW_NUM:
			change_show_num(pLib);
			break;
		case SET_SEEK_WAY:
			pLib->setup.seek_way = pLib->setup.seek_way > 0 ? 0 : 1;
			break;
//		case SET_RECOVER_DATA_BAK:
//			recover_data_bak(pLib);
//			break;
//		case SET_DEL_LIB:
//			delete_library(pLib);
//			break;
//		case SET_IMPORT:
//			//����̲���Ϣ
//			import_book_information(pLib);
//			break;
//		case SET_CHECK_DATE:
//			if (pLib->setup.check_date == 1)
//				pLib->setup.check_date = 0;
//			else
//				pLib->setup.check_date = 1;
//			break;
//		case SET_EXPORT:
//			//�����̲���Ϣ
//			export_book_information(pLib);
//			break;
//		case SET_BAK_DATA:
//			//��������
//			back_information();
//			printf("----------\n");
//			printf("�����������...");
//			_getch();
//			break;
		case SET_COLOR:
			revise_screen_color(pLib);
			break;
		case SET_POWER:
			power > 0 ? warn_printf(power) : user_activation(pLib);//������Կ
			break;
		case SET_PASSWORD:
			change_password(pLib);
			break;
		case SET_EXIT_ACCOUNT:
			if(if_input())
			{
				//����̲���Ϣ
				save_book_information(pLib);
				//������������
				save_setup_information(pLib);
	//			//����ϵͳ
	//			destroyed_library(pLib);
				return 1;
			}
			break;
		case SET_HIGH_SETUP:
			power > 0 ? high_system_set_up(pLib) : warn_printf(power);
			break;
		default:
			printf("\a");
			//Sleep(400);//��ͣ400����
			break;
		}
	}
	while (1);
}
