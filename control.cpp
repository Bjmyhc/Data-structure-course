#include "library.h"
#include "user.h"

/*��ӡ��̨�˵�*/
void print_control_menu(const library* pLib)
{
	int power = pLib->user_data[pLib->login_user_location].power;
	
	system("cls");
//	printf("����ǰ�û�[%s],Ȩ��Ϊ��%s\n",pLib->user_data[pLib->login_user_location].account, 
//		power > 1 ? "����": power > 0 ? "����Ա" : "��ͨ�û�" );
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

//��̨����
void user_control(library* pLib)
{
	control_choice user_choice;//�û�ѡ��

	do
	{
		print_control_menu(pLib);//��ӡ���˵�
		
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
			break;
		default:
			//	printf("������Ч������������!");
			break;
		}
	}while(1);
}
