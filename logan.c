#include "libDisk.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DISKS 10
Disk disks[MAX_DISKS];
int diskCount = 0;

int openDisk(char *filename, int nBytes) {
    int fd = -1;

    if (nBytes == 0){
        fd = open(filename, O_RDWR);
    }
    else if (nBytes > 0){
        fd = open(filename, (nBytes == 0) ? O_RDWR : (O_RDWR | O_CREAT | O_TRUNC), 0666);
        lseek(fd, nBytes, SEEK_SET);
        write(fd, "\n", 1);
    } else if (nBytes < 0) {
        return -1;
    }

    return fd;
}