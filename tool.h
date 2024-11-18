#ifndef __TOOL_H__
#define __TOOL_H__

#include "library.h"
//输入检查函数
void input(char* hint, char* output, size_t size);
// 1|0 输入判断是否继续
int if_input();
//修改背景/字体颜色
void revise_screen_color(library* pLib);
#endif
