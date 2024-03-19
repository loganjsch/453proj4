#include "libDisk.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

// Assuming a simple fixed array to manage multiple disks
// In a real application, a dynamic data structure might be more appropriate
#define MAX_DISKS 10
Disk disks[MAX_DISKS];
int diskCount = 0;

int openDisk(char *filename, int nBytes) {
    int fd;

    if (nBytes < 0 || filename == NULL) {
        return -1; // Invalid arguments
    }

    if (nBytes == 0) {
        fd = open(filename, O_RDWR);
    } else {
        // Create a new file or truncate existing one,
        fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
    }

    if (fd < 0) {
        return -1; // Opening or creating the file failed
    }

    // Fill the file with null characters if creating a new file with specified size
    if (nBytes > 0) {
        for (int i = 0; i < nBytes; i++) {
            if (write(fd, "\0", 1) != 1) {
                // Failed to write, close the file and indicate failure
                close(fd);
                return -1;
            }
        }
    }

    return fd;
}


int closeDisk(int disk)
{
    if (disk < 0 || disk >= diskCount)
        return -1; // Invalid disk number
    close(disks[disk].fd);
    disks[disk].fd = -1; // Mark as closed
    return 0;
}

int readBlock(int disk, int bNum, void *block)
{
    if(bNum < 0 || lseek(disk, bNum * BLOCKSIZE, SEEK_SET) < 0) {
        return -1; // Return error if block number is negative or seeking fails
    }

    ssize_t bytesRead = read(disk, block, BLOCKSIZE);
    if (bytesRead < 0) {
        // Read operation failed
        return -1;
    } else if (bytesRead != BLOCKSIZE) {
        return -1; // Partial Read we're calling it an error
    }

    return 0; // Success code = 0

}

int writeBlock(int disk, int bNum, void *block) {

    if(bNum < 0) {
        // Validate block number before attempting to seek
        return -1;
    }

    if(lseek(disk, bNum * BLOCKSIZE, SEEK_SET) < 0) {
        // Error seeking to the correct position, return -1 on failure
        return -1;
    }

    ssize_t bytesWritten = write(disk, block, BLOCKSIZE);
    if (bytesWritten < 0) {
        // Write operation failed
        return -1;
    } else if (bytesWritten != BLOCKSIZE) {
        return -1; // partial write considered an error -1 returned 
    }

    return 0;
}
