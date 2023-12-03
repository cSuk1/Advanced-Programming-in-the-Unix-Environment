/*******************************************************
 * @file signal.c
 * @author cSuk1 (652240843@qq.com)
 * @brief 信号示例程序
 * @version 0.1
 * @date 2023-12-01
 *
 *
 *******************************************************/

#include "header.h"

// 信号处理函数
void sig_handler(int signo)
{
    // SIGINT 信号的默认操作是终止进程。
    // 当程序接收到 SIGINT 信号时，操作系统会终止进程的执行。
    printf("signal %d received\n", signo);
    exit(0);
}

int main(int argc, char const *argv[])
{
    // 设置SIGINT信号处理函数为sig_handler
    if (signal(SIGINT, sig_handler) == SIG_ERR)
    {
        // 如果设置失败，打印错误信息并退出
        perror("signal");
        exit(1);
    }
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
    return 0;
}
