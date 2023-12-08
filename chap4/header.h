#ifndef __HEADER_H__
#define __HEADER_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <termio.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

// struct stat
// {
//     mode_t st_mode;
//     uid_t st_uid;
//     gid_t st_gid;
//     dev_t st_dev;
//     dev_t st_rdev;
//     ino_t st_ino;
//     nlink_t st_nlink;
//     off_t st_size;
//     struct timespec st_atim;
//     struct timespec st_mtim;
//     struct timespec st_ctim;
//     blksize_t st_blksize;
//     blkcnt_t st_blocks;
// };

#endif // __HEADER_H__