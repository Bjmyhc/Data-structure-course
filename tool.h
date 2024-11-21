#ifndef __TOOL_H__
#define __TOOL_H__

#include "library.h"

#define MAX_TIME 64

//输入检查函数
void input(char* hint, char* output, size_t size);
// 1|0 输入判断是否继续
int if_input();
//打印警告信息函数
void warn_printf(int power, int limit = 0);
//修改背景/字体颜色
void revise_screen_color(library* pLib);
//获取本地时间
void local_time(char* local_time);
//限制长度输出
void limit_printf(const char* format, const char* var, int limit);
//空函数,什么也不做
void null_function();
#endif
