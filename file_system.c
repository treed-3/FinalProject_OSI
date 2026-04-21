/**
 * Contributors:
 * 	Kyle Boynton
 * 	Tyler Reed
 */

// Necessary C libraries
#include <stdio.h>
#include <string.h>
#include <unistd.h>




int main() {

char cmd[1024];


printf("Welcome to the simple file system simulator.\n\n");

printf("Available commands:\n\n");

printf("--> format\n--> create <filename>\n--> read <filename>\n--> write <filename>\n--> del <filename>\n--> ls\n--> exit\n\n");


while(1) {

	printf("Enter system call: ");
	fflush(stdout);
	// Format System Call
	if (fgets(cmd, sizeof(cmd), stdin) == NULL) {
		break; // End-of-file
	}
	
	// Strip newline
	cmd[strcspn(cmd, "\n")] = '\0';

	// Format System Call
	if (strcmp(cmd, "format") == 0) {
		printf("TODO FORMAT\n");
	}

	// Create System Call
	else if (strcmp(cmd, "create") == 0) {

		printf("TODO CREATE\n");

	}

	// Read System Call
	else if (strcmp(cmd, "read") == 0) {

		printf("TODO READ\n");

	}

	// Write System Call
	else if (strcmp(cmd, "write") == 0) {

		printf("TODO WRITE\n");

	}

	// Delete System Call
	else if (strcmp(cmd, "del") == 0) {

		printf("TODO DELETE\n");

	}

	// ls System Call
	else if (strcmp(cmd, "ls") == 0) {

		printf("TODO LS\n");

	}

	// Exit
	else if (strcmp(cmd, "exit") == 0) {

		printf("Exiting...\n");
		break;
	}
	}

	return 0;
}
