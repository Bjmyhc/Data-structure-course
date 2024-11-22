#include "library.h"
#include "book.h"
#include "tool.h"
#include "user.h"
////////////////////////////�޹��ܺ���/////////////////////////////////////

/*��ӡ���˵�*/
void print_main_book_menu(const library* pLib)
{
	int power = pLib->user_data[pLib->login_user_location].power;
	
	system("cls");
	printf("����ǰ�û�[%s],Ȩ��Ϊ��%s\n",pLib->user_data[pLib->login_user_location].account, 
		power > 1 ? "����": power > 0 ? "����Ա" : "��ͨ�û�" );
	printf("-----------------------\n");
	printf("|**** %u.��ӽ̲� **** |\n", ADD);
	printf("|**** %u.ɾ���̲� **** |\n", DEL);
	printf("|**** %u.���ҽ̲� **** |\n", SEEK);
	printf("|**** %u.�޸���Ϣ **** |\n", CHANGE);
	printf("|**** %u.��ʾ���� **** |\n", SHOW);
	printf("|**** %u.ϵͳ���� **** |\n", SETUP);
	if(power > 1)
		printf("|**** %u.��̨���� **** |\n", USER);
//	printf("|**** %u.������Կ **** |\n", POWER);
//	printf("|**** %u.�˳��˺� **** |\n", EXIT);
	printf("-----------------------\n\n");
	printf("��ѡ��>:");
}

/*��ӡ����_�޸ķ�ʽ�˵� */
void print_find_and_change_menu()
{
	printf("------------------------\n");
	printf("|**** %u.����     **** |\n", BY_NAME);
	printf("|**** %u.����     **** |\n", BY_AUTHOR);
	printf("|**** %u.������   **** |\n", BY_PRESS);
	printf("|**** %u.����ʱ�� **** |\n", BY_DATE);
	printf("|**** %u.ISBN     **** |\n", BY_ISBN);
	printf("|**** %u.�۸�     **** |\n", BY_PRICE);
	printf("|**** %u.�ص���ҳ **** |\n", BY_EXIT);
	printf("------------------------\n\n");
	printf("��ѡ��>:");
}
/*��ӡ���ܲ˵�*/
void printf_function_menu()
{
	printf("\n                               �˵�\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      \n");
	printf("�������ݨK                    \n");
	printf("  %u.����  %u.����  %u.������  %u.����ʱ��  %u.ISBN  %u.�۸�  %u.Ĭ������ \n", BY_NAME, BY_AUTHOR, BY_PRESS, BY_DATE, BY_ISBN, BY_PRICE, RECOVER);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      \n");
	printf("������ŨK                    \n");
	printf("  %u.�鿴�̲���ϸ��Ϣ                     \n", SHOW_THIS);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      \n");
	printf("�����ת�K                    \n");
	printf("  %u.��ҳ  %u.βҳ  %u.ָ��ҳ                     \n", FIRST_PAGE, LAST_PAGE, A_PAGE);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      \n");
	printf("  %u.�ص���ҳ                     \n", BY_EXIT);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      \n");
	printf("��ѡ��:>");
}

/*��ӡ���ֹ��ܲ˵�*/
void print_part_of_function_menu()
{
	printf("\n                               �˵�\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      \n");
	printf("������ŨK                    \n");
	printf("  %u.�鿴�̲���ϸ��Ϣ                     \n", SHOW_THIS);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      \n");
	printf("�����ת�K                    \n");
	printf("  %u.��ҳ  %u.βҳ  %u.ָ��ҳ                     \n", FIRST_PAGE, LAST_PAGE, A_PAGE);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      \n");
	printf("  %u.�ص���ҳ                     \n", BY_EXIT);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      \n");
	printf("��ѡ��:>");
}


//���˵�
void main_book_menu(library* pLib)
{
	main_choice user_choice;//�û�ѡ��
	
	
	do
	{
		int power = pLib->user_data[pLib->login_user_location].power;//��ȡ��¼�û���Ȩ��
		print_main_book_menu(pLib);//��ӡ���˵�
		
		user_choice = (main_choice)99;//��ʼ��ѡ���ֹ����ֵ���빦��
		scanf(" %u", (unsigned int*)&user_choice);	//��ȡ�û�����ѡ��
		getchar();
		
		switch (user_choice)
		{
//		case EXIT:
//			//����̲���Ϣ
//			save_book_information(pLib);
//			//������������
//			save_setup_information(pLib);
//			//����ϵͳ
//			destroyed_library(pLib);
//			break;
		case ADD:
			power > 0 ? add_book_information(pLib) : warn_printf(power);//��ӽ̲���Ϣ
			break;
		case DEL:
			power > 0 ? dele_book_information(pLib) : warn_printf(power);//ɾ���̲���Ϣ
			break;
		case SEEK:
			seek_book_information(pLib);//���ҽ̲���Ϣ
			break;
		case CHANGE:
			power > 0 ? change_book_information(pLib) : warn_printf(power);//�޸Ľ̲���Ϣ
			break;
		case SHOW:
			show_book_information(pLib);//չʾ�̲���Ϣ
			break;
		case SETUP:
			if(0 != system_set_up(pLib))//�̲�ϵͳ����
				return;
			break;
//		case POWER:
//			power > 0 ? warn_printf(power) : user_activation(pLib);//������Կ
//			break;
		case USER:
			power > 1 ? user_control(pLib) : warn_printf(power,1);//��̨����
			break;
		default:
			//	printf("������Ч������������!");
			break;
		}
	}while(1);
}


