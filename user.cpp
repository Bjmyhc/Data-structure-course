#include "library.h"
#include "user.h"
#include "book.h"
#include "tool.h"

void print_user_login_register_menu()
{
		system("cls");
		printf("--------------------\n");
		printf("|**** %u.登录 **** |\n", LOG);
		printf("|**** %u.注册 **** |\n", REG);
		printf("|**** %u.退出 **** |\n", EXI);
		printf("--------------------\n\n");
		printf("请选择>:");
	
}

/*打印查找_修改方式菜单 */
void print_find_and_change_user_menu()
{
	printf("------------------------\n");
	printf("|**** %u.密码     **** |\n", CHANGE_PASSWORD);
	printf("|**** %u.权限     **** |\n", CHANGE_POWER);
	printf("|**** %u.回到主页 **** |\n", CHANGE_EXIT);
	printf("------------------------\n\n");
	printf("请选择>:");
}

/*打印部分用户功能菜单*/
void print_part_of_user_function_menu()
{
	printf("\n                               菜单\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      \n");
	printf("快捷跳转↘                    \n");
	printf("  %u.首页  %u.尾页  %u.指定页                     \n", FIRST_PAGE, LAST_PAGE, A_PAGE);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      \n");
	printf("  %u.回到主页                     \n", BY_EXIT);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      \n");
	printf("请选择:>");
}
//用户登录或注册
int user_login_register(library* pLib)
{
	user_lr_choice user_choice;//用户选择

	do{
		print_user_login_register_menu();	//打印登录注册菜单
		user_choice = (user_lr_choice)99;	//初始化选项，防止错误值乱入功能
		scanf(" %u", (unsigned int*)&user_choice);			//获取用户输入选项
		getchar();
		
		switch (user_choice) {
		case EXI:
			//保存用户信息
			save_user_information(pLib);
			//销毁系统
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
			//	printf("输入无效，请重新输入!");
			break;
		}
	}while(1);
	return 0;
}

//用户登录
int user_login(library* pLib)
{
	char account[MAX_ACCOUNT];
	char password[MAX_PASSWPRD];
	int i = 0;
	bool flag = false;
	input("请输入用户名:>", account, MAX_ACCOUNT);
	input("请输入密码:>", password, MAX_PASSWPRD);
	
	//判断用户是否存在
	for (i = 0; i < pLib->now_user_capacity; i++)
	{
		if (0 == strcmp(pLib->user_data[i].account, account))
		{
			flag = true;
			break;
		}
	}		
	//判断密码是否正确
	if(flag == true)
		if(0 == strcmp(pLib->user_data[i].password, password)){
			pLib->login_user_location = i;
			return 1;
		}
	else
		printf("密码错误！\n");
	else
		printf("用户不存在,请注册!\n");
	getchar();
	return 0;
}
//用户注册
void user_register(library* pLib)
{
	char space[MAX_ACCOUNT];
	int if_change_check_way = 0;//是否改变了检查方式
	seek_situation seek;
	
	//检查容量
	check_user_capacity(pLib);
	//录入用户信息
	do
	{
		input("请输入用户名:>", space, MAX_ACCOUNT);
		
		//调用精确查找用户
		if (pLib->setup.seek_way == 0)
		{
			pLib->setup.seek_way = 1;
			if_change_check_way = 1;
		}
		//检查用户是否存在重复
		find_user_by_account(pLib, space, &seek);
//		printf("数量：%d\n", seek.num);
		//如果改变了检查方式，则改回来
		if (if_change_check_way == 1)
		{
			pLib->setup.seek_way = 0;
			if_change_check_way = 0;
		}
		//如果不存在，则录入
		if (seek.num == 0)
		{
			strcpy(pLib->user_data[pLib->now_user_capacity].account, space);
			break;
		}
		else
		{
			printf("该用户已存在\n");
			printf("按任意键继续...");
			_getch();
			return;
		}
	}while(1);
	
	input("请输入密码:>", pLib->user_data[pLib->now_user_capacity].password, MAX_PASSWPRD);
	
	//更新用户数据
	if(0 == strcmp(space, "admin"))
		pLib->user_data[pLib->now_user_capacity].power = 2;
	else
		pLib->user_data[pLib->now_user_capacity].power = 0;
	
	pLib->user_data[pLib->now_user_capacity].is_deleted = 't';
	pLib->now_user_capacity++;
	pLib->show_user_capacity++;
	
	//释放查找时创建的动态数组
	free(seek.location);
	seek.location = NULL;
	
	printf("注册成功！");
	printf("按任意键继续...");
	_getch();
}

