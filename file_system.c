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

// Format System Call - Kyle implemented
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

// Create System Call - Kyle implemented            
void createFile(const char *filename) {
		int block;


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
void writeFile(const char *filename) {

	int block = findFileBlock(filename);
	char data[BLOCK_SIZE];


	if (block == -1) {

		printf("File not found.\n");

		return;
	}

	printf("Enter content to write (max %d bytes): ", BLOCK_SIZE - 257);

	fgets(data, sizeof(data), stdin);

	trim_newline(data);

	memset(disk[block], 0, BLOCK_SIZE);

	strncpy(disk[block], data, BLOCK_SIZE - 1);

	printf("Content written to file '%s' .\n", filename);
}

// Read System Call - Kyle implemented
void readFile(const char *filename) {

	int block = findFileBlock(filename);

	
	if (block == -1) {

		printf("File not found.\n");

		return;
	}

	printf("Content of '%s':\n", filename);
	printf("%s\n", disk[block]);
}

// Delete System Call - Kyle implemented
void delFile(const char *filename) {

	int block = findFileBlock(filename);

	
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

	for (i = RESERVED_BLOCKS; i < TOTAL_BLOCKS; i++) {

		if (fileTable[i].used) {

			printf("- %s\n", fileTable[i].filename);

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
char command[32];
char arg[MAX_FILENAME];


formatDisk();


printMenu();


// Tyler implemented
while(1) {


	printf("Enter system call or exit: ");

	fgets(cmd, sizeof(cmd), stdin);
	
	// Strip newline
	cmd[strcspn(cmd, "\n")] = '\0';


	// Split command & argument
	arg[0] = '\0';
	sscanf(cmd, "%31s %63s", command, arg);

	if (strcmp(command, "format") == 0) {

		formatDisk();
	}

	else if (strcmp(command, "create") == 0) {

		if (strlen(arg) == 0) {

			printf("Usage: create <filename>\n");
		} else {

                createFile(arg);
		}
        }

	else if (strcmp(command, "read") == 0) {

		if (strlen(arg) == 0) {
			printf("Usage: read <filename>\n");
		} else {

                readFile(arg);
		}
        }


	else if (strcmp(command, "write") == 0) {

		if (strlen(arg) == 0) {
			printf("Usage: write <filename>\n");
		} else {

                writeFile(arg);
		}
        }


	else if (strcmp(command, "del") == 0) {

		if (strlen(arg) == 0) {
			printf("Usage: delete <filename>\n");
		} else {

                delFile(arg);
		}
        }


	else if (strcmp(command, "ls") == 0) {

                lsFile();
        }

	else if (strcmp(command, "exit") == 0) {

		printf("Exiting file system simulator.\n\n");
		break;

	}
}

	return 0;
}
