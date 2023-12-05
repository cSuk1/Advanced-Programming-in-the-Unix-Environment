/*******************************************************
 * @file fd.c
 * @author Andromeda (ech0uname@qq.com)
 * @brief 文件描述符示例程序-open openat close write read lseek
 * @version 0.1
 * @date 2023-12-03
 *
 *
 *******************************************************/

#include "header.h"

int main(int argc, char const *argv[])
{
    // 创建一个文件
    int fd;
    if ((fd = open("./test", O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1)
    {
        perror("fail to create");
    }
    // 写入内容
    char buff[BUFFER_SIZE];
    bzero(buff, BUFFER_SIZE);
    strcpy(buff, "hello world!");
    write(fd, buff, strlen(buff));
    close(fd);
    // 读取内容
    fd = open("./test", O_RDONLY);
    bzero(buff, BUFFER_SIZE);
    // 读取成功返回读取的字节数，如果读取完文件，则返回0，出错返回-1
    read(fd, buff, BUFFER_SIZE);
    printf("%s\n", buff);
    bzero(buff, BUFFER_SIZE);
    close(fd);

    // openat函数
    fd = open("../chap1", O_RDONLY);
    // fd参数指定path在文件系统中的开始位置
    int fd1 = openat(fd, "./test", O_RDONLY);
    bzero(buff, BUFFER_SIZE);
    read(fd1, buff, BUFFER_SIZE);
    printf("%s\n", buff);
    close(fd1);
    close(fd);

    // 如果openat的第二个参数为绝对路径，则fd参数被忽略
    fd = open("./", O_RDONLY);
    fd1 = openat(fd, "/home/tsuk1/caixing/Advanced-Programming-in-the-Unix-Environment/chap1/test", O_RDONLY);
    read(fd1, buff, BUFFER_SIZE);
    printf("%s\n", buff);
    bzero(buff, BUFFER_SIZE);
    close(fd1);
    close(fd);

    // lseek函数
    fd = open("./test", O_RDWR | O_APPEND);
    bzero(buff, BUFFER_SIZE);
    // 偏移量为2
    off_t offset = 2;
    // 设置fd偏移量
    /**
     * 第三个参数
     * SEEK_SET	0	Seek from beginning of file.
     * SEEK_CUR	1	Seek from current position.
     * SEEK_END 2   Seek from end of file.
     */
    if (lseek(fd, offset, SEEK_CUR) == -1)
    {
        perror("lseek fail");
    }
    read(fd, buff, BUFFER_SIZE);
    printf("%s\n", buff);
    bzero(buff, BUFFER_SIZE);
    close(fd);

    return 0;
}
