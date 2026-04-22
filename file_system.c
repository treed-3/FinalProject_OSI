/**
 * Contributors:
 * 	Kyle Boynton
 * 	Tyler Reed
 */

// Necessary C libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TOTAL_BLOCKS 100
#define BLOCK_SIZE 512
#define RESERVED_BLOCKS 10
#define MAX_FILENAME 64


typedef struct {

	char filename[MAX_FILENAME];
	int used;
} FileEntry;



// Simulated disk
char disk[TOTAL_BLOCKS][BLOCK_SIZE];

// Free map; 1 = allocated & 0 = free
int freeMap[TOTAL_BLOCKS];

// File table: index corresponds to block number
FileEntry fileTable[TOTAL_BLOCKS];

// Remove newline from fgets input
void trim_newline(char *str) {

	str[strcspn(str, "\n")] = '\0';
}

// Format System Call
void formatDisk() {

	int i;

	for (i = 0; i < TOTAL_BLOCKS; i++) {

		memset(disk[i], 0, BLOCK_SIZE);
		freeMap[i] = 0;
		fileTable[i].used = 0;
		fileTable[i].filename[0] = '\0';
	}

	// Reserve first 10 blocks for free map
	for (i = 0; i < RESERVED_BLOCKS; i++) {

		freeMap[i] = 1;
	}

	printf("\nDisk formatted successfully. FreeMap blocks 0 - 9 are now allocated.\n\n");
}

// Find file block by filename
int findFileBlock(const char *filename) {

	int i;

	for (i = RESERVED_BLOCKS; i < TOTAL_BLOCKS; i++) {

		if (fileTable[i].used && strcmp(fileTable[i].filename, filename) == 0) {

			return i;
		}
	}

	return -1;
}

// Find first free data block
int findFreeBlock() {

	int i;

	for (i = RESERVED_BLOCKS; i < TOTAL_BLOCKS; i++) {

		if (freeMap[i] == 0) {

			return i;
		}
	}

	return -1;
}

// Create System Call            
void createFile(const char *filename) {
		int block;


		if (findFileBlock(filename) != -1) {

			printf("\nFile already exists.\n");

			return;
		}

		block = findFreeBlock();

		if (block == -1) {

			printf("\nNo free blocks available.\n");

			return;
		}

		freeMap[block] = 1;
			
		fileTable[block].used = 1;

		strncpy(fileTable[block].filename, filename, MAX_FILENAME - 1);

		fileTable[block].filename[MAX_FILENAME - 1] = '\0';

		memset(disk[block], 0, BLOCK_SIZE);

		printf("\n'%s' created at block %d.\n", filename, block);
	}


// Write System Call
void writeFile(const char *filename) {

	int block = findFileBlock(filename);
	char data[BLOCK_SIZE];


	if (block == -1) {

		printf("\nFile not found.\n");

		return;
	}

	printf("\nEnter content to write (max %d bytes): ", BLOCK_SIZE - 257);

	fgets(data, sizeof(data), stdin);

	trim_newline(data);

	memset(disk[block], 0, BLOCK_SIZE);

	strncpy(disk[block], data, BLOCK_SIZE - 1);

	printf("\nContent written to file '%s'.\n", filename);
}

// Read System Call
void readFile(const char *filename) {

	int block = findFileBlock(filename);

	
	if (block == -1) {

		printf("\nFile not found.\n");

		return;
	}

	printf("\nContent of '%s':\n", filename);
	printf("\n%s\n", disk[block]);
}

// Delete System Call
void delFile(const char *filename) {

	int block = findFileBlock(filename);

	
	if (block == -1) {

		printf("\nFile not found.\n");

		return;
	}

	freeMap[block] = 0;

	fileTable[block].used = 0;

	fileTable[block].filename[0] = '\0';

	memset(disk[block], 0, BLOCK_SIZE);

	printf("\n'%s' deleted.\n", filename);
}

// ls System Call
void lsFile() {

	int i;
	int found = 0;

	for (i = RESERVED_BLOCKS; i < TOTAL_BLOCKS; i++) {

		if (fileTable[i].used) {

			printf("\n- %s\n", fileTable[i].filename);

			found = 1;
		}
	}

	if (!found) {

		printf("\nNo files found.\n");
	}
}

// Menu
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

printf("Loading file table from disk.\n\n");
printf("File table loaded successfully.\n\n");

printMenu();

while(1) {


	printf("\nEnter system call or exit: ");

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

			printf("\n'Create' is not recognized.\n");
		} else {

                createFile(arg);
		}
        }

	else if (strcmp(command, "read") == 0) {

		if (strlen(arg) == 0) {
			printf("\n'Read' is not recognized.\n");
		} else {

                readFile(arg);
		}
        }


	else if (strcmp(command, "write") == 0) {

		if (strlen(arg) == 0) {
			printf("\n'Write' is not recognized.\n");
		} else {

                writeFile(arg);
		}
        }


	else if (strcmp(command, "del") == 0) {

		if (strlen(arg) == 0) {
			printf("\n'Delete' is not recognized.\n");
		} else {

                delFile(arg);
		}
        }


	else if (strcmp(command, "ls") == 0) {

                lsFile();
        }

	else if (strcmp(command, "exit") == 0) {

		printf("\nExiting file system simulator.\n\n");
		break;

	}
}

	return 0;
}
