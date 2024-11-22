#include "library.h"
#include "book.h"
#include "tool.h"
#include "user.h"
////////////////////////////无功能函数/////////////////////////////////////

/*打印主菜单*/
void print_main_book_menu(const library* pLib)
{
	int power = pLib->user_data[pLib->login_user_location].power;
	
	system("cls");
	printf("您当前用户[%s],权限为：%s\n",pLib->user_data[pLib->login_user_location].account, 
		power > 1 ? "超管": power > 0 ? "管理员" : "普通用户" );
	printf("-----------------------\n");
	printf("|**** %u.添加教材 **** |\n", ADD);
	printf("|**** %u.删除教材 **** |\n", DEL);
	printf("|**** %u.查找教材 **** |\n", SEEK);
	printf("|**** %u.修改信息 **** |\n", CHANGE);
	printf("|**** %u.显示所有 **** |\n", SHOW);
	printf("|**** %u.系统设置 **** |\n", SETUP);
	if(power > 1)
		printf("|**** %u.后台管理 **** |\n", USER);
//	printf("|**** %u.激活密钥 **** |\n", POWER);
//	printf("|**** %u.退出账号 **** |\n", EXIT);
	printf("-----------------------\n\n");
	printf("请选择>:");
}

/*打印查找_修改方式菜单 */
void print_find_and_change_menu()
{
	printf("------------------------\n");
	printf("|**** %u.书名     **** |\n", BY_NAME);
	printf("|**** %u.作者     **** |\n", BY_AUTHOR);
	printf("|**** %u.出版社   **** |\n", BY_PRESS);
	printf("|**** %u.出版时间 **** |\n", BY_DATE);
	printf("|**** %u.ISBN     **** |\n", BY_ISBN);
	printf("|**** %u.价格     **** |\n", BY_PRICE);
	printf("|**** %u.回到主页 **** |\n", BY_EXIT);
	printf("------------------------\n\n");
	printf("请选择>:");
}
/*打印功能菜单*/
void printf_function_menu()
{
	printf("\n                               菜单\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      \n");
	printf("排序依据↘                    \n");
	printf("  %u.书名  %u.作者  %u.出版社  %u.出版时间  %u.ISBN  %u.价格  %u.默认排序 \n", BY_NAME, BY_AUTHOR, BY_PRESS, BY_DATE, BY_ISBN, BY_PRICE, RECOVER);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      \n");
	printf("输入序号↘                    \n");
	printf("  %u.查看教材详细信息                     \n", SHOW_THIS);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      \n");
	printf("快捷跳转↘                    \n");
	printf("  %u.首页  %u.尾页  %u.指定页                     \n", FIRST_PAGE, LAST_PAGE, A_PAGE);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      \n");
	printf("  %u.回到主页                     \n", BY_EXIT);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      \n");
	printf("请选择:>");
}

/*打印部分功能菜单*/
void print_part_of_function_menu()
{
	printf("\n                               菜单\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      \n");
	printf("输入序号↘                    \n");
	printf("  %u.查看教材详细信息                     \n", SHOW_THIS);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      \n");
	printf("快捷跳转↘                    \n");
	printf("  %u.首页  %u.尾页  %u.指定页                     \n", FIRST_PAGE, LAST_PAGE, A_PAGE);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      \n");
	printf("  %u.回到主页                     \n", BY_EXIT);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      \n");
	printf("请选择:>");
}


//主菜单
void main_book_menu(library* pLib)
{
	main_choice user_choice;//用户选择
	
	
	do
	{
		int power = pLib->user_data[pLib->login_user_location].power;//获取登录用户的权限
		print_main_book_menu(pLib);//打印主菜单
		
		user_choice = (main_choice)99;//初始化选项，防止错误值乱入功能
		scanf(" %u", (unsigned int*)&user_choice);	//获取用户输入选项
		getchar();
		
		switch (user_choice)
		{
//		case EXIT:
//			//保存教材信息
//			save_book_information(pLib);
//			//保存配置数据
//			save_setup_information(pLib);
//			//销毁系统
//			destroyed_library(pLib);
//			break;
		case ADD:
			power > 0 ? add_book_information(pLib) : warn_printf(power);//添加教材信息
			break;
		case DEL:
			power > 0 ? dele_book_information(pLib) : warn_printf(power);//删除教材信息
			break;
		case SEEK:
			seek_book_information(pLib);//查找教材信息
			break;
		case CHANGE:
			power > 0 ? change_book_information(pLib) : warn_printf(power);//修改教材信息
			break;
		case SHOW:
			show_book_information(pLib);//展示教材信息
			break;
		case SETUP:
			if(0 != system_set_up(pLib))//教材系统设置
				return;
			break;
//		case POWER:
//			power > 0 ? warn_printf(power) : user_activation(pLib);//激活密钥
//			break;
		case USER:
			power > 1 ? user_control(pLib) : warn_printf(power,1);//后台操作
			break;
		default:
			//	printf("输入无效，请重新输入!");
			break;
		}
	}while(1);
}


