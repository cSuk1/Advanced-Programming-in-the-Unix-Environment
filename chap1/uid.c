/*******************************************************
 * @file uid.c
 * @author cSuk1 (652240843@qq.com)
 * @brief 用户标识示例程序
 * @version 0.1
 * @date 2023-12-01
 *
 *
 *******************************************************/

#include "header.h"

int main(int argc, char const *argv[])
{
    int uid = getuid();
    int gif = getgid();
    printf("uid:%d, gid:%d\n", uid, gif);
    return 0;
}
