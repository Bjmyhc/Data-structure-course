#include "library.h"
#include "user.h"

/*打印后台菜单*/
void print_control_menu(const library* pLib)
{
	int power = pLib->user_data[pLib->login_user_location].power;
	
	system("cls");
//	printf("您当前用户[%s],权限为：%s\n",pLib->user_data[pLib->login_user_location].account, 
//		power > 1 ? "超管": power > 0 ? "管理员" : "普通用户" );
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

//后台管理
void user_control(library* pLib)
{
	control_choice user_choice;//用户选择

	do
	{
		print_control_menu(pLib);//打印主菜单
		
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
			break;
		default:
			//	printf("输入无效，请重新输入!");
			break;
		}
	}while(1);
}
