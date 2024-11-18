#ifndef __BOOK_H__
#define __BOOK_H__

#include "library.h"
//打印书籍操作菜单
void print_main_book_menu();
//书籍操作菜单
void main_book_menu(library* pLib);
//销毁系统
void destroyed_library(library* pLib);
//添加教材信息
void add_book_information(library* pLib);
//删除教材信息
void dele_book_information(library* pLib);
//查找教材信息
void seek_book_information(const library* pLib);
//修改教材信息
void change_book_information(library* pLib);
//打印教材信息
void show_book_information(const library* pLib);

//保存教材信息
void save_book_information(library* pLib);
//加载教材信息
void load_book_information(library* pLib);

//导入教材信息
void import_book_information(library* pLib);
//导出教材信息
void export_book_information(library* pLib);

#endif
