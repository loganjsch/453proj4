#include <stdint.h>
#ifndef LIB_TINY_FS_H
#define LIB_TINY_FS_H

/* The default size of the disk and file system block */
#define BLOCKSIZE 256
/* Your program should use a 10240 Byte disk size giving you 40 blocks total. This is a default size. You must be able to support different possible values */
#define DEFAULT_DISK_SIZE 10240
/* use this name for a default emulated disk file name */
#define DEFAULT_DISK_NAME “tinyFSDisk”

/* use as a special type to keep track of files */
#define MAGIC_NUMBER 0x44
#define SUPERBLOCK_TYPE 1
#define INODE_TYPE 2
#define FILE_EXTENT_TYPE 3
#define FREE_BLOCK_TYPE 4

typedef int fileDescriptor;

typedef struct {
    unsigned char blockType;
    unsigned char magicNumber; // 0x44
    unsigned char nextBlock; // for the linkedLists
} BlockHeader;

typedef struct {
    BlockHeader header;
    unsigned short rootInodeBlock;
    unsigned short freeBlockList;
} SuperBlock;

typedef struct {
    BlockHeader header;
    char fileName[MAX_FILENAME_LENGTH];
    unsigned int fileSize;
    unsigned short firstDataBlock;
} Inode;

typedef struct {
    BlockHeader header;
    unsigned char data[BLOCKSIZE - sizeof(BlockHeader) - sizeof(unsigned short)];
    unsigned short nextDataBlock;
} FileExtent;

typedef struct {
    BlockHeader header;
    unsigned short nextFreeBlock;
} FreeBlock;



int tfs_mkfs(char *filename, int nBytes);
int tfs_mount(char *filename);
int tfs_unmount(void);
fileDescriptor tfs_openFile(char *name);
int tfs_closeFile(fileDescriptor FD);
int tfs_writeFile(fileDescriptor FD, char *buffer, int size);
int tfs_deleteFile(fileDescriptor FD);
int tfs_readByte(fileDescriptor FD, char *buffer);
int tfs_seek(fileDescriptor FD, int offset);

#endif // LIB_TINY_FS_H
