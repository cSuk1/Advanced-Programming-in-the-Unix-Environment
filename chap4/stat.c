/*******************************************************
 * @file stat.c
 * @author Andromeda (ech0uname@qq.com)
 * @brief stat、fstat、fstatat、lstat函数示例程序
 * @version 0.1
 * @date 2023-12-08
 *
 *
 *******************************************************/

#include "header.h"

/*******************************************************
 * @brief 输出stat结构体中的内容
 *
 * @param st
 * @author Andromeda (ech0uname@qq.com)
 * @date 2023-12-09
 *******************************************************/
void printStat(struct stat st)
{
    // 输出stat的内容
    if (S_ISREG(st.st_mode))
    {
        printf("regular file\n");
    }
    if (S_ISDIR(st.st_mode))
    {
        printf("directory\n");
    }
    if (S_ISCHR(st.st_mode))
    {
        printf("character device\n");
    }
    if (S_ISBLK(st.st_mode))
    {
        printf("block device\n");
    }
    if (S_ISFIFO(st.st_mode))
    {
        printf("fifo\n");
    }
    if (S_ISLNK(st.st_mode))
    {
        printf("symbolic link\n");
    }
    if (S_ISSOCK(st.st_mode))
    {
        printf("socket\n");
    }

    printf("st_dev: %ld\n", st.st_dev);         // 输出文件的设备ID
    printf("st_ino: %ld\n", st.st_ino);         // 输出文件的inode号
    printf("st_mode: %d\n", st.st_mode);        // 输出文件的权限模式
    printf("st_nlink: %ld\n", st.st_nlink);     // 输出文件的链接数
    printf("st_uid: %d\n", st.st_uid);          // 输出文件的所有者ID
    printf("st_gid: %d\n", st.st_gid);          // 输出文件的所有者所在组的ID
    printf("st_rdev: %ld\n", st.st_rdev);       // 输出文件的设备ID（对于特殊文件）
    printf("st_size: %ld\n", st.st_size);       // 输出文件的大小
    printf("st_blksize: %ld\n", st.st_blksize); // 输出块大小
    printf("st_blocks: %ld\n", st.st_blocks);   // 输出文件的块数
    printf("st_atim: %ld\n", st.st_atime);      // 输出文件的最后访问时间
    printf("st_mtim: %ld\n", st.st_mtime);      // 输出文件的最后修改时间
    printf("st_ctim: %ld\n", st.st_ctime);      // 输出文件的最后更改时间
}

int main(int argc, char const *argv[])
{
    printf("*******************************************************\n");
    {
        /*******************************************************
         * @brief stat函数示例程序
         *
         * todo int stat(const char *path, struct stat *buf);
         * @note stat函数用于获取指定路径下文件的信息，并将结果存储在struct stat结构体中。
         * @note 它接受文件路径作为第一个参数，将文件信息存储在第二个参数指向的结构体中。
         * @author Andromeda (ech0uname@qq.com)
         * @date 2023-12-09
         *******************************************************/
        struct stat st;
        stat("./link", &st);
        printStat(st);
    }
    printf("*******************************************************\n");
    {
        /*******************************************************
         * @brief lstat示例程序
         * todo int lstat(const char *path, struct stat *buf);
         *
         * @note lstat函数类似于stat函数，用于获取指定路径下文件的信息。
         * @note 它与stat函数的区别在于，它不解析符号链接，而是直接获取符号链接指向的文件信息。
         * @note 创建一个符号链接ln -s /path/to/test /path/to/link
         * @author Andromeda (ech0uname@qq.com)
         * @date 2023-12-09
         *******************************************************/
        struct stat st;
        lstat("./link", &st);
        printStat(st);
    }
    printf("*******************************************************\n");
    {
        /*******************************************************
         * @brief fstat示例程序
         * todo int fstat(int fd, struct stat *buf);
         * @note fstat函数用于获取已打开文件的信息，并将结果存储在struct stat结构体中。
         * @note 它接受文件描述符作为第一个参数，将文件信息存储在第二个参数指向的结构体中。
         * @author Andromeda (ech0uname@qq.com)
         * @date 2023-12-09
         *******************************************************/
        struct stat st;
        int fd = open("./link", O_RDONLY);
        fstat(fd, &st);
        printStat(st);
    }
    printf("*******************************************************\n");
    {
        /*******************************************************
         * @brief fstatat示例程序
         *
         * todo int fstatat(int dirfd, const char *pathname, struct stat *buf, int flags);
         * @note 类似于stat函数，用于获取指定路径下文件的信息，并将结果存储在struct stat结构体中。
         * @note 它接受一个目录文件描述符作为第一个参数，文件路径作为第二个参数，将文件信息存储在第三个参数指向的结构体中。
         * @note flags参数用于指定一些行为选项，如解析符号链接等。
         * @author Andromeda (ech0uname@qq.com)
         * @date 2023-12-09
         *******************************************************/
        struct stat st;
        int fd = open("./", O_RDONLY);
        fstatat(fd, "link", &st, 0);
        printStat(st);
    }
    printf("*******************************************************\n");
    return 0;
}
