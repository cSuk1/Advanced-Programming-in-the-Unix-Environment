/*******************************************************
 * @file process.c
 * @author cSuk1 (652240843@qq.com)
 * @brief 程序和进程示例程序
 * @version 0.1
 * @date 2023-12-01
 *
 *
 *******************************************************/
#include "header.h"

int main(int argc, char const *argv[])
{
    // printf("parent: id:%d\n", getpid());
    pid_t pid;
    char buffer[BUFFER_SIZE];
    int fd;
    while (fgets(buffer, BUFFER_SIZE, stdin) != NULL)
    {
        // 创建子进程
        if (0 > (pid = fork()))
        {
            perror("fork");
            exit(1);
        }
        // 子进程
        else if (0 == pid)
        {
            int len = strlen(buffer);
            buffer[len - 1] = '\0';
            /*******************************************************
             * @brief exec函数族
             * exec 函数族是一组在 UNIX 或 UNIX-like 操作系统上使用的函数，用于在当前进程中执行新程序。
             * int execl(const char *path, const char *arg, ...)：
             * 接受一个可变数量的参数列表，用于指定新程序的命令行参数。
             * 参数列表以 NULL 结束。该函数根据给定的路径执行新程序。
             * int execv(const char *path, char *const argv[])：
             * 接受一个字符串数组 argv，用于指定新程序的命令行参数。
             * 数组的最后一个元素必须是 NULL，以标识参数列表的结束。该函数根据给定的路径执行新程序。
             * int execle(const char *path, const char *arg, ..., char *const envp[])：
             * 与 execl 类似，但还接受一个环境变量数组 envp，用于指定新程序的环境变量。
             * 环境变量数组的最后一个元素必须是 NULL，以标识数组的结束。
             * int execve(const char *path, char *const argv[], char *const envp[])：
             * 与 execv 类似，但还接受一个环境变量数组 envp，用于指定新程序的环境变量。
             * 环境变量数组的最后一个元素必须是 NULL，以标识数组的结束。
             * int execlp(const char *file, const char *arg, ...)：
             * 类似于 execl，但会在系统的环境变量 PATH 中搜索可执行文件。
             * int execvp(const char *file, char *const argv[])：
             * 类似于 execv，但会在系统的环境变量 PATH 中搜索可执行文件。
             *
             * l 结尾的函数使用可变数量的参数列表传递命令行参数，
             * v 结尾的函数使用字符串数组传递命令行参数。
             * e 结尾的函数还接受环境变量数组作为参数。
             * p 结尾的函数会在系统的环境变量 PATH 中搜索可执行文件。
             *******************************************************/
            execlp(buffer, buffer, NULL);
            perror("exec");
            exit(128);
        }
        // 父进程
        else
        {
            int stat_code;
            waitpid(pid, &stat_code, 0);
            printf("parent: child exit code %d\n", stat_code);
        }
    }
    return 0;
}
