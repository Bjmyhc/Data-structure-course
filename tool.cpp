#include "tool.h"

/*输入检查函数*/
//---------------提示-------输出数组-------数组大小
void input(char* hint, char* output, size_t size)
{
	size += 2;
	char* cache = (char*)malloc(size * sizeof(char));
	do
	{
		printf("%s", hint);
		fgets(cache, size, stdin);
		
		if (cache[0] == '\n' || cache[0] == ' ')
		{
			printf("输入空白，请重新输入\n");
		}
		else if (strlen(cache) == size - 1 && cache[size - 2] != '\n')
		{
			
			printf("输入超出限度，请重新输入\n");
			// 清空输入缓冲区
			char c;
			while ((c = getchar()) != '\n' && c != EOF);
		}
		else
		{
			sscanf(cache, "%s", output);
			break;
		}
	}
	while (1);
	free(cache);
	cache = NULL;
}

/* 1|0 输入判断函数*/
int if_input()
{
	char export_choice;
	
	printf("确认继续执行该操作嘛(1/0):");
	
	do
	{
		scanf(" %c", &export_choice);
		getchar();
		
		if (export_choice == '1')
		{
			//返回合法值
			return 1;
		}
		else if (export_choice == '0')
		{
			return 0;
		}
		else
		{
			printf("\x1b[G");//调到行首
			printf("\x1b[K");//清除该行
			printf("输入错误，请重新输入:>");
		}
	}
	while (1);
}
////////////////////////////个性化功能函数/////////////////////////////////////
/*通过方向键修改屏幕颜色*/
void revise_screen_color(library* pLib)
{
	char cChoose_color_key;
	char Fore_color[] = "0123456789ABCDEF";//前景颜色
	char Back_color[] = "0123456789ABCDEF";//背景颜色
	char command_color[10];//存放修改颜色命令 
	char* pF = Fore_color;
	char* pB = Back_color;
	
	system("cls");
	printf(" =左右方向键选择前景颜色，上下方向键选择背景颜色，回车键确认=\n\n");
	
	printf("\033[?25l"); //隐藏光标 
	
	do
	{
		printf("\033[K"); //清除当前行 
		printf("\033[3H");//将光标移动到第三行首位 
		
		cChoose_color_key = getch();//用户按下方向键 
		//printf("%d\n", cChoose_color_key);
		//key：上 72 || 下 80 || 左 75 || 右 77 
		
		if (cChoose_color_key == 72)
		{
			if (*pF == '0')
				printf("已到最上端\n");
			else
				pF--;
		}
		else if (cChoose_color_key == 80)
		{
			if (*pF == 'F')
				printf("已到最下端\n");
			else
				pF++;
		}
		else if (cChoose_color_key == 75)
		{
			if (*pB == '0')
				printf("已到最左端\n");
			else
				pB--;
		}
		else if (cChoose_color_key == 77)
		{
			if (*pB == 'F')
				printf("已到最右端\n");
			else
				pB++;
		}
		
		sprintf(command_color, "color %c%c", *pF, *pB);//拼接字符串 
		system(command_color);//设置颜色 
		strcpy(pLib->setup.color, command_color);//记录下来
		
	} while (cChoose_color_key != 13);//回车键ASCII码值，完成修改 
	
	printf("\033[?25h"); //显示光标
}
