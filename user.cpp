#include "library.h"
#include "user.h"
#include "book.h"
#include "tool.h"

void print_user_login_register_menu()
{
		system("cls");
		printf("--------------------\n");
		printf("|**** %u.��¼ **** |\n", LOG);
		printf("|**** %u.ע�� **** |\n", REG);
		printf("|**** %u.�˳� **** |\n", EXI);
		printf("--------------------\n\n");
		printf("��ѡ��>:");
	
}
int user_login_register(library* pLib)
{
	user_lr_choice user_choice;//�û�ѡ��

	do{
		print_user_login_register_menu();	//��ӡ��¼ע��˵�
		user_choice = (user_lr_choice)99;	//��ʼ��ѡ���ֹ����ֵ���빦��
		scanf(" %u", (unsigned int*)&user_choice);			//��ȡ�û�����ѡ��
		getchar();
		
		switch (user_choice) {
		case EXI:
			//�����û���Ϣ
			save_user_information(pLib);
			exit(0);
		case LOG:
			if(user_login(pLib))
				return 1;
			else
				return 0;
			break;
		case REG:
			user_register(pLib);
			break;
		default:
			//	printf("������Ч������������!");
			break;
		}
	}while(1);
	return 0;
}

//�û���¼
int user_login(library* pLib)
{
	char account[MAX_ACCOUNT];
	char password[MAX_PASSWPRD];
	int i = 0;
	bool flag = false;
	input("�������û���:>", account, MAX_ACCOUNT);
	input("����������:>", password, MAX_PASSWPRD);
	
	//�ж��û��Ƿ����
	for (i = 0; i < pLib->now_user_capacity; i++)
	{
		if (0 == strcmp(pLib->user_data[i].account, account))
		{
			flag = true;
			break;
		}
	}		
	//�ж������Ƿ���ȷ
	if(flag == true)
		if(0 == strcmp(pLib->user_data[i].password, password)){
			pLib->login_user_location = i;
			return 1;
		}
	else
		printf("�������\n");
	else
		printf("�û�������,��ע��!\n");
	getchar();
	return 0;
}
//�û�ע��
void user_register(library* pLib)
{
	char space[MAX_ACCOUNT];
	int if_change_check_way = 0;//�Ƿ�ı��˼�鷽ʽ
	seek_situation seek;
	
	//�������
	check_user_capacity(pLib);
	//¼���û���Ϣ
	do
	{
		input("�������û���:>", space, MAX_ACCOUNT);
		
		//���þ�ȷ�����û�
		if (pLib->setup.seek_way == 0)
		{
			pLib->setup.seek_way = 1;
			if_change_check_way = 1;
		}
		//����û��Ƿ�����ظ�
		find_user_by_account(pLib, space, &seek);
//		printf("������%d\n", seek.num);
		//����ı��˼�鷽ʽ����Ļ���
		if (if_change_check_way == 1)
		{
			pLib->setup.seek_way = 0;
			if_change_check_way = 0;
		}
		//��������ڣ���¼��
		if (seek.num == 0)
		{
			strcpy(pLib->user_data[pLib->now_user_capacity].account, space);
			break;
		}
		else
		{
			printf("���û��Ѵ���\n");
			printf("�����������...");
			_getch();
			return;
		}
	}while(1);
	
	input("����������:>", pLib->user_data[pLib->now_user_capacity].password, MAX_PASSWPRD);
	
	//�����û�����
	if(0 == strcmp(space, "admin"))
		pLib->user_data[pLib->now_user_capacity].power = 2;
	else
		pLib->user_data[pLib->now_user_capacity].power = 0;
	
	pLib->user_data[pLib->now_user_capacity].is_deleted = 't';
	pLib->now_user_capacity++;
	pLib->show_user_capacity++;
	
	//�ͷŲ���ʱ�����Ķ�̬����
	free(seek.location);
	seek.location = NULL;
	
	printf("ע��ɹ���");
	printf("�����������...");
	_getch();
}