/////////////////////////////子函数/////////////////////////////
//查找方式：pLib->setup.seek_way，1代表精确，2代表模糊

/*查找书名*/
void find_book_by_name(const library* pLib, char name[MAX_NAME], seek_situation* situation)
{
	int i = 0;
	int j = 0;
	//初始化查找情况数组
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

/*查找作者*/
void find_book_by_author(const library* pLib, char author[MAX_AUTHOR], seek_situation* situation)
{
	int i = 0;
	int j = 0;
	//初始化查找情况数组
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

/*查找出版社*/
void find_book_by_press(const library* pLib, char press[MAX_PRESS], seek_situation* situation)
{
	int i = 0;
	int j = 0;
	//初始化查找情况数组
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

/*查找出版日期*/
void find_book_by_date(const library* pLib, seek_situation* situation)
{
	int i = 0;
	int j = 0;
	int y, m, d;
	char date[MAX_DATE];
	//初始化查找情况数组
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
		printf("日期格式错误，请重新输入:>");
		goto date_again;
	}
	
}

/*查找ISBN*/
void find_book_by_isbn(const library* pLib, char isbn[MAX_ISBN], seek_situation* situation)
{
	int i = 0;
	int j = 0;
	//初始化查找情况数组
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

/*查找价格*/
void find_book_by_price(const library* pLib, float price, seek_situation* situation)
{
	int i = 0;
	int j = 0;
	//初始化查找情况数组
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

/*修改教材日期*/
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
		printf("请输入教材ID:>");
		scanf(" %d", &show_id);
		show_id -= 1;
		getchar();
	}
	
	if (show_id < 0)
	{
		printf("输入序号错误\n");
	}
	else
	{
		if (copy[show_id].is_deleted == 't')
		{
			printf("-----     \n");
			printf("书名：%s\n作者：%s\n出版社：%s\n出版日期：%d-%d-%d\nISBN：%s\n价格：%.2f\n",
				copy[show_id].name, copy[show_id].author, copy[show_id].press,
				copy[show_id].date.y, copy[show_id].date.m, copy[show_id].date.d,
				copy[show_id].isbn, copy[show_id].price);
			printf("-----      \n");
		}
		else
		{
			printf("该教材不存在\n");
		}
	}
	printf("按任意键继续...");
	_getch();
}

//-------------------------------------------------------------

int sort_book_by_name_flag = 1;
/*书名排序函数*/
int compar_by_name(const void* a, const void* b)
{
	return sort_book_by_name_flag * strcmp(((book*)a)->name, ((book*)b)->name);
}

/*排序书名*/
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
/*作者排序函数*/
int compar_by_author(const void* a, const void* b)
{
	return sort_book_by_author_flag * strcmp(((book*)a)->author, ((book*)b)->author);
}

/*排序作者*/
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
/*出版社排序函数*/
int compar_by_press(const void* a, const void* b)
{
	return sort_book_by_press_flag * strcmp(((book*)a)->press, ((book*)b)->press);
}

/*排序出版社*/
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
/* 日期排序函数 */
int compar_by_date(const void* a, const void* b)
{
	const book* book_a = (const book*)a;
	const book* book_b = (const book*)b;
	int order = 0;
	
	// 比较年
	if (book_a->date.y != book_b->date.y)
	{
		order = book_a->date.y - book_b->date.y;
	}
	else
	{
		// 年份相同，比较月
		if (book_a->date.m != book_b->date.m)
		{
			order = book_a->date.m - book_b->date.m;
		}
		else
		{
			// 月也相同，比较日
			order = book_a->date.d - book_b->date.d;
		}
	}
	
	// 如果sort_order_flag为正，表示升序；如果为负，表示降序
	return sort_book_by_date_flag * order;
}

/*排序日期*/
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
/*ISBN排序函数*/
int compar_by_isbn(const void* a, const void* b)
{
	return sort_book_by_isbn_flag * strcmp(((book*)a)->isbn, ((book*)b)->isbn);
}

/*排序ISBN*/
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
/*价格排序函数*/
int compar_by_price(const void* a, const void* b)
{
	return sort_book_by_price_flag * (((book*)a)->price > ((book*)b)->price ? 1 : -1);
}

/*排序价格*/
void sort_book_by_price(const library* pLib, book* copy)
{
	qsort(copy, pLib->now_capacity, sizeof(book), compar_by_price);
	if (sort_book_by_price_flag == 1)
		sort_book_by_price_flag = -1;
	else
		sort_book_by_price_flag = 1;
}

//-------------------------------------------------------------







/*书籍容量扩容*/
void check_capacity(library* pLib)
{
	//如果容量已满
	if (pLib->now_capacity == pLib->total_capacity)
	{
		//扩容
		book* ptr = (book*)realloc(pLib->data, (pLib->total_capacity + pLib->setup.expansion) * sizeof(book));
		//如果扩容失败
		if (ptr == NULL)
		{
			perror("realloc_capacity");
			printf("按任意键继续...");
			_getch();
		}
		else
		{
			pLib->data = ptr;
			pLib->total_capacity += pLib->setup.expansion;
			pLib->setup.default_capacity = pLib->total_capacity;
			printf("扩容成功！\n");
		}
	}
}


///////////////////////////////菜单功能函数////////////////////////////////

/*添加教材信息*/
void add_book_information(library* pLib)
{
	if (if_input())
	{
		char space[sizeof(book)];
		char isbn[MAX_ISBN];
		float price = 0.0;
		int if_change_check_way = 0;//是否改变了检查方式
		int y, m, d;
		seek_situation seek;
		//检查通讯录容量,已满就扩容
		check_capacity(pLib);
		
		//录入信息
		input("请输入书名:>", space, MAX_NAME);
		sscanf(space, "%s", pLib->data[pLib->now_capacity].name);
		input("请输入作者:>", space, MAX_AUTHOR);
		sscanf(space, "%s", pLib->data[pLib->now_capacity].author);
		input("请输入出版社:>", space, MAX_PRESS);
		sscanf(space, "%s", pLib->data[pLib->now_capacity].press);
		
		printf("请输入价格:>");
		do
		{
			scanf(" %f", &price);
			getchar();
			
			if (price <= 0.0)
			{
				printf("价格错误，请重新输入:>");
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
			input("请输入出版日期(y-m-d):>", space, MAX_DATE);
			if (if_book_date(pLib, space) == 1)
			{
				printf("日期格式错误，请重新输入!\n");
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
			input("请输入ISBN:>", space, MAX_ISBN);
			sscanf(space, "%s", isbn);
			
			//调用精确查找isbn
			if (pLib->setup.seek_way == 0)
			{
				pLib->setup.seek_way = 1;
				if_change_check_way = 1;
			}
			//检查isbn是否存在重复
			find_book_by_isbn(pLib, isbn, &seek);
			//如果改变了检查方式，则改回来
			if (if_change_check_way == 1)
			{
				pLib->setup.seek_way = 0;
				if_change_check_way = 0;
			}
			//如果不存在，则录入
			if (seek.num == 0)
			{
				strcpy(pLib->data[pLib->now_capacity].isbn, isbn);
				break;
			}
			else
			{
				printf("该教材已存在\n");
			}
		}
		while (1);
		
		//更新教材数据
		pLib->data[pLib->now_capacity].is_deleted = 't';
		pLib->now_capacity++;
		pLib->show_capacity++;
		
		//释放查找时创建的动态数组
		free(seek.location);
		seek.location = NULL;
		
		printf("添加成功！");
		printf("按任意键继续...");
		_getch();
	}
	else
	{
		return;
	}
}

/*删除教材信息*/
void dele_book_information(library* pLib)
{
	if (if_input())
	{
		seek_situation seek;
		char isbn[MAX_ISBN];
		int if_change_check_way = 0;
	
		if (pLib->show_capacity == 0)
		{
			printf("教材库为空\n");
		}
		else
		{
			printf("请输入想删除教材的ISBN:>");
			scanf("%s", isbn);
			getchar();
			
			//调用精确查找isbn
			if (pLib->setup.seek_way == 0)
			{
				pLib->setup.seek_way = 1;
				if_change_check_way = 1;
			}
			//检查isbn是否存在重复
			find_book_by_isbn(pLib, isbn, &seek);
			//如果改变了检查方式，则改回来
			if (if_change_check_way == 1)
			{
				pLib->setup.seek_way = 0;
				if_change_check_way = 0;
			}
			
			if (seek.num == 0)
			{
				printf("该教材不存在\n");
				
			}
			else
			{
				//执行删除操作
				pLib->data[seek.location[0]].is_deleted = 'f';
				pLib->show_capacity--;
				printf("删除成功\n");
			}
			//释放查找时创建的动态数组
			free(seek.location);
			seek.location = NULL;
		}
		
		printf("按任意键继续...");
		_getch();
	}
	
}

/*查找教材信息*/
void seek_book_information(const library* pLib)
{
	if (if_input())
	{
		//初始化查找情况
		seek_situation seek;
		seek_and_sort_choice user_choice;//菜单选择
		char fn_choice;//功能选择
		char input[sizeof(book)];
		int print_book = 0;
		int now_page = 0;//当前页码
		int now_page_form_book_num = 0;
		int total_page = 0;
		int show_id = 0;
		int page = 0;
		float price = 0.0;
	
		if (pLib->show_capacity == 0)
		{
			printf("教材库为空\n");
			printf("按任意键继续...");
			getchar();
		}
		else
		{
			do
			{
				user_choice = (seek_and_sort_choice)99;
				system("cls");
				printf("你想根据什么查找:\n");
				//打印查找菜单
				print_find_and_change_menu();
				
				scanf(" %u", (unsigned int*)&user_choice);
				getchar();
				printf("输入查找信息:");
				
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
					printf("按任意键继续...");
					_getch();
					continue;
				}
				else
				{
					print_book = 0;//所打印教材（i）
					now_page = 1;//当前页码
					now_page_form_book_num = 0;//当前页的起始数据位置（下标）
					total_page = seek.num / pLib->setup.show_num + (seek.num % pLib->setup.show_num > 0 ? 1 : 0);
					change_page:
					again:
					system("cls");
					printf("共%d本，方向键换页，'~'键呼出菜单\n", seek.num);
					printf("--------------------------------------------------------------------------------------------------------------------\n");
					printf(" %-6s|%-23s|%-23s|%-20s|%-11s|%-16s|%-6s\n", "序号", "书名", "作者", "出版社", "出版日期", "ISBN", "价格");
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
					printf("\n					-当前%d/%d页- \n", now_page, total_page);
				}
				
				do
				{
					//翻页或退出
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
								printf("请输入教材ID:>");
								
								do
								{
									scanf(" %d", &show_id);
									if (show_id < 1)
									{
										printf("序号错误，请重新输入:>");
									}
									
								}
								while (show_id < 1);
								getchar();
								//展示教材详细信息
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
								printf("请输入指定页:>");
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
								printf("输入无效，请重新输入！\a");
								//Sleep(400);//暂停400毫秒
								break;
							}
							
						}
						while (user_choice != BY_EXIT);    //退出程序
					}
					else if (fn_choice == 72 || fn_choice == 80 || fn_choice == 75 || fn_choice == 77)//key：上 72 || 下 80 || 左 75 || 右 77
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
			while (user_choice != BY_EXIT);    //退出程序
			free(seek.location);
			seek.location = NULL;
			//		printf("请输入想查找的书名:>");
			//		scanf("%s", name);
		}
	}
	
}

/*修改教材信息*/
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
			printf("教材库为空\n");
			printf("按任意键继续...");
			_getch();
			return;
		}
		else
		{
			seek_and_sort_choice user_choice;
			
			printf("请输入被修改书的ISBN:>");
			scanf("%s", isbn);
			getchar();
			//精确查找教材
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
				printf("该教材不存在\n");
				printf("按任意键继续...");
				_getch();
				return;
			}
			else
			{
				do
				{
					system("cls");
					printf("你想修改什么数据:\n");
					print_find_and_change_menu();
					user_choice = (seek_and_sort_choice)99;
					scanf(" %u", (unsigned int*)&user_choice);
					getchar();
					printf("输入新数据:>");
					
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
								printf("日期格式错误，请重新输入:>");
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
					printf("修改成功,");
					break;
				}
				while (user_choice != BY_EXIT);
			}
			//释放查找时创建的动态数组
			free(seek.location);
			seek.location = NULL;
		}
		printf("按任意键继续...");
		_getch();
	}
	
}


