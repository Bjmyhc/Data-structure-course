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

/*打印后台菜单*/
void print_control_menu(const library* pLib)
{
	system("cls");
	//查询管理员数量
	int admin_num  = administrator_num(pLib);
//	printf("您当前用户[%s],权限为：%s\n",pLib->user_data[pLib->login_user_location].account, 
//		power > 1 ? "超管": power > 0 ? "管理员" : "普通用户" );
	printf("目前共%d名用户,其中管理员%d名\n",pLib->total_user_capacity, admin_num);
	printf("-----------------------\n");
	printf("|**** %u.添加用户 **** |\n", CONTROL_ADD);
	printf("|**** %u.删除用户 **** |\n", CONTROL_DEL);
	printf("|**** %u.查找用户 **** |\n", CONTROL_SEEK);
	printf("|**** %u.修改信息 **** |\n", CONTROL_CHANGE);
	printf("|**** %u.所有用户 **** |\n", CONTROL_SHOW);
	printf("|**** %u.后台设置 **** |\n", CONTROL_SETUP);
	printf("|**** %u.退出后台 **** |\n", CONTROL_EXIT);
	printf("-----------------------\n\n");
	printf("请选择>:");
}

//打印后台设置
void print_user_control_setup(library* pLib)
{
	system("cls");
	printf("        设置        \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("导入↘                  \n");
	printf("  %u.导入用户(.txt)     \n", USER_IMPORT);
//	printf("  %u.检查完整性：%s\n", USER_CHECK, pLib->setup.check_user_data > 0 ? "是" : "否");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("导出↘                  \n");
	printf("  %u.导出用户(.txt)     \n", USER_EXPORT);
//	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
//	printf("操作↘                  \n");
//	printf("  %u.备份所有数据       \n", HIGH_SET_BAK_DATA);
//	printf("  %u.清空所有数据       \n", HIGH_SET_DEL_LIB);
//	printf("  %u.恢复备份数据       \n", HIGH_SET_RECOVER_DATA_BAK);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("  %u.退出后台设置       \n", USER_EXIT);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf("请选择:>");
}

//后台设置
void user_control_setup(library* pLib)
{
	user_setup_choice user_choice;
	
	do
	{
		//打印后台设置菜单
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

//后台管理
void user_control(library* pLib)
{
	control_choice user_choice;//用户选择

	do
	{
		print_control_menu(pLib);//打印菜单
		
		user_choice = (control_choice)99;//初始化选项，防止错误值乱入功能
		scanf(" %u", (unsigned int*)&user_choice);	//获取用户输入选项
		getchar();
		
		switch (user_choice)
		{
		case CONTROL_EXIT:
			return;
		case CONTROL_ADD:
			user_register(pLib);//用户注册
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
			//	printf("输入无效，请重新输入!");
			break;
		}
	}while(1);
}


