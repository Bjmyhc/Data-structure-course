#include "book.h"
#include "user.h"
#include "library.h"

int main()
{
	//定义系统w
	library lib;
	//初始化系统
	init_library(&lib);
	//进入登录_注册界面
	
	do
	{
		if(user_login_register(&lib) == 1)
			main_book_menu(&lib);//进入书籍操作界面
	}while(1);
	
	return 0;
}