/*打印教材信息*/
void show_book_information(const library* pLib)
{
	// 创建数组的副本
	book* copy = (book*)malloc(pLib->total_capacity * sizeof(book));
	if (copy == NULL)
	{
		perror("show_book");
		printf("按任意键继续...");
		_getch();
		return;
	}
	recover:
	memcpy(copy, pLib->data, pLib->total_capacity * sizeof(book)); // 复制数据
	
	char fn_choice;
	int print_book = 0;//所打印教材（i）
	int now_page = 1;//当前页码
	int now_page_form_book_num = 0;//当前页的起始数据位置（下标）
	int total_page = pLib->now_capacity / pLib->setup.show_num + (pLib->now_capacity % pLib->setup.show_num > 0 ? 1 : 0);
	sort_print:
	change_page:
	system("cls");
	
	if (pLib->show_capacity == 0)
	{
		printf("教材库为空\n");
		printf("按任意键继续...");
		_getch();
		free(copy);
		copy = NULL;
		return;
	}
	else
	{
		
		printf("方向键翻页，'~'键呼出菜单\n");
		
		printf("--------------------------------------------------------------------------------------------------------------------\n");
		printf(" %-6s|%-23s|%-23s|%-20s|%-11s|%-16s|%-6s\n", "序号", "书名", "作者", "出版社", "出版日期", "ISBN", "价格");
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
		printf("\n					    -当前%d/%d页- \n", now_page, total_page);
	}
	
	//进入二级菜单
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
					printf("请输入指定页:>");
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
					printf("输入无效，请重新输入！\a");
					//Sleep(400);//暂停400毫秒
					break;
				}
				
			}
			while (user_choice != BY_EXIT);    //退出程序
			//释放复制的空间
			free(copy);
			copy = NULL;
		}
		else if (fn_choice == 72 || fn_choice == 80 || fn_choice == 75 || fn_choice == 77)//key：上 72 || 下 80 || 左 75 || 右 77
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
		//printf("按任意键继续...");
	}
	while (1);
}

