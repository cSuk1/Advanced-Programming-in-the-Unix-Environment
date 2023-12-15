/*******************************************************
 * @file dup.c
 * @author Andromeda (ech0uname@qq.com)
 * @brief dup和dup2
 * @version 0.1
 * @date 2023-12-04
 *
 *
 *******************************************************/

#include "header.h"

// #define dup
// #define dup2
// #define stdout2fd
// #define stdin2fd

int main(int argc, char const *argv[])
{
    // dup，返回当前可用的最大文件描述符
#ifdef dup
    int fd1 = dup(STDOUT_FILENO);
    // dup等效于
    int fd2 = fcntl(fd1, F_DUPFD, 0);

    write(fd1, "hello", 5);
    write(fd2, "world", 5);
    printf("\nfd1 %d fd2 %d\n", fd1, fd2);
    close(fd1);
    close(fd2);
#endif

#ifdef dup2
    // dup2可以自己指定返回的文件描述符，既将参数一复制到参数二
    int fd3 = dup2(STDIN_FILENO, 10);
    // dup2等效于
    close(10);
    int fd4 = fcntl(STDIN_FILENO, F_DUPFD, 10);

    printf("fd3 %d fd4 %d\n", fd3, fd4);
    char buf[BUFFER_SIZE];
    while (1)
    {
        bzero(buf, BUFFER_SIZE);
        read(fd4, buf, BUFFER_SIZE);
        if (strncmp(buf, "exit", 4) == 0)
        {
            break;
        }
        printf("%s", buf);
    }
    close(fd3);
    close(fd4);
#endif

#ifdef stdout2fd
    int fd5 = open("./test", O_RDWR | O_APPEND);
    // 将标准输出重定向到fd5
    dup2(fd5, STDOUT_FILENO);
    // 写入文件
    // printf("caixng");
    write(STDOUT_FILENO, "caixing", 7);
    bzero(buf, BUFFER_SIZE);
    close(fd5);
#endif

#ifdef stdin2fd
    int fd6 = open("./test", O_RDWR | O_APPEND);
    // 标准输入重定向到fd6
    dup2(fd6, STDIN_FILENO);
    // 读取标准输入，既读取文件
    // scanf("%s", buf);
    // 读取文件
    read(STDIN_FILENO, buf, BUFFER_SIZE);
    // 写入标准输出，既写入文件
    printf("%s\n", buf);
    close(fd6);
#endif

    return 0;
}
