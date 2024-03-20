#ifndef DISK_EMULATOR_H
#define DISK_EMULATOR_H

#include <stdio.h>

#define BLOCKSIZE 256 // Size of a disk block in bytes

// Define the disk structure
typedef struct
{
    int fd;   // File descriptor for the disk file
    int size; // Size of the disk in blocks
} Disk;

int openDisk(char *filename, int nBytes);
int closeDisk(int disk);
int readBlock(int disk, int bNum, void *block);
int writeBlock(int disk, int bNum, void *block);

#endif // DISK_EMULATOR_H