//用户激活管理员
void user_activation(library* pLib)
{
	char space[MAX_TIME];
	char ret_time[MAX_TIME];
	
	input("请输入激活密钥:>",space, MAX_TIME);
	local_time(ret_time);
	
	if(0 == strcmp(space, ret_time))
	{
		pLib->user_data[pLib->login_user_location].power = 1;
		printf("激活成功，您现在已获取管理员资格！\n");
//		printf("local:%d, power:%d",pLib->login_user_location, pLib->user_data[pLib->login_user_location].power);
	}
	else
	{
		printf("激活失败！\n");
	}
	printf("按任意键继续...");
	_getch();
}

//初始化用户数据
void init_user_data(library* pLib)
{
	//分配用户空间
	pLib->user_data = (user*)malloc(DEFAULT_USER*sizeof(user));
	if(pLib->user_data == NULL)
	{
		perror("init_library:init_user");
		printf("按任意键继续...");
		_getch();
		return;
	}
	//初始化用户容量
	pLib->now_user_capacity = 0;
	pLib->show_user_capacity = 0;
	pLib->total_user_capacity = DEFAULT_USER;//后续决定是否集成到基本配置
	load_user_information(pLib);
}

/*加载用户信息*/
void load_user_information(library* pLib)
{
	//创建book类型结构体
	user tmp = { 0 };
	FILE* pRead = fopen(".\\Library\\user_information.dat", "rb");
	
	if (pRead == NULL)
	{
		perror("load_user");
		printf("按任意键继续...");
		getchar();
		return;
	}
	
	//以二进制的方式读取
	while (fread(&tmp, sizeof(user), 1, pRead))
	{
		check_user_capacity(pLib);
		pLib->user_data[pLib->now_user_capacity] = tmp;	
		pLib->now_user_capacity++;
		pLib->show_user_capacity++;
	}
	//关闭文件流
	fclose(pRead);
	pRead = NULL;
}

/*用户容量扩容*/
void check_user_capacity(library* pLib)
{
	//如果容量已满
	if (pLib->now_user_capacity == pLib->total_user_capacity)
	{
		//扩容
		user* ptr = (user*)realloc(pLib->user_data, (pLib->total_user_capacity + EXPANSION_USER) * sizeof(user));
		//如果扩容失败
		if (ptr == NULL)
		{
			perror("user_realloc_capacity");
			printf("按任意键继续...");
			_getch();
		}
		else
		{
			pLib->user_data = ptr;
			pLib->total_user_capacity += EXPANSION_USER;
//			printf("扩容成功！\n");
		}
	}
}