/*导入教材信息*/
void import_book_information(library* pLib)
{
	if (if_input())
	{
		seek_situation seek;
		char new_books[128];
		char line_information[256];
		char name[MAX_NAME];		//	书名
		char author[MAX_AUTHOR];	//	作者
		char press[MAX_PRESS];		//	出版社
		char date[MAX_DATE];		//	出版日期
		char isbn[MAX_ISBN];		//	ISBN
		float price = 0.0;			//	价格
		
		int error_lack = 0;			//	数据缺失错误
		int error_form = 0;			//	数据格式错误
		int error_repeat = 0;		//	数据重复错误
		int how_many_book = 0;		//	导入教材数量
		int import_flag = 0;		//	导入标志量
		int if_change_check_way = 0;//	是否改变查找方式
		int y = 0, m = 0, d = 0;	//	年，月，日
	
		printf("请输入导入文件名称:>");
		scanf(" %s", new_books);
		getchar();
		FILE* pRead = fopen(new_books, "r");
		//printf("----------");
		//备份原来数据
		//back_information();
		
		//判断读情况
		if (pRead == NULL)
		{
			perror("[Error]文件不存在\a");
			printf("----------\n");
			printf("按任意键继续...");
			_getch();
			return;
		}
		
		//执行导入操作
		while (fgets(line_information, 256, pRead) != NULL)//一行一行读取
		{
			how_many_book++;//书籍总数量增加
			
			if (sscanf(line_information, "%*d %s %s %s %s %s %f", name, author, press, date, isbn, &price) != 6)//检查元素有效个数
			{
				printf("[Error_line:%d]: 数据缺失\n", how_many_book);
				error_lack++;
			}
			else
			{
				//检查通讯录容量,已满就扩容
				check_capacity(pLib);
				
				//精确查找教材
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
				
				//判断教材情况
				if (seek.num == 0)
				{
					
					//判断是否进一步检查日期格式
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
							printf("[Error]%s :日期格式错误\n", name);
							error_form++;
						}
					}
					
					if (import_flag == 1 || import_flag == 2)
					{
						//添加一本教材的所有数据
						strcpy(pLib->data[pLib->now_capacity].name, name);
						strcpy(pLib->data[pLib->now_capacity].author, author);
						strcpy(pLib->data[pLib->now_capacity].press, press);
						strcpy(pLib->data[pLib->now_capacity].isbn, isbn);
						
						pLib->data[pLib->now_capacity].date.y = y;
						pLib->data[pLib->now_capacity].date.m = m;
						pLib->data[pLib->now_capacity].date.d = d;
						pLib->data[pLib->now_capacity].price = price;
						
						//更新数据：标签，现在数量，展示数量
						pLib->data[pLib->now_capacity].is_deleted = 't';
						pLib->now_capacity++;
						pLib->show_capacity++;
						
						//释放查找时创建的动态数组
						free(seek.location);
						seek.location = NULL;
					}
				}
				else
				{
					printf("[Error]%s: 已存在\n", name);
					error_repeat++;
				}
			}
			
		}
		//情况归纳
		printf("----------\n");
		if (error_form + error_lack + error_repeat == how_many_book)
			printf("导入失败,");
		else
			printf("导入成功,");
		
		printf("一共%d本教材，发生了%d处错误.\n错误归纳:[格式错误：%d, 缺失错误：%d, 重复错误：%d]\n", how_many_book, error_form + error_lack + error_repeat, error_form, error_lack, error_repeat);
		printf("----------\n");
		//关闭文件流
		fclose(pRead);
		pRead = NULL;
		printf("按任意键继续...");
		_getch();
	}
	
}

