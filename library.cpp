#include "library.h"
#include "book.h"
#include "tool.h"
#include "user.h"
/////////////////////////系统创建与销毁函数///////////////////////////////

/*初始化系统*/
void init_library(library* pLib)
{
	//创建存放数据的文件夹
	struct stat sb;
	int flag = 0;
	
	if (stat("Library", &sb) != 0)//如果文件夹不存在
		system("mkdir Library");
	
	//加载配置信息
	load_setup_information(pLib);

	//分配默认容量
	pLib->data = (book*)malloc(pLib->setup.default_capacity * sizeof(book));
	//分配用户空间
	pLib->user_data = (user*)malloc(DEFAULT_USER*sizeof(user));
	
	if(pLib->data == NULL)
	{
		perror("init_library:init_data");
		flag = 1;
	}
	else if(pLib->user_data == NULL)
	{
		perror("init_library:init_user");
		flag = 1;
	}
	
	if(flag == 1)
	{
		printf("按任意键继续...");
		_getch();
		return;
	}
	
	//初始化书籍容量
	pLib->now_capacity = 0;
	pLib->show_capacity = 0;
	pLib->total_capacity = pLib->setup.default_capacity;
	load_book_information(pLib);
	//初始化用户容量
	pLib->now_user_capacity = 0;
	pLib->show_user_capacity = 0;
	pLib->total_user_capacity = DEFAULT_USER;//后续决定是否集成到基本配置
	load_user_information(pLib);
}

/*销毁系统*/
void destroyed_library(library* pLib)
{
	free(pLib->data);
	pLib->data = NULL;
}

//加载配置信息
void load_setup_information(library* pLib)
{
	//打开配置数据文件流
	FILE* pSite = fopen(".\\Library\\setup.info", "rb");

	//如果数据不缺失
	if (pSite != NULL)
	{
		//读取配置信息
		fread(&(pLib->setup), sizeof(setup), 1, pSite);
		//关闭文件流
		fclose(pSite);
		pSite = NULL;
	}
	else
	{
		//没有配置信息，设置基本数据
		pLib->setup.default_capacity = 10000;	//默认容量
		pLib->setup.expansion = 1000;			//每次扩容容量
		pLib->setup.show_num = 12;				//每页展示数量
		pLib->setup.seek_way = 0;				//查找精度
		pLib->setup.check_date = 0;				//导入时检查日期
		strcpy(pLib->setup.color, "color 01");	//屏幕颜色
		save_setup_information(pLib);			//保存一下
	}
	//设置屏幕颜色
	system(pLib->setup.color);
}

//保存配置数据
void save_setup_information(library* pLib)
{
	//打开文件
	FILE* pWrite = fopen(".\\Library\\setup.info", "wb");
	//如果保存失败
	if (pWrite == NULL)
	{
		perror("save_setup_information");
		printf("按任意键继续...");
		_getch();
		return;
	}
	//以二进制方式写入
	fwrite(&(pLib->setup), sizeof(setup), 1, pWrite);

	//关闭文件流
	fclose(pWrite);
	pWrite = NULL;
}   

