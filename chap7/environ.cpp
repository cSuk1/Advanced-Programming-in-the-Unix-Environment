/*******************************************************
 * @file environ.cpp
 * @author Andromeda (ech0uname@qq.com)
 * @brief 环境表
 * @version 0.1
 * @date 2023-12-15
 *
 *
 *******************************************************/
#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char const *argv[])
{
    // ! 环境指针->环境表->环境字符串
    extern char **environ;
    for (int i = 0; environ[i] != nullptr; i++)
    {
        cout << environ[i] << endl;
    }
    cout << "get env USER = " << getenv("USER") << endl;
    return 0;
}
