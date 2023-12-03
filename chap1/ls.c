/*******************************************************
 * @file ls.c
 * @author cSuk1 (652240843@qq.com)
 * @brief ls 示例程序
 * @version 0.1
 * @date 2023-12-01
 *
 *
 *******************************************************/
#include "header.h"

int main(int argc, char const *argv[])
{
    // 定义一个DIR类型的指针
    DIR *dp;
    // 定义一个struct dirent类型的指针
    struct dirent *ep;
    // 如果参数大于2，则报错
    if (argc > 2)
    {
        perror("./ls <dir>");
        return 1;
    }
    // 可以用chdir改变进程的工作目录
    chdir("../");
    // 如果参数小于2，则将参数1赋值给dir，否则将"./"赋值给dir
    const char *dir = argc == 2 ? argv[1] : "./";
    // 如果opendir函数返回NULL，则报错
    // 正确情况下返回DIR结构指针
    if ((dp = opendir(dir)) == NULL)
    {
        perror("opendir failed");
        return 1;
    }
    // 循环读取目录中的文件
    printf("%-8s\t%-8s\t%-12s\t%-9s\n", "filename", "filetype", "recordlength", "fileinode");
    // 正确情况下返回dirent结构指针
    while ((ep = readdir(dp)) != NULL)
    {
        // 打印文件名
        printf("%-8s\t%-8s\t%-12d\t%-9ld\n", ep->d_name, ep->d_type == DT_DIR ? "dir" : "file", ep->d_reclen, ep->d_ino);
    }
    // 关闭目录
    closedir(dp);
    exit(0);
}