/////////////////////////////�Ӻ���/////////////////////////////
//���ҷ�ʽ��pLib->setup.seek_way��1����ȷ��2����ģ��

/*��������*/
void find_book_by_name(const library* pLib, char name[MAX_NAME], seek_situation* situation)
{
	int i = 0;
	int j = 0;
	//��ʼ�������������
	situation->location = (int*)malloc(pLib->now_capacity * sizeof(int));
	memset(situation->location, 0, pLib->now_capacity * sizeof(int));
	situation->num = 0;
	
	if (pLib->setup.seek_way == 1)
	{
		for (i = 0; i < pLib->now_capacity; i++)
		{
			if (0 == strcmp(pLib->data[i].name, name))
			{
				if (pLib->data[i].is_deleted == 't')
				{
					situation->location[j++] = i;
					situation->num++;
				}
			}
		}
	}
	else
	{
		for (i = 0; i < pLib->now_capacity; i++)
		{
			if (strstr(pLib->data[i].name, name) != NULL)
			{
				if (pLib->data[i].is_deleted == 't')
				{
					situation->location[j++] = i;
					situation->num++;
				}
			}
		}
	}
}

/*��������*/
void find_book_by_author(const library* pLib, char author[MAX_AUTHOR], seek_situation* situation)
{
	int i = 0;
	int j = 0;
	//��ʼ�������������
	situation->location = (int*)malloc(pLib->now_capacity * sizeof(int));
	memset(situation->location, 0, pLib->now_capacity * sizeof(int));
	situation->num = 0;
	
	if (pLib->setup.seek_way == 1)
	{
		for (i = 0; i < pLib->now_capacity; i++)
		{
			
			if (0 == strcmp(pLib->data[i].author, author))
			{
				if (pLib->data[i].is_deleted == 't')
				{
					situation->location[j++] = i;
					situation->num++;
				}
			}
		}
	}
	else
	{
		for (i = 0; i < pLib->now_capacity; i++)
		{
			
			if (strstr(pLib->data[i].author, author) != NULL)
			{
				if (pLib->data[i].is_deleted == 't')
				{
					situation->location[j++] = i;
					situation->num++;
				}
			}
		}
	}
	
}

/*���ҳ�����*/
void find_book_by_press(const library* pLib, char press[MAX_PRESS], seek_situation* situation)
{
	int i = 0;
	int j = 0;
	//��ʼ�������������
	situation->location = (int*)malloc(pLib->now_capacity * sizeof(int));
	memset(situation->location, 0, pLib->now_capacity * sizeof(int));
	situation->num = 0;
	
	if (pLib->setup.seek_way == 1)
	{
		for (i = 0; i < pLib->now_capacity; i++)
		{
			if (0 == strcmp(pLib->data[i].press, press))
			{
				if (pLib->data[i].is_deleted == 't')
				{
					situation->location[j++] = i;
					situation->num++;
				}
			}
		}
	}
	else
	{
		for (i = 0; i < pLib->now_capacity; i++)
		{
			if (strstr(pLib->data[i].press, press) != NULL)
			{
				if (pLib->data[i].is_deleted == 't')
				{
					situation->location[j++] = i;
					situation->num++;
				}
			}
		}
	}
	
}

/*���ҳ�������*/
void find_book_by_date(const library* pLib, seek_situation* situation)
{
	int i = 0;
	int j = 0;
	int y, m, d;
	char date[MAX_DATE];
	//��ʼ�������������
	situation->location = (int*)malloc(pLib->now_capacity * sizeof(int));
	memset(situation->location, 0, pLib->now_capacity * sizeof(int));
	situation->num = 0;
	
	date_again:
	scanf("%s", date);
	getchar();
	sscanf(date, "%d-%d-%d", &y, &m, &d);
	
	if (y < 9999 && m > 0 && m <= 12 && d > 0 && d <= 31)
	{
		
		if (pLib->setup.seek_way == 1)
		{
			for (i = 0; i < pLib->now_capacity; i++)
			{
				if (pLib->data[i].date.y == y && pLib->data[i].date.m == m && pLib->data[i].date.d == d)
				{
					if (pLib->data[i].is_deleted == 't')
					{
						situation->location[j++] = i;
						situation->num++;
					}
				}
			}
		}
		else
		{
			for (i = 0; i < pLib->now_capacity; i++)
			{
				if (pLib->data[i].date.y == y || pLib->data[i].date.m == m || pLib->data[i].date.d == d)
				{
					if (pLib->data[i].is_deleted == 't')
					{
						situation->location[j++] = i;
						situation->num++;
					}
				}
			}
		}
	}
	else
	{
		printf("���ڸ�ʽ��������������:>");
		goto date_again;
	}
	
}

