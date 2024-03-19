#include "libDisk.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DISKS 10
Disk disks[MAX_DISKS];
int diskCount = 0;

int openDisk(char *filename, int nBytes)
{
    if (nBytes != 0 && nBytes < BLOCKSIZE)
        return -1; // Failure for less than BLOCKSIZE

    /* if not multiple then get lowest common multiple */
}