/*******************************************************
 * @file atexit.cpp
 * @author Andromeda (ech0uname@qq.com)
 * @brief atexit注册程序终止回调函数
 * @version 0.1
 * @date 2023-12-15
 *
 *
 *******************************************************/

#include <iostream>
#include <unistd.h>

using namespace std;

void exit_handler1()
{
    cout << "exit_handler1 called" << endl;
}

void exit_handler2()
{
    cout << "exit_handler2 called" << endl;
}

int main(int argc, char const *argv[])
{
    // ! 调用与注册的顺序相反
    // ! ISO C标准规定最多可以注册32个回调函数
    if (0 != atexit(exit_handler1))
    {
        perror("atexit");
    }
    if (0 != atexit(exit_handler2))
    {
        perror("atexit");
    }
    return 0;
}
