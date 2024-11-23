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

/*��ӡ����_�޸ķ�ʽ�˵� */
void print_find_and_change_user_menu()
{
	printf("------------------------\n");
	printf("|**** %u.����     **** |\n", CHANGE_PASSWORD);
	printf("|**** %u.Ȩ��     **** |\n", CHANGE_POWER);
	printf("|**** %u.�ص���ҳ **** |\n", CHANGE_EXIT);
	printf("------------------------\n\n");
	printf("��ѡ��>:");
}

/*��ӡ�����û����ܲ˵�*/
void print_part_of_user_function_menu()
{
	printf("\n                               �˵�\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      \n");
	printf("�����ת�K                    \n");
	printf("  %u.��ҳ  %u.βҳ  %u.ָ��ҳ                     \n", FIRST_PAGE, LAST_PAGE, A_PAGE);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      \n");
	printf("  %u.�ص���ҳ                     \n", BY_EXIT);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      \n");
	printf("��ѡ��:>");
}
//�û���¼��ע��
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
			//����ϵͳ
			destroyed_library(pLib);
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

//��ʼ���û�����
void init_user_data(library* pLib)
{
	//�����û��ռ�
	pLib->user_data = (user*)malloc(DEFAULT_USER*sizeof(user));
	if(pLib->user_data == NULL)
	{
		perror("init_library:init_user");
		printf("�����������...");
		_getch();
		return;
	}
	//��ʼ���û�����
	pLib->now_user_capacity = 0;
	pLib->show_user_capacity = 0;
	pLib->total_user_capacity = DEFAULT_USER;//���������Ƿ񼯳ɵ���������
	load_user_information(pLib);
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


/*ɾ���û���Ϣ*/
void user_delete(library* pLib)
{
	if (if_input())
	{
		seek_situation seek;
		char account[MAX_ACCOUNT];
		int if_change_check_way = 0;
		
		if (pLib->show_user_capacity == 0)
		{
			printf("����ע���û�\n");
		}
		else
		{
			printf("��������ɾ���̲ĵ��û���:>");
			scanf("%s", account);
			getchar();
			
			//���þ�ȷ����isbn
			if (pLib->setup.seek_way == 0)
			{
				pLib->setup.seek_way = 1;
				if_change_check_way = 1;
			}
			//���isbn�Ƿ�����ظ�
			find_user_by_account(pLib, account, &seek);
			//����ı��˼�鷽ʽ����Ļ���
			if (if_change_check_way == 1)
			{
				pLib->setup.seek_way = 0;
				if_change_check_way = 0;
			}
			
			if (seek.num == 0)
			{
				printf("���û�������\n");
				
			}
			else
			{
				//ִ��ɾ������
				pLib->user_data[seek.location[0]].is_deleted = 'f';
				pLib->show_user_capacity--;
				printf("ɾ���ɹ�\n");
			}
			//�ͷŲ���ʱ�����Ķ�̬����
			free(seek.location);
			seek.location = NULL;
		}
		
		printf("�����������...");
		_getch();
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
void user_seek(library* pLib)
{
	if (if_input())
	{
		seek_situation seek;
		char account[MAX_ACCOUNT];
		int if_change_check_way = 0;
		
		if (pLib->show_user_capacity == 0)
		{
			printf("����ע���û�\n");
		}
		else
		{
			printf("����������ҵ��û���:>");
			scanf("%s", account);
			getchar();
			
			//���þ�ȷ����isbn
			if (pLib->setup.seek_way == 0)
			{
				pLib->setup.seek_way = 1;
				if_change_check_way = 1;
			}
			//�����û�
			find_user_by_account(pLib, account, &seek);
			//����ı��˼�鷽ʽ����Ļ���
			if (if_change_check_way == 1)
			{
				pLib->setup.seek_way = 0;
				if_change_check_way = 0;
			}
			
			if (seek.num == 0)
			{
				printf("���û�������\n");
				
			}
			else
			{
				//��ӡ�û�����
				printf("-----     \n");
				printf("�û���%s\n���룺%s\nȨ�ޣ�%d\n",
					pLib->user_data[seek.location[0]].account,
					pLib->user_data[seek.location[0]].password,
					pLib->user_data[seek.location[0]].power);
				printf("-----      \n");
			}
			//�ͷŲ���ʱ�����Ķ�̬����
			free(seek.location);
			seek.location = NULL;
		}
		
		printf("�����������...");
		_getch();
	}
	
}


/*�޸��û���Ϣ*/
void user_change(library* pLib)
{
	if (if_input())
	{
		seek_situation seek;
		char account[MAX_ACCOUNT];
		int if_change_check_way = 0;
		
		if (pLib->show_user_capacity == 0)
		{
			printf("�����û�\n");
			printf("�����������...");
			_getch();
			return;
		}
		else
		{
			change_choice user_choice;
			
			printf("�����뱻�޸��û���:>");
			scanf("%s", account);
			getchar();
			
			if(0 == strcmp(account, "admin"))
			{
				printf("���ܲ�֧�ִ˹���");
				printf("�����������...");
				_getch();
				return;
			}
			
			
			//��ȷ���ҽ̲�
			if (pLib->setup.seek_way == 0)
			{
				pLib->setup.seek_way = 1;
				if_change_check_way = 1;
			}
			find_user_by_account(pLib, account, &seek);
			if (if_change_check_way == 1)
			{
				pLib->setup.seek_way = 0;
				if_change_check_way = 0;
			}
			
			if (seek.num == 0)
			{
				printf("���û�������\n");
				printf("�����������...");
				_getch();
				return;
			}
			else
			{
				do
				{
					system("cls");
					printf("�����޸�ʲô����:\n");
					//��ӡ�޸Ĳ˵�
					print_find_and_change_user_menu();
					
					user_choice = (change_choice)99;
					int power = 0;
					
					scanf(" %u", (unsigned int*)&user_choice);
					getchar();
					
					switch (user_choice)
					{
					case CHANGE_EXIT:
						return;
					case CHANGE_PASSWORD:
						input("����������:>", pLib->user_data[seek.location[0]].password, 20);
						break;
					case CHANGE_POWER:
						do{
							printf("������Ȩ��:>");
							scanf("%d", &power);
							if(power < 0 || power >2)
								printf("��������ȷ��ֵ!\n");
							else if(2 == power)
								printf("���ܽ�����һλ��\n");
							else
								break;
						}while(1);
						//����Ȩ��
						pLib->user_data[seek.location[0]].power = power;
						break;
					default:
						continue;
					}
					printf("�޸ĳɹ�,");
					getchar();
					break;
				}
				while (user_choice != CHANGE_EXIT);
			}
			//�ͷŲ���ʱ�����Ķ�̬����
			free(seek.location);
			seek.location = NULL;
		}
		printf("�����������...");
		_getch();
	}
	
}

/*��ӡ�û���Ϣ*/
void user_print(const library* pLib)
{
	// ��������ĸ���
	user* copy = (user*)malloc(pLib->total_user_capacity * sizeof(user));
	if (copy == NULL)
	{
		perror("show_user");
		printf("�����������...");
		_getch();
		return;
	}
	// ��������
	memcpy(copy, pLib->user_data, pLib->total_user_capacity * sizeof(user)); 
	
	char fn_choice;
	int print_user = 0;//����ӡ�û���i��
	int now_page = 1;//��ǰҳ��
	int page = 0;
	int now_page_form_user_num = 0;//��ǰҳ����ʼ����λ�ã��±꣩
	int total_page = pLib->now_user_capacity / pLib->setup.show_num + (pLib->now_user_capacity % pLib->setup.show_num > 0 ? 1 : 0);
	change_page:
	system("cls");
	
	if (pLib->show_user_capacity == 0)
	{
		printf("�����û�\n");
		printf("�����������...");
		_getch();
		free(copy);
		copy = NULL;
		return;
	}
	else
	{
		
		printf("�������ҳ��'~'�������˵�\n");
		
		printf("------------------------------------------------------------\n");
		printf(" %-6s|%-23s|%-23s|%-2s\n", "���", "�û�", "����", "Ȩ��");
		printf("------------------------------------------------------------\n");
		for (print_user = now_page_form_user_num; print_user < now_page_form_user_num + pLib->setup.show_num; print_user++)
		{
			if (copy[print_user].is_deleted== 't')
			{
				//printf(" %-6d\t|%-50.48s\t|\t%-32s\t|%-32s\t|%04d-%02d-%02d\t|%-15s\t|%-6f\n",
				printf(" %-6d", print_user + 1);
				printf("|");
				//printf("%s ",copy[print_book].name);
				limit_printf("%-20s", copy[print_user].account, 10);
				printf("|");
				//printf("%-20s ",copy[print_book].author);
				limit_printf("%-20s", copy[print_user].password, 10);
				printf("|");
				printf("%d\n", copy[print_user].power);
//				printf("|");
//				printf("%04d-", copy[print_user].date.y);
//				printf("%02d-", copy[print_user].date.m);
//				printf("%02d ", copy[print_user].date.d);				
			}
		}
		printf("------------------------------------------------------------\n");
		printf("\n				-��ǰ%d/%dҳ- \n", now_page, total_page);
	}
	
	do
	{
		//��ҳ���˳�
		fn_choice = _getch();
		
		if (fn_choice == '~' || fn_choice == '`')
		{
			seek_and_sort_choice user_choice;
			
			do
			{
				print_part_of_user_function_menu();
				scanf("%u", (unsigned int*)&user_choice);
				getchar();
				
				switch (user_choice)
				{
				case BY_EXIT:
					return;
				case FIRST_PAGE:
					now_page = 1;
					now_page_form_user_num = 0;
					goto change_page;
					break;
				case LAST_PAGE:
					now_page = total_page;
					now_page_form_user_num = (total_page - 1) * pLib->setup.show_num;
					goto change_page;
					break;
				case A_PAGE:
					printf("������ָ��ҳ:>");
					scanf(" %d", &page);
					getchar();
					if (page > 0 && page <= total_page)
					{
						now_page = page;
						now_page_form_user_num = (page - 1) * pLib->setup.show_num;
						goto change_page;
					}
					break;
				default:
					system("cls");
					printf("������Ч�����������룡\a");
					//Sleep(400);//��ͣ400����
					break;
				}
				
			}
			while (user_choice != BY_EXIT);    //�˳�����
		}
		else if (fn_choice == 72 || fn_choice == 80 || fn_choice == 75 || fn_choice == 77)//key���� 72 || �� 80 || �� 75 || �� 77
		{
			switch (fn_choice)
			{
			case 72:
			case 75:
				if (now_page > 1)
				{
					now_page--;
					now_page_form_user_num -= pLib->setup.show_num;
				}
				break;
			case 77:
			case 80:
				if (now_page < total_page)
				{
					now_page++;
					now_page_form_user_num += pLib->setup.show_num;
				}
				break;
			}
			goto change_page;
		}
	}while (1);
}


//�����û���Ϣ
void user_import(library* pLib)
{
	if(if_input())
	{
		seek_situation seek;
		char new_users[128];
		char line_information[256];
		char account[MAX_ACCOUNT] = {0};
		char password[MAX_PASSWPRD] = {0};
		int power;
		
		int error_lack = 0;			//	����ȱʧ����
		int error_repeat = 0;		//	�����ظ�����
		int error_power = 0;		//	Ȩ�޴�������
		int how_many_user = 0;		//	�����û�����
		int import_flag = 0;		//	�����־��
		int if_change_check_way = 0;//	�Ƿ�ı���ҷ�ʽ
		
		printf("�����뵼���ļ�����:>");
		scanf(" %s", new_users);
		getchar();
		FILE* pRead = fopen(new_users, "r");
		
		//�ж϶����
		if (pRead == NULL)
		{
			perror("[Error]�ļ�������\a");
			printf("----------\n");
			printf("�����������...");
			_getch();
			return;
		}
		
		//ִ�е������
		while (fgets(line_information, 256, pRead) != NULL)//һ��һ�ж�ȡ
		{
			seek.num = 0;
			power = -1;
			how_many_user++;//��¼�û���
			
			//�ж��Ƿ�����������
			if(sscanf(line_information, "%*d %s %s %d", account, password, &power) != 3)
			{
				printf("[Error_line:%d]: ����ȱʧ\n", how_many_user);
				error_lack++;
//				getchar();
			}
			else
			{
				check_user_capacity(pLib);
				
				//��ȷ�����û�
				if (pLib->setup.seek_way == 0)
				{
					pLib->setup.seek_way = 1;
					if_change_check_way = 1;
				}
				find_user_by_account(pLib, account, &seek);
				if (if_change_check_way == 1)
				{
					pLib->setup.seek_way = 0;
					if_change_check_way = 0;
				}
				
				if(seek.num == 0)
				{
					if(0 == strcmp(account, "admin"))
					{
						printf("[Error_line:%d]: �û����Ƿ�\n", how_many_user);
						error_power++;
					}
					else if(power < 0 || power > 1)//��һ�����Ȩ��
					{
						printf("[Error_line:%d]: Ȩ����ֵ����\n", how_many_user);
						error_power++;
					}
					else
					{
						strcpy(pLib->user_data[pLib->now_user_capacity].account, account);
						strcpy(pLib->user_data[pLib->now_user_capacity].password, password);
						pLib->user_data[pLib->now_user_capacity].power = power;
						
						//�������ݣ���ǩ������������չʾ����
						pLib->user_data[pLib->now_user_capacity].is_deleted = 't';
						pLib->now_user_capacity++;
						pLib->show_user_capacity++;
						
					}
				
				}
				else
				{
					printf("[Error]%s: �Ѵ���\n", account);
					error_repeat++;
				}
			}
		}
		//�������
		printf("----------\n");
		if (error_power + error_lack + error_repeat == how_many_user)
			printf("����ʧ��,");
		else
			printf("����ɹ�,");
		
		printf("һ��%d���û���������%d������.\n�������:[Ȩ�޴���%d, ȱʧ����%d, �ظ�����%d]\n", how_many_user, error_power + error_lack + error_repeat, error_power, error_lack, error_repeat);
		printf("----------\n");
		
		//�ͷŲ���ʱ�����Ķ�̬����
		free(seek.location);
		seek.location = NULL;
		
		//�ر��ļ���
		fclose(pRead);
		pRead = NULL;
		printf("�����������...");
		_getch();
	}
	
}

//�����û���Ϣ
void user_export(library* pLib)
{
	if(if_input())
	{
		int i = 0;
		int id = 0;
		
		if(pLib->show_user_capacity == 0)
		{
			printf("�����û�\n");
			printf("�����������...");
			_getch();
			return;
		}
		else
		{
			//ִ�е�������
			FILE* pwrite = fopen(".\\Library\\�û�.txt", "w");//���ļ�
			//�����ʧ��
			if (pwrite == NULL)
			{
				perror("export_book");
				printf("�����������...");
				_getch();
				return;
			}
			//������Ϣ
			for(i = 0; i < pLib->now_user_capacity; i++)
			{
				if(pLib->user_data[i].is_deleted == 't')
				{
					fprintf(pwrite, "%d\t%s\t%s\t%d\n",
						id,
						pLib->user_data[i].account,
						pLib->user_data[i].password,
						pLib->user_data[i].power);
					id++;
				}
			}
			printf("�����ɹ��������������...");
			_getch();
			//�ر��ļ���
			fclose(pwrite);
			pwrite = NULL;
			return;
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