/*删除用户信息*/
void user_delete(library* pLib)
{
	if (if_input())
	{
		seek_situation seek;
		char account[MAX_ACCOUNT];
		int if_change_check_way = 0;
		
		if (pLib->show_user_capacity == 0)
		{
			printf("暂无注册用户\n");
		}
		else
		{
			printf("请输入想删除教材的用户名:>");
			scanf("%s", account);
			getchar();
			
			//调用精确查找isbn
			if (pLib->setup.seek_way == 0)
			{
				pLib->setup.seek_way = 1;
				if_change_check_way = 1;
			}
			//检查isbn是否存在重复
			find_user_by_account(pLib, account, &seek);
			//如果改变了检查方式，则改回来
			if (if_change_check_way == 1)
			{
				pLib->setup.seek_way = 0;
				if_change_check_way = 0;
			}
			
			if (seek.num == 0)
			{
				printf("该用户不存在\n");
				
			}
			else
			{
				//执行删除操作
				pLib->user_data[seek.location[0]].is_deleted = 'f';
				pLib->show_user_capacity--;
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

/*查找用户名*/
void find_user_by_account(const library* pLib, char account[MAX_ACCOUNT], seek_situation* situation)
{
	int i = 0;
	int j = 0;
	//初始化查找情况数组
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

/*查找用户信息*/
void user_seek(library* pLib)
{
	if (if_input())
	{
		seek_situation seek;
		char account[MAX_ACCOUNT];
		int if_change_check_way = 0;
		
		if (pLib->show_user_capacity == 0)
		{
			printf("暂无注册用户\n");
		}
		else
		{
			printf("请输入想查找的用户名:>");
			scanf("%s", account);
			getchar();
			
			//调用精确查找isbn
			if (pLib->setup.seek_way == 0)
			{
				pLib->setup.seek_way = 1;
				if_change_check_way = 1;
			}
			//查找用户
			find_user_by_account(pLib, account, &seek);
			//如果改变了检查方式，则改回来
			if (if_change_check_way == 1)
			{
				pLib->setup.seek_way = 0;
				if_change_check_way = 0;
			}
			
			if (seek.num == 0)
			{
				printf("该用户不存在\n");
				
			}
			else
			{
				//打印用户数据
				printf("-----     \n");
				printf("用户：%s\n密码：%s\n权限：%d\n",
					pLib->user_data[seek.location[0]].account,
					pLib->user_data[seek.location[0]].password,
					pLib->user_data[seek.location[0]].power);
				printf("-----      \n");
			}
			//释放查找时创建的动态数组
			free(seek.location);
			seek.location = NULL;
		}
		
		printf("按任意键继续...");
		_getch();
	}
	
}


/*修改用户信息*/
void user_change(library* pLib)
{
	if (if_input())
	{
		seek_situation seek;
		char account[MAX_ACCOUNT];
		int if_change_check_way = 0;
		
		if (pLib->show_user_capacity == 0)
		{
			printf("暂无用户\n");
			printf("按任意键继续...");
			_getch();
			return;
		}
		else
		{
			change_choice user_choice;
			
			printf("请输入被修改用户名:>");
			scanf("%s", account);
			getchar();
			
			if(0 == strcmp(account, "admin"))
			{
				printf("超管不支持此功能");
				printf("按任意键继续...");
				_getch();
				return;
			}
			
			
			//精确查找教材
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
				printf("该用户不存在\n");
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
					//打印修改菜单
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
						input("输入新密码:>", pLib->user_data[seek.location[0]].password, 20);
						break;
					case CHANGE_POWER:
						do{
							printf("输入新权限:>");
							scanf("%d", &power);
							if(power < 0 || power >2)
								printf("请输入正确的值!\n");
							else if(2 == power)
								printf("超管仅能有一位！\n");
							else
								break;
						}while(1);
						//更新权限
						pLib->user_data[seek.location[0]].power = power;
						break;
					default:
						continue;
					}
					printf("修改成功,");
					getchar();
					break;
				}
				while (user_choice != CHANGE_EXIT);
			}
			//释放查找时创建的动态数组
			free(seek.location);
			seek.location = NULL;
		}
		printf("按任意键继续...");
		_getch();
	}
	
}

/*打印用户信息*/
void user_print(const library* pLib)
{
	// 创建数组的副本
	user* copy = (user*)malloc(pLib->total_user_capacity * sizeof(user));
	if (copy == NULL)
	{
		perror("show_user");
		printf("按任意键继续...");
		_getch();
		return;
	}
	// 复制数据
	memcpy(copy, pLib->user_data, pLib->total_user_capacity * sizeof(user)); 
	
	char fn_choice;
	int print_user = 0;//所打印用户（i）
	int now_page = 1;//当前页码
	int page = 0;
	int now_page_form_user_num = 0;//当前页的起始数据位置（下标）
	int total_page = pLib->now_user_capacity / pLib->setup.show_num + (pLib->now_user_capacity % pLib->setup.show_num > 0 ? 1 : 0);
	change_page:
	system("cls");
	
	if (pLib->show_user_capacity == 0)
	{
		printf("暂无用户\n");
		printf("按任意键继续...");
		_getch();
		free(copy);
		copy = NULL;
		return;
	}
	else
	{
		
		printf("方向键翻页，'~'键呼出菜单\n");
		
		printf("------------------------------------------------------------\n");
		printf(" %-6s|%-23s|%-23s|%-2s\n", "序号", "用户", "密码", "权限");
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
		printf("\n				-当前%d/%d页- \n", now_page, total_page);
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
					printf("请输入指定页:>");
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


//导入用户信息
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
		
		int error_lack = 0;			//	数据缺失错误
		int error_repeat = 0;		//	数据重复错误
		int error_power = 0;		//	权限错误数量
		int how_many_user = 0;		//	导入用户数量
		int import_flag = 0;		//	导入标志量
		int if_change_check_way = 0;//	是否改变查找方式
		
		printf("请输入导入文件名称:>");
		scanf(" %s", new_users);
		getchar();
		FILE* pRead = fopen(new_users, "r");
		
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
			seek.num = 0;
			power = -1;
			how_many_user++;//记录用户数
			
			//判断是否检查数据完整
			if(sscanf(line_information, "%*d %s %s %d", account, password, &power) != 3)
			{
				printf("[Error_line:%d]: 数据缺失\n", how_many_user);
				error_lack++;
//				getchar();
			}
			else
			{
				check_user_capacity(pLib);
				
				//精确查找用户
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
						printf("[Error_line:%d]: 用户名非法\n", how_many_user);
						error_power++;
					}
					else if(power < 0 || power > 1)//进一步检查权限
					{
						printf("[Error_line:%d]: 权限数值错误\n", how_many_user);
						error_power++;
					}
					else
					{
						strcpy(pLib->user_data[pLib->now_user_capacity].account, account);
						strcpy(pLib->user_data[pLib->now_user_capacity].password, password);
						pLib->user_data[pLib->now_user_capacity].power = power;
						
						//更新数据：标签，现在数量，展示数量
						pLib->user_data[pLib->now_user_capacity].is_deleted = 't';
						pLib->now_user_capacity++;
						pLib->show_user_capacity++;
						
					}
				
				}
				else
				{
					printf("[Error]%s: 已存在\n", account);
					error_repeat++;
				}
			}
		}
		//情况归纳
		printf("----------\n");
		if (error_power + error_lack + error_repeat == how_many_user)
			printf("导入失败,");
		else
			printf("导入成功,");
		
		printf("一共%d个用户，发生了%d处错误.\n错误归纳:[权限错误：%d, 缺失错误：%d, 重复错误：%d]\n", how_many_user, error_power + error_lack + error_repeat, error_power, error_lack, error_repeat);
		printf("----------\n");
		
		//释放查找时创建的动态数组
		free(seek.location);
		seek.location = NULL;
		
		//关闭文件流
		fclose(pRead);
		pRead = NULL;
		printf("按任意键继续...");
		_getch();
	}
	
}

