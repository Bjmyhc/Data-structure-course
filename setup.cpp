#include "book.h"
#include "user.h"
#include "tool.h"
#include "library.h"

/*打印设置菜单*/
void print_set_up_menu(library* pLib)
{
	system("cls");
	printf("         设置           \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~ \n");
	printf("修改↘                  \n");
//	printf("  %u.默认容量：%d       \n", SET_DEFAULT_CAPACITY, pLib->setup.default_capacity);
//	printf("  %u.单次扩容：%d       \n", SET_EXPANSION, pLib->setup.expansion);
	printf("  %u.每页展示：%d       \n", SET_SHOW_NUM, pLib->setup.show_num);
	printf("  %u.查找精度：%s       \n", SET_SEEK_WAY, pLib->setup.seek_way > 0 ? "精确" : "模糊");
//	printf("~~~~~~~~~~~~~~~~~~~~~~~ \n");
//	printf("导入↘                  \n");
//	printf("  %u.导入教材(.txt)     \n", SET_IMPORT);
//	printf("  %u.检查日期(y-m-d)：%s\n", SET_CHECK_DATE, pLib->setup.check_date > 0 ? "是" : "否");
//	printf("~~~~~~~~~~~~~~~~~~~~~~~ \n");
//	printf("导出↘                  \n");
//	printf("  %u.导出教材(.txt)     \n", SET_EXPORT);
//	printf("~~~~~~~~~~~~~~~~~~~~~~~ \n");
//	printf("操作↘                  \n");
//	printf("  %u.备份所有数据       \n", SET_BAK_DATA);
//	printf("  %u.清空所有数据       \n", SET_DEL_LIB);
//	printf("  %u.恢复备份数据       \n", SET_RECOVER_DATA_BAK);
	printf("~~~~~~~~~~~~~~~~~~~~~~~ \n");
	printf("个性化↘                \n");
	printf("  %u.修改屏幕颜色       \n", SET_COLOR);
	printf("~~~~~~~~~~~~~~~~~~~~~~~ \n");
	printf("账号↘                  \n");
	printf("  %u.激活密钥           \n", SET_POWER);
	printf("  %u.修改密码           \n", SET_PASSWORD);
	printf("  %u.退出账号           \n", SET_EXIT_ACCOUNT);
	printf("~~~~~~~~~~~~~~~~~~~~~~~ \n");
	if(pLib->user_data[pLib->login_user_location].power > 0){
		printf("  %u.高级设置           \n", SET_HIGH_SETUP);
		printf("~~~~~~~~~~~~~~~~~~~~~~~ \n");
	}
	printf("  %u.回到主页           \n", SET_EXIT);
	printf("~~~~~~~~~~~~~~~~~~~~~~~ \n\n");
	printf("请选择:>");
}

