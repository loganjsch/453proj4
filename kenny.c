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
    int fd;
    /* if not multiple then get lowest common multiple */

    /* check if nBytes is < 0 and check filename */
    if ((nBytes < 0) || (filename == NULL))
    {
        return -1;
    }

    /* file already exists */
    if (nBytes == 0){
        if((fd = open(filename, O_RDWR)) < 0){
            return -1;
        }
    }else{
        /* creates a new file with the permission granted by 0666 */
        if ((fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0666)) < 0){
            return -1;
        }

        /* fill empty file with null characters */
        for (int i = 0; i < nBytes; i++){
            if (write(fd, "\0", 1) < 0){
                return -1;
            }
        }
    }
    return fd;
}

int readBlock(int disk, int bNum, void *block) {

    if(lseek(disk, 0, SEEK_SET) < 0 || bNum < 0) {
            return -1;
        }

        lseek(disk, bNum * BLOCKSIZE, SEEK_SET);
        read(disk, block, BLOCKSIZE);

        return 0;
}
