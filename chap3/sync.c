/*******************************************************
 * @file sync.c
 * @author Andromeda (ech0uname@qq.com)
 * @brief  sync fsync fdatasync示例程序
 * @version 0.1
 * @date 2023-12-06
 *
 *
 *******************************************************/
#include "header.h"

int main(int argc, char const *argv[])
{
    /*******************************************************
     * @brief
     * * void sync(void)
     * ! 修改过的数据块缓冲区放入到设备写队列中后立即返回
     * * int fsync(int fd)
     * ! 把 fd 对应的文件数据以及文件属性信息（inode等信息）写入到磁盘，
     * ! 并且等待写磁盘操作完成后而返回。
     * ! 应用程序一般都是通过调用该函数确保修改过的数据能够立即写入到磁盘上，比如 redis等。
     * * int fdatasync(int fd)
     * ! 与 fsync 类似，只不过 fdatasync 只将数据更新到磁盘，而不更新文件属性信息到磁盘。
     * @author Andromeda (ech0uname@qq.com)
     * @date 2023-12-06
     *******************************************************/
    // 计时器
    struct timeval start, end;

    // !异步
    int fd = open("./test", O_RDWR);
    gettimeofday(&start, NULL);
    write(fd, "test", 4);
    gettimeofday(&end, NULL);
    // 时间差，微秒为单位
    printf("asyn time: %ld us\n", (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));
    close(fd);

    // !sync函数
    fd = open("./test", O_RDWR);
    gettimeofday(&start, NULL);
    write(fd, "test", 4);
    sync();
    gettimeofday(&end, NULL);
    // 时间差，微秒为单位
    printf("sycn time: %ld us\n", (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));
    close(fd);

    // !fsync
    fd = open("./test", O_RDWR);
    gettimeofday(&start, NULL);
    write(fd, "test", 4);
    fsync(fd);
    gettimeofday(&end, NULL);
    // 时间差，微秒为单位
    printf("fsycn time: %ld us\n", (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));
    close(fd);

    // !fdatasync
    fd = open("./test", O_RDWR);
    gettimeofday(&start, NULL);
    write(fd, "test", 4);
    fdatasync(fd);
    gettimeofday(&end, NULL);
    // 时间差，微秒为单位
    printf("fdatasycn time: %ld us\n", (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));
    close(fd);

    // !设置O_SYNC标志位
    fd = open("./test", O_RDWR | O_SYNC);
    gettimeofday(&start, NULL);
    write(fd, "test", 4);
    gettimeofday(&end, NULL);
    // 时间差，微秒为单位
    printf("o_sync time: %ld us\n", (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));
    close(fd);

    return 0;
}
