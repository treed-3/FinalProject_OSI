/*
 * Simplified File System Simulation
 * Author:
 * Collaborators:
 * Hours spent:
 *
 * Description:
 * This program simulates a tiny file system with 100 disk blocks.
 * Each block holds 512 bytes.
 * Blocks 0-9 are reserved for the free map.
 * Blocks 10-99 can store files.
 *
 * Each file occupies exactly one block.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_BLOCKS 100
#define BLOCK_SIZE 512
#define RESERVED_BLOCKS 10
#define MAX_FILENAME 64

typedef struct {
    char filename[MAX_FILENAME];
    int used;
} FileEntry;

/* Simulated disk */
char disk[TOTAL_BLOCKS][BLOCK_SIZE];

/* Free map: 1 = allocated, 0 = free */
int freeMap[TOTAL_BLOCKS];

/* File table: index corresponds to block number */
FileEntry fileTable[TOTAL_BLOCKS];

/* Remove newline from fgets input */
void trim_newline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

/* Initialize disk and file system */
void formatDisk() {
    int i;

    for (i = 0; i < TOTAL_BLOCKS; i++) {
        memset(disk[i], 0, BLOCK_SIZE);
        freeMap[i] = 0;
        fileTable[i].used = 0;
        fileTable[i].filename[0] = '\0';
    }

    /* Reserve first 10 blocks for free map */
    for (i = 0; i < RESERVED_BLOCKS; i++) {
        freeMap[i] = 1;
    }

    printf("Disk formatted successfully.\n");
}

/* Find file block by filename */
int findFileBlock(const char *filename) {
    int i;
    for (i = RESERVED_BLOCKS; i < TOTAL_BLOCKS; i++) {
        if (fileTable[i].used && strcmp(fileTable[i].filename, filename) == 0) {
            return i;
        }
    }
    return -1;
}

/* Find first free data block */
int findFreeBlock() {
    int i;
    for (i = RESERVED_BLOCKS; i < TOTAL_BLOCKS; i++) {
        if (freeMap[i] == 0) {
            return i;
        }
    }
    return -1;
}

/* Create a file */
void createFile() {
    char filename[MAX_FILENAME];
    int block;

    printf("Enter filename: ");
    fgets(filename, sizeof(filename), stdin);
    trim_newline(filename);

    if (strlen(filename) == 0) {
        printf("Filename cannot be empty.\n");
        return;
    }

    if (findFileBlock(filename) != -1) {
        printf("File already exists.\n");
        return;
    }

    block = findFreeBlock();
    if (block == -1) {
        printf("No free blocks available.\n");
        return;
    }

    freeMap[block] = 1;
    fileTable[block].used = 1;
    strncpy(fileTable[block].filename, filename, MAX_FILENAME - 1);
    fileTable[block].filename[MAX_FILENAME - 1] = '\0';
    memset(disk[block], 0, BLOCK_SIZE);

    printf("File '%s' created at block %d.\n", filename, block);
}

/* Write data to a file */
void writeFile() {
    char filename[MAX_FILENAME];
    char data[BLOCK_SIZE];
    int block;

    printf("Enter filename: ");
    fgets(filename, sizeof(filename), stdin);
    trim_newline(filename);

    block = findFileBlock(filename);
    if (block == -1) {
        printf("File not found.\n");
        return;
    }

    printf("Enter data to write (max %d characters): ", BLOCK_SIZE - 1);
    fgets(data, sizeof(data), stdin);
    trim_newline(data);

    memset(disk[block], 0, BLOCK_SIZE);
    strncpy(disk[block], data, BLOCK_SIZE - 1);

    printf("Data written to file '%s'.\n", filename);
}

/* Read file contents */
void readFile() {
    char filename[MAX_FILENAME];
    int block;

    printf("Enter filename: ");
    fgets(filename, sizeof(filename), stdin);
    trim_newline(filename);

    block = findFileBlock(filename);
    if (block == -1) {
        printf("File not found.\n");
        return;
    }

    printf("Contents of '%s':\n", filename);
    printf("%s\n", disk[block]);
}

/* Delete a file */
void deleteFile() {
    char filename[MAX_FILENAME];
    int block;

    printf("Enter filename: ");
    fgets(filename, sizeof(filename), stdin);
    trim_newline(filename);

    block = findFileBlock(filename);
    if (block == -1) {
        printf("File not found.\n");
        return;
    }

    freeMap[block] = 0;
    fileTable[block].used = 0;
    fileTable[block].filename[0] = '\0';
    memset(disk[block], 0, BLOCK_SIZE);

    printf("File '%s' deleted.\n", filename);
}

/* List all files */
void listFiles() {
    int i;
    int found = 0;

    printf("Files in root directory:\n");
    for (i = RESERVED_BLOCKS; i < TOTAL_BLOCKS; i++) {
        if (fileTable[i].used) {
            printf("Block %d : %s\n", i, fileTable[i].filename);
            found = 1;
        }
    }

    if (!found) {
        printf("No files found.\n");
    }
}

/* Print menu */
void printMenu() {
    printf("\n===== Simple File System =====\n");
    printf("1. Format\n");
    printf("2. Create\n");
    printf("3. Read\n");
    printf("4. Write\n");
    printf("5. Delete\n");
    printf("6. ls\n");
    printf("7. Exit\n");
    printf("Choose an option: ");
}

int main() {
    int choice;
    char input[32];

    /* Start with a formatted disk */
    formatDisk();

    while (1) {
        printMenu();

        fgets(input, sizeof(input), stdin);
        choice = atoi(input);

        switch (choice) {
            case 1:
                formatDisk();
                break;
            case 2:
                createFile();
                break;
            case 3:
                readFile();
                break;
            case 4:
                writeFile();
                break;
            case 5:
                deleteFile();
                break;
            case 6:
                listFiles();
                break;
            case 7:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}
