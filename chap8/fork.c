/*******************************************************
 * @file fork.c
 * @author Andromeda (ech0uname@qq.com)
 * @brief fork示例程序
 * @version 0.1
 * @date 2023-12-17
 *
 *
 *******************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    // ! write不带用户空间缓冲区，所以只输出一次
    // write(STDOUT_FILENO, "Hello, World!\n", 13);
    int fd = open("./test", O_RDWR | O_CREAT, 0666);
    dup2(fd, STDOUT_FILENO);
    // ! printf带用户空间缓冲区，所以复制后该内容还存在缓冲区，父进程和子进程都输出一次
    // ! 但是需要重定向到文件，因为标准输出是行缓冲的，否则是全缓冲
    /**
     * * 在UNIX系统中，标准输出（stdout）默认情况下是行缓冲的，
     * * 这意味着当数据被写入stdout时，它们会被缓存在内存中，
     * * 直到达到一定条件才会被刷新到目标设备（通常是终端）。
     * * 这个条件通常是当缓冲区被填满，或者遇到换行符（'\n'）时。
     * * 所以重定向到文件改为全缓冲时，会输出两次，否则仍然输出一次
     * * 另外需要注意的——父子进程共享同一个文件偏移量
     */
    printf("Hello, World!\n");
    if (fork() == 0)
    {
        // write(STDOUT_FILENO, "c Hello, World!\n", 15);
        printf("c Hello, World!\n");
        exit(0);
    }
    else
    {
        // write(STDOUT_FILENO, "p Hello, World!\n", 15);
        printf("p Hello, World!\n");
    }

    return 0;
}