//导出用户信息
void user_export(library* pLib)
{
	if(if_input())
	{
		int i = 0;
		int id = 0;
		
		if(pLib->show_user_capacity == 0)
		{
			printf("暂无用户\n");
			printf("按任意键继续...");
			_getch();
			return;
		}
		else
		{
			//执行导出操作
			FILE* pwrite = fopen(".\\Library\\用户.txt", "w");//打开文件
			//如果打开失败
			if (pwrite == NULL)
			{
				perror("export_book");
				printf("按任意键继续...");
				_getch();
				return;
			}
			//保存信息
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
			printf("导出成功！按任意键继续...");
			_getch();
			//关闭文件流
			fclose(pwrite);
			pwrite = NULL;
			return;
		}
	}
}

/*保存用户信息*/
void save_user_information(library* pLib)
{
	int i = 0;
	//打开文件
	FILE* pWrite = fopen(".\\Library\\user_information.dat", "wb");
	//如果保存失败
	if (pWrite == NULL)
	{
		perror("save_user");
		printf("按任意键继续...");
		_getch();
		return;
	}
	
	//以二进制方式写入
	for (i = 0; i < pLib->now_user_capacity; i++)
	{
		if (pLib->user_data[i].is_deleted == 't')
			fwrite(&(pLib->user_data[i]), sizeof(user), 1, pWrite);
	}
	//关闭文件流
	fclose(pWrite);
	pWrite = NULL;
}
