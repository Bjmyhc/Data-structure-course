# 数据结构

#### 介绍
本项目为大二数据结构作业，开发的一个教材管理系统。github仓库：https://github.com/Bjmyhc/Data-structure-course

#### 软件架构
采用c语言编写，为了提高兼容性，使用.cpp为后缀。编写工具为小熊猫c++，`project.dev`是项目文件。


#### 使用说明

一 .用户权限说明

1，超管：即超级管理员，等级2，为系统最高权限，可管理所有用户以及教材。只有注册指定账号`admin`可获得。

2，管理员：普通管理员，等级1，可管理所有教材。不能进入后台对用户进行操作。

3，普通用户：注册用户，等级0，只能对书籍进行查询和打印（后续可能添加订书功能）。

二 .密钥说明：

密钥是根据本地时间得到的一个时间字符串，格式为年-月-日-时-分。例如2024-11-22-15-04。

三.使用提示

a.项目路径中`Library`文件夹储存着用户数据、教材数据和程序配置的数据，以及导出后的教材文本文件和用户文本文件。

在项目根目录中，`books.txt`为教材文本文件，`books_test.txt`为测试文件,截取自`books.txt`。由管理员登录后导入。

b.注册过程中，输入账号为`admin`会被系统识别为超级管理员，其他则为普通用户。普通用户可通过激活码成为管理员，或者由超级管理员设置为管理员。另外，超级管理员可以将管理员降级为普通用户，但不能升级为超级管理员。



ps：本项目由于作者能力有限，可能还有bug尚未解决，欢迎提出疑问~



