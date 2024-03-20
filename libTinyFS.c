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
    return 0;
}

/* Function to close an open file */
int tfs_closeFile(fileDescriptor FD) {
    return 0;
}

/* Function to write data to an open file */
int tfs_writeFile(fileDescriptor FD, char *buffer, int size) {
    
}

/* Function to delete a file from the file system */
int tfs_deleteFile(fileDescriptor FD) {
    return 0;
}

/* Function to read a byte from an open file */
int tfs_readByte(fileDescriptor FD, char *buffer) {
    return 0;
}

/* Function to seek to a specific location in an open file */
int tfs_seek(fileDescriptor FD, int offset) {
    return 0;
}
