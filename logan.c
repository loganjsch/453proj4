#include "libTinyFS.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initializes the file system structures on the disk
int tfs_mkfs(char *filename, int nBytes) {
    FILE* disk = fopen(filename, "wb+");
    if (!disk) {
        return -1; // Error opening file
    }

    // Calculate the number of blocks
    int num_blocks = nBytes / BLOCKSIZE;

    // Initialize disk with zeros
    for (int i = 0; i < num_blocks; i++) {
        uint8_t zero_block[BLOCKSIZE];
        memset(zero_block, 0, BLOCKSIZE);
        fwrite(zero_block, BLOCKSIZE, 1, disk);
    }

    // Initialize and write super block
    super_block sb;
    sb.type = 0x01; // Assuming type 0x01 is for super block
    sb.magic_number = MAGIC_NUMBER;
    sb.root_inode = 2; // Assuming the first inode will be at block 2
    // sb.free_blocks handling depends on your implementation approach

    fseek(disk, 0, SEEK_SET); // Move to the start of the disk
    fwrite(&sb, sizeof(super_block), 1, disk); // Write super block to disk

    // Further initialization like creating a root directory inode,
    // setting up free blocks list, etc., should be done here

    fclose(disk);
    return 0; // Success
}


int mountFS() {
   int diskNum = -1;
   int isFSValid = -1;

   // check for the disk or create one
   if (isDiskExtant(DEFAULT_DISK_NAME) == 1) {
      // open the disk
      if ((diskNum = openDisk(DEFAULT_DISK_NAME, 0)) == -1) {
         return -1;
      }
   }
   else {
      // create the disk and open it
      if ((diskNum = openDisk(DEFAULT_DISK_NAME, DEFAULT_DISK_SIZE)) == -1) {
         return -1;
      }
   }

   // check FS exists
   if ((isFSValid = checkFSValid(diskNum)) == -1) {
      return -1;
   }
   else if (isFSValid == 0) {
      formatFS(diskNum);
   }

   return diskNum;
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
