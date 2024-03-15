#include "disk_emulator.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

// Assuming a simple fixed array to manage multiple disks
// In a real application, a dynamic data structure might be more appropriate
#define MAX_DISKS 10
Disk disks[MAX_DISKS];
int diskCount = 0;

int openDisk(char *filename, int nBytes)
{
    if (nBytes != 0 && nBytes < BLOCKSIZE)
        return -1; // Failure for less than BLOCKSIZE

    // Calculate disk size in blocks
    int sizeInBlocks = (nBytes > 0) ? (nBytes / BLOCKSIZE) : 0;
    int actualSize = sizeInBlocks * BLOCKSIZE;

    int fd = open(filename, (nBytes == 0) ? O_RDWR : (O_RDWR | O_CREAT | O_TRUNC), 0666);
    if (fd < 0)
        return -1; // Failure to open file

    if (nBytes > 0 && ftruncate(fd, actualSize) < 0)
    { // Set disk size
        close(fd);
        return -1; // Failure to set size
    }

    // Initialize and store disk information
    if (diskCount >= MAX_DISKS)
    {
        close(fd);
        return -1; // No more disks can be managed
    }
    disks[diskCount].fd = fd;
    disks[diskCount].size = sizeInBlocks;
    return diskCount++; // Return disk number and increment count
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
    if (disk < 0 || disk >= diskCount || disks[disk].fd < 0)
        return -1; // Check if disk is valid and open
    if (bNum < 0 || bNum >= disks[disk].size)
        return -1; // Check if block number is within bounds

    off_t offset = bNum * BLOCKSIZE;
    if (lseek(disks[disk].fd, offset, SEEK_SET) < 0)
        return -1; // Seek to block position

    if (read(disks[disk].fd, block, BLOCKSIZE) != BLOCKSIZE)
        return -1; // Read block
    return 0;
}

int writeBlock(int disk, int bNum, void *block)
{
    if (disk < 0 || disk >= diskCount || disks[disk].fd < 0)
        return -1; // Check if disk is valid and open
    if (bNum < 0 || bNum >= disks[disk].size)
        return -1; // Check if block number is within bounds

    off_t offset = bNum * BLOCKSIZE;
    if (lseek(disks[disk].fd, offset, SEEK_SET) < 0)
        return -1; // Seek to block position

    if (write(disks[disk].fd, block, BLOCKSIZE) != BLOCKSIZE)
        return -1; // Write block
    return 0;
}
