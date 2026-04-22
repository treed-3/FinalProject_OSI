/**
 * Contributors:
 * 	Kyle Boynton
 * 	Tyler Reed
 */

// Necessary C libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Kyle implemented
#define TOTAL_BLOCKS 100
#define BLOCK_SIZE 512
#define RESERVED_BLOCKS 10
#define MAX_FILENAME 64


// Kyle implemented
typedef struct {

	char filename[MAX_FILENAME];
	int used;
} FileEntry;

char cmd[1024];


// Simulated disk - Kyle implemented
char disk[TOTAL_BLOCKS][BLOCK_SIZE];

// Free map; 1 = allocated & 0 = free - Kyle implemented
int freeMap[TOTAL_BLOCKS];

// File table: index corresponds to block number - Kyle implemented
FileEntry fileTable[TOTAL_BLOCKS];

// Remove newline from fgets input - Kyle implemented
void trim_newline(char *str) {

	str[strcspn(str, "\n")] = '\0';
}

// Initialize disk & file system - Kyle implemented
void formatDisk() {

	int i;

	for (i = 0; i < TOTAL_BLOCKS; i++) {

		memset(disk[i], 0, BLOCK_SIZE);
		freeMap[i] = 0;
		fileTable[i].used = 0;
		fileTable[i].filename[0] = '\0';
	}

	// Reserve first 10 blocks for free map - Kyle implemented
	for (i = 0; i < RESERVED_BLOCKS; i++) {

		freeMap[i] = 1;
	}

	printf("\nDisk formatted successfully.\n\n");
}

// Find file block by filename - Kyle implemented
int findFileBlock(const char *filename) {

	int i;

	for (i = RESERVED_BLOCKS; i < TOTAL_BLOCKS; i++) {

		if (fileTable[i].used && strcmp(fileTable[i].filename, filename) == 0) {

			return i;
		}
	}

	return -1;
}

// Find first free data block - Kyle implemented
int findFreeBlock() {

	int i;

	for (i = RESERVED_BLOCKS; i < TOTAL_BLOCKS; i++) {

		if (freeMap[i] == 0) {

			return i;
		}
	}

	return -1;
}

// Format System Call - Kyle implemented            
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


// Write System Call - Kyle implemented
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

	printf("Data written to file '%s' .\n", filename);
}

// Read System Call - Kyle implemented
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

	printf("Content of '%s':\n", filename);
	printf("%s\n", disk[block]);
}

// Delete System Call - Kyle implemented
void delFile() {

	char filename[MAX_FILENAME];
	int block;

	printf("Enter filename");
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

// ls System Call - Kyle implemented
void lsFile() {

	int i;
	int found = 0;

	printf("File in root directory:\n");

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

// Menu - Tyler implemented
void printMenu() {

	printf("Welcome to the simple file system simulator.\n\n");

	printf("Available commands:\n\n");

	printf("--> format\n");
	printf("--> create <filename>\n");
	printf("--> read <filename>\n");
	printf("--> write <filename>\n");
	printf("--> del <filename>\n");
	printf("--> ls\n");
	printf("--> exit\n\n");
}




int main() {

char cmd[32];
int choice;


formatDisk();


printMenu();


// Tyler implemented
while(1) {


	printf("Enter system call or exit: ");

	fgets(cmd, sizeof(cmd), stdin);
	
	// Strip newline
	cmd[strcspn(cmd, "\n")] = '\0';



	if (strcmp(cmd, "format") == 0) {

		formatDisk();
	}

	else if (strcmp(cmd, "create") == 0) {

                createFile();
        }

	else if (strcmp(cmd, "read") == 0) {

                readFile();
        }


	else if (strcmp(cmd, "write") == 0) {

                writeFile();
        }


	else if (strcmp(cmd, "del") == 0) {

                delFile();
        }


	else if (strcmp(cmd, "ls") == 0) {

                lsFile();
        }

	else if (strcmp(cmd, "exit") == 0) {

		break;

	}
}

	return 0;
}