/*����ISBN*/
void find_book_by_isbn(const library* pLib, char isbn[MAX_ISBN], seek_situation* situation)
{
	int i = 0;
	int j = 0;
	//��ʼ�������������
	situation->location = (int*)malloc(pLib->now_capacity * sizeof(int));
	memset(situation->location, 0, pLib->now_capacity * sizeof(int));
	situation->num = 0;
	
	if (pLib->setup.seek_way == 1)
	{
		for (i = 0; i < pLib->now_capacity; i++)
		{
			if (0 == strcmp(pLib->data[i].isbn, isbn))
			{
				if (pLib->data[i].is_deleted == 't')
				{
					situation->location[j++] = i;
					situation->num++;
				}
			}
		}
	}
	else
	{
		for (i = 0; i < pLib->now_capacity; i++)
		{
			if (strstr(pLib->data[i].isbn, isbn) != NULL)
			{
				if (pLib->data[i].is_deleted == 't')
				{
					situation->location[j++] = i;
					situation->num++;
				}
			}
		}
	}
	
}

/*���Ҽ۸�*/
void find_book_by_price(const library* pLib, float price, seek_situation* situation)
{
	int i = 0;
	int j = 0;
	//��ʼ�������������
	situation->location = (int*)malloc(pLib->now_capacity * sizeof(int));
	memset(situation->location, 0, pLib->now_capacity * sizeof(int));
	situation->num = 0;
	
	for (i = 0; i < pLib->now_capacity; i++)
	{
		if (pLib->data[i].price == price)
		{
			if (pLib->data[i].is_deleted == 't')
			{
				situation->location[j++] = i;
				situation->num++;
			}
		}
	}
	
}

