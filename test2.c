#include "libDisk.h" // Make sure the name matches your header file name
#include "libDisk.c"
#include <string.h>
#include <stdlib.h>

// Test data for writing and reading from a disk block
const char *testData = "Hello, disk emulator! This is a test string.";

int main() {
    char *filename = "test_disk.img"; // Filename for the disk image
    int diskSize = BLOCKSIZE * 10;    // Create a disk with 10 blocks
    char block[BLOCKSIZE];            // Buffer for reading/writing a block
    memset(block, 0, BLOCKSIZE);      // Initialize the block with zeros

    // Open a disk
    int disk = openDisk(filename, diskSize);
    if (disk < 0) {
        printf("Error opening disk.\n");
        return -1;
    }
    printf("Disk opened successfully. Disk number: %d\n", disk);

    // Prepare a block to write
    strncpy(block, testData, strlen(testData) + 1); // +1 to include the null terminator

    // Write the block to the disk
    if (writeBlock(disk, 0, block) < 0) {
        printf("Error writing to block.\n");
        closeDisk(disk);
        return -1;
    }
    printf("Data written to block successfully.\n");

    // Clear the block buffer before reading
    memset(block, 0, BLOCKSIZE);

    // Read the block from the disk
    if (readBlock(disk, 0, block) < 0) {
        printf("Error reading from block.\n");
        closeDisk(disk);
        return -1;
    }
    printf("Data read from block successfully.\n");

    // Verify the data read matches the data written
    if (strcmp(block, testData) == 0) {
        printf("Data verification successful. Data: \"%s\"\n", block);
    } else {
        printf("Data verification failed.\n");
    }

    // Close the disk
    if (closeDisk(disk) < 0) {
        printf("Error closing disk.\n");
        return -1;
    }
    printf("Disk closed successfully.\n");

    return 0;
}
