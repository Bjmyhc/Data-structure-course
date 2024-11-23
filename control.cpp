#include "library.h"
#include "user.h"
int administrator_num(const library* pLib)
{
	int i = 0;
	int num = 0;
	for(i = 0; i < pLib->now_user_capacity; i++)
	{
		if(pLib->user_data[i].is_deleted == 't')
		{
			if(pLib->user_data[i].power == 1)
			{
				num++;
			}
		}
	}
	return num;
}

/*��ӡ��̨�˵�*/
void print_control_menu(const library* pLib)
{
	system("cls");
	//��ѯ����Ա����
	int admin_num  = administrator_num(pLib);
//	printf("����ǰ�û�[%s],Ȩ��Ϊ��%s\n",pLib->user_data[pLib->login_user_location].account, 
//		power > 1 ? "����": power > 0 ? "����Ա" : "��ͨ�û�" );
	printf("Ŀǰ��%d���û�,���й���Ա%d��\n",pLib->total_user_capacity, admin_num);
	printf("-----------------------\n");
	printf("|**** %u.����û� **** |\n", CONTROL_ADD);
	printf("|**** %u.ɾ���û� **** |\n", CONTROL_DEL);
	printf("|**** %u.�����û� **** |\n", CONTROL_SEEK);
	printf("|**** %u.�޸���Ϣ **** |\n", CONTROL_CHANGE);
	printf("|**** %u.�����û� **** |\n", CONTROL_SHOW);
	printf("|**** %u.��̨���� **** |\n", CONTROL_SETUP);
	printf("|**** %u.�˳���̨ **** |\n", CONTROL_EXIT);
	printf("-----------------------\n\n");
	printf("��ѡ��>:");
}

//��ӡ��̨����
void print_user_control_setup(library* pLib)
{
	system("cls");
	printf("        ����        \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("����K                  \n");
	printf("  %u.�����û�(.txt)     \n", USER_IMPORT);
//	printf("  %u.��������ԣ�%s\n", USER_CHECK, pLib->setup.check_user_data > 0 ? "��" : "��");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("�����K                  \n");
	printf("  %u.�����û�(.txt)     \n", USER_EXPORT);
//	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
//	printf("�����K                  \n");
//	printf("  %u.������������       \n", HIGH_SET_BAK_DATA);
//	printf("  %u.�����������       \n", HIGH_SET_DEL_LIB);
//	printf("  %u.�ָ���������       \n", HIGH_SET_RECOVER_DATA_BAK);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("  %u.�˳���̨����       \n", USER_EXIT);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf("��ѡ��:>");
}

//��̨����
void user_control_setup(library* pLib)
{
	user_setup_choice user_choice;
	
	do
	{
		//��ӡ��̨���ò˵�
		print_user_control_setup(pLib);
		
		scanf("%u", (unsigned int*)&user_choice);
		getchar();
		
		switch (user_choice) {
		case USER_EXIT:
			return;
		case USER_IMPORT:
			user_import(pLib);
			break;
//		case USER_CHECK:
////			user_check(pLib);
//			break;
		case USER_EXPORT:
			user_export(pLib);
			break;
		default:
			//TODO
			break;
		}
		
	}while(1);
	
}

//��̨����
void user_control(library* pLib)
{
	control_choice user_choice;//�û�ѡ��

	do
	{
		print_control_menu(pLib);//��ӡ�˵�
		
		user_choice = (control_choice)99;//��ʼ��ѡ���ֹ����ֵ���빦��
		scanf(" %u", (unsigned int*)&user_choice);	//��ȡ�û�����ѡ��
		getchar();
		
		switch (user_choice)
		{
		case CONTROL_EXIT:
			return;
		case CONTROL_ADD:
			user_register(pLib);//�û�ע��
			break;
		case CONTROL_DEL:
			user_delete(pLib);
			break;
		case CONTROL_SEEK:
			user_seek(pLib);
			break;
		case CONTROL_CHANGE:
			user_change(pLib);
			break;
		case CONTROL_SHOW:
			user_print(pLib);
			break;
		case CONTROL_SETUP:
			user_control_setup(pLib);
			break;
		default:
			//	printf("������Ч������������!");
			break;
		}
	}while(1);
}


