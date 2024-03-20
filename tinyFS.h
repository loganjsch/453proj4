#include <stdint.h>
#ifndef LIB_TINY_FS_H
#define LIB_TINY_FS_H

/* The default size of the disk and file system block */
#define BLOCKSIZE 256
#define MAX_FILENAME_LENGTH 8

/* Your program should use a 10240 Byte disk size giving you 40 blocks total. This is a default size. You must be able to support different possible values */
#define DEFAULT_DISK_SIZE 10240
/* use this name for a default emulated disk file name */
#define DEFAULT_DISK_NAME 'tinyFSDisk'

#define MAGIC_NUMBER 0x44

/* use as a special type to keep track of files */

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

typedef struct inode {
// For TinyFS core only the file’s name and size is required. You must support names up to 8 alphanumeric characters (not including a NULL terminator), and no longer. 
// For example: “file1234”, “file1” or “f”.
// For inode blocks, you must design where and how to store the file metadata. 
// This includes how you index the data blocks (file extents) that correspond to the inode

    uint8_t type;
    uint8_t fileName[8];
    uint8_t fileSize;
    uint8_t dataBlocks[8];
} inode;

typedef struct file_extent {
// A file extent block is a fixed sized block that contains file data and (optionally) a pointer to the next data block. 
// If the file extent is the last (or only) block, the remaining bytes and the pointer should be set to 0x00.
    uint8_t type;
    uint8_t nextBlock;
    uint8_t data[BLOCKSIZE - 2];
} file_extent;

typedef struct super_block {
// 1) It specifies the “magic number,” used for detecting when the disk is not of the correct format. For TinyFS, that number is 0x44, and it is to be found exactly on the second byte of every block. 
// 2) It contains the block number of the root inode (for directory-based file systems). 
// 3) It contains a pointer to the list of free blocks, or some other way to manage free blocks.
    uint8_t type;
    uint8_t magic_number;
    uint8_t root_inode;
    uint8_t *free_blocks;
} super_block;

typedef struct free_block {
    uint8_t type;
    uint8_t magic_number;
    uint8_t block_number;
    struct free_block *next;
} free_block;


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
