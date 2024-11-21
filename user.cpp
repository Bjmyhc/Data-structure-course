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
