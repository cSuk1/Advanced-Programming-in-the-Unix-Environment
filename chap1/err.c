/*******************************************************
 * @file err.c
 * @author cSuk1 (652240843@qq.com)
 * @brief 错误处理示例程序
 * @version 0.1
 * @date 2023-12-01
 *
 *
 *******************************************************/

#include "header.h"

extern int errno;

int main(int argc, char const *argv[])
{
    errno = 0;
    printf("%s\n", strerror(errno));
    perror("now errno is 0 ");
    errno = 1;
    printf("%s\n", strerror(errno));
    perror("now errno is 1 ");
    errno = 2;
    printf("%s\n", strerror(errno));
    perror("now errno is 2 ");
    return 0;
}
