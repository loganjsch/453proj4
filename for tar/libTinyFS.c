#include "libDisk.c"
#include "libTinyFS.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void initBlock(void *block) {
    memset(block, 0, BLOCKSIZE);
}

int tfs_mkfs(char *filename, int nBytes){
    int disk;
    unsigned char block[BLOCKSIZE];
    SuperBlock superBlock;

    /* make TinyFS file system of size nBytes on the unix file specific by filename */
    disk = openDisk(filename, nBytes);
    if (disk < 0) {
        /* return specified error code*/
        return -1;
    }

    /* initialize all data to 0x00 */
    initBlock(&superBlock);
    superBlock.header.blockType = SUPERBLOCK_TYPE;
    superBlock.header.magicNumber = MAGIC_NUMBER;
    superBlock.rootInodeBlock = 1;
    superBlock.freeBlockList = 2;

    /* write super block to disk */
    if (writeBlock(disk, 0, &superBlock) < 0) {
        /* return specified error code */
        closeDisk(disk);
        return -1;
    }

    /* init and write free blocks */
    initBlock(block);
    block[0] = FREE_BLOCK_TYPE;
    block[1] = MAGIC_NUMBER;
    for(int i = superBlock.freeBlockList; i < nBytes / BLOCKSIZE; i++){
        if (writeBlock(disk, i, block) < 0) {
            closeDisk(disk);
            return -1;
        }
    }

    /* successfully create the file system */
    closeDisk(disk);
    return 0;
}

/* Function to mount a TinyFS file system */
int tfs_mount(char *diskname) {
    SuperBlock superBlock;
    unsigned char block[BLOCKSIZE];

    if(mountedDisk != -1){
        return -1;
    }

    /* attempt to open the disk (0 = opening, not create) */
    int disk = openDisk(diskname, 0);
    if (disk < 0){
        return -1;
    }

    /* read the super block */
    if(readBlock(disk, 0, &block) != 0){
        closeDisk(disk);
        return -1;
    }

    /* check if the super block is valid */
    memcpy(&superBlock, block, sizeof(SuperBlock));
    if(superBlock.header.blockType != SUPERBLOCK_TYPE || superBlock.header.magicNumber != MAGIC_NUMBER){
        closeDisk(disk);
        return -1;
    }

    /* file system is verified, set it as mounted */
    mountedDisk = disk;

    return 0;
}

/* Function to unmount the currently mounted TinyFS file system */
int tfs_unmount(void) {
    if(mountedDisk == -1){
        return -1;
    }

    /* attempt to close disk */
    if(closeDisk(mountedDisk) != 0){
        return -1;
    }

    mountedDisk = -1;

    return 0;
}

/* Function to open a file within the TinyFS file system */
fileDescriptor tfs_openFile(char *name) {
    // Searching the inode blocks for an existing file with the specified name.
    // If not found, allocating a new inode block, initializing it with the file's metadata, and updating the free block list accordingly.
    // returning a file descriptor which can be used as an index into a table of the open files 
    return 0;
}

/* Function to close an open file */
int tfs_closeFile(fileDescriptor FD) {
    // validate the file descriptor

    // make the entry in the open file table

    // Flush any cached data or metadata for the file back to the disk if necessary.
    return 0;
}

/* Function to write data to an open file */
int tfs_writeFile(fileDescriptor FD, char *buffer, int size) {
    // Validate the file descriptor.

    // Locate the file's inode using the FD and read its metadata.


    // Allocate as many file extent blocks as needed to hold the new content, updating the inode and free block list accordingly.

    // Write the data from buffer into the allocated blocks.

    // Update the file's size in its inode and write any changes back to the disk.
    return 0;
}

/* Function to delete a file from the file system */
int tfs_deleteFile(fileDescriptor FD) {
    // Validate the file descriptor.

    // Locate and read the file's inode to find all allocated file extent blocks.

    // Mark all blocks used by the file (including the inode block) as free, updating the free block list accordingly.

    // Remove the file from the open file table if it's open.

    return 0;
}

/* Function to read a byte from an open file */
int tfs_readByte(fileDescriptor FD, char *buffer) {
    // Validate the file descriptor and ensure the file pointer is within bounds.

    // Calculate which block contains the byte to be read based on the file pointer.

    // Read the appropriate file extent block and copy the byte into buffer.

    // Increment the file pointer.
    return 0;
}

/* Function to seek to a specific location in an open file */
int tfs_seek(fileDescriptor FD, int offset) {
    // Validate the file descriptor.

    // Ensure the offset is within the bounds of the file's size.

    // Update the file pointer in the open file table to the new location.
    return 0;
}
