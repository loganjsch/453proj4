# include "libDisk.c"
#include "libTinyFS.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Global Variables */
int mounted_disk_fd = -1; // File descriptor for the mounted disk. -1 indicates no disk is mounted.

int tfs_mkfs(char *filename, int nBytes){
    /* make TinyFS file system of size nBytes on the unix file specific by filename */

    /* initialize all data to 0x00 */

    /* set magi cnumbers */

    /* initialize and writeL superblock, inodes */

    int diskNum;
    
    // Create or overwrite a disk file with the specified size
    if ((diskNum = openDisk(filename, nBytes)) < 0) {
        return -1; // Error opening/creating the disk
    }
    
    // Initialize superblock
    super_block sb = {
        .type = 1,
        .magic_number = MAGIC_NUMBER,
        .root_inode = 2, // Assuming the root inode is at block 2
        .free_blocks = 3  // Assuming the list of free blocks starts at block 3
    };
    
    // Write superblock to disk
    if (writeBlock(diskNum, 0, &sb) < 0) {
        return -1; // Error writing superblock
    }
    
    // Further initialization like creating root inode, setting up free block list, etc., would go here

    return 0; // Success
}

/* Function to mount a TinyFS file system */
int tfs_mount(char *filename) {
    // Your implementation here
    return 0;
}

/* Function to unmount the currently mounted TinyFS file system */
int tfs_unmount(void) {
    // Your implementation here
    return 0;
}

/* Function to open a file within the TinyFS file system */
fileDescriptor tfs_openFile(char *name) {
    // Your implementation here
    return 0;
}

/* Function to close an open file */
int tfs_closeFile(fileDescriptor FD) {
    // Your implementation here
    return 0;
}

/* Function to write data to an open file */
int tfs_writeFile(fileDescriptor FD, char *buffer, int size) {
    // Your implementation here
    return 0;
}

/* Function to delete a file from the file system */
int tfs_deleteFile(fileDescriptor FD) {
    // Your implementation here
    return 0;
}

/* Function to read a byte from an open file */
int tfs_readByte(fileDescriptor FD, char *buffer) {
    // Your implementation here
    return 0;
}

/* Function to seek to a specific location in an open file */
int tfs_seek(fileDescriptor FD, int offset) {
    // Your implementation here
    return 0;
}