//�û��������Ա
void user_activation(library* pLib)
{
	char space[MAX_TIME];
	char ret_time[MAX_TIME];
	
	input("�����뼤����Կ:>",space, MAX_TIME);
	local_time(ret_time);
	
	if(0 == strcmp(space, ret_time))
	{
		pLib->user_data[pLib->login_user_location].power = 1;
		printf("����ɹ����������ѻ�ȡ����Ա�ʸ�\n");
//		printf("local:%d, power:%d",pLib->login_user_location, pLib->user_data[pLib->login_user_location].power);
	}
	else
	{
		printf("����ʧ�ܣ�\n");
	}
	printf("�����������...");
	_getch();
}

/*�����û���Ϣ*/
void load_user_information(library* pLib)
{
	//����book���ͽṹ��
	user tmp = { 0 };
	FILE* pRead = fopen(".\\Library\\user_information.dat", "rb");
	
	if (pRead == NULL)
	{
		perror("load_user");
		printf("�����������...");
		getchar();
		return;
	}
	
	//�Զ����Ƶķ�ʽ��ȡ
	while (fread(&tmp, sizeof(user), 1, pRead))
	{
		check_user_capacity(pLib);
		pLib->user_data[pLib->now_user_capacity] = tmp;	
		pLib->now_user_capacity++;
		pLib->show_user_capacity++;
	}
	//�ر��ļ���
	fclose(pRead);
	pRead = NULL;
}

/*�û���������*/
void check_user_capacity(library* pLib)
{
	//�����������
	if (pLib->now_user_capacity == pLib->total_user_capacity)
	{
		//����
		user* ptr = (user*)realloc(pLib->user_data, (pLib->total_user_capacity + EXPANSION_USER) * sizeof(user));
		//�������ʧ��
		if (ptr == NULL)
		{
			perror("user_realloc_capacity");
			printf("�����������...");
			_getch();
		}
		else
		{
			pLib->user_data = ptr;
			pLib->total_user_capacity += EXPANSION_USER;
//			printf("���ݳɹ���\n");
		}
	}
}

/*�����û���*/
void find_user_by_account(const library* pLib, char account[MAX_ACCOUNT], seek_situation* situation)
{
	int i = 0;
	int j = 0;
	//��ʼ�������������
	situation->location = (int*)malloc(pLib->now_user_capacity * sizeof(int));
	memset(situation->location, 0, pLib->now_user_capacity * sizeof(int));
	situation->num = 0;
	
	if (pLib->setup.seek_way == 1)
	{
		for (i = 0; i < pLib->now_user_capacity; i++)
		{
			if (0 == strcmp(pLib->user_data[i].account, account))
			{
				if (pLib->user_data[i].is_deleted == 't')
				{
					situation->location[j++] = i;
					situation->num++;
				}
			}
		}
	}
	else
	{
		for (i = 0; i < pLib->now_user_capacity; i++)
		{
			if (strstr(pLib->user_data[i].account, account) != NULL)
			{
				if (pLib->user_data[i].is_deleted == 't')
				{
					situation->location[j++] = i;
					situation->num++;
				}
			}
		}
	}
	
}

/*�����û���Ϣ*/
void save_user_information(library* pLib)
{
	int i = 0;
	//���ļ�
	FILE* pWrite = fopen(".\\Library\\user_information.dat", "wb");
	//�������ʧ��
	if (pWrite == NULL)
	{
		perror("save_user");
		printf("�����������...");
		_getch();
		return;
	}
	
	//�Զ����Ʒ�ʽд��
	for (i = 0; i < pLib->now_user_capacity; i++)
	{
		if (pLib->user_data[i].is_deleted == 't')
			fwrite(&(pLib->user_data[i]), sizeof(user), 1, pWrite);
	}
	//�ر��ļ���
	fclose(pWrite);
	pWrite = NULL;
}