/*�޸Ľ̲�����*/
int if_book_date(const library* pLib, char date[MAX_DATE])
{
	int y, m, d;
	sscanf(date, "%d-%d-%d", &y, &m, &d);
	
	if (y < 9999 && m > 0 && m <= 12 && d > 0 && d <= 31)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void show_this_book(book* copy, int location)
{
	int show_id = 0;
	
	if (location != -1)
	{
		show_id = location;
	}
	else
	{
		printf("������̲�ID:>");
		scanf(" %d", &show_id);
		show_id -= 1;
		getchar();
	}
	
	if (show_id < 0)
	{
		printf("������Ŵ���\n");
	}
	else
	{
		if (copy[show_id].is_deleted == 't')
		{
			printf("-----     \n");
			printf("������%s\n���ߣ�%s\n�����磺%s\n�������ڣ�%d-%d-%d\nISBN��%s\n�۸�%.2f\n",
				copy[show_id].name, copy[show_id].author, copy[show_id].press,
				copy[show_id].date.y, copy[show_id].date.m, copy[show_id].date.d,
				copy[show_id].isbn, copy[show_id].price);
			printf("-----      \n");
		}
		else
		{
			printf("�ý̲Ĳ�����\n");
		}
	}
	printf("�����������...");
	_getch();
}

//-------------------------------------------------------------

int sort_book_by_name_flag = 1;
/*����������*/
int compar_by_name(const void* a, const void* b)
{
	return sort_book_by_name_flag * strcmp(((book*)a)->name, ((book*)b)->name);
}

/*��������*/
void sort_book_by_name(const library* pLib, book* copy)
{
	qsort(copy, pLib->now_capacity, sizeof(book), compar_by_name);
	if (sort_book_by_name_flag == 1)
		sort_book_by_name_flag = -1;
	else
		sort_book_by_name_flag = 1;
}

//-------------------------------------------------------------

int sort_book_by_author_flag = 1;
/*����������*/
int compar_by_author(const void* a, const void* b)
{
	return sort_book_by_author_flag * strcmp(((book*)a)->author, ((book*)b)->author);
}

/*��������*/
void sort_book_by_author(const library* pLib, book* copy)
{
	qsort(copy, pLib->now_capacity, sizeof(book), compar_by_author);
	if (sort_book_by_author_flag == 1)
		sort_book_by_author_flag = -1;
	else
		sort_book_by_author_flag = 1;
}

//-------------------------------------------------------------

int sort_book_by_press_flag = 1;
/*������������*/
int compar_by_press(const void* a, const void* b)
{
	return sort_book_by_press_flag * strcmp(((book*)a)->press, ((book*)b)->press);
}

/*���������*/
void sort_book_by_press(const library* pLib, book* copy)
{
	qsort(copy, pLib->now_capacity, sizeof(book), compar_by_press);
	if (sort_book_by_press_flag == 1)
		sort_book_by_press_flag = -1;
	else
		sort_book_by_press_flag = 1;
}

//-------------------------------------------------------------

int sort_book_by_date_flag = 1;
/* ���������� */
int compar_by_date(const void* a, const void* b)
{
	const book* book_a = (const book*)a;
	const book* book_b = (const book*)b;
	int order = 0;
	
	// �Ƚ���
	if (book_a->date.y != book_b->date.y)
	{
		order = book_a->date.y - book_b->date.y;
	}
	else
	{
		// �����ͬ���Ƚ���
		if (book_a->date.m != book_b->date.m)
		{
			order = book_a->date.m - book_b->date.m;
		}
		else
		{
			// ��Ҳ��ͬ���Ƚ���
			order = book_a->date.d - book_b->date.d;
		}
	}
	
	// ���sort_order_flagΪ������ʾ�������Ϊ������ʾ����
	return sort_book_by_date_flag * order;
}

/*��������*/
void sort_book_by_date(const library* pLib, book* copy)
{
	qsort(copy, pLib->now_capacity, sizeof(book), compar_by_date);
	if (sort_book_by_date_flag == 1)
		sort_book_by_date_flag = -1;
	else
		sort_book_by_date_flag = 1;
}

//-------------------------------------------------------------

int sort_book_by_isbn_flag = 1;
/*ISBN������*/
int compar_by_isbn(const void* a, const void* b)
{
	return sort_book_by_isbn_flag * strcmp(((book*)a)->isbn, ((book*)b)->isbn);
}

/*����ISBN*/
void sort_book_by_isbn(const library* pLib, book* copy)
{
	qsort(copy, pLib->now_capacity, sizeof(book), compar_by_isbn);
	if (sort_book_by_isbn_flag == 1)
		sort_book_by_isbn_flag = -1;
	else
		sort_book_by_isbn_flag = 1;
}

//-------------------------------------------------------------

int sort_book_by_price_flag = 1;
/*�۸�������*/
int compar_by_price(const void* a, const void* b)
{
	return sort_book_by_price_flag * (((book*)a)->price > ((book*)b)->price ? 1 : -1);
}

/*����۸�*/
void sort_book_by_price(const library* pLib, book* copy)
{
	qsort(copy, pLib->now_capacity, sizeof(book), compar_by_price);
	if (sort_book_by_price_flag == 1)
		sort_book_by_price_flag = -1;
	else
		sort_book_by_price_flag = 1;
}

//-------------------------------------------------------------







/*�鼮��������*/
void check_capacity(library* pLib)
{
	//�����������
	if (pLib->now_capacity == pLib->total_capacity)
	{
		//����
		book* ptr = (book*)realloc(pLib->data, (pLib->total_capacity + pLib->setup.expansion) * sizeof(book));
		//�������ʧ��
		if (ptr == NULL)
		{
			perror("realloc_capacity");
			printf("�����������...");
			_getch();
		}
		else
		{
			pLib->data = ptr;
			pLib->total_capacity += pLib->setup.expansion;
			pLib->setup.default_capacity = pLib->total_capacity;
			printf("���ݳɹ���\n");
		}
	}
}


///////////////////////////////�˵����ܺ���////////////////////////////////

/*��ӽ̲���Ϣ*/
void add_book_information(library* pLib)
{
	if (if_input())
	{
		char space[sizeof(book)];
		char isbn[MAX_ISBN];
		float price = 0.0;
		int if_change_check_way = 0;//�Ƿ�ı��˼�鷽ʽ
		int y, m, d;
		seek_situation seek;
		//���ͨѶ¼����,����������
		check_capacity(pLib);
		
		//¼����Ϣ
		input("����������:>", space, MAX_NAME);
		sscanf(space, "%s", pLib->data[pLib->now_capacity].name);
		input("����������:>", space, MAX_AUTHOR);
		sscanf(space, "%s", pLib->data[pLib->now_capacity].author);
		input("�����������:>", space, MAX_PRESS);
		sscanf(space, "%s", pLib->data[pLib->now_capacity].press);
		
		printf("������۸�:>");
		do
		{
			scanf(" %f", &price);
			getchar();
			
			if (price <= 0.0)
			{
				printf("�۸��������������:>");
			}
			else
			{
				pLib->data[pLib->now_capacity].price = price;
				break;
			}
		}
		while (1);
		
		do
		{
			input("�������������(y-m-d):>", space, MAX_DATE);
			if (if_book_date(pLib, space) == 1)
			{
				printf("���ڸ�ʽ��������������!\n");
			}
			else
			{
				sscanf(space, "%d-%d-%d", &y, &m, &d);
				pLib->data[pLib->now_capacity].date.y = y;
				pLib->data[pLib->now_capacity].date.m = m;
				pLib->data[pLib->now_capacity].date.d = d;
				break;
			}
		}
		while (1);
		
		do
		{
			input("������ISBN:>", space, MAX_ISBN);
			sscanf(space, "%s", isbn);
			
			//���þ�ȷ����isbn
			if (pLib->setup.seek_way == 0)
			{
				pLib->setup.seek_way = 1;
				if_change_check_way = 1;
			}
			//���isbn�Ƿ�����ظ�
			find_book_by_isbn(pLib, isbn, &seek);
			//����ı��˼�鷽ʽ����Ļ���
			if (if_change_check_way == 1)
			{
				pLib->setup.seek_way = 0;
				if_change_check_way = 0;
			}
			//��������ڣ���¼��
			if (seek.num == 0)
			{
				strcpy(pLib->data[pLib->now_capacity].isbn, isbn);
				break;
			}
			else
			{
				printf("�ý̲��Ѵ���\n");
			}
		}
		while (1);
		
		//���½̲�����
		pLib->data[pLib->now_capacity].is_deleted = 't';
		pLib->now_capacity++;
		pLib->show_capacity++;
		
		//�ͷŲ���ʱ�����Ķ�̬����
		free(seek.location);
		seek.location = NULL;
		
		printf("��ӳɹ���");
		printf("�����������...");
		_getch();
	}
	else
	{
		return;
	}
}

/*ɾ���̲���Ϣ*/
void dele_book_information(library* pLib)
{
	if (if_input())
	{
		seek_situation seek;
		char isbn[MAX_ISBN];
		int if_change_check_way = 0;
	
		if (pLib->show_capacity == 0)
		{
			printf("�̲Ŀ�Ϊ��\n");
		}
		else
		{
			printf("��������ɾ���̲ĵ�ISBN:>");
			scanf("%s", isbn);
			getchar();
			
			//���þ�ȷ����isbn
			if (pLib->setup.seek_way == 0)
			{
				pLib->setup.seek_way = 1;
				if_change_check_way = 1;
			}
			//���isbn�Ƿ�����ظ�
			find_book_by_isbn(pLib, isbn, &seek);
			//����ı��˼�鷽ʽ����Ļ���
			if (if_change_check_way == 1)
			{
				pLib->setup.seek_way = 0;
				if_change_check_way = 0;
			}
			
			if (seek.num == 0)
			{
				printf("�ý̲Ĳ�����\n");
				
			}
			else
			{
				//ִ��ɾ������
				pLib->data[seek.location[0]].is_deleted = 'f';
				pLib->show_capacity--;
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

/*���ҽ̲���Ϣ*/
void seek_book_information(const library* pLib)
{
	if (if_input())
	{
		//��ʼ���������
		seek_situation seek;
		seek_and_sort_choice user_choice;//�˵�ѡ��
		char fn_choice;//����ѡ��
		char input[sizeof(book)];
		int print_book = 0;
		int now_page = 0;//��ǰҳ��
		int now_page_form_book_num = 0;
		int total_page = 0;
		int show_id = 0;
		int page = 0;
		float price = 0.0;
	
		if (pLib->show_capacity == 0)
		{
			printf("�̲Ŀ�Ϊ��\n");
			printf("�����������...");
			getchar();
		}
		else
		{
			do
			{
				user_choice = (seek_and_sort_choice)99;
				system("cls");
				printf("�������ʲô����:\n");
				//��ӡ���Ҳ˵�
				print_find_and_change_menu();
				
				scanf(" %u", (unsigned int*)&user_choice);
				getchar();
				printf("���������Ϣ:");
				
				switch (user_choice)
				{
				case BY_EXIT:
					return;
				case BY_NAME:
					scanf("%s", input);
					find_book_by_name(pLib, input, &seek);
					break;
				case BY_AUTHOR:
					scanf("%s", input);
					find_book_by_author(pLib, input, &seek);
					break;
				case BY_PRESS:
					scanf("%s", input);
					find_book_by_press(pLib, input, &seek);
					break;
				case BY_DATE:
					find_book_by_date(pLib, &seek);
					break;
				case BY_ISBN:
					scanf("%s", input);
					find_book_by_isbn(pLib, input, &seek);
					break;
				case BY_PRICE:
					scanf("%f", &price);
					find_book_by_price(pLib, price, &seek);
					break;
				default:
					continue;
				}
				getchar();
				
				if (seek.num == 0)
				{
					printf("not_found\n");
					printf("�����������...");
					_getch();
					continue;
				}
				else
				{
					print_book = 0;//����ӡ�̲ģ�i��
					now_page = 1;//��ǰҳ��
					now_page_form_book_num = 0;//��ǰҳ����ʼ����λ�ã��±꣩
					total_page = seek.num / pLib->setup.show_num + (seek.num % pLib->setup.show_num > 0 ? 1 : 0);
					change_page:
					again:
					system("cls");
					printf("��%d�����������ҳ��'~'�������˵�\n", seek.num);
					printf("--------------------------------------------------------------------------------------------------------------------\n");
					printf(" %-6s|%-23s|%-23s|%-20s|%-11s|%-16s|%-6s\n", "���", "����", "����", "������", "��������", "ISBN", "�۸�");
					printf("--------------------------------------------------------------------------------------------------------------------\n");
					for (print_book = now_page_form_book_num; print_book < now_page_form_book_num + pLib->setup.show_num; print_book++)
					{
						if (pLib->data[print_book].is_deleted == 't' && print_book < seek.num)
						{
							printf(" %-6d", print_book + 1);
							printf("|");
							//printf("%s ",copy[print_book].name);
							limit_printf("%-20s", pLib->data[seek.location[print_book]].name, 10);
							printf("|");
							//printf("%-20s ",copy[print_book].author);
							limit_printf("%-20s", pLib->data[seek.location[print_book]].author, 10);
							printf("|");
							printf("%-20s", pLib->data[seek.location[print_book]].press);
							printf("|");
							printf("%d-", pLib->data[seek.location[print_book]].date.y);
							printf("%d-", pLib->data[seek.location[print_book]].date.m);
							printf("%-4d", pLib->data[seek.location[print_book]].date.d);
							printf("|");
							printf("%-16s", pLib->data[seek.location[print_book]].isbn);
							printf("|");
							printf("%.2f\n", pLib->data[seek.location[print_book]].price);
						}
					}
					printf("--------------------------------------------------------------------------------------------------------------------\n");
					printf("\n					-��ǰ%d/%dҳ- \n", now_page, total_page);
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
							print_part_of_function_menu();
							scanf("%u", (unsigned int*)&user_choice);
							getchar();
							
							switch (user_choice)
							{
							case BY_EXIT:
								return;
							case SHOW_THIS:
								printf("������̲�ID:>");
								
								do
								{
									scanf(" %d", &show_id);
									if (show_id < 1)
									{
										printf("��Ŵ�������������:>");
									}
									
								}
								while (show_id < 1);
								getchar();
								//չʾ�̲���ϸ��Ϣ
								show_this_book(pLib->data, seek.location[show_id - 1]);
								goto again;
								break;
							case FIRST_PAGE:
								now_page = 1;
								now_page_form_book_num = 0;
								goto change_page;
								break;
							case LAST_PAGE:
								now_page = total_page;
								now_page_form_book_num = (total_page - 1) * pLib->setup.show_num;
								goto change_page;
								break;
							case A_PAGE:
								printf("������ָ��ҳ:>");
								scanf(" %d", &page);
								getchar();
								if (page > 0 && page <= total_page)
								{
									now_page = page;
									now_page_form_book_num = (page - 1) * pLib->setup.show_num;
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
								now_page_form_book_num -= pLib->setup.show_num;
							}
							break;
						case 77:
						case 80:
							if (now_page < total_page)
							{
								now_page++;
								now_page_form_book_num += pLib->setup.show_num;
							}
							break;
						}
						goto change_page;
					}
				}
				while (1);
			}
			while (user_choice != BY_EXIT);    //�˳�����
			free(seek.location);
			seek.location = NULL;
			//		printf("����������ҵ�����:>");
			//		scanf("%s", name);
		}
	}
	
}

/*�޸Ľ̲���Ϣ*/
void change_book_information(library* pLib)
{
	if (if_input())
	{
		seek_situation seek;
		char isbn[MAX_ISBN];
		char input[MAX_DATE];
		int if_change_check_way = 0;
		int y, m, d;
	
		if (pLib->show_capacity == 0)
		{
			printf("�̲Ŀ�Ϊ��\n");
			printf("�����������...");
			_getch();
			return;
		}
		else
		{
			seek_and_sort_choice user_choice;
			
			printf("�����뱻�޸����ISBN:>");
			scanf("%s", isbn);
			getchar();
			//��ȷ���ҽ̲�
			if (pLib->setup.seek_way == 0)
			{
				pLib->setup.seek_way = 1;
				if_change_check_way = 1;
			}
			find_book_by_isbn(pLib, isbn, &seek);
			if (if_change_check_way == 1)
			{
				pLib->setup.seek_way = 0;
				if_change_check_way = 0;
			}
			
			if (seek.num == 0)
			{
				printf("�ý̲Ĳ�����\n");
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
					print_find_and_change_menu();
					user_choice = (seek_and_sort_choice)99;
					scanf(" %u", (unsigned int*)&user_choice);
					getchar();
					printf("����������:>");
					
					switch (user_choice)
					{
					case BY_EXIT:
						return;
					case BY_NAME:
						scanf(" %s", pLib->data[seek.location[0]].name);
						break;
					case BY_AUTHOR:
						scanf(" %s", pLib->data[seek.location[0]].author);
						break;
					case BY_PRESS:
						scanf(" %s", pLib->data[seek.location[0]].press);
						break;
					case BY_DATE:
						do
						{
							scanf(" %s", input);
							if (if_book_date(pLib, input) == 1)
								printf("���ڸ�ʽ��������������:>");
							else
								break;
						}
						while (1);
						sscanf(input, "%d-%d-%d", &y, &m, &d);
						pLib->data[seek.location[0]].date.y = y;
						pLib->data[seek.location[0]].date.m = m;
						pLib->data[seek.location[0]].date.d = d;
						
						break;
					case BY_ISBN:
						scanf(" %s", pLib->data[seek.location[0]].isbn);
						break;
					case BY_PRICE:
						scanf(" %f", &pLib->data[seek.location[0]].price);
						break;
					default:
						continue;
					}
					getchar();
					printf("�޸ĳɹ�,");
					break;
				}
				while (user_choice != BY_EXIT);
			}
			//�ͷŲ���ʱ�����Ķ�̬����
			free(seek.location);
			seek.location = NULL;
		}
		printf("�����������...");
		_getch();
	}
	
}


/*��ӡ�̲���Ϣ*/
void show_book_information(const library* pLib)
{
	// ��������ĸ���
	book* copy = (book*)malloc(pLib->total_capacity * sizeof(book));
	if (copy == NULL)
	{
		perror("show_book");
		printf("�����������...");
		_getch();
		return;
	}
	recover:
	memcpy(copy, pLib->data, pLib->total_capacity * sizeof(book)); // ��������
	
	char fn_choice;
	int print_book = 0;//����ӡ�̲ģ�i��
	int now_page = 1;//��ǰҳ��
	int now_page_form_book_num = 0;//��ǰҳ����ʼ����λ�ã��±꣩
	int total_page = pLib->now_capacity / pLib->setup.show_num + (pLib->now_capacity % pLib->setup.show_num > 0 ? 1 : 0);
	sort_print:
	change_page:
	system("cls");
	
	if (pLib->show_capacity == 0)
	{
		printf("�̲Ŀ�Ϊ��\n");
		printf("�����������...");
		_getch();
		free(copy);
		copy = NULL;
		return;
	}
	else
	{
		
		printf("�������ҳ��'~'�������˵�\n");
		
		printf("--------------------------------------------------------------------------------------------------------------------\n");
		printf(" %-6s|%-23s|%-23s|%-20s|%-11s|%-16s|%-6s\n", "���", "����", "����", "������", "��������", "ISBN", "�۸�");
		printf("--------------------------------------------------------------------------------------------------------------------\n");
		for (print_book = now_page_form_book_num; print_book < now_page_form_book_num + pLib->setup.show_num; print_book++)
		{
			if (copy[print_book].is_deleted == 't')
			{
				//printf(" %-6d\t|%-50.48s\t|\t%-32s\t|%-32s\t|%04d-%02d-%02d\t|%-15s\t|%-6f\n",
				printf(" %-6d", print_book + 1);
				printf("|");
				//printf("%s ",copy[print_book].name);
				limit_printf("%-20s", copy[print_book].name, 10);
				printf("|");
				//printf("%-20s ",copy[print_book].author);
				limit_printf("%-20s", copy[print_book].author, 10);
				printf("|");
				printf("%-20s", copy[print_book].press);
				printf("|");
				printf("%04d-", copy[print_book].date.y);
				printf("%02d-", copy[print_book].date.m);
				printf("%02d ", copy[print_book].date.d);
				printf("|");
				printf("%-16s", copy[print_book].isbn);
				printf("|");
				printf("%.2f\n", copy[print_book].price);
				
			}
		}
		printf("--------------------------------------------------------------------------------------------------------------------\n");
		printf("\n					    -��ǰ%d/%dҳ- \n", now_page, total_page);
	}
	
	//��������˵�
	do
	{
		fn_choice = _getch();
		if (fn_choice == '~' || fn_choice == '`')
		{
			seek_and_sort_choice user_choice;
			
			do
			{
				printf_function_menu();
				scanf("%u", (unsigned int*)&user_choice);
				getchar();
				int page = 0;
				switch (user_choice)
				{
				case BY_EXIT:
					free(copy);
					copy = NULL;
					return;
				case BY_NAME:
					sort_book_by_name(pLib, copy);
					goto sort_print;
					break;
				case BY_AUTHOR:
					sort_book_by_author(pLib, copy);
					goto sort_print;
					break;
				case BY_PRESS:
					sort_book_by_press(pLib, copy);
					goto sort_print;
					break;
				case BY_DATE:
					sort_book_by_date(pLib, copy);
					goto sort_print;
					break;
				case BY_ISBN:
					sort_book_by_isbn(pLib, copy);
					goto sort_print;
					break;
				case BY_PRICE:
					sort_book_by_price(pLib, copy);
					goto sort_print;
					break;
				case RECOVER:
					goto recover;
					break;
				case SHOW_THIS:
					show_this_book(copy, -1);
					goto sort_print;
					break;
				case FIRST_PAGE:
					now_page = 1;
					now_page_form_book_num = 0;
					goto sort_print;
					break;
				case LAST_PAGE:
					now_page = total_page;
					now_page_form_book_num = (total_page - 1) * pLib->setup.show_num;
					goto sort_print;
					break;
				case A_PAGE:
					printf("������ָ��ҳ:>");
					scanf(" %d", &page);
					getchar();
					if (page > 0 && page <= total_page)
					{
						now_page = page;
						now_page_form_book_num = (page - 1) * pLib->setup.show_num;
						goto sort_print;
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
			//�ͷŸ��ƵĿռ�
			free(copy);
			copy = NULL;
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
					now_page_form_book_num -= pLib->setup.show_num;
				}
				break;
			case 77:
			case 80:
				if (now_page < total_page)
				{
					now_page++;
					now_page_form_book_num += pLib->setup.show_num;
				}
				break;
			}
			goto change_page;
		}
		//printf("�����������...");
	}
	while (1);
}

/*����̲���Ϣ*/
void import_book_information(library* pLib)
{
	if (if_input())
	{
		seek_situation seek;
		char new_books[128];
		char line_information[256];
		char name[MAX_NAME];		//	����
		char author[MAX_AUTHOR];	//	����
		char press[MAX_PRESS];		//	������
		char date[MAX_DATE];		//	��������
		char isbn[MAX_ISBN];		//	ISBN
		float price = 0.0;			//	�۸�
		
		int error_lack = 0;			//	����ȱʧ����
		int error_form = 0;			//	���ݸ�ʽ����
		int error_repeat = 0;		//	�����ظ�����
		int how_many_book = 0;		//	����̲�����
		int import_flag = 0;		//	�����־��
		int if_change_check_way = 0;//	�Ƿ�ı���ҷ�ʽ
		int y = 0, m = 0, d = 0;	//	�꣬�£���
	
		printf("�����뵼���ļ�����:>");
		scanf(" %s", new_books);
		getchar();
		FILE* pRead = fopen(new_books, "r");
		//printf("----------");
		//����ԭ������
		//back_information();
		
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
			how_many_book++;//�鼮����������
			
			if (sscanf(line_information, "%*d %s %s %s %s %s %f", name, author, press, date, isbn, &price) != 6)//���Ԫ����Ч����
			{
				printf("[Error_line:%d]: ����ȱʧ\n", how_many_book);
				error_lack++;
			}
			else
			{
				//���ͨѶ¼����,����������
				check_capacity(pLib);
				
				//��ȷ���ҽ̲�
				if (pLib->setup.seek_way == 0)
				{
					pLib->setup.seek_way = 1;
					if_change_check_way = 1;
				}
				find_book_by_isbn(pLib, isbn, &seek);
				if (if_change_check_way == 1)
				{
					pLib->setup.seek_way = 0;
					if_change_check_way = 0;
				}
				
				//�жϽ̲����
				if (seek.num == 0)
				{
					
					//�ж��Ƿ��һ��������ڸ�ʽ
					if (pLib->setup.check_date == 0)
					{
						sscanf(date, "%04d%*s", &y);
						import_flag = 1;
					}
					else
					{
						sscanf(date, "%04d-%02d-%02d", &y, &m, &d);
						
						if (y < 9999 && m > 0 && m <= 12 && d > 0 && d <= 31)
						{
							import_flag = 2;
						}
						else
						{
							import_flag = 0;
							printf("[Error]%s :���ڸ�ʽ����\n", name);
							error_form++;
						}
					}
					
					if (import_flag == 1 || import_flag == 2)
					{
						//���һ���̲ĵ���������
						strcpy(pLib->data[pLib->now_capacity].name, name);
						strcpy(pLib->data[pLib->now_capacity].author, author);
						strcpy(pLib->data[pLib->now_capacity].press, press);
						strcpy(pLib->data[pLib->now_capacity].isbn, isbn);
						
						pLib->data[pLib->now_capacity].date.y = y;
						pLib->data[pLib->now_capacity].date.m = m;
						pLib->data[pLib->now_capacity].date.d = d;
						pLib->data[pLib->now_capacity].price = price;
						
						//�������ݣ���ǩ������������չʾ����
						pLib->data[pLib->now_capacity].is_deleted = 't';
						pLib->now_capacity++;
						pLib->show_capacity++;
						
						//�ͷŲ���ʱ�����Ķ�̬����
						free(seek.location);
						seek.location = NULL;
					}
				}
				else
				{
					printf("[Error]%s: �Ѵ���\n", name);
					error_repeat++;
				}
			}
			
		}
		//�������
		printf("----------\n");
		if (error_form + error_lack + error_repeat == how_many_book)
			printf("����ʧ��,");
		else
			printf("����ɹ�,");
		
		printf("һ��%d���̲ģ�������%d������.\n�������:[��ʽ����%d, ȱʧ����%d, �ظ�����%d]\n", how_many_book, error_form + error_lack + error_repeat, error_form, error_lack, error_repeat);
		printf("----------\n");
		//�ر��ļ���
		fclose(pRead);
		pRead = NULL;
		printf("�����������...");
		_getch();
	}
	
}

/*�����̲���Ϣ*/
void export_book_information(library* pLib)
{
	if (if_input())
	{
		int i = 0;
		int id = 1;
	
		if (pLib->show_capacity == 0)
		{
			printf("�̲Ŀ�Ϊ��\n");
			printf("�����������...");
			_getch();
			return;
		}
		else
		{
			//ִ�е�������
			FILE* pwrite = fopen(".\\Library\\�̲Ĺ���ϵͳ.txt", "w");//���ļ�
			//�����ʧ��
			if (pwrite == NULL)
			{
				perror("export_book");
				printf("�����������...");
				_getch();
				return;
			}
			//������Ϣ
			for (i = 0; i < pLib->now_capacity; i++)
			{
				if (pLib->data[i].is_deleted == 't')
				{
					fprintf(pwrite, "%-5d\t%-15s\t%-15s\t%-30s\t%04d-%02d-%02d\t%-15s\t%-6f\n",
						id,
						pLib->data[i].name,
						pLib->data[i].author,
						pLib->data[i].press,
						pLib->data[i].date.y,
						pLib->data[i].date.m,
						pLib->data[i].date.d,
						pLib->data[i].isbn,
						pLib->data[i].price);
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

/*��ʼ���鼮����*/
void init_book_data(library* pLib)
{
	//����Ĭ������
	pLib->data = (book*)malloc(pLib->setup.default_capacity * sizeof(book));
	
	if(pLib->data == NULL)
	{
		perror("init_library:init_data");
		printf("�����������...");
		_getch();
		return;
	}
	
	//��ʼ���鼮����
	pLib->now_capacity = 0;
	pLib->show_capacity = 0;
	pLib->total_capacity = pLib->setup.default_capacity;
	load_book_information(pLib);
}

/*����̲���Ϣ*/
void save_book_information(library* pLib)
{
	int i = 0;
	//���ļ�
	FILE* pWrite = fopen(".\\Library\\book_information.dat", "wb");
	//�������ʧ��
	if (pWrite == NULL)
	{
		perror("save_book");
		printf("�����������...");
		_getch();
		return;
	}
	
	//�Զ����Ʒ�ʽд��
	for (i = 0; i < pLib->now_capacity; i++)
	{
		if (pLib->data[i].is_deleted == 't')
			fwrite(&(pLib->data[i]), sizeof(book), 1, pWrite);
	}
	//�ر��ļ���
	fclose(pWrite);
	pWrite = NULL;
}

/*���ؽ̲���Ϣ*/
void load_book_information(library* pLib)
{
	//����book���ͽṹ��
	book tmp = { 0 };
	FILE* pRead = fopen(".\\Library\\book_information.dat", "rb");
	
	if (pRead == NULL)
	{
		//perror("load_book");
		//printf("�����������...");
		//getchar();
		return;
	}
	
	//�Զ����Ƶķ�ʽ��ȡ
	while (fread(&tmp, sizeof(book), 1, pRead))
	{
		check_capacity(pLib);
		pLib->data[pLib->now_capacity] = tmp;
		pLib->now_capacity++;
		pLib->show_capacity++;
	}
	//�ر��ļ���
	fclose(pRead);
	pRead = NULL;
}

/////////////////////////////////////////////////////////////////////////