/*打印高级设置菜单*/
void print_high_set_up_menu(library* pLib)
{
	system("cls");
	printf("        高级设置        \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("修改↘                  \n");
	printf("  %u.默认容量：%d       \n", HIGH_SET_DEFAULT_CAPACITY, pLib->setup.default_capacity);
	printf("  %u.单次扩容：%d       \n", HIGH_SET_EXPANSION, pLib->setup.expansion);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("导入↘                  \n");
	printf("  %u.导入教材(.txt)     \n", HIGH_SET_IMPORT);
	printf("  %u.检查日期(y-m-d)：%s\n", HIGH_SET_CHECK_DATE, pLib->setup.check_date > 0 ? "是" : "否");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("导出↘                  \n");
	printf("  %u.导出教材(.txt)     \n", HIGH_SET_EXPORT);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("操作↘                  \n");
	printf("  %u.备份所有数据       \n", HIGH_SET_BAK_DATA);
	printf("  %u.清空所有数据       \n", HIGH_SET_DEL_LIB);
	printf("  %u.恢复备份数据       \n", HIGH_SET_RECOVER_DATA_BAK);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("  %u.退出高级设置       \n", SET_EXIT);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf("请选择:>");
}


/*改变默认容量*/
void change_default_capacity(library* pLib)
{
	int new_default_capacity = 0;
	
	do
	{
		printf("输入新默认容量:>");
		scanf(" %d", &new_default_capacity);
		getchar();
		
		if (new_default_capacity > 0)
		{
			if (pLib->now_capacity != 0)
			{
				printf("存在教材，无法修改\n");
				printf("按任意键继续...");
				_getch();
				return;
			}
			else
			{
				pLib->setup.default_capacity = new_default_capacity;
				//执行扩容操作
				book* ptr = (book*)realloc(pLib->data, (pLib->setup.default_capacity) * sizeof(book));
				//如果扩容失败
				if (ptr == NULL)
				{
					perror("realloc_capacity_by_situp");
				}
				else
				{
					pLib->data = ptr;
					pLib->total_capacity = pLib->setup.default_capacity;
					printf("扩容成功！\n");
					return;
				}
				printf("按任意键继续...");
				_getch();
			}
		}
		else
		{
			printf("请输入有效值\n");
		}
	}
	while (1);
}

/*改变每次扩容量*/
void change_expansion(library* pLib)
{
	int new_expansion = 0;
	do
	{
		printf("输入新扩容容量:>");
		scanf("%d", &new_expansion);
		getchar();
		
		if (new_expansion > 0)
		{
			pLib->setup.expansion = new_expansion;
			printf("修改成功！\n");
			break;
		}
		else
		{
			printf("请输入有效值\n");
		}
	}
	while (1);
}

/*改变每页展示数量*/
void change_show_num(library* pLib)
{
	int new_show_num = 0;
	do
	{
		printf("输入每页展示数:>");
		scanf("%d", &new_show_num);
		getchar();
		if (new_show_num > 0)
		{
			pLib->setup.show_num = new_show_num;
			printf("修改成功！\n");
			break;
		}
		else
		{
			printf("请输入有效值\n");
		}
	}
	while (1);
}

/*恢复备份文件*/
void recover_data_bak(library* pLib)
{
	if (if_input())
	{
		//将备份文件重命名为过渡文件
		int result = rename(".\\Library\\book_information.dat.bak", ".\\Library\\book_information.date");
		//如果命名成功
		if (result == 0)
		{
			//将数据文件重命名为备份文件
			rename(".\\Library\\book_information.dat", ".\\Library\\book_information.dat.bak");
			//将过渡文件重命名为数据文件
			int re = rename(".\\Library\\book_information.date", ".\\Library\\book_information.dat");
			
			if (re == 0)
			{
				printf("恢复成功！");
				init_library(pLib);
			}
			else
			{
				printf("恢复失败！");
			}
		}
		else
		{
			printf("暂无备份！\n");
			
		}
		printf("按任意键继续...");
		_getch();
	}
}

/*备份数据*/
void back_information()
{
	if (CopyFile(".\\Library\\book_information.dat", ".\\Library\\book_information.dat.bak", FALSE))
		printf("\n备份旧数据成功\n");
	else
		printf("\n备份旧数据失败\n");
}

/*清除数据*/
void delete_library(library* pLib)
{
	if (if_input())
	{
		if (pLib->now_capacity == 0)
		{
			printf("教材库为空\n");
		}
		else
		{
			remove(".\\Library\\book_information.dat");
			
			printf("删除成功 ");
			init_book_data(pLib);
		}
		printf("按任意键继续...");
		_getch();
	}
}

void change_password(library* pLib)
{

	
	if(if_input())
	{
		char space[MAX_PASSWPRD];
		input("请输入旧密码:>", space, MAX_PASSWPRD);
		if(0 == strcmp(space, pLib->user_data[pLib->login_user_location].password))
		{
			input("请输入新密码:>", space, MAX_PASSWPRD);
			strcpy(pLib->user_data[pLib->login_user_location].password, space);
			printf("修改成功！\n");
		}
		else
		{
			printf("密码错误！\n");
		}
		printf("按任意键继续...");
		_getch();
	}
}
//高级系统设置
void high_system_set_up(library* pLib)
{
	high_set_up_choice user_choice;
	
	do
	{
		//打印高级设置菜单
		print_high_set_up_menu(pLib);
		
		scanf("%u", (unsigned int*)&user_choice);
		getchar();
		
		switch (user_choice)
		{
		case SET_EXIT:
			return;
		case HIGH_SET_DEFAULT_CAPACITY:
			change_default_capacity(pLib);//改变默认容量
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
			//导入教材信息
			import_book_information(pLib);
			break;
		case HIGH_SET_CHECK_DATE:
			if (pLib->setup.check_date == 1)
				pLib->setup.check_date = 0;
			else
				pLib->setup.check_date = 1;
			break;
		case HIGH_SET_EXPORT:
			//导出教材信息
			export_book_information(pLib);
			break;
		case HIGH_SET_BAK_DATA:
			//备份数据
			back_information();
			printf("----------\n");
			printf("按任意键继续...");
			_getch();
			break;
		default:
			printf("\a");
			//Sleep(400);//暂停400毫秒
			break;
		}
	}
	while (1);
}

//系统设置
int system_set_up(library* pLib)
{
	int power = 0;
	
	set_up_choice user_choice;
	
	do
	{
		power = pLib->user_data[pLib->login_user_location].power;
		//打印设置菜单
		print_set_up_menu(pLib);
		
		scanf("%u", (unsigned int*)&user_choice);
		getchar();
		
		switch (user_choice)
		{
		case SET_EXIT:
			return 0;
//		case SET_DEFAULT_CAPACITY:
//			change_default_capacity(pLib);//改变默认容量
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
//			//导入教材信息
//			import_book_information(pLib);
//			break;
//		case SET_CHECK_DATE:
//			if (pLib->setup.check_date == 1)
//				pLib->setup.check_date = 0;
//			else
//				pLib->setup.check_date = 1;
//			break;
//		case SET_EXPORT:
//			//导出教材信息
//			export_book_information(pLib);
//			break;
//		case SET_BAK_DATA:
//			//备份数据
//			back_information();
//			printf("----------\n");
//			printf("按任意键继续...");
//			_getch();
//			break;
		case SET_COLOR:
			revise_screen_color(pLib);
			break;
		case SET_POWER:
			power > 0 ? warn_printf(power) : user_activation(pLib);//激活密钥
			break;
		case SET_PASSWORD:
			change_password(pLib);
			break;
		case SET_EXIT_ACCOUNT:
			if(if_input())
			{
				//保存教材信息
				save_book_information(pLib);
				//保存配置数据
				save_setup_information(pLib);
	//			//销毁系统
	//			destroyed_library(pLib);
				return 1;
			}
			break;
		case SET_HIGH_SETUP:
			power > 0 ? high_system_set_up(pLib) : warn_printf(power);
			break;
		default:
			printf("\a");
			//Sleep(400);//暂停400毫秒
			break;
		}
	}
	while (1);
}