/*导出教材信息*/
void export_book_information(library* pLib)
{
	if (if_input())
	{
		int i = 0;
		int id = 1;
	
		if (pLib->show_capacity == 0)
		{
			printf("教材库为空\n");
			printf("按任意键继续...");
			_getch();
			return;
		}
		else
		{
			//执行导出操作
			FILE* pwrite = fopen(".\\Library\\教材管理系统.txt", "w");//打开文件
			//如果打开失败
			if (pwrite == NULL)
			{
				perror("export_book");
				printf("按任意键继续...");
				_getch();
				return;
			}
			//保存信息
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
			printf("导出成功！按任意键继续...");
			_getch();
			//关闭文件流
			fclose(pwrite);
			pwrite = NULL;
			return;
		}
	}
	
}

/*初始化书籍数据*/
void init_book_data(library* pLib)
{
	//分配默认容量
	pLib->data = (book*)malloc(pLib->setup.default_capacity * sizeof(book));
	
	if(pLib->data == NULL)
	{
		perror("init_library:init_data");
		printf("按任意键继续...");
		_getch();
		return;
	}
	
	//初始化书籍容量
	pLib->now_capacity = 0;
	pLib->show_capacity = 0;
	pLib->total_capacity = pLib->setup.default_capacity;
	load_book_information(pLib);
}

