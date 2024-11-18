#include "tool.h"

/*�����麯��*/
//---------------��ʾ-------�������-------�����С
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
			printf("����հף�����������\n");
		}
		else if (strlen(cache) == size - 1 && cache[size - 2] != '\n')
		{
			
			printf("���볬���޶ȣ�����������\n");
			// ������뻺����
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

/* 1|0 �����жϺ���*/
int if_input()
{
	char export_choice;
	
	printf("ȷ�ϼ���ִ�иò�����(1/0):");
	
	do
	{
		scanf(" %c", &export_choice);
		getchar();
		
		if (export_choice == '1')
		{
			//���غϷ�ֵ
			return 1;
		}
		else if (export_choice == '0')
		{
			return 0;
		}
		else
		{
			printf("\x1b[G");//��������
			printf("\x1b[K");//�������
			printf("�����������������:>");
		}
	}
	while (1);
}
////////////////////////////���Ի����ܺ���/////////////////////////////////////
/*ͨ��������޸���Ļ��ɫ*/
void revise_screen_color(library* pLib)
{
	char cChoose_color_key;
	char Fore_color[] = "0123456789ABCDEF";//ǰ����ɫ
	char Back_color[] = "0123456789ABCDEF";//������ɫ
	char command_color[10];//����޸���ɫ���� 
	char* pF = Fore_color;
	char* pB = Back_color;
	
	system("cls");
	printf(" =���ҷ����ѡ��ǰ����ɫ�����·����ѡ�񱳾���ɫ���س���ȷ��=\n\n");
	
	printf("\033[?25l"); //���ع�� 
	
	do
	{
		printf("\033[K"); //�����ǰ�� 
		printf("\033[3H");//������ƶ�����������λ 
		
		cChoose_color_key = getch();//�û����·���� 
		//printf("%d\n", cChoose_color_key);
		//key���� 72 || �� 80 || �� 75 || �� 77 
		
		if (cChoose_color_key == 72)
		{
			if (*pF == '0')
				printf("�ѵ����϶�\n");
			else
				pF--;
		}
		else if (cChoose_color_key == 80)
		{
			if (*pF == 'F')
				printf("�ѵ����¶�\n");
			else
				pF++;
		}
		else if (cChoose_color_key == 75)
		{
			if (*pB == '0')
				printf("�ѵ������\n");
			else
				pB--;
		}
		else if (cChoose_color_key == 77)
		{
			if (*pB == 'F')
				printf("�ѵ����Ҷ�\n");
			else
				pB++;
		}
		
		sprintf(command_color, "color %c%c", *pF, *pB);//ƴ���ַ��� 
		system(command_color);//������ɫ 
		strcpy(pLib->setup.color, command_color);//��¼����
		
	} while (cChoose_color_key != 13);//�س���ASCII��ֵ������޸� 
	
	printf("\033[?25h"); //��ʾ���
}
