/*******************************************************
 * @file vfork.c
 * @author Andromeda (ech0uname@qq.com)
 * @brief vfork示例程序
 * @version 1.0
 * @date 2023-12-17
 *
 *
 *******************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    int val = 314;
    printf("parent val: %d\n", val);
    if (0 == (pid = vfork()))
    {
        printf("child pid: %d\n", getpid());
        val++;
        /**
         * ! 需要注意的另外一点
         * ! vfork保证子进程先执行，子进程execv或者exit后父进程才执行
         * ! 所以如果子进程调用execv或者exit之前依赖父进程的进一步处理，则会造成死锁
         * ! 造成死锁的代码如下
         */
        // while (val != 316)
        // {
        //     continue;
        // }
        // char *const argv[] = {"/bin/ls", NULL};
        // execv("/bin/ls", argv);
        /**
         * * 如果子进程调用exit，输出结果是不确定的，依赖于标准IO库的实现
         * * 如果标准IO库冲洗标准IO流，有尚未写入设备的输出数据将被写入到相应的设备，则与_exit结果相同
         * * 如果标准IO库关闭标准IO流，那么表示标准输出的FILE对象相关存储区会被清0
         * * 父进程就不会产生任何输出
         */
        // exit(0);
        _exit(0);
    }
    else
    {
        if (pid > 0)
        {
            int status;
            // 等到子进程结束
            wait(&status);
            printf("parent pid: %d\n", getpid());
            printf("child pid: %d\n", pid);
            printf("child status: %d\n", status);
            /**
             * * 这个函数和fork一样创建一个子进程
             * * 但是不会将父进程的地址空间完全复制到子进程
             * * 因为这个函数用于创建子进程执行execv函数
             * * 所以默认不会引用父进程的地址空间
             * * 子进程调用execv和exit之前，
             * * 子进程在父进程空间运行，与父进程共享同一堆栈
             * * 能够提高效率
             */
            // ! 变为316了，说明子进程的操作影响了父进程
            val++;
            printf("parent val: %d\n", val);
        }
        else
        {
            perror("vfork");
            exit(1);
        }
    }
    return 0;
}