/*保存教材信息*/
void save_book_information(library* pLib)
{
	int i = 0;
	//打开文件
	FILE* pWrite = fopen(".\\Library\\book_information.dat", "wb");
	//如果保存失败
	if (pWrite == NULL)
	{
		perror("save_book");
		printf("按任意键继续...");
		_getch();
		return;
	}
	
	//以二进制方式写入
	for (i = 0; i < pLib->now_capacity; i++)
	{
		if (pLib->data[i].is_deleted == 't')
			fwrite(&(pLib->data[i]), sizeof(book), 1, pWrite);
	}
	//关闭文件流
	fclose(pWrite);
	pWrite = NULL;
}

/*加载教材信息*/
void load_book_information(library* pLib)
{
	//创建book类型结构体
	book tmp = { 0 };
	FILE* pRead = fopen(".\\Library\\book_information.dat", "rb");
	
	if (pRead == NULL)
	{
		//perror("load_book");
		//printf("按任意键继续...");
		//getchar();
		return;
	}
	
	//以二进制的方式读取
	while (fread(&tmp, sizeof(book), 1, pRead))
	{
		check_capacity(pLib);
		pLib->data[pLib->now_capacity] = tmp;
		pLib->now_capacity++;
		pLib->show_capacity++;
	}
	//关闭文件流
	fclose(pRead);
	pRead = NULL;
}

/////////////////////////////////////////////////////////////////////////
