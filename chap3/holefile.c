/*******************************************************
 * @file holefile.c
 * @author Andromeda (ech0uname@qq.com)
 * @brief 创建空洞文件
 * @version 0.1
 * @date 2023-12-04
 *
 *
 *******************************************************/

#include "header.h"

int main(int argc, char const *argv[])
{
    char buf1[] = "caixing";
    char buf2[] = "andromeda";
    int fd;

    // 创建一个名为hole_file的文件，如果文件已存在，则将其覆盖
    if ((fd = open("./hole_file", O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1)
    {
        perror("fail to create");
    }

    // 将buf1写入文件，如果文件写入失败，则返回-strlen(buf1)
    if (write(fd, buf1, strlen(buf1)) == -strlen(buf1))
    {
        perror("file to write");
    }

    // 设置文件当前读写位置为16384
    off_t offset = 16384;
    if (lseek(fd, offset, SEEK_SET) == -1)
    {
        perror("fail to lseek");
    }

    // 将buf2写入文件，如果文件写入失败，则返回-strlen(buf2)
    if (write(fd, buf2, strlen(buf2)) == -strlen(buf2))
    {
        perror("file to write");
    }

    return 0;
}
