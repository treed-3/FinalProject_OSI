----- PROGRAM OVERVIEW -----

A file system simulator that allows the user to interact with the file system by a means of enacting the commands along with user arguments such as formatting the disk, creating files, writing to those files,
reading the files, listing the files, to then exiting the file system. All relying on what the user types.

----- DIVISION of WORK -----

Kyle implemented:
- C libraries
- definition variables
- typedef struct
- disk
- freeMap
- fileTable
- newline from fgets input
- format system call
- findFileBlock()
- findFreeBlock()
- create system call
- write system call
- read system call
- delete system call

Tyler implemented:
- ls system call
- Menu
- main program
  
----- COLLABORATIVE EXPERIENCE -----

As we programed more code in creating the file system simulator, we knew that there would be potenial errors within the program. Hence, when there was a "git pulling" from the modifications done from the GitHub repository, there would be errors. We then decided to create our own code sections in the GitHub repository and then at the final stage we would merge our collection of code to the one file named'file_system.c'. For both of us the coding aspect was trial and error and to try to make the program function as best we could.
