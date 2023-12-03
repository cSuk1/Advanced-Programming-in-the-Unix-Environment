/*******************************************************
 * @file io.c
 * @author cSuk1 (652240843@qq.com)
 * @brief IO示例程序
 * @version 0.1
 * @date 2023-12-01
 *
 *
 *******************************************************/
#include "header.h"

void WithBuf()
{
    // 声明文件描述符
    int fd;
    // 声明缓冲区
    char buffer[BUFFER_SIZE];
    // 读取标准输入
    while ((fd = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0)
    {
        // 写入标准输出
        if (fd != write(STDOUT_FILENO, buffer, fd))
        {
            perror("write");
            exit(1);
        }
    }
    // 判断是否读取到数据
    if (fd < 0)
    {
        perror("read");
        exit(1);
    }
}

void WithoutBuf()
{
    int fd;
    // 一次读一个字符
    while ((fd = getc(stdin)) != EOF)
    {
        // 输出字符
        if (putc(fd, stdout) == EOF)
        {
            perror("putc");
            exit(1);
        }
    }
    if (ferror(stdin))
    {
        perror("ferror");
        exit(1);
    }
}

int main(int argc, char const *argv[])
{
    WithoutBuf();
    return 0;
}
