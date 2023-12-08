/*******************************************************
 * @file fcntl.c
 * @author Andromeda (ech0uname@qq.com)
 * @brief fcntl示例程序
 * @version 0.1
 * @date 2023-12-06
 * ! fcntl函数可以修改已经打开的文件属性
 * * int fcntl(int fd, int cmd, …);
 *
 *******************************************************/
#include "header.h"

void setFL(int, int);
void getFL(int);
void setFd(int, int);
void getFd(int);
void setSig(int);
void getSig(int);
void dupFd(int *, int *);
void setOwn(int);
void getOwn(int);

int main(int argc, char const *argv[])
{
    int fd;

    fd = open("./test", O_RDWR);
    printf("fd is %d\n", fd);

    int fd2;
    // 复制
    dupFd(&fd, &fd2);
    printf("fd2 is %d\n", fd2);

    // 获取和设置sig
    getSig(fd2);
    setSig(fd2);
    getSig(fd2);

    // 获取和设置fd文件状态描述符
    setFd(fd2, 0);
    getFd(fd2);
    setFd(fd2, 1);
    getFd(fd2);

    // 获取和设置FL文件描述符标志
    getFL(fd2);
    setFL(fd2, O_APPEND);
    getFL(fd2);

    getOwn(fd2);
    setOwn(fd2);
    getOwn(fd2);

    write(fd2, "hello world!", 12);
    close(fd2);
    return 0;
}

// F_DUPFD复制描述符
void dupFd(int *fd, int *fd2)
{
    close(*fd2);
    *fd2 = fcntl(*fd, F_DUPFD, *fd2);
    /**
     * F_DUPFD 在复制文件描述符时不会将文件描述符的信号掩码（如 FD_CLOEXEC）设置为相同。
     * * 当一个进程创建一个文件描述符时，如果将此标志设置为 1，
     * * 则该文件描述符将具有“close on exit”属性。这意味着在进程退出时，
     * * 任何打开的文件描述符都将被关闭，即使这些文件描述符没有被显式关闭。
     * 如果多个进程共享相同的文件描述符，可能会导致进程之间的竞争条件或其他问题。
     * 因此，在复制文件描述符时，通常会使用 F_DUPFD_CLOEXEC 文件描述符操作来设置相同的信号掩码。
     */
}

// SIG的获取
void getSig(int fd)
{
    int flags;
    flags = fcntl(fd, __F_GETSIG, 0);
    if (-1 == flags)
    {
        perror("fcntl");
        exit(1);
    }

    // 检查 FD_CLOEXEC 标志是否设置
    if (flags & FD_CLOEXEC)
    {
        printf("FD_CLOEXEC is set\n");
    }
    else
    {
        printf("FD_CLOEXEC is not set\n");
    }
}

// SIG的设置
void setSig(int fd)
{
    // 设置FD_CLOEXEC标志位
    int flags;
    flags = fcntl(fd, __F_SETSIG, FD_CLOEXEC);
    if (-1 == flags)
    {
        perror("fcntl");
        exit(1);
    }
    printf("set FD_CLOEXEC sig\n");
}

// 文件状态描述符获取
void getFd(int fd)
{
    // 获取文件描述状态符
    int flags;
    flags = fcntl(fd, F_GETFD, 0);
    if (flags == -1)
    {
        perror("fcntl");
        exit(1);
    }
    if (flags & FD_CLOEXEC)
    {
        printf("FD_CLOEXEC is set\n");
    }
    else
    {
        printf("FD_CLOEXEC is not set\n");
    }
}

// 文件状态描述符设置
void setFd(int fd, int op)
{
    int flags;
    flags = fcntl(fd, F_SETFD, op == 0 ? 0 : FD_CLOEXEC);
    if (flags == -1)
    {
        perror("fcntl");
        exit(1);
    }
    if (op == 0)
    {
        printf("unset FD_CLOEXEC FD\n");
    }

    printf("set FD_CLOEXEC FD\n");
}

// 获取文件描述符标志
void getFL(int fd)
{
    int flags;
    flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1)
    {
        perror("fcntl");
        exit(1);
    }
    printf("fd flags is ");
    switch (flags & O_ACCMODE)
    {
    case O_RDWR:
        printf("O_RDWR ");
        break;
    case O_WRONLY:
        printf("O_WRONLY ");
        break;
    case O_RDONLY:
        printf("O_RDONLY ");
        break;
    default:
        printf("unknown ");
        break;
    }

    if (flags & O_APPEND)
    {
        printf("O_APPEND");
    }
    if (flags & O_TRUNC)
    {
        printf("O_TRUNC");
    }
    if (flags & O_CREAT)
    {
        printf("O_CREATE");
    }
    if (flags & O_SYNC)
    {
        printf("O_SYNC");
    }
    printf("\n");
}

// 设置文件描述符标志
void setFL(int fd, int op)
{
    int flags;
    flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1)
    {
        perror("fcntl");
        exit(1);
    }
    flags = flags | op;
    flags = fcntl(fd, F_SETFL, flags);
    if (flags == -1)
    {
        perror("fcntl");
        exit(1);
    }
    printf("set flags is %d", op);
    printf("\n");
}

void setOwn(int fd)
{
    int flags;
    flags = fcntl(fd, __F_GETOWN, 0);
    printf("%d\n", flags);
}

void getOwn(int fd)
{
    int flags;
    flags = fcntl(fd, __F_GETOWN, getpid());